#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)

// Read before you start:
// Do not modify any part of this program that you are given. Doing so may cause you to fail automated test cases.
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully.
// If you modify the function return types or parameters, you will fail the automated test cases.
// You can assume that all inputs are valid. Ex: If prompted for a char, the input will be a char.

// Global Macro Values
#define NUM_STRINGS 4
#define STRING_LENGTH 32

// Forward Declarations
void reverseString(char strings[NUM_STRINGS][STRING_LENGTH]);
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void swapStrings(char[STRING_LENGTH], char[STRING_LENGTH]);
void sortStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
int charCounter(char[STRING_LENGTH],char);
int isAPalindrome(char[STRING_LENGTH]);
void extractAlphabet(char[STRING_LENGTH]);

// Problem 1: reverseString (10 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// In this part you change the string in the reverse order.
// This function can be used by other functions.
void reverseString(char strings[NUM_STRINGS][STRING_LENGTH])
{
    int i,j, l;
	char temp;
	char *p=strings;

   	for(i=0;i<NUM_STRINGS;i++){
		l=strlen(strings[i])-1;
   		for(j=0;j<strlen(strings[i])/2;j++)
   		{
      			temp=*(p+i*(STRING_LENGTH)+j);
      			*(p+i*(STRING_LENGTH)+j)=*(p+i*(STRING_LENGTH)+l);
      			*(p+i*(STRING_LENGTH)+l)=temp;
      			l= l-1;
   		}
	}
}
// Problem 2: encryptStrings (5 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
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
	char *p;
    for (i = 0; i < NUM_STRINGS; i++)
	{
			p=&strings[i];
			while(*p!='\0')
			{
                      *p+=key;
                       p++;
            }
	}
	reverseString(strings);
}
// Problem 3: decryptStrings (5 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// Traverse the 2D array of characters variable 'strings' and decrypt each string using the integer value 'key'.
// Revserse each string and shift each character in each string using the integer value 'key'.
// If the string after reversing is "jgnnq" and key = 2, we will shift those characters backward in ASCII by 2 and the result will be "hello".
// NOTE: DO NOT decrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
// HINT: This should be very similiar to the encryption function defined above in Problem 3.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	int i,j;
	char *p;
    for (i = 0; i < NUM_STRINGS; i++)
	{
		     p=&strings[i];
			while(*p!='\0')
			{
                      *p-=key;
                       p++;
            }
	}
	reverseString(strings);
}

void swapStrings(char string1[STRING_LENGTH], char string2[STRING_LENGTH])
{
	char temp[STRING_LENGTH];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}

// Problem 4: sortStrings (10 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// Sort the 5 strings contained in the 2D character array parameter labeled "strings".
// Sort the strings based on their ASCII character value (use strcmp to compare strings).
// NOTE: You MUST incorporate your "swapStrings" function to recieve full points for this part.
// See the output provided in the word document for example input and output.
void sortStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int min,i,j;

	for (i = 0; i < NUM_STRINGS; i++)
	{
		min = i; // set initial min index

		for (j = i + 1; j < NUM_STRINGS; j++)
		{
			if (strcmp(*(strings + min), *(strings + j)) > 0)
			{
				min = j; // set new min index
			}
		}

		swapStrings(*(strings + min), *(strings + i)); // swap strings
	}
}

void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i;
    for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("%s\n", strings[i]);
	}
}

// Problem 5: charCounter (5 points)
// This function gets a string (array of characters) and a single character and returns the number of times the character has been used in the string.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
int charCounter(char string[STRING_LENGTH],char input)
{
	int count = 0;
	char *p = string;
	while (*p != '\0')
	{
		if (*p == input)
			count++;
		p++;
	}
	return count;
}

// Problem 6: isAPalindrome (10 points)
// This function accepts an array of characters and returns an integer.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// This function should return 1 (true) if the parameter 'string' is a palindrome, or 0 (false) if 'string' is not a palindrome.
// A palindrome is a sequence of characters which when reversed, is the same sequence of characters.
// For this assignment, you can assume that 'string' will be a single word containing only lowercase letters and no spaces.
// Example Palindromes: mom, racecar, stats, rotator, deleveled
int isAPalindrome(char string[STRING_LENGTH])
{
	int result = 1,i;
    char *p = string;

	for (i = 0; i < strlen(string) / 2; i++)
	{
        char head = *(p + i);
		char tail = *(p + strlen(string) - i - 1);

		if (head != tail)
			result = 0;
	}

	return result;
}

// Problem 7: extractAlphabet (5 points)
// This function accepts an array of characters and removes all the characters that are not alphabets.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// Example: If the input string is "hi4g5h67", then the modified string is "high"
void extractAlphabet(char string[STRING_LENGTH])
{
	int i,j;
	char *p=string;
    for(i=0; *(p+i)!='\0'; i++)
    {
        while (!((*(p+i)>='a'&&*(p+i)<='z') || (*(p+i)>='A'&&*(p+i)<='Z' || *(p+i)=='\0')))
        {
            for(j=i;*(p+j)!='\0';j++)
            {
                *(p+j)=*(p+j+1);
            }
            *(p+j)='\0';
        }
    }
}

// You should study and understand how this main function works.
// Do not modify it in any way, there is no implementation needed here.
void main()
{
	int selection;
	char input[STRING_LENGTH];

	printf("Assignment 4: Pointer Operations\n\n");
	printf("Choose one of the following: \n1. Sorting Encrypted Strings\n2. Character Counter\n3. Palindrome\n4. Alphabet Extraction\n\n");
	scanf("%d", &selection); // store integer
	getchar(); // consume newline char

	if (selection == 1)
	{
		char strings[NUM_STRINGS][STRING_LENGTH]; // will store 4 strings each with a max length of 32
		int key,i;

		for (i = 0; i < NUM_STRINGS; i++)
		{
			printf("\nEnter the next String: "); // prompt for string
			fgets(input, sizeof(input), stdin); // store input string
			input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
			strcpy(strings[i], input); // copy input to 2D strings array
		}

		printf("\nEnter a key value for encryption: "); // prompt for integer
		scanf("%d", &key); // store integer
    	encryptStrings(strings, key);
        printf("\nEncrypted Strings:\n");
        printStrings(strings);
        decryptStrings(strings, key);
        sortStrings(strings);

        printf("\nSorted Strings after decryption:\n");
        printStrings(strings);

	}
	else if (selection == 2)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
		char inputchar;
		printf("\nEnter a letter to be check: "); // prompt for char
		scanf(" %c", &inputchar); // store input char
		int numVowels = charCounter(input,inputchar);

		printf("\nThere are %d number of %c in \"%s\"", numVowels, inputchar, input);
	}
	else if (selection == 3)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)

		int isPalindrome = isAPalindrome(input);

		if (isPalindrome)
			printf("\nThe string \"%s\" is a palindrome", input);
		else
			printf("\nThe string \"%s\" is not a palindrome", input);
	}
	else if (selection == 4)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
		extractAlphabet(input);

		printf("\nResult of removing characters is: %s", input);
	}
	else
	{
		printf("Program terminating...");
	}
	selection = getchar();
	getchar();

}
