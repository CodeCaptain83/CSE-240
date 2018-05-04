// Your name here
// CSE240
// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of students for a class.
// Each student has the corresponding information: name, gender, class_standing, roll_number, and tuition.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// The following will be accepted as input in the following format: "name:gender:class_standing:roll_number:tuition_fee"
// Example Input: "Tom:M:freshman:10:2000.10" or "Emma:F:junior:15:2700"
// Valid name: String containing alphabetical letters beginning with a capital letter
// Valid gender: Char value 'M' or 'F'
// Valid class_standing: String containing class standing
// Valid roll_number: Positive integer value
// Valid tuition fee: Float containing no more than 2 decimal value, for example: 1500.45 or 2000.7 or 2700
// All inputs will be a valid length and no more than the allowed number of students will be added to the list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable: 4996) // for Visual Studio Only

typedef enum { male = 0, female } gender; // enumeration type gender
										  // linked list of students
struct student {
	char name[30];
	gender genderValue;
	char class_standing[10];
	int roll_number;
	float tuition_fee;
	struct student* next;
} *list = NULL;

// forward declaration of functions
void flush();
void branching(char);
void registration(char);
int add(char*, char*, char*, int, float); // 10 points
void remove_student(); // 10 points
char* search(int); // 5 points
int count(); // 5 points
void swap(struct student *, struct student *); // 5 points
void display();// 15 points

int main()
{
	char ch = 'i';
	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new student to the list\n");
		printf("\ts: search for a student on the list\n");
		printf("\tr: remove a student from the list\n");
		printf("\td: display list of students\n");
		printf("\tq: quit\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	return 0;
}

// consume leftover '\n' characters
void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

// branch to different tasks
void branching(char c)
{
	switch (c)
	{
	case 'a':
	case 's': registration(c); break;
	case 'd': display(); break;
	case 'r': remove_student(); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// The registration function is used to determine how much information is needed and which function to send that information to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void registration(char c)
{
	char input[100];

	if (c == 'a')
	{
		printf("\nPlease enter the student's information in the following format:\n");
		printf("\tname:gender:class_standing:roll_number:tuition_fee\n");

		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* name = strtok(input, ":"); // strtok used to parse string
		char* genderValueString = strtok(NULL, ":");
		char* class_standing = strtok(NULL, ":");
		int roll_number = atoi(strtok(NULL, ":")); // atoi used to convert string to int
		float tuition_fee = atof(strtok(NULL, ":")); // atof used to convert string to float

		int result = add(name, genderValueString, class_standing, roll_number, tuition_fee);

		if (result == 0)
			printf("\nThat student is already on the list\n\n");
		else
			printf("\nStudent added to list successfully\n\n");
	}
	else // c == 's'
	{
		printf("\nPlease enter the student's information in the following format:\n");
		printf("\troll_number\n");
		fgets(input, sizeof(input), stdin);
		int roll_number = atoi(input); // atoi used to convert string to int

		char* result = search(roll_number);

		if (result == NULL) {
			printf("\nThat student is not on the list\n\n");
		}
		else
			printf("\nName & Class standing: %s\n\n", result);

	}
}

// Q1 : add (10 points)
// This function is used to insert a new student into the linked list. You can simply insert the new student to the end of list.
// Do not allow for the same roll number for different students.
// If the roll number already exists on the list, print an error message and return 0. If the student is added to the list, return 1.
//
// NOTE: You must convert the string "genderValueString to an enum type and store it in the list. This will be tested.
// (You must store all of the required information correctly to pass all of the test cases)
// NOTE: You should not allow for the same roll number to be added twice, you will lose points if you do not account for this.
// (That means that students on the list are allowed to have the same name but not the same roll number).

int add(char* name, char* genderValueString, char* class_standing, int roll_number, float tuition_fee)
{
	struct student *new_student = (struct student *)malloc(sizeof(struct student));

	strcpy(new_student->name, name);

	new_student->genderValue = male;
	if (strcmp(genderValueString, "F") == 0)
		new_student->genderValue = female;

	strcpy(new_student->class_standing, class_standing);
	new_student->roll_number = roll_number;
	new_student->tuition_fee = tuition_fee;

	new_student->next = NULL;

	struct student* follow = list;

	if (list == NULL) // inserting into an empty list
	{
		list = new_student; return 1;
	}

	struct student* temp = list;

	while (temp != NULL)
	{
			if (strcmp(new_student->name, temp->name) == 0) // same name, student is already on the list
					if (new_student->roll_number == temp->roll_number)
						return 0;
		follow = temp;
		temp = temp->next;
	}
	follow->next = new_student; // inserting at the end of the list
	return 1;
}
// Q2 : search (5 points)
// This function is used to search for a student on the list by roll_number and returns the name and class_standing of that student
// If the student exists in the list, return a String containing the name and the class_standing of the requested student.
// If the student does not exist on the list, return NULL
// As the output, you should return the char * containing both name and class standing. 
// You can use strcat(s1, s2) to concatenate two strings (arrays of char) with the space between using strcat function. 
char* search(int roll_number)
{
	char * result = malloc(41);
	struct student* temp = list;
	while (temp != NULL)
	{
		if (temp->roll_number == roll_number){
			strcpy(result,temp->name);
			return strcat(strcat(result, " "),temp->class_standing);
		}

		temp = temp->next;
	}
	return NULL;
}
// Q3: count (5 points)
// This function should count the number of students on the linked list and returns the number. The function is used in display function.
int count()
{
	int count = 0;
	struct student* temp = list;
	while (temp != NULL)
	{
		temp = temp->next;
		count = count + 1;
	}
	return count;
}
// Q4: swap (5 points)
// This function should swap the data elements (including name, class standing, ...)
// of two nodes inside the linkedlist. It is used in display function to sort the linked list.
void swap(struct student *x, struct student *y)
{
	char nametmp[30];
	char standingtmp[10];
	gender gendertmp;
	int rolltmp;
	float tuitiontmp;
	strcpy(nametmp, x->name); strcpy(standingtmp,x->class_standing);gendertmp = x->genderValue; rolltmp = x->roll_number;tuitiontmp = x->tuition_fee;
	strcpy(x->name,y->name); strcpy(x->class_standing,y->class_standing);x->genderValue = y->genderValue;x->roll_number = y->roll_number; x->tuition_fee = y->tuition_fee;
	strcpy(y->name ,nametmp);strcpy(y->class_standing ,standingtmp);y->genderValue = gendertmp;y->roll_number = rolltmp;y->tuition_fee = tuitiontmp;
}
// Q5 : display (15 points)
// This function displays the list of students and the information for each one.
// If there are no students in the list, it prints out "There are no students on this list!"
// If there is one student, it should print "There is one student on this list!"
// For more than one student, at first, it should print the number of students stored
// in the list using count function.
// Then, it takes a char input. The printed list must be sorted (using swap function) by name
// if the entered char == 'n' or 'N', and it must be sorted by roll number if char == 'r' or 'R'.
// If other characters are entered, ask for reentering.
// Then, for each student, the name, gender, class standing, roll number, and tuition are printed.
// The exact format can be found at the description of assignment (output screenshot).

void display()
{
	struct student* temp = list;
	struct student* last = NULL;
	int swapped;
	char* genderValue = "Male";

	if (list == NULL)
		printf("\nThere are no students on this list!\n\n");
	else
	{
		if(temp-> next == NULL){
			printf("\nThere is one student on this list!\n\n");
			printf("\nName: %s\n", temp->name);
			if (temp->genderValue == male)
				genderValue = "Male";
			else
				genderValue = "Female";
			printf("Gender: %s\n", genderValue);
			printf("Class Standing: %s\n", temp->class_standing);
			printf("Roll No: %d \n", temp->roll_number);
			printf("Tuition Fee: $ %.2f \n", temp->tuition_fee);
			printf("\n");
		}
		else{
			printf("\nThere are %d students on this list!\n",count());
			char ch;
			do{
				printf("Please enter sorting method N (by name) or R (by roll number)\n");
				ch = tolower(getchar());
				getchar();
				if(ch!='n'  && ch !='r'){
					printf ("Invalid option. Please try again.\n");
				}
			}while (ch!='n'  && ch !='r');
			if (ch=='r'){

				do
				{
					swapped = 0;
					temp = list;

					while (temp->next != last)
					{
						if (temp->roll_number > temp->next->roll_number)
						{
							swap(temp, temp->next);
							swapped = 1;
						}
						temp = temp->next;
					}
					last = temp;
				}
				while (swapped);
			}
			else{
				do
				{
					swapped = 0;
					temp = list;

					while (temp->next != last)
					{
						if (strcmp(temp->name, temp->next->name) > 0)
						{
							swap(temp, temp->next);
							swapped = 1;
						}
						temp = temp->next;
					}
					last = temp;
				}
				while (swapped);

			}
		temp = list;
		while (temp != NULL)
		{
			printf("\nName: %s\n", temp->name);

			if (temp->genderValue == male)
				genderValue = "Male";
			else
				genderValue = "Female";
			printf("Gender: %s\n", genderValue);
			printf("Class Standing: %s\n", temp->class_standing);
			printf("Roll No: %d \n", temp->roll_number);
			printf("Tuition Fee: $ %.2f \n", temp->tuition_fee);
			printf("\n");
			temp = temp->next;
		}
		printf("\n");
		}

	}
}

// Q6 : deletion (10 points)
// This function is used to remove a student from the linked list by roll_number.
// The roll_number must be entered in the function.
// If the student exists in the list, print the student name before returning.
// If the student does not exist on the list, print "The student does not exist before returning.
// You must make sure that no memory leak can occur when removing a linked list node.
void remove_student()
{
	if(count() == 0){
        printf("\nThere are no students on this list! \n \n");
        return;
	}
	struct student* temp = list->next;
	struct student* follow = list;
	int roll_number = 0;
	printf("Please enter the roll number of student to be removed \n");
	scanf("%d",&roll_number);
	flush();

	if (roll_number == list -> roll_number)
	{
		temp = list;
		printf("\nThe name of student with roll number %d is %s\n",roll_number, list->name);
		list = list->next;
		free(temp);
		printf("The student has been removed\n \n");
		return;
	}

	while (temp != NULL)
	{
		if (roll_number == temp -> roll_number)
		{
			printf("\nThe name of student with roll number %d is %s\n",roll_number, temp->name);
			follow->next = temp->next;
			free(temp);
			printf("The student has been removed\n \n");
			return;
		}
		follow = temp;
		temp = temp->next;
	}
	printf("The student does not exist \n \n");
}



