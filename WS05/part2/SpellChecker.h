#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

// We will replace the bad word?
// if not correct then throw const char*?
/*
fstream fin("words.txt");
fin.getline(...);
fin >> str1;
fin >> str2;
can already get the words to the array

make another array szie 6 and update? to count the replacement

find / replace()
*/

namespace sdds {
   class SpellChecker {
      std::string m_badWords[6]{};
      std::string m_goodWords[6]{};
      // int m_replacementCount[6];
   public:
      SpellChecker() {};

      SpellChecker(const char* filename);
      void operator()(std::string& text);
      void showStatistics(std::ostream& out) const;

      // RULES OF FIVE:
      //SpellChecker(const SpellChecker& scSrc);
      //SpellChecker& operator=(const SpellChecker& scSrc);
      //SpellChecker(const SpellChecker&& scSrc) noexcept;
      //SpellChecker& operator=(const SpellChecker&& scSrc) noexcept;
      //~SpellChecker();
   };

}

#endif // !SDDS_SPELLCHECKER_H