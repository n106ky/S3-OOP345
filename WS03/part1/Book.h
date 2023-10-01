#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

namespace sdds {
	class Book {
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);

		// TODO: In completing Part 1, add here the missing 
		// member prototypes that would be necessary for the 
		// Collection module code and tester module w3_p1.cpp 
		// to manage Book-type objects. 

		//operator bool() const;
		//void setEmpty();
		//// RULE OF FIVE:
		//Book(const Book& src);
		//Book& operator=(const Book& src);
		//Book(Book&& src) noexcept; // What is noexcept again? Is it a good practice?
		//Book& operator=(Book&& src) noexcept;
		//~Book();

		// In completing Part 2, add here the missing 
		// member prototypes that would be necessary for 
		// OrderedCollection module code and tester module 
		// w3_p2.cpp to manage Book-type object. 
		
		// Write the implementations of these functions 
		// in Book.cpp file
		std::ostream& print(std::ostream& os) const;

	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}
#endif
