// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 15, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Workstation.h"

using namespace std;
namespace sdds { 
   std::deque<CustomerOrder> g_pending{};       // holds the orders to be placed onto the assembly line at the first station.
   std::deque<CustomerOrder> g_completed{};     // holds the orders that have been removed from the last station and have been completely filled.
   std::deque<CustomerOrder> g_incomplete{};    // holds the orders that have been removed from the last station and could not be filled completely.


   Workstation::Workstation(const std::string& str): Station(str) {}

   // this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
   void Workstation::fill(std::ostream& os) {

   }

   /*
   * attempts to move the order order at the front of the queue to the next station in the assembly line :
   + if the order requires no more service at this station or cannot be filled(not enough inventory), move it to the next station; otherwise do nothing
   + if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
   + if an order has been moved, return true; false otherwise.
   */
   bool Workstation::attemptToMoveOrder() {
      return 1;
   }


   //this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation.Parameter defaults to nullptr.
   void Workstation::setNextStation(Workstation* station) {

   }

   // this query returns the address of next Workstation
   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }


   /*
   * this query inserts the name of the Item for which the current object is responsible into stream os following the format : ITEM_NAME-- > NEXT_ITEM_NAME
   + if the current object is the last Workstation in the assembly line this query inserts : ITEM_NAME-- > End of Line.
   + in either case, the message is terminated with \n
   */
   void Workstation::display(std::ostream& os) const {

   }


   // moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {

      return *this;
   }




}