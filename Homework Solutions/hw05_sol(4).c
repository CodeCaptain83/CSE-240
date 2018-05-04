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

struct student {
	char name[30];
	gender genderValue;
	char class_standing[10];
	int roll_number;
	float tuition_fee;
};

int count = 0; // the number of students currently stored in the list (initialized at 0)

struct student list[30]; // initialize list of students

// forward declaration of functions
void flush();
void branching(char);
void registration(char);
int add(char*, char*, char*, int, float, struct student*); // 20 points
char* search(char*, int, struct student*); // 10 points
void display();// 10 points
void save(char* fileName);
void load(char* fileName); // 10 points

int main()
{
	load("Sudent_List.txt"); // load list of students from file (if it exists)
	char ch = 'i';
	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new student to the list\n");
		printf("\ts: search for a student on the list\n");
		printf("\td: display list of students\n");
		printf("\tq: quit\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	save("Student_List.txt"); // save list of students to file (overwrite if it exists)
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

		int result = add(name, genderValueString, class_standing, roll_number, tuition_fee, list);

		if (result == 0)
			printf("\nThat student is already on the list\n\n");
		else
			printf("\nStudent added to list successfully\n\n");
	}
	else // c = 's'
	{
		printf("\nPlease enter the student's information in the following format:\n");
		printf("\tname:roll_number\n");
		fgets(input, sizeof(input), stdin);

		char* name = strtok(input, ":"); // strtok used to parse string
		int roll_number = atoi(strtok(NULL, ":")); // atoi used to convert string to int

		char* result = search(name, roll_number, list);

		if (result == NULL)
			printf("\nThat student is not on the list\n\n");
		else
			printf("\nClass standing: %s\n\n", result);
	}
}

// Q1 : add (10 points)
// This function is used to insert a new student into the list. You can simply insert the new student to the end of list (array).
// Do not allow for the same student to be added to the list multiple times: the same roll number is NOT allowed.
// If the roll number already exists on the list, return 0. If the student is added to the list, return 1.
//
// NOTE: You must convert the string "genderValueString to an enum type and store it in the list. This will be tested.
// (You must store all of the required information correctly to pass all of the test cases)
// NOTE: You should not allow for the same roll number to be added twice, you will lose points if you do not account for this.
// (That means that students on the list are allowed to have the same name but not the same roll number).
// You are not required to use pointer operations for your list but you may do so if you'd like to. 
// 'list' is passed to this function for automated testing purposes only, it is global.
int add(char* name, char* genderValueString, char* class_standing, int roll_number, float tuition_fee, struct student* list)
{
	int i,j;
    gender genderValue = male;
	if (strcmp(genderValueString, "F") == 0) 
		genderValue = female;

	if (count > 0)
	{
		for (i = 0; i < count; i++)
		{
				if (strcmp(name, list[i].name) == 0) // same name
				{
					if (roll_number == list[i].roll_number) // student is already in list
					{
						return 0;
					}
				}
		}
		// end of list
		strcpy(list[count].name, name);
		list[count].genderValue = genderValue;
		strcpy(list[count].class_standing, class_standing);
		list[count].roll_number = roll_number;
		list[count].tuition_fee = tuition_fee;
		count++;
		return 1;
	}
	else // list is empty
	{
		strcpy(list[count].name, name);
		list[count].genderValue = genderValue;
		strcpy(list[count].class_standing, class_standing);
		list[count].roll_number = roll_number;
		list[count].tuition_fee = tuition_fee;
		count++;
		return 1;
	}
}

// Q2 : search (10 points)
// This function is used to search for a student on the list and returns the class_standing of that student
// You will need to compare the search keys: name and roll_number, with the stored name and roll_number.
// If the student exists in the list, return a String containing the class_standing of the requested student.
// If the student does not exist on the list, return NULL
char* search(char* name, int roll_number, struct student* list)
{
	int i;
    for (i = 0; i < count; i++)
		if (strcmp(name, list[i].name) == 0 && roll_number == list[i].roll_number)
			return list[i].class_standing;

    return NULL;	
}
// Q3 : display (20 points)
// This function displays the list of students and the information for each one. At the beginning of the function, it takes a char input.
// The printed list must be sorted by name if the entered char == 'n' or 'N', and it must be sorted by roll number if char == 'r' or 'R'. 
// If other characters are entered, ask for reentering.
// At first, it should print out the number of students stored in the list. 
// If there is no student, it prints out "There are no students on this list!". Otherwise, the number of students are printed. Then, for each student, 
// the name, gender, class standing, roll number, and tuition are printed. The exact format can be found at the description of assignment (output screenshot).

void display() // sort can take char n. N, r, or R as input.
{
	
	char* genderValue = "Male";
	if (count == 0)
		printf("\nThere are no students on this list!\n\n");
	if (count ==1){
		printf("\nThere are %d students on this list!\n",count);
		printf("\nName: %s\n", list[0].name);

			if (list[0].genderValue == male)
				genderValue = "Male";
			else if (list[0].genderValue == female)
				genderValue = "Female";

			printf("Gender: %s\n", genderValue);
			printf("Class Standing: %s\n", list[0].class_standing);
			printf("Roll No: %d \n", list[0].roll_number);
			printf("Tuition Fee: $ %.2f \n", list[0].tuition_fee);
			printf("\n");
	}
	if (count > 1) {
		printf("\nThere are %d students on this list!\n",count);
		char ch;
		do{
			printf("Please enter sorting method N (by name) or R (by roll number)\n");
			ch = tolower(getchar());
			getchar();
			if(ch!='n'  && ch !='r'){
				printf ("Invalid option. Please try again.\n");
			}
		}while (ch!='n'  && ch !='r');
		
		int min;
		int i,j;
		struct student tmp;
		if (ch=='r'){
			for (i = 0; i < count; i++){	
				min = i; // set initial min index
				for (j = i + 1; j < count; j++){
					if (list[min].roll_number > list[j].roll_number){
						min = j; // set new min index
					}
				}
				tmp = list[i];
				list[i] = list[min];
				list[min] = tmp;
			}
		}
		if (ch =='n'){
			for (i = 0; i < count; i++){	
				min = i; // set initial min index
				for (j = i + 1; j < count; j++){
					if (strcmp(list[min].name, list[j].name) > 0){
						min = j; // set new min index
					}
				}
				tmp = list[i];
				list[i] = list[min];
				list[min] = tmp;
			}
			
		}
		for (i = 0; i < count; i++)
		{
			printf("\nName: %s\n", list[i].name);

			if (list[i].genderValue == male)
				genderValue = "Male";
			else if (list[i].genderValue == female)
				genderValue = "Female";

			printf("Gender: %s\n", genderValue);
			printf("Class Standing: %s\n", list[i].class_standing);
			printf("Roll No: %d \n", list[i].roll_number);
			printf("Tuition Fee: $ %.2f \n", list[i].tuition_fee);
			printf("\n");
		}
		
	}
	
}

// This function saves the array of structures to file. It is already implemented for you.
// You should understand how this code works so that you know how to use it for future assignments.
void save(char* fileName)
{
	FILE* file;
    int i;
	file = fopen(fileName, "wb");

	fwrite(&count, sizeof(count), 1, file);
	for (i = 0; i < count; i++)
	{
		fwrite(list[i].name, sizeof(list[i].name), 1, file);
		fwrite(list[i].class_standing, sizeof(list[i].class_standing), 1, file);
		fwrite(&list[i].genderValue, sizeof(list[i].genderValue), 1, file);
		fwrite(&list[i].roll_number, sizeof(list[i].roll_number), 1, file);
		fwrite(&list[i].tuition_fee, sizeof(list[i].tuition_fee), 1, file);
	}
	fclose(file);
}

// Q4:  Load file (10 points)
// This function loads data from file and build the the array of structures. 
// Use the save function given above as an example on how to write this function.
void load(char* fileName)
{
    int i;
    FILE* file;

	file = fopen(fileName, "rb");

	if (file == NULL) // no file to load
		return;
	else
	{
		fread(&count, sizeof(count), 1, file);
		for (i = 0; i < count; i++)
		{
			fread(list[i].name, sizeof(list[i].name), 1, file);
			fread(list[i].class_standing, sizeof(list[i].class_standing), 1, file);
			fread(&list[i].genderValue, sizeof(list[i].genderValue), 1, file);
			fread(&list[i].roll_number, sizeof(list[i].roll_number), 1, file);
			fread(&list[i].tuition_fee, sizeof(list[i].tuition_fee), 1, file);
		}
		fclose(file);
	}
}

