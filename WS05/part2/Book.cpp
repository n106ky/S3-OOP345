/* ****************************************************************************
   OOP345 NFF WS05   | PROF. HONG HUANG   |

   KA YING, CHAN     | #123231227         | kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 8
**************************************************************************** */
#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"
using namespace std;
namespace sdds {
   Book::Book(const string& strBook) {
      // cout << strBook;
      string line = strBook;

      // WHAT IF WE HAVE SOME MORE ATTRIBUTES, WE NEED TO CHANGE THE FUNCTION TO ADOPT BETTER:

      string author{};
      string title{};       // std::stoul() to unsigned long integer
      string country{};     // std::stod() change it back to double
      string year{};
      string price{};
      string desc{};

      line = findStr(author, line);
      line = findStr(title, line);
      line = findStr(country, line);
      line = findStr(price, line); 
      line = findStr(year, line);
      desc = line;

      author = trimStr(author);
      title = trimStr(title);
      country = trimStr(country);
      year = trimStr(year);
      price = trimStr(price);
      desc = trimStr(desc);

      m_author = author;
      m_title = title;
      m_country = country;
      m_year = std::stoul(year);   // std::stoul() to unsigned long integer
      m_price = std::stod(price);  // std::stod() change it back to double
      m_desc = desc;
   }


   // QUERIES:
   const string& Book::title() const {
      return m_title;
   }
   const string& Book::country() const {
      return m_country;
   }
   const size_t& Book::year() const {
      return m_year;
   }

   // MUTATABLE:
   double& Book::price() {
      return m_price;
   }

   // FRIEND:
   ostream& operator<<(ostream& os, const Book& bkSrc) {
      os
         << setw(20) << bkSrc.m_author << " | "
         << setw(22) << bkSrc.m_title << " | "
         << setw(5)<< bkSrc.m_country << " | "
         << setw(4) << bkSrc.m_year << " | "
         << setw(6) << setprecision(2) << fixed << bkSrc.m_price << " | "
          << bkSrc.m_desc << endl;
      return os;
   }

   // OTHERS:
   string Book::findStr(string& found, const string& str) {
      string line = str;
      size_t comma = line.find(',');
      found = line.substr(0, comma);
      line.erase(0, comma + 1); // +1: erase ','
      return line;
   }
   string Book::trimStr(string& str) {
      size_t fCharPos = str.find_first_not_of(' ');
      size_t lCharPos = str.find_last_not_of(' ');
      return str.substr(fCharPos, (lCharPos - fCharPos + 1));
   }

}

// FOR LATER:

/*
string Book::changeStr(string& features) {
   string newFts = features;
   size_t space = newFts.find(' ');
   while (space != std::string::npos) {
      newFts.erase(space, 1);
      space = newFts.find(' ');
   }
   size_t comma = newFts.find(',');
   while (comma != std::string::npos) {
      newFts[comma] = ' ';
      comma = newFts.find(',');
   }
   return newFts;
}
*/

// RULE OF FIVE:
//Book::Book(const Book& bkSrc) {
//   *this = bkSrc;
//}
//Book& Book::operator=(const Book& bkSrc) {
//   if (this!=&bkSrc) {

//   }
//   return *this;
//}
//Book::Book(const Book&& bkSrc) {
//   *this = move(bkSrc);
//}
//Book& Book::operator=(const Book&& bkSrc) {
//   if (this != &bkSrc) {
//   }
//   return *this;
//}
//Book::~Book() {}