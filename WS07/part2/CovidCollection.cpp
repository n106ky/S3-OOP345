#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>

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
   /*
   void CovidCollection::display(std::ostream& os) const {
      std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& c) {
         os << c;
         });
   }*/

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
         << setw(3) << c.m_deaths << " |";
      return os;
   }


   /*
   This function represents Task #1 -- DO NOT USE MANUAL LOOPS!
   Update this function's prototype to receive a second parameter country. 
   This parameter should have the default value ALL if the client doesn't provide it (don't overload the function).
   
   Implement the function to print only the information about the country specified in the second parameter. 
   If the parameter has the value ALL, then print information for all countries.
   This function should also calculate the percentage of cases/deaths in the specified country from the world total. 
   If the second parameter is ALL, then this function should print the number of cases/deaths in the world. See the sample output for the format.
   */
   void CovidCollection::display(std::ostream& os, const std::string& country) const {
      /*
      if (country == "ALL") {
         std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& c) {
            os
               << c
               << "|" << c.m_status << "|" << endl;
            });
      }
      else {
      }
      */

   }

   /*
   This function represents Task #2 -- DO NOT USE MANUAL LOOPS!
   Sort the collection of Covid objects in ascending order based on the field received as parameter.
   The parameter should have a default value of country (do not overload this function).
   If two Covid objects have the same value for the specified field, then the object with lower deaths is considered smaller.
   */
   void CovidCollection::sort(const std::string& field) {

   }


   /*
   This function represents Task #3 -- DO NOT USE MANUAL LOOPS!
   Search in the collection for a city in the specified country where the variant from the first parameter has caused more deaths than the last parameter.
   Return true if such an object exists, false otherwise.
   */
   bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {

      return 1;
   }

   /*
   This function represents Task #4 -- DO NOT USE MANUAL LOOPS!
   Create and return a collection of Covid objects from the current instance where the number of deaths is at least as the value specified as parameter.
   */
   list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
      list<Covid> filteredList{};
   
      return filteredList;
   }

   /*
   This function represents Task #5 -- DO NOT USE MANUAL LOOPS!
   updates the status of each city. 
   If the number of deaths is greater than 300, the status should be EPIDEMIC, 
   if it is less than 50, it should be EARLY; 
   for anything else, the status should be MILD.
   */
   void CovidCollection::updateStatus() {
      for_each(m_collection.begin(), m_collection.end(), [](Covid& c) {
         if (c.m_deaths > 300) {
            c.m_status = "EPIDEMIC";
         }
         else if (c.m_deaths < 50) {
            c.m_status = "EARLY";
         }
         else {
            c.m_status = "MILD";
         }
         });
   }
}