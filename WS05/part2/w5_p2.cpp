// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     // intentional
#include "SpellChecker.h"
#include "SpellChecker.h"   // intentional
#include "Book.h"
#include "Book.h"           // intentional
#include "Movie.h"
#include "Movie.h"          // intentional

#include <string>

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
    #error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
    #error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
    #error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors {
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
	const sdds::Book& theBook) {
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection,
	const sdds::Movie& theMovie) {
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv){
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";


	// [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] [BOOKS] //

	size_t bkCnt = 0;

	sdds::Collection<sdds::Book> library("Bestsellers");
	if (argc == 5) {
		std::ifstream fBook(argv[1]);
		if (!fBook) {
			std::cerr << "AppErrors::CannotOpenFile\n";
			exit(AppErrors::CannotOpenFile);
		}
		std::string line;
		do {
			std::getline(fBook, line);
			if (fBook) {
				if (line[0] != '#') {
					sdds::Book newBook(line);
					library += newBook;  // Add the book to the collection
					++bkCnt;
					if (bkCnt == 4) {
						library.setObserver(bookAddedObserver);
					}
				}
			}
		} while (fBook);
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	auto multiplyPrice = [&usdToCadRate, &gbpToCadRate](sdds::Book& bkSrc) {
		if (bkSrc.country() == "US") {
			bkSrc.price() *= usdToCadRate;
		}
		else if (bkSrc.country() == "UK" && bkSrc.year() >= 1990 && bkSrc.year() <= 1999) {
			bkSrc.price() *= gbpToCadRate;
		}
	};

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	if (bkCnt != 0) {
		for (auto i = 0u; i < bkCnt; i++) {
			multiplyPrice(library[i]);
		}
	}
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	// [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] [MOVIES] //

	size_t mvCnt = 0;
	sdds::Collection<sdds::Movie> theCollection("Action Movies"); // library
	// Process the file
	sdds::Movie movies[5];
	if (argc > 2) {
		std::ifstream fMovie(argv[2]);
		if (!fMovie) {
			std::cerr << "AppErrors::CannotOpenFile\n";
			exit(AppErrors::CannotOpenFile);
		}
		std::string line;
		do {
			std::getline(fMovie, line);
			if (fMovie) {
				if (line[0] != '#' && mvCnt < 5) { // 
					sdds::Movie newMovie(line);
					// theCollection += newMovie;  // Add the book to the collection
						movies[mvCnt] = newMovie;
						++mvCnt;
				}
			}
		} while (fMovie);
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::exit(AppErrors::BadArgumentCount);
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing addition and callback function\n";
	std::cout << "-----------------------------------------\n";
	if (argc > 2) {
		// Add a few movies to collection; no observer is set
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		// add more movies; now we get a callback from the collection
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
	}
	else {
		std::cout << "** No movies in the Collection\n";
	}
	std::cout << "-----------------------------------------\n\n";
	
	
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing exceptions and operator[]\n";
	std::cout << "-----------------------------------------\n";
		// TODO: The following loop can generate generate an exception
		//         write code to handle the exception
		//       If an exception occurs print a message in the following format
		//** EXCEPTION: ERROR_MESSAGE<endl>
		//         where ERROR_MESSAGE is extracted from the exception object.

	try{
		for (auto i = 0u; i < 10; ++i)
			std::cout << theCollection[i];
	}
	catch (std::out_of_range& e){
		std::cerr << "** EXCEPTION: " << e.what() << std::endl;
	}
	std::cout << "-----------------------------------------\n\n";
	

	std::cout << "-----------------------------------------\n";
	std::cout << "Testing the functor\n";
	std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
		// TODO: The following statement can generate generate an exception
		//         write code to handle the exception
		//       If an exception occurs print a message in the following format
		//** EXCEPTION: ERROR_MESSAGE<endl>
		//         where ERROR_MESSAGE is extracted from the exception object.
		sdds::SpellChecker sp(argv[i]);

		for (auto j = 0u; j < library.size(); ++j)
			library[j].fixSpelling(sp);
		sp.showStatistics(std::cout);

		for (auto j = 0u; j < theCollection.size(); ++j)
			theCollection[j].fixSpelling(sp);
		sp.showStatistics(std::cout);
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";


	/*
	std::cout << "=========================================\n";
	std::cout << "Wrapping up this workshop\n";
	std::cout << "--------------- Movies ------------------\n";
	std::cout << theCollection;
	std::cout << "--------------- Books -------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing operator[] (the other overload)\n";
	std::cout << "-----------------------------------------\n";
	const sdds::Movie* aMovie = theCollection["Terminator 2"];
	if (aMovie == nullptr)
		std::cout << "** Movie Terminator 2 not in collection.\n";
	aMovie = theCollection["Dark Phoenix"];
	if (aMovie != nullptr)
		std::cout << "In this collection:\n" << *aMovie;
	std::cout << "-----------------------------------------\n";
	*/
	return cout;
}
