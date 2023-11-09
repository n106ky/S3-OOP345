// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : Nov 8, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
   //size_t m_widthField = 0;
   size_t sdds::Station::m_widthField = 0;
   int id_generator = 0;

   /*
   * Custom 1-argument constructor
   +  Upon instantiation, a Station object receives a reference to an unmodifiable std::string.
      This string contains a single record (one line) that has been retrieved from the input file specified by the user.
   +  This constructor uses a Utilities object (defined locally) to extract each token from the record and populates the Station object accordingly.
   +  This constructor assumes that the string contains 4 fields separated by the delimiter, in the following order:
      - name of the item
      - starting serial number
      - quantity in stock
      - description
   +  The token delimiter is a single character, specified by the client and previously stored into the Utilities class of objects.
   +  This constructor extracts name, starting serial number, and quantity from the string first
   +  Before extracting description, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.
      - Note: the display(...) member function uses this field width to align the output across all the records retrieved from the file.
   */

   Station::Station(const std::string src) {
      // cout << src << endl;
      Utilities utils;
      size_t pos = 0;
      bool more{};

      try {
         m_itemName = utils.extractToken(src, pos, more);
         m_serialNumber = std::stoi(utils.extractToken(src, pos, more));
         m_quantity = std::stoi(utils.extractToken(src, pos, more));

         m_widthField = std::max(m_widthField, utils.getFieldWidth()); // returns the greater of the two arguments it receives.

         m_desc = utils.extractToken(src, pos, more);

         //cout << "itemname   : " << m_itemName << endl;
         //cout << "serial no. : " << m_serialNumber << endl;
         //cout << "quantity   : " << m_quantity << endl;
         //cout << "desc       : " << m_desc << endl;

      }
      catch (const exception& e) {
         cerr << "Error: " << e.what() << endl;
      }
   }

   const std::string& Station::getItemName() const {
      return m_itemName;
   }

   size_t Station::getNextSerialNumber() {
      return m_serialNumber++;
   }

   size_t Station::getQuantity() const {
      return m_quantity;
   }

   void Station::updateQuantity() {
      if (m_quantity > 0) {
         --m_quantity;
      }
   }

   void Station::display(std::ostream& os, bool full) const {
      os << setw(3) << setfill('0') << m_id << " | ";
      os << left << setw(m_widthField) << setfill(' ') << m_itemName << " | ";
      os << setw(6) << setfill('0') << m_serialNumber << " | ";
      if (full) {
         os << setw(4) << setfill(' ') << m_quantity << " | ";
         os << m_desc;
      }
      os << endl;
   }
   
}