// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 27, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include "Workstation.h"
/*
   Workstation:
      Workstation = Current working station.

      Think of a workstation as a small work area in a factory assembly line. 
      It's a specific type of station where work is actually done on products. 
      Each workstation is responsible for adding a specific part to a product. 
      For example, one workstation might be where a computer gets its CPU installed, another might be where the computer gets its memory installed, and so on.

   LineManager:
      The LineManager is like a supervisor who oversees the entire assembly line. 
      The LineManager's job is to set up the assembly line by deciding the order in which products should move through the different workstations. 
      Once the setup is complete, the LineManager starts moving products (in this case, CustomerOrders) down the line.

   Assembly Line Configuration:
      Before the assembly line starts running, the LineManager needs to arrange all the workstations in a specific sequence. 
      This means deciding in what order the parts will be added to the product.

   Moving Orders Along:
      Once everything is set up, the LineManager begins the work process. 
      Each workstation tries to add its part to the product. 
      If a workstation has the part in stock, it adds it to the product, and the product moves on to the next workstation. 
      If the workstation doesn't have the part, the product still moves on, but without that part being added.

   Complete or Incomplete Orders:
      As products move through the assembly line, they are either getting completed or not, depending on the availability of parts at each workstation. 
      Once a product reaches the end of the line, it's checked to see if it has all its parts (complete) or if it's missing any (incomplete). 
      An incomplete order is one that went through the line but didn't get all the parts it needed because some workstations ran out of stock.
*/
namespace sdds {

   class LineManager {
      std::vector<Workstation*> m_activeLine{};    // the collection of workstations for the current assembly line.
      size_t m_cntCustomerOrder{};                 // the total number of CustomerOrder objects
      Workstation* m_firstStation{};               // points to the first active station on the current line
   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);

      void reorderStations();
      bool run(std::ostream& os);
      void display(std::ostream& os) const;
   };
}
#endif 

