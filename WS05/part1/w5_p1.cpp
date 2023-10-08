/* ****************************************************************************
	OOP345 NFF WS05   | PROF. HONG HUANG   |

	KA YING, CHAN     | #123231227         | kchan151@myseneca.ca

	I have done all the coding by myself and only copied the code
	that my professor provided to complete my workshops and assignments.

	Completed on 2023 OCT 8
**************************************************************************** */
// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h"
#include "Book.h" // intentional

#include <string>

// Checking if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";


	// get the books
	sdds::Book library[7];
	size_t bkCnt = 0;

	if (argc == 2) {
		// TODO: load the collection of books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the array "library"
		//       - lines that start with "#" are considered comments and should be ignored
		//       - if the file cannot be open, print a message to standard error console and
		//                exit from application with error code "AppErrors::CannotOpenFile"

		// logic follows WS04 main:
		std::ifstream file(argv[1]);
		if (!file) {
			std::cerr << "AppErrors::CannotOpenFile\n";
			exit(AppErrors::CannotOpenFile);
		}
		std::string line;
		do {
			std::getline(file, line);
			if (file) { // if the previous operation failed, the "file" object is in error mode
				if (line[0] != '#') {
					library[bkCnt] = sdds::Book(line);
					bkCnt++;
				}
				//std::cout << line << std::endl; // check
				//std::cout << bkCnt << std::endl; // check
			}
		} while (file);
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// TODO: create a lambda expression that fixes the price of a book accoding to the rules
	//       - the expression should receive a single parameter of type "Book&"
	//       - if the book was published in US, multiply the price with "usdToCadRate"
	//            and save the new price in the book object
	//       - if the book was published in UK between 1990 and 1999 (inclussive),
	//            multiply the price with "gbpToCadRate" and save the new price in the book object


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
	for (auto i = 0u; i < bkCnt; i++) {
		std::cout << library[i];
	}


	std::cout << "-----------------------------------------\n\n";

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
		// TODO: iterate over the library and update the price of each book
	//         using the lambda defined above.
	if (bkCnt != 0) {
		for (auto i = 0u; i < bkCnt; i++) {
			if (library[i].country() == "US") {
				library[i].price(usdToCadRate);
			}
			else if (library[i].country() == "UK" && (library[i].year() >= 1990 && library[i].year() <= 1999)) {
				library[i].price(gbpToCadRate);
			}
			std::cout << library[i];
		}
		//display("Prompt1", [](type) { cout << "Hello from lambda1" << endl; });
	}



	std::cout << "-----------------------------------------\n";

	return cout;
}
