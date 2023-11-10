#pragma once
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <vector>
// <algorithms>
// modifier, transform, replace if
// greater<object>
// sort then merge, or runtime issue will pop
// accumulate (2 kinds)

namespace sdds {

   struct Covid {
      std::string m_country{};
      std::string m_city{};
      std::string m_variant{};
      int m_year{};
      unsigned int m_cases{};
      unsigned int m_deaths{};
      std::string m_status{"General"};
      //static size_t m_count;
   };

   class CovidCollection {
      std::vector<Covid> m_collection;
      void TrimStr(std::string&);
   public:
      CovidCollection() {};
      CovidCollection(const std::string filename);

      /*
      This function represents Task #1 -- DO NOT USE MANUAL LOOPS!
      Update this function's prototype to receive a second parameter country. 
      This parameter should have the default value ALL if the client doesn't provide it (don't overload the function).
      Implement the function to print only the information about the country specified in the second parameter. If the parameter has the value ALL, then print information for all countries.
      This function should also calculate the percentage of cases/deaths in the specified country from the world total. If the second parameter is ALL, then this function should print the number of cases/deaths in the world. See the sample output for the format.
      */
      void display(std::ostream& os, const std::string& country="ALL") const;

      /*
      This function represents Task #2 -- DO NOT USE MANUAL LOOPS!
      Sort the collection of Covid objects in ascending order based on the field received as parameter.
      The parameter should have a default value of country (do not overload this function).
      If two Covid objects have the same value for the specified field, then the object with lower deaths is considered smaller.
      */
      void sort(const std::string& field = "country");


      /*
      This function represents Task #3 -- DO NOT USE MANUAL LOOPS!
      Search in the collection for a city in the specified country where the variant from the first parameter has caused more deaths than the last parameter. 
      Return true if such an object exists, false otherwise.
      */
      bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;

      /*
      This function represents Task #4 -- DO NOT USE MANUAL LOOPS!
      Create and return a collection of Covid objects from the current instance where the number of deaths is at least as the value specified as parameter.
      */
      std::list<Covid> getListForDeaths(unsigned int deaths) const;

      /*
      This function represents Task #5 -- DO NOT USE MANUAL LOOPS!
      updates the status of each city. If the number of deaths is greater than 300, the status should be EPIDEMIC, if it is less than 50, it should be EARLY; for anything else, the status should be MILD.
      */
      void updateStatus();

   };

   // Free Helpers
   std::ostream& operator<<(std::ostream&, const Covid&);

}

#endif