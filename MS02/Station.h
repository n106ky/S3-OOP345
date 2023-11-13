// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 13, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds {

   // The Station module manages information about a station on the assembly line, which holds a specific item and fills customer orders.
   // A Station object manages a single station on the assembly line. Each station handles a specific item for filling customer orders.
   class Station {
      int m_id{};
      std::string m_itemName{};
      size_t m_serialNumber{};
      size_t m_quantity{};
      std::string m_desc{};
      static size_t m_widthField;
      static int id_generator; // a variable used to generate IDs for new instances of type Station. Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented. Initial value is 0.
  
   public:
      Station(const std::string);

      const std::string& getItemName() const;
      size_t getNextSerialNumber(); 

      size_t getQuantity() const; 
      void updateQuantity();

      void display(std::ostream& os, bool full) const;
   };
}
#endif
