// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 15, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <vector>

#include "LineManager.h"
#include "Workstation.h"

using namespace std;
namespace sdds {

   // Member Functions

   /*
   * this constructor receives the name of the file that identifies the active stations on the assembly line(example : AssemblyLine.txt) and the collection of workstations available for configuring the assembly line.
      The file contains the linkage between workstation pairs.
      The format of each record in the file is WORKSTATION | NEXT_WORKSTATION.The records themselves are not in any particular order.
      This function stores the workstations in the order received from the file in the m_activeLine instance variable.
      It loads the contents of the file, stores the address of the next workstation in each element of the collection, identifies the first station in the assembly line and stores its address in the m_firstStation attribute.
      This function also updates the attribute that holds the total number of orders in the g_pending queue.If something goes wrong, this constructor reports an error.
      Note: to receive full marks, use STL algorithms throughout this function, except for iterating through the file records(one while loop); marks will be deducted if you use any of for, while or do - while loops except for iterating through the file records.

   */
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {

   }

   // this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.The elements in the reordered collection start with the first station, proceeds to the next, and so forth until the end of the line.
   void LineManager::reorderStations() {

   }

   /*
   * this modifier performs one iteration of operations on all of the workstations in the current assembly line by doing the following :
      keeps track of the current iteration number(use a local variable)
      inserts into stream os the iteration number(how many times this function has been called by the client) in the format Line Manager Iteration : COUNT<endl>
      moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue.This function moves only one order to the line on a single iteration.
      for each station on the line, executes one fill operation
      for each station on the line, attempts to move an order down the line
      return true if all customer orders have been filled or cannot be filled, otherwise returns false.
   */
   bool LineManager::run(std::ostream& os) {
      return 1;
   }


   // this query displays all active stations on the assembly line in their current order
   void LineManager::display(std::ostream& os) const {

   }

}