// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 27, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
// (50% of LineManager constructor took referenced from github)

#include <iostream>
#include <iomanip>
#include <vector>

#include <fstream>
#include <string>
#include <algorithm>

#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace sdds {

   // Member Functions

   /*
   * This constructor receives the name of the file that identifies the active stations on the assembly line (example : AssemblyLine.txt), 
     and the collection of workstations available for configuring the assembly line.

      + The file contains the linkage between workstation pairs.
         - The format of each record in the file is WORKSTATION | NEXT_WORKSTATION.
         - The records themselves are not in any particular order.

      + This function stores the workstations in the order received from the file in the m_activeLine instance variable.
         - It loads the contents of the file, stores the address of the next workstation in each element of the collection, 
           identifies the first station in the assembly line and stores its address in the m_firstStation attribute.
         - This function also updates the attribute that holds the total number of orders in the g_pending queue.
         - If something goes wrong, this constructor reports an error.

      Note: to receive full marks, use STL algorithms throughout this function, except for iterating through the file records(one while loop); 
            marks will be deducted if you use any of for, while or do - while loops except for iterating through the file records.
   */
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
      // cout << "filename: " << file << endl;
      ifstream inFile(file);
      Utilities utils{};
      Utilities::setDelimiter('|');
      size_t pos{};
      bool more{};

      try {
         if (inFile) {
            std::string line{};
            while (getline(inFile, line)) {
               string st, nst;
               st = utils.extractToken(line, pos, more);
               nst = utils.extractToken(line, pos, more); // if there is no delimeter, st & nst will be the same
               pos = 0; // reset pos & more for next line
               more = false;

               // assign current station (st) to m_activeLine
               auto item = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                  return ws->getItemName() == st;
                  });
               if (item != stations.end()) {
                  m_activeLine.push_back(*item);
               }

               // if there is next_station, assign next station (nst) to the back of m_activeLine
               if (st != nst) {
                  auto nextItem = std::find_if(stations.begin(), stations.end(), [=](Workstation* ws) {
                     return ws->getItemName() == nst;
                     });
                  if (nextItem != stations.end()) {
                     m_activeLine.back()->setNextStation(*nextItem);
                  }

                  // find the first working station:
                  auto firstws = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) { // if none_of is true, (= none_of them match is true), that means the first one is found.
                     return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) {
                        return ws == other->getNextStation(); // if all false, none_of will return true. In this return statement, every one of them should return "false" for none_of to return true.
                        }); // if current ws match with the next station of the other ws
                     });

                  // assign to m_firstStation if found
                  if (firstws != stations.end()) {
                     m_firstStation = *firstws;
                  }

                  m_cntCustomerOrder = g_pending.size();
               }
            }
         }
      }
      catch (const exception& e) {
         cerr << "Error: " << e.what() << endl;
      }
   }

   // Reordering Workstations:
   void LineManager::reorderStations() {
      Workstation* temp = m_firstStation;
      std::deque<Workstation*> reorderedTemp;
      while (temp) {
         reorderedTemp.push_back(temp);
         temp = temp->getNextStation();
      }
      m_activeLine.clear();
      m_activeLine.assign(reorderedTemp.begin(), reorderedTemp.end());
   }

   /*
   * this modifier performs one iteration of operations on all of the workstations in the current assembly line by doing the following :
      keeps track of the current iteration number (use a local variable)
      inserts into stream os the iteration number (how many times this function has been called by the client) in the format Line Manager Iteration : COUNT<endl>
      moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue.
      This function moves only one order to the line on a single iteration.
      for each station on the line, executes one fill operation
      for each station on the line, attempts to move an order down the line
      return true if all customer orders have been filled or cannot be filled, otherwise returns false.
   */
   bool LineManager::run(std::ostream& os) {
      static size_t iCnt{};
      iCnt++;
      os << "Line Manager Iteration: " << iCnt << endl;

      if (!g_pending.empty()) {
         *m_firstStation += move(g_pending.front());
         g_pending.pop_front();
      }

      //for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* s) {
      // s->fill(os);
      //   });
      for (auto item : m_activeLine) {
         item->fill(os);
      }
      //for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* s) {
      // s->attemptToMoveOrder();
      //   });
      for (auto item : m_activeLine) {
         item->attemptToMoveOrder();
      }

      return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
   }

    void LineManager::display(std::ostream& os) const {
       /*
       (Workstation* station): This is the parameter list of the lambda function. 
       Each element of m_activeLine is passed to this lambda one by one during the iteration. 
       Each element is a pointer to a Workstation object.

        using "&" to capture the "os" by reference, it will be used for the display function.
        the lambda can access and modify local variables of the enclosing scope
        (in this case, os from the display function)

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
          station->display(os);
          });
       */

      for (auto& wstation : m_activeLine) {
         wstation->display(os);
      }
    }
}