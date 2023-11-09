// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : Nov 8, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#include <iostream>
//#include <fstream>
#include <string>
#include "Utilities.h"
using namespace std;

   char Utilities::m_delimiter{};

   Utilities::Utilities() {};
   // MEMBER FUNCTIONS

   /*
   * Extracts a token from string str referred to by the first parameter.
   + Uses the delimiter to extract the next token from str starting at position next_pos.
      -  If successful, return a copy of the extracted token found(without spaces at the beginning / end),
         update next_pos with the position of the next token, 
         and set more to true (false otherwise).
   + Reports an exception if a delimiter is found at next_pos.
   + Updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
     Note: in this application, str represents a single line that has been read from an input file.
   */
   /**/
   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

      more = false;
      string token{};
      size_t delimiter_pos = next_pos;

      // GET TOKEN:
      delimiter_pos = str.find(m_delimiter, next_pos);
      if (delimiter_pos != string::npos) {
         token = str.substr(next_pos, delimiter_pos - next_pos); // substr(starting pos, length)
         if (!token.empty()) {
            next_pos = delimiter_pos + 1;
            more = true;
         }
      }
      else {
         token = str.substr(next_pos, delimiter_pos);
         more = false;
      }

      // TRIM SPACES:
      size_t fSpacePos = token.find_first_not_of(' ');
      size_t lSpacePos = token.find_last_not_of(' ');
      token = token.substr(fSpacePos, (lSpacePos - fSpacePos + 1));
      //cout << "|" << token << "|" << endl;

      if (str[next_pos] == m_delimiter) {
         throw "Double Delimiter";
      }

      if (m_widthField < token.length()) {
         m_widthField = token.length();
      }
      return token;
   }


   void Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }
   size_t Utilities::getFieldWidth() const {
      return m_widthField;
   }

   // CLASS FUNCTION
   void Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }
      char Utilities::getDelimiter() {
      return m_delimiter;
   }