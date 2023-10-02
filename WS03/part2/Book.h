/* ****************************************************************************
	OOP345 NFF WS03
	PROF. HONG HUANG

	KA YING, CHAN #123231227
	kchan151@myseneca.ca

	I have done all the coding by myself and only copied the code
	that my professor provided to complete my workshops and assignments.

	Completed on 2023 OCT 1
**************************************************************************** */

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

namespace sdds {
	class Book {
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
		//double m_avg{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);
		Book& operator=(const Book& book);

		operator bool() const;
		bool operator<(const Book& item) const;
		bool operator>(const Book& item) const;

		std::ostream& print(std::ostream& os) const;
	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}
#endif
