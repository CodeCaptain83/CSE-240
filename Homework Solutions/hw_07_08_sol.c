// CSE 240
// READ BEFORE YOU START:
// Please read the given Word document for the project description with an illustrartive diagram.
// You are given a partially completed program that creates a list of books.
// Each book has the corresponding information: title, author, price and a linked list of frequently bought books.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, return types, or parameters, you risk failing test cases.

// The following will be accepted as input in the following format: "title:author:price"
// Example Input:	"ProgrammingLanguages:Chen:45"
// Valid title:		String containing alphabetical letters beginning with a capital letter
// Valid author:	String containing alphabetical letters beginning with a capital letter
// Valid price:		A float variable

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable: 4996)

// used to create a linked list of containers, each contaning a "book"
struct container {
	struct book *book;
	struct container *next;
} *list = NULL;

// used to hold book information and linked list of "frequently bought together (fbt)"
struct book {
	char title[30];
	char author[30];
	float price;
	struct fbt *fbts;
};

// used to create a linked list of frequently bought together (fbt)
struct fbt {
	struct book *book;
	struct fbt *next;
};


// forward declaration of functions that have already been implemented
void flush();
void branching(char);
void registration(char);


// the following forward declarations are for functions that require implementation
// HW07
// Total: 50 points for hw07
// return type		// name and parameters				// points
void				add_book(char*, char*,float);		//  15
struct book*		search_book(char*);					//  10
void				remove_book(char*);					//  15
void	            print_all_books();					//	10

// HW08
//	Total: 50 points for hw08
struct container *	buy_book();							// 15
struct container *  setfbt(struct container *);			// 25
void 				display_fbt(struct container*);		// 10	

int main()
{
	char ch = 'i';
	printf("Book Information\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new book to the list\n");
		printf("\ts: search for a book on the list\n");
		printf("\tr: remove a book from the list\n");
		printf("\tl: print the list of all books\n");
		printf("\tb: buy a book\n");
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
	case 's':
	case 'r':
	case 'l':registration(c); break;
	case 'b':{
	    struct container * buy = buy_book();
	    buy = setfbt(buy);
	    display_fbt(buy);
	    break;
	}
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}
//
// This function will determine what info is needed and which function to send that info to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should trace the code and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void registration(char c)
{
	if (c == 'a')
	{
		char input[100];

		printf("\nPlease enter the book's info in the following format:\n");
		printf("title:author:price\n");
		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* title = strtok(input, ":"); // strtok used to parse string
		char * author = strtok(NULL, ":");
		float price = atof(strtok(NULL, ":"));

		struct book* result = search_book(title);

		if (result == NULL)
		{
			add_book(title, author, price);
			printf("\nBook added to list successfully\n\n");
		}
		else
			printf("\nThat book is already on the list\n\n");
	}
	else if (c == 's' || c == 'r' )
	{
		char title[30];

		printf("\nPlease enter the book's title:\n");
		fgets(title, sizeof(title), stdin);

		// discard '\n' chars attached to input
		title[strlen(title) - 1] = '\0';

		struct book* result = search_book(title);

		if (result == NULL)
			printf("\nThat book is not on the list\n\n");
		else if (c == 's'){
			printf("\nTitle: %s\n", result->title);
			printf("Author: %s\n", result->author);
			printf("Price: %.2f\n\n", result->price);
		}
		else
		{
			remove_book(title);
			printf("\nBook removed from the list\n\n");
		}
	}
	else 
	{
		print_all_books();
	}
}

// hw07 Q1 : add (15 points)
// This function should add book to the head of the list of containers.
// The function search_book() is called before calling this function,
// therefore you can assume that the book is not already on the list.
void add_book(char* title, char* author, float price)
{
	struct book *new_book = (struct book *)malloc(sizeof(struct book));
	strcpy(new_book->title, title);
	strcpy(new_book->author, author);
	new_book->price = price;
	new_book->fbts = NULL;

	struct container *new_container = (struct container *)malloc(sizeof(struct container));
	new_container->book = new_book;
	new_container->next = NULL;

	new_container->next = list;
	list = new_container;
}

// hw07 Q2 : search (10 points)
// In this function, you are passed the title of a book to find.
// If the book exists on the list, return a pointer to the requested book. If not, return NULL.
// (You must return a pointer to a node in your list.)

struct book* search_book(char* title)
{
	struct container* container_traverser = list;
	while (container_traverser != NULL)
	{
		if (strcmp(container_traverser->book->title, title) == 0)
			return container_traverser->book;
		container_traverser = container_traverser->next;
	}
	return NULL;
}


// hw07 Q3: remove_one (15)
// In this function, you are passed the title of a book to remove the corresponding book from the list.
// The search function is called before this function so you can assume that the book is on the list.
// You will need to find the book and remove it using proper memory management to ensure no memory leaks.
void remove_book(char* title)
{
	struct container* container_follower = list;
	struct fbt* ptr;

	// remove from head of list
	if (strcmp(title, list->book->title) == 0)
	{
		list = list->next;

		// traverse and remove all absents
		while (container_follower->book->fbts != NULL)
		{
			ptr = container_follower->book->fbts;
			container_follower->book->fbts = container_follower->book->fbts->next;
			free(ptr);
		}
		free(container_follower->book);
		free(container_follower);
		return;
	}

	struct container* container_traverser = list->next;

	// remove from anywhere else in list
	while (container_traverser != NULL)
	{
		// find book
		if (strcmp(title, container_traverser->book->title) == 0)
		{
			container_follower->next = container_traverser->next;

			// traverse and remove all absents
			while (container_traverser->book->fbts != NULL)
			{
				ptr = container_traverser->book->fbts;
				container_traverser->book->fbts = container_traverser->book->fbts->next;
				free(ptr);
			}
			free(container_traverser->book);
			free(container_traverser);
			return;
		}
		container_follower = container_traverser;
		container_traverser = container_traverser->next;
	}
}
// hw07 Q4: print_all_books (10)
// In this function, you should print the list of available books in the list. 
//If there is no book in the list, you should print "There are no books on this list!"

void print_all_books()
{
    struct container* container_traverser = list;
	if(container_traverser==NULL){
		printf("\nThere are no books on this list!\n\n");
		return;
	}
	printf("\nThe list of books is as follows:\n");
	while (container_traverser != NULL)
	{
        printf("\nTitle: %s\n", container_traverser->book->title);
        printf("Author: %s\n", container_traverser->book->author);
        printf("Price: %.2f\n", container_traverser->book->price);    
		container_traverser = container_traverser->next;
	}
	printf("\n");
}
// hw08 Q1: buy_book (15)
// In this function, you should return the linked list of books that the user wants to buy. 
// The user should be able to buy as many books as he/she wants until 'n' is pressed.
// The user can buy a book using its title.
// The book that the user is going to buy should be on the main linked list. 

struct container * buy_book(){
    char ch;
    char title[30];
    struct container *res = NULL;
    printf("Do you want to buy a book? y for YES and n for NO:");
    ch = tolower(getchar());
    flush();
    while (ch != 'n'){
		printf("\nPlease enter the book's title:\n");
		fgets(title, sizeof(title), stdin);
		// discard '\n' chars attached to input
		title[strlen(title) - 1] = '\0';

		struct book* new_book = search_book(title);

		if (new_book == NULL)
			printf("\nThere are no books with this title on the list\n\n");
		else {

                struct container *new_container = (struct container *)malloc(sizeof(struct container));
                new_container->book = new_book;
                new_container->next = NULL;
                new_container->next = res;
                res = new_container;
		}
		printf("Do you want to buy a book? y for YES and n for NO:");
        ch = tolower(getchar());
        flush();
    }
    printf("Thanks for your shopping\n\n");	
    return res;

}
// hw08 Q2: setfbt (25)
// When a user buys a book, the frequently bought togther(fbt) linked list should be updated for each book.
// The update in fbt list should be done for each book in the buying list. 
// For simplicity, you do not consider the number of times the books are bought. 

struct container *  setfbt (struct container * in){
    struct container* containeri = in;
    struct container* containerj = in;
    struct fbt* fbt_to_add;

	//
    while(containeri!=NULL){
        //fbt_to_add->next = NULL;
        containerj = in;
        while(containerj!=NULL){
            if(containeri->book!=containerj->book){

                if(containeri->book->fbts == NULL){
                    fbt_to_add = (struct fbt *)malloc(sizeof(struct fbt));
					fbt_to_add->book = containerj->book;
                    fbt_to_add->next = NULL;
                    containeri->book->fbts = fbt_to_add;

                }
                else{
					fbt_to_add = (struct fbt *)malloc(sizeof(struct fbt));
                    fbt_to_add->book = containerj->book;
                    fbt_to_add->next = NULL;
                    struct fbt* fbt_traverser;
                    fbt_traverser = containeri->book->fbts;
                    while (fbt_traverser->next != NULL)
                        fbt_traverser = fbt_traverser->next;
                    fbt_traverser->next = fbt_to_add;
                }
            }
            containerj = containerj->next;

        }
        containeri = containeri->next;
    }
	
    return in;

}
// hw08 Q3: display_fbt (10)
// This function prints the list of books for a given container.
// It should both print the details of each book and the fbt for that book.  
// This function is used to print the book list in the buy option. 
void display_fbt(struct container* books)
{
	struct container* container_traverser = books;

	if (container_traverser == NULL)
	{
		printf("\nThere are no books on this list!\n\n");
		return;
	}

	while (container_traverser != NULL) // traverse list of books
	{
		printf("\nTitle: %s\n", container_traverser->book->title);
		printf("Author: %s\n", container_traverser->book->author);
		printf("Price: %.2f\n", container_traverser->book->price);
		while(container_traverser->book->fbts!=NULL){
            printf("Frequently Bought Together Book: \n");
            printf("Title: %s\n", container_traverser->book->fbts->book->title);
            printf("Author: %s\n", container_traverser->book->fbts->book->author);
            printf("Price: %.2f\n", container_traverser->book->fbts->book->price);
            container_traverser->book->fbts = container_traverser->book->fbts->next;
		}
		printf("\n\n"); // formatting
		container_traverser = container_traverser->next;
	}
}
