// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : Nov 8, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#ifndef UTILITIES_H
#define UTILITIES_H

// namespace sdds {
   // module supports the parsing of input files, which contain information used to setup and configure the assembly line.
   class Utilities {
      size_t m_widthField{ 1 };  // specifies the length of the token extracted; used for display purposes; default value is 1
      static char m_delimiter;   // separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter.
   public:

      Utilities();

      // MEMBER FUNCTIONS:
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

      void setFieldWidth(size_t newWidth); // sets the field width of the current object to the value of parameter newWidth
      size_t getFieldWidth() const; // returns the field width of the current object

      // CLASS FUNCTIONS:
      static void setDelimiter(char newDelimiter); // sets the delimiter for this class to the character received
      static char getDelimiter(); // returns the delimiter for this class.

   };
//}
#endif
