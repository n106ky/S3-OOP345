// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 27, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque> // Efficient Insertions/Deletions at Both Ends
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {

   // Forward declaration of the global queues
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;

   /*
      Each queue is accessible outside this module's translation unit.

      The Workstation class defines the structure of an active station on the assembly line and contains all the functionality for filling customer orders with station items.
      Each Workstation is-a-kind-of Station. A Workstation object manages order processing for a single Item on the assembly line.
      Since a Workstation object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved.
      Make sure that this capability is deleted in your definition of the Workstation class.

      The Workstation class includes the following additional information:
   */
   class Workstation : public Station {
      std::deque<CustomerOrder> m_orders; // is a double-ended-queue with CustomerOrders entering the back and exiting the front. 
                                          // These are orders that have been placed on this station to receive service (or already received service).
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string&);

      // RULE OF FIVE
      Workstation(const Workstation& src) = delete;
      Workstation& operator=(const Workstation& src) = delete;
      Workstation(Workstation&& src) = delete;
      Workstation& operator=(Workstation&& src) = delete;
      // ~Workstation();

      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station=nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;

      Workstation& operator+=(CustomerOrder&& newOrder);

   };
}
#endif 
