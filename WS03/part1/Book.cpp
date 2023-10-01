#include <iostream>
#include <iomanip>
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
   // An object of Book type is valid or usable only when the title is not empty (has at least one character), it has at least one chapter, and it has at least one page.
   //Book::operator bool() const {
   //   return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
   //}
   //void Book::setEmpty() {
   //   m_title.clear(); // to empty string, "not nullptr"
   //   m_numChapters = 0;
   //   m_numPages = 0;
   //}
   //Book::Book(const Book& src) {
   //   if (src) {
   //      m_title = src.m_title;
   //      m_numChapters = src.m_numChapters;
   //      m_numPages = src.m_numPages;
   //   } else {
   //      setEmpty();
   //   }
   //}
   //Book& Book::operator=(const Book& src) {
   //   if (this!=&src) {
   //      if (src) {
   //         m_title = src.m_title;
   //         m_numChapters = src.m_numChapters;
   //         m_numPages = src.m_numPages;
   //      }
   //      else { // set empty;
   //         setEmpty();
   //      }
   //   }
   //   return *this;
   //}
   //Book::Book(Book&& src) noexcept {
   //}
   //Book& Book::operator=(Book&& src) noexcept {
   //}
   //Book::~Book() {
   //}



   ostream& Book::print(std::ostream& os) const {
      cout 
         << setw(57) << right << m_title << ',' << m_numChapters << ',' << m_numPages << "|" 
         << " (" << setw(16) << left << ((double)m_numPages / (double)m_numChapters) << ")";
      return os;
   }

   ostream& operator<<(std::ostream& os, const Book& bk) {
      return bk.print(os);
   }
}