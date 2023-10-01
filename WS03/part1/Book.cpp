/* ****************************************************************************
   OOP345 NFF WS03
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code 
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 1
**************************************************************************** */

#include <iostream>
#include <iomanip>
#include <sstream> 
#include "Book.h"

using namespace std;
namespace sdds {
   Book::Book() {}
   Book::Book(const string& title, unsigned nChapters, unsigned nPages) {
      if (!title.empty() && nChapters > 0 && nPages > 0) {
         m_title = title;
         m_numChapters = nChapters;
         m_numPages = nPages;
      }
   }

   // Book type is valid only when the title is not empty, >= one chapter, >= one page.
   Book::operator bool() const {
      return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
   }

   ostream& Book::print(std::ostream& os) const {
      if (*this) {
         //os << setw(51) << right << m_title << ','
         //   << setw(2) << right << m_numChapters << ','
         //   << setw(3) << right << m_numPages;
         ostringstream oss, oss2;
         oss << m_title << ',' << m_numChapters << ',' << m_numPages;
         oss2 << setprecision(6) << fixed << ((double)m_numPages / (double)m_numChapters) << ")";
         os << setw(56) << right << oss.str();

         os << " | " << "(";
         os << setw(15) << left << oss2.str();
      }
      else {
         os << "| Invalid book data";
      }
      return os;
   }

   ostream& operator<<(std::ostream& os, const Book& bk) {
      return bk.print(os);
   }
}
