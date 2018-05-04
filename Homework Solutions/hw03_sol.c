// Your name here
// State the IDE that you use: Visual Studio or GCC

#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// Do not modify any part of this program that you are given. Doing so may cause you to fail automated test cases.
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// If you modify the function return types or parameters, you will fail the automated test cases.
// You can assume that all inputs are valid. Ex: If prompted for an integer, an integer will be input.

// Global Macro Values. They are used to define the size of a 4 x 32 two-dimensional array of characters
#define NUM_STRINGS 4
#define STRING_LENGTH 32

// Forward Declarations
void initializeStrings(char[NUM_STRINGS][STRING_LENGTH]);
void reverseString(char strings[NUM_STRINGS][STRING_LENGTH]);
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void swapStrings(char[STRING_LENGTH], char[STRING_LENGTH]);
void sortStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
void reversePrint(char[NUM_STRINGS][STRING_LENGTH]);


// Problem 1: initializeStrings (5 points)
// Traverse the 2D array of characters variable 'strings' (in the main program) and set all 32 characters in each of 
// the 4 char arrays to a null terminator so that there is a 4 row and 32 column 2D array full of null terminators.
// The null terminator is represented by the character value '\0' and is used to denote the end of a string.
// This will come in use later in the program when you will need to print the 2D array of characters.
void initializeStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i,j;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		for (j = 0; j < STRING_LENGTH; j++)
		{
			strings[i][j] = '\0';
		}
	}
}

// Problem 2: reverseString (5 points)
//In this part you change the string in the reverse order. 
// This function can be used by other functions.
void reverseString(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i,j, l;
	char temp; 
	
   	for(i=0;i<NUM_STRINGS;i++){
		l=strlen(strings[i])-1;
   		for(j=0;j<strlen(strings[i])/2;j++)
   		{
      			temp=strings[i][j];
      			strings[i][j]=strings[i][l];
      			strings[i][l--]=temp;
   		}
	}	
}

// Problem 3: encryptStrings (5 points)
// Traverse the 2D array of characters variable 'strings' and encrypt each string using the integer value 'key'.
// In order to encrypt the 2D array of characters, we will shift those ASCII characters forward by the integer value of 'key'.
// If the string is "hello" and key = 2, we will shift those characters forward in ASCII by 2 and the result will be "jgnnq".
// The case above is an example of a string that has alphabetical letters in the encrypted and decrypted string.
// Once the value of 'key' gets larger, you will extend past alphabetical characters and reach non-alphabetical characters. 
// After all characters are shifted, you revise the string to complete the encryption. 
// For example, if the string is "xyz123", the reversed string is "321zyx"
// NOTE: DO NOT encrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
void encryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	int i,j;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		for (j = 0; j < strlen(strings[i]); j++)
		{
			strings[i][j] += key;
		}
	}
	reverseString(strings);
	
}
// Problem 4: decryptStrings (5 points)
// Traverse the 2D array of characters variable 'strings' and decrypt each string using the integer value 'key'.
// Revserse each string and shift each character in each string using the integer value 'key'.
// If the string after reversing is "jgnnq" and key = 2, we will shift those characters backward in ASCII by 2 and the result will be "hello".
// NOTE: DO NOT decrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
// HINT: This should be very similiar to the encryption function defined above in Problem 3.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	int i,j;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		for (j = 0; j < strlen(strings[i]); j++)
		{
			strings[i][j] -= key;
		}
	}
	reverseString(strings);

}

// Problem 5: swapStrings (5 points)
// Swap the strings that are passed as parameters, this function will be used in Problem 6.
// If string1 is "hello" and string2 is "goodbye", after calling this function, string1 will be "goodbye" and string2 will be "hello".
void swapStrings(char string1[STRING_LENGTH], char string2[STRING_LENGTH])
{
	char temp[STRING_LENGTH];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}
// Problem 5 Alternative solution:
// The following solution is also correct:
void swapStringsAlt(char *string1, char *string2)
{
	char temp[STRING_LENGTH];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}

// Problem 6: sortStrings (15 points)
// Sort the four strings contained in the 2D character array parameter labeled "strings".
// Sort the strings based on their ASCII character value.
// NOTE: You MUST incorporate your "swapStrings" function to recieve full points for this part.
// See the output provided in the word document for example input and output.
void sortStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int min;
	int i,j;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		min = i; // set initial min index

		for (j = i + 1; j < NUM_STRINGS; j++)
		{
			if (strcmp(strings[min], strings[j]) > 0)
			{
				min = j; // set new min index
			}
		}

		swapStrings(strings[min], strings[i]); // swap strings
	}
}
// Problem 7: printStrings (5 points)
// Traverse the 2D character array "strings" and print each of the contained strings.
// See the example outputs provided in the word document. Your output should match the example outputs.
void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("%s\n", strings[i]);
	}
}

// Problem 8: reversePrint (5 points)
// You should print the reverse of strings using the functions that you have.
// See the example outputs provided in the word document. Your output should match the example outputs.

void reversePrint(char strings[NUM_STRINGS][STRING_LENGTH]){
	reverseString(strings);
	printStrings (strings);
	
}

// You should study and understand how this main function works.
// Do not modify it in any way, there is no implementation needed here.
void main()
{
	char strings[NUM_STRINGS][STRING_LENGTH]; // will store four strings each with a max length of 32
	int i, key;
	char input[STRING_LENGTH];
	initializeStrings(strings);

	printf("Assignment 3: 2D Character Arrays\n\n");

	for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("Enter the next String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
		strcpy(strings[i], input); // copy input to 2D strings array
	}

	printf("Enter a key value for encryption: "); // prompt for integer
	scanf("%d", &key); // store integer

	encryptStrings(strings, key);
	printf("\nEncrypted Strings:\n");
	printStrings(strings);
	decryptStrings(strings, key);
	sortStrings(strings);
	
	printf("\nSorted Strings after decryption:\n");
	printStrings(strings);
	printf("\nStrings after reversing:\n");
	reversePrint(strings);
	
	i = getchar(); // remove the character '\n'
	i = getchar(); // keep console open
}