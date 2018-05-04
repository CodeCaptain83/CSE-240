// CSE 240
// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of books with the dates that they have been bought.
// Each book has the corresponding information: title, author, price, and a linked list of buys.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// You are to assume that all input is valid:
// Valid title:	String containing alphabetical letters beginning with a capital letter
// Valid author: String containing alphabetical letters beginning with a capital letter
// Valid price: A float number
// Valid date:	String in the following format: "MM/DD/YYYY" ex: "01/01/2010"
// All input will be a valid length and no more than the allowed amount of memory will be used
//
// Q1 : CLASS METHODS Part 1 : Constructor and Accessor Methods for Book class in Book.cpp file	(5 points)
// Q2 : CLASS METHODS Part 2 : Class methods for Book class in Book.cpp file					(10 points)
// Q3 : Add Function in hw09.cpp file															(5 points)
// Q4 : Search Function in hw09.cpp file														(5 points)
// Q5 : Change Price Function in hw09.cpp file													(5 points)
// Q6 : Remove Book Function in hw09.cpp file													(10 points)
// Q7 : Print_all function using cin and cout in hw09.cpp file									(10 points)

#include <iostream>
#include <fstream>
#include <string>

#include "Container.h"
#include "Book.h"
#include "Buy.h"

using namespace std;

// forward declarations
void flush();
void branching(char);
void helper(char);
void add_book(string, string, float);
void change_price(Book *);
Book* search_book(string,string);
void remove_book(string,string);
void print_all(Container*);


Container* list = NULL; // global list

int main()
{

	char ch = 'i';

	do {

		cout << "Please enter your selection\n";
		cout << "\ta: add a new book to the list\n";
		cout << "\tc: change the price of a book\n";
		cout << "\tb: buy a book\n";
		cout << "\tr: remove a book from the list\n";
		cout << "\tp: print all books on the list\n";
		cout << "\tq: quit\n";
		cin >> ch;		

		flush();
		branching(ch);
	} while (ch != 'q');

	list = NULL;
	return 0;
}

void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

void branching(char c)
{
	switch (c) {
	case 'a':
	case 'b':
	case 'c':
	case 'r':
	case 'p':
		helper(c);
		break;
	case 'q':
		break;
	default:
		printf("\nInvalid input!\n\n");
	}
}

// The helper function is used to determine how much data is needed and which function to send that data to.
// It uses pointers and values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	string title, author;
	float price;
	if (c == 'p')
		print_all(list);
	else
	{
		cout << endl << "Please enter the books's title: " << endl;
		cin >> title;
		cout << "Please enter the books's author: " << endl;
		cin >> author; 
		cout << "Please enter the price of the book: " << endl;
		cin >> price;
		flush();

		Book* book_result = search_book(title,author);

		if (c == 'a') // add book
		{
			if (book_result == NULL)
			{
				add_book(title, author,price);
				cout << endl << "Book was added." << endl << endl;
			}
			else
				cout << endl << "Book is already on the list." << endl << endl;
		}
		else if (c == 'c')
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}
			change_price(book_result);

			
		}
		else if (c == 'b') // buy book
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}

			string date;
			cout << "Please enter the date of the buying: " << endl;
			cin >> date; flush();

			book_result->buyBook(date);
			cout << endl << "Date of buying is added." << endl << endl;
		}
		else if (c == 'r') // remove book
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}

			remove_book(title,author);
			cout << endl << "Book is removed from the list." << endl << endl;
		}
	}
}

// Q3: Add Book (5 points)
// This function will be used to add a new book to the head of you linked list of containers, no need for sorting.
// The search function is called before this function, therefore you can assume the book is not already on the list.
void add_book(string title, string author, float price)
{
	Container* new_container = new Container();
	new_container->book = new Book(title, author,price);
	new_container->next = list;
	list = new_container;
}

// Q4: Search Book (5 points)
// This function will be used to search for a book on the list. 
// You must traverse the list and return a pointer to a 'Book' with the desired title AND author.
// If the book does not exist on the list, return NULL. (See helper function for use of this function).
Book* search_book(string title,string author)
{
	Container *container_traverser = list;
	while (container_traverser != NULL)
	{
		if (container_traverser->book->getTitle() == title && container_traverser->book->getAuthor() == author)
			return container_traverser->book;
		container_traverser = container_traverser->next;
	}
	return NULL;
}
// Q5: Change price (5 points)
// This function will be used to change the price of a book. 
// The function gets a pointer to the book and change the value of price using the set function inside the book class.
void change_price(Book * book) 
{
	float newPrice;
	cout << "Please enter the new price for the book: " << endl;
	cin >> newPrice; flush();
	book->setPrice(newPrice);
	cout << "The price of the book was changed. " << endl;

}

void remove_bought(Container *current_container, Buy *top)
{
	if (top != NULL)
	{
		Buy *buy_to_be_removed = current_container->book->buys;
		current_container->book->buys = current_container->book->buys->next;
		delete buy_to_be_removed;
		remove_bought(current_container, current_container->book->buys->next);
	}

}

// Q6: Remove Book (15 points)
// This function will be used to remove a book from the list. 
// Traverse the list and use the parameters to remove the book. 
// You must remove all the elements in the buys linked list.
void remove_book(string title, string author)
{
	Container *container_traverser = list;

	if (list->book->getTitle() == title && list->book->getAuthor() == author)
	{
		list = list->next;
		remove_bought(container_traverser, container_traverser->book->buys);

		delete container_traverser->book;
		delete container_traverser;
	}
	else
	{
		Container *container_traverser = list->next;
		Container *container_follower = list;
		Container *container_to_be_removed;

		while (container_traverser != NULL)
		{
			if (container_traverser->book->getTitle() == title && container_traverser->book->getAuthor() == author)
			{
				container_to_be_removed = container_traverser;
				container_traverser = container_traverser->next;
				container_follower->next = container_traverser;

				remove_bought(container_traverser, container_traverser->book->buys);

				delete container_to_be_removed->book;
				delete container_to_be_removed;
				return;
			}
			container_follower = container_traverser;
			container_traverser = container_traverser->next;
		}
	}
}

// Question 7. Print_all (10 points for this question)
// Write a recursive function to implement the print_all function. 
// You will not receive any point if you use a while loop. 
// Please use comments to indicate the four steps (1 point each step): 
// (1) size-n problem, (2) stopping condition and return value, 
// (3) size-(n-1) problem, (4) construct the solution of size-n problem
// You should print out the information of a book and also the number of times a book has been bought.
// For each time that a book has been bought, you should print out the date.
// You should use the methods inside the book.cpp file to print. 
void print_all(Container* top)
{
	if (top == NULL) cout << endl << "Done with printing." << endl << endl;
	else
	{
		cout << endl;
		cout << top->book->toString();

		int times_bought = top->book->timesBought();

		if (times_bought == 0)
			cout << "Not Bought " << endl << endl;
		else 
		{
			cout << "Bought " << times_bought << " times " << endl;
			cout << "Dates:" << endl;
			cout << top->book->displayBought() << endl;
		}
		print_all(top->next);

	}
}