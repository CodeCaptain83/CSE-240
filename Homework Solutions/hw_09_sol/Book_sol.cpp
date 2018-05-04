#include "Book.h"
#include <string>
#include <iostream>


// Q1 : CLASS METHODS Part 1 : Constructor and Accessor Methods for Book (5 points)

// Constructor
// Create a constructor for the class Book which takes 2 string parameters and one float parameter.
// Use the parameters to initialize the three private local variables title, author, and price.
// HINT: Don't forget to initialize your linked list of buys to NULL.

Book::Book(string book_title, string book_author,float book_price) 
{
	title = book_title;
	author = book_author;
	price = book_price;
	buys = NULL;
}

// Accessor and Set Methods
// Create accessor and set methods for private local strings title and author and also float price.

string Book::getTitle() 
{
	return title;
}

string Book::getAuthor() 
{
	return author;
}

float Book::getPrice()
{
	return price;
}

void Book::setTitle(string title_name)
{
	title = title_name;
}

void Book::setAuthor(string author_name)
{
	author = author_name;
}

void Book::setPrice(float price_set)
{
	price = price_set;
}


// Q2 : CLASS METHODS Part 2 : Class Methods for Book (10 points)

// Create a method called "toString"
// This method has no input parameters and returns the string containing the title, author, and price of a book.
// This function is used in print_all function inside main to print the information of a book.
// The exact format can be found in the sample output of assignment description. 
string Book::toString()
{
	string res = "Title: " + title + '\n' + "Author: " + author + '\n' + "Price: " + to_string(price) + '\n';
	return res;

}
// Create a method named "buyBook" which has one string parameter date and no return type (see helper function for use).
// This method is used to add a new date to the book's linked list of buys. The string parameter is the date of buying.
// You should add the date to the tail of the linked list "buys". Buys will be added in chronological order.

void Book::buyBook(string date) 
{
	if (buys == NULL) // no previous buy
		buys = new Buy(date);

	Buy* buy_traverser = buys;

	// traverse non-empty list of buys
	while (buy_traverser->next != NULL)
		buy_traverser = buy_traverser->next;

	// add to the tail of list of buys
	buy_traverser->next = new Buy(date);
}

// Create a method named "timesBought"
// This method has no input parameters and returns the number of times the book has been bought.
// This function is used in print_all function inside the main function. 
int Book::timesBought() {

	int res = 0;
	Buy* buy_traverser = buys;

	// empty list of buys
	if (buy_traverser == NULL)
		return res;

	// traverse to tail of buys
	while (buy_traverser->next != NULL) {
		buy_traverser = buy_traverser->next;
		res++;
	}
	return res;
}

// Create a method named "displayBought" which has no parameters and returns a string (see print_all function for use).
// This method will be used to return a string for the dates where the book has been bought.
// If the book was not bought, return an empty string.

string Book::displayBought() 
{
	string res;
	Buy* buy_traverser = buys;
	if (buy_traverser == NULL)
		return NULL;
	
	// traverse to tail of buys
	while (buy_traverser->next != NULL)
	{
		buy_traverser = buy_traverser->next;
		res += buy_traverser->getDate() + '\n';
	
	}
	return res;
}


