#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
//#include "Collection.h"

namespace sdds {
   class Movie {
      std::string m_title{};
      std::string m_releaseYear{};
      std::string m_desc{};

      // OTHERS:
      std::string findStr(std::string& found, const std::string& str);
      std::string trimStr(std::string& str);

   public:
      Movie() {};
      const std::string& title() const;
      Movie(const std::string& strMovie);

      template<typename T>
      void fixSpelling(T& spellChecker) {

      }

      friend std::ostream& operator<<(std::ostream& os, const Movie& mvSrc);
   };
}

#endif