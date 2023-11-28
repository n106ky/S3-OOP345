// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 27, 2023
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
      if (!m_orders.empty()) {
         m_orders.front().fillItem(*this, os);
      }
   }


   /*
   * attempts to move the order at the front of the queue to the next station in the assembly line :
   + if the order requires no more service at this station or cannot be filled (not enough inventory), 
      move it to the next station; otherwise do nothing
   + if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
   + if an order has been moved, return true; false otherwise.
   */
   /*
   bool Workstation::attemptToMoveOrder() {
      bool isMoved = false;
     
      if ("no more service at the station" || "cannot be filled (inventory <= a number)") {

            if ("no next station"){
               "move into g_completed or g_incomplete queue";
               isMoved = true;
            }
            else {
               "move to next station";
               isMoved = true;
            }
            "remove(order_at_the_front)";
      }
     
      if (!m_orders.empty() || getQuantity() < 1) {

         if (!m_pNextStation) {
            if (m_orders.front().isOrderFilled()) {
               g_completed.push_back(move(m_orders.front()));
            }
            else {
               g_incomplete.push_back(move(m_orders.front()));
            }
         }
         else {
            *m_pNextStation += move(m_orders.front()); // why do I need to have * in front of m_pNextStation
         }
         m_orders.pop_front(); //  "remove(order_at_the_front)";
         isMoved = true;
      }
      return isMoved;
   }*/

   bool Workstation::attemptToMoveOrder() {
      bool result = false;
      if (!m_orders.empty()) {
         if (m_orders.front().isOrderFilled() || m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1) {
            if (m_pNextStation) {
               *m_pNextStation += std::move(m_orders.front());
            }
            else if (m_orders.front().isOrderFilled()) {
               g_completed.push_back(std::move(m_orders.front()));
            }
            else {
               g_incomplete.push_back(std::move(m_orders.front()));
            }
            m_orders.pop_front();
            result = true;
         }
      }

      return result;
   }



   //this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation.
   void Workstation::setNextStation(Workstation* station) {
      m_pNextStation = station;
   }

   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }


   /*
   * this query inserts the name of the Item for which the current object is responsible into stream os following the format : 
      ITEM_NAME-- > NEXT_ITEM_NAME
   + if the current object is the last Workstation in the assembly line this query inserts : ITEM_NAME-- > End of Line.
   + in either case, the message is terminated with \n
   */
   void Workstation::display(std::ostream& os) const {
      os << getItemName() << " --> ";
      if (m_pNextStation) {
         os << m_pNextStation->getItemName() << endl;
      }
      else {
         os << "End of Line" << endl;
      }
   }


   // moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
      // g_pending.push_back(newOrder);
      m_orders.push_back(move(newOrder)); // "moves"
      return *this;
   }




}