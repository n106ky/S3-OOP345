#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include "CovidCollection.h"

using namespace std;
namespace sdds {
   /*
    * A custom constructor that receives as a parameter the name of the file containing the information about the covid details of various cities to be added to the collection.
    + This function should load into the attributes all the covid details in the file.
    + If the filename is incorrect, this constructor should raise an exception.

    + Each line from the file contains covid information about a single city in the following format :
      - COUNTRY CITY VARIANT YEAR CASES DEATHS

    + The fields are not separated by delimiters; each field has a fixed size :
      - COUNTRY, CITY and VARIANT have exactly 25 characters; while YEAR, CASES and DEATHS have exactly 5 characters.

    + Any blank space at the beginning / end of a token is not part of the token and should be removed.
   */
   void CovidCollection::TrimStr(string& str) {
      //cout << "Recevied str: |" << str << "|" << endl;
      size_t fPos = str.find_first_not_of(' ');
      size_t lPos = str.find_last_not_of(' ');
      str = str.substr(fPos, (lPos - fPos + 1));
   }
   //size_t sdds::Covid::m_count = 0;
   CovidCollection::CovidCollection(const string filename) {
      ifstream inFile(filename);
      string line{};

      if (!inFile.is_open()) {
         throw std::runtime_error("Incorrect filename");
      }
      while (getline(inFile, line)) {
         //cout << line << endl;
         Covid cv{};
         cv.m_country = line.substr(0, 25); // substr: starting at index 0 and spanning 25 characters in length
         cv.m_city = line.substr(25, 25);
         cv.m_variant = line.substr(50, 25);
         cv.m_year = stoi(line.substr(75, 5));
         cv.m_cases = stoul(line.substr(80, 5));
         cv.m_deaths = stoul(line.substr(85, 5));

         TrimStr(cv.m_country);
         TrimStr(cv.m_city);
         TrimStr(cv.m_variant);
         
         m_collection.push_back(cv);
      }
   }

   // print the content of the collection into the parameter(one city details / line). Use the insertion operator (see below). DO NOT USE MANUAL LOOPS!
   void CovidCollection::display(std::ostream& os) const {
      std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& c) {
         os << c;
         });
   }

   // Free Helpers
   /*
   Inserts one Covid object into the first parameter, using the following format(the width of each field is specified in brackets) :

   | COUNTRY(21) | CITY(15) | VARIANT(20) | YEAR(6) | CASES(4) | DEATHS(3) |
   Look in the sample output to see how the numbers should be formatted and the alignment of each field.
   */
   std::ostream& operator<<(std::ostream& os, const Covid& c) {
      os << "| "
         << setw(21) << left << c.m_country << " | "
         << setw(15) << c.m_city << " | "
         << setw(20) << c.m_variant << " | "
         << setw(6) << right;
      (c.m_year > 0) ? os << c.m_year : os << "";
      os << " | "
         << setw(4) << c.m_cases << " | "
         << setw(3) << c.m_deaths << " |" << endl;
      return os;
   }
}