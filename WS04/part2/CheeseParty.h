/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 6
**************************************************************************** */
#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H
#include "Cheese.h"

namespace sdds {
   class CheeseParty {
      const Cheese** m_pChz{};
      size_t m_ptySize{};

   public:
      CheeseParty();
      CheeseParty& addCheese(const Cheese& chz);
      CheeseParty& removeCheese();

      // RULE OF FIVE:
      CheeseParty(const CheeseParty& ptySrc);
      CheeseParty& operator=(const CheeseParty& ptySrc);
      CheeseParty(CheeseParty&& ptySrc);
      CheeseParty& operator=(CheeseParty&& ptySrc);
      ~CheeseParty();

      friend std::ostream& operator<<(std::ostream& os, const CheeseParty& ptySrc);
   };


}

#endif SDDS_CHEESEPARTY_H
