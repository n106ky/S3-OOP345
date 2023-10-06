/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 4
**************************************************************************** */
#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H
#include "Cheese.h"

namespace sdds {
   class CheeseShop {
      std::string m_shopname{};
      const Cheese** m_chz{}; // Each element in this array (m_chz) is a pointer to an object (Cheese*)
      size_t m_size;

   public:
      //CheeseShop();

      // a constructor that receives as a parameter the name of the shop. The default value for the parameter is "No Name".
      CheeseShop(const std::string& name = "No Name");

      // RULE OF FIVE:
      CheeseShop(const CheeseShop& shopSrc);
      CheeseShop& operator=(const CheeseShop& shopSrc);
      CheeseShop(CheeseShop&& shopSrc)noexcept;
      CheeseShop& operator=(CheeseShop&& shopSrc)noexcept;
      ~CheeseShop();


      // a modifier that adds a cheese object to the array of pointers.
      CheeseShop& addCheese(const Cheese& chz); 

      friend std::ostream& operator<<(std::ostream& os, const CheeseShop& chzShop);
   };

}

#endif SDDS_CHEESESHOP_H
