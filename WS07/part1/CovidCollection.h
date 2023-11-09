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
      std::string m_country;
      std::string m_city;
      std::string m_variant;
      int m_year;
      unsigned int m_cases;
      unsigned int m_deaths;
      //static size_t m_count;
   };

   class CovidCollection {
      std::vector<Covid> m_collection{};
      void TrimStr(std::string&);
   public:
      CovidCollection() {};
      CovidCollection(const std::string filename);
      void display(std::ostream&) const;

   };

   // Free Helpers
   std::ostream& operator<<(std::ostream&, const Covid&);

}



#endif