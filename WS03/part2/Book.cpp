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
   //Book::Book(const string& title, unsigned nChapters, unsigned nPages) {
   //   if (!title.empty() && nChapters > 0 && nPages > 0) {
   //      m_title = title;
   //      m_numChapters = nChapters;
   //      m_numPages = nPages;
   //      //m_avg = static_cast<double>(m_numPages) / m_numChapters;
   //   }
   //}
   Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {};

   Book& Book::operator=(const Book& other)
   {
      if (this != &other) {
         m_title = other.m_title;
         m_numChapters = other.m_numChapters;
         m_numPages = other.m_numPages;
         //m_avg = other.m_avg;
      }
      return *this;
   }

   // Book type is valid only when the title is not empty, >= one chapter, >= one page.
   Book::operator bool() const {
      return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
   }

   //bool Book::operator<(const Book& item) const {
   //   return item.m_avg < m_avg;
   //}
   //bool Book::operator>(const Book& item) const {
   //   return m_avg > item.m_avg;
   //}
   bool Book::operator>(const Book& item) const {
      return (double)m_numPages / m_numChapters > (double)item.m_numPages / item.m_numChapters;
   };
   bool Book::operator<(const Book& item) const {
      return (double)m_numPages / m_numChapters < (double)item.m_numPages / item.m_numChapters;
   };

   ostream& Book::print(std::ostream& os) const {
      if (*this) { // m_title != "" && m_numChapters > 0 && m_numPages > 0
         ostringstream oss, oss2;
         oss << m_title << ',' << m_numChapters << ',' << m_numPages;
         oss2 << setprecision(6) << fixed << (double)m_numPages / m_numChapters << ") "; // m_avg
         os << setw(56) << right << oss.str();
         os << " | " << "(";
         os << setw(14) << left << oss2.str();
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
