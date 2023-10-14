#include <iostream>
#include <iomanip>
#include "Movie.h"
using namespace std;
namespace sdds {
   const string& Movie::title() const {
      return m_title;
   }
   Movie::Movie(const string& strMovie) {
      string line = strMovie;

      string title{};
      string releaseYear{};
      string summary{};

      line = findStr(title, line);
      line = findStr(releaseYear, line);
      summary = line;

      title = trimStr(title);
      releaseYear = trimStr(releaseYear);
      summary = trimStr(summary);

      m_title = title;
      m_releaseYear = releaseYear;
      m_desc = summary;
   }

   string Movie::findStr(string& found, const string& str) {
      string line = str;
      size_t comma = line.find(',');
      found = line.substr(0, comma);
      line.erase(0, comma + 1); // +1: erase ','
      return line;
   }
   string Movie::trimStr(string& str) {
      size_t fCharPos = str.find_first_not_of(' ');
      size_t lCharPos = str.find_last_not_of(' ');
      return str.substr(fCharPos, (lCharPos - fCharPos + 1));
   }

   ostream& operator<<(ostream& os, const Movie& mvSrc) {
      os
         << setw(40) << right << mvSrc.m_title << " | "
         << setw(4) << mvSrc.m_releaseYear << " | "
         << mvSrc.m_desc << endl;
      return os;
   }

}