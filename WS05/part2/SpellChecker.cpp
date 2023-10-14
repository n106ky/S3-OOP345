
#include <iostream>
// #include <iomanip>
#include "SpellChecker.h"
using namespace std;
namespace sdds {
   SpellChecker::SpellChecker(const char* filename) {
      // ifstream file(filename);

      /*
       receives the address of a C-style null-terminated string that holds the name of the file that contains the misspelled words. 
       If the file exists, this constructor loads its contents. 
       If the file is missing, this constructor throws an exception of type const char*, with the message Bad file name!. 
       Each line in the file has the format BAD_WORD  GOOD_WORD; the two fields can be separated by any number of spaces.
      */
   }
   void SpellChecker::operator()(std::string& text) {
      /*
      this operator searches text and replaces any misspelled word with the correct version. It should also count how many times each misspelled word has been replaced.
      When implementing this operator, consider the following functions:
      std::string::find()
      std::string::replace()
      */
   }
   void SpellChecker::showStatistics(std::ostream& out) const {
      /*
       inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance. 
       The format of the output is:
       BAD_WORD: CNT replacements<endl>
       where BAD_WORD is to be printed on a field of size 15, aligned to the right.
       You will have to design a method to remember how many times each bad word has been replaced.
      */
   }
}