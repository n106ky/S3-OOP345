/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 4
**************************************************************************** */
#include <iostream>
#include <iomanip>
#include "CheeseShop.h"

using namespace std;
namespace sdds {

   CheeseShop::CheeseShop(const string& name) {
      m_shopname = name;
   }

   // RULE OF FIVE:
   CheeseShop::CheeseShop(const CheeseShop& shopSrc) {
      *this = shopSrc;
   }
   CheeseShop& CheeseShop::operator=(const CheeseShop& shopSrc) {
      //if (this!=&shopSrc) {
      //   delete[] m_chz;
      //   m_shopname = shopSrc.m_shopname;
      //   m_chz = shopSrc.m_chz;
      //}
      if (this != &shopSrc) {
         for (size_t i = 0; i < m_size; i++) {
            delete m_chz[i];
         }
         delete[] m_chz;
         m_shopname = shopSrc.m_shopname;
         m_size = shopSrc.m_size;
         m_chz = new const Cheese * [m_size]; //const
         for (size_t i = 0; i < m_size; i++) {
            m_chz[i] = new Cheese(*(shopSrc.m_chz[i])); // might be wrong // const
         }
      }
      return *this;
   }
   CheeseShop::CheeseShop(CheeseShop&& shopSrc) noexcept { // why noexcept? why should not throw?
      *this = move(shopSrc);
   }
   CheeseShop& CheeseShop::operator=(CheeseShop&& shopSrc) noexcept {
      if (this!=&shopSrc) {
         delete[] m_chz;
         m_shopname = shopSrc.m_shopname;
         shopSrc.m_shopname.clear();
         m_chz = shopSrc.m_chz;
         shopSrc.m_chz = nullptr;
      }
      return *this;
   }

   CheeseShop::~CheeseShop() {
      // might need to use for loop to delete it one by one.
      delete[] m_chz;
   }

   // a modifier that adds a cheese object to the array of pointers.
   CheeseShop& CheeseShop::addCheese(const Cheese& chz) {
      const Cheese** temp_chz = new const Cheese*[m_size + 1];
      size_t i = 0;
      for (i = 0; i < m_size; i++) {
         temp_chz[i] = m_chz[i];
      }
      // temp_chz[i] = chz; Why not working?
      // temp_chz[i] = &chz; // Am I using move() here??
      temp_chz[i] = new Cheese(chz);

      //for (i = 0; i < m_size; i++) { // BIG QUESTION: WHY I DON'T NEED IT?????????
      //   delete m_chz[i];
      //}
      //delete[] m_chz;

      m_chz = temp_chz; // STH WRONG HERE, CANNOT STORE STRING PROPERLY
      m_size++;

      return *this;
   }


   ostream& operator<<(ostream& os, const CheeseShop& chzShop) {
      os
         << "--------------------------" << endl
         << chzShop.m_shopname << endl
         << "--------------------------" << endl;
      if (chzShop.m_size > 0) {
         for (size_t i = 0; i < chzShop.m_size; i++) {
            os
         
               << '|' << setw(21) << left << chzShop.m_chz[i]->getName()
               << '|' << setw(5) << chzShop.m_chz[i]->getWeight()
               << '|' << setw(5) << fixed << setprecision(2) << chzShop.m_chz[i]->getWeight()
               << '|' << setw(33) << right << chzShop.m_chz[i]->getFeatures()
               << " |" << endl;
         }
      }
      else {
         os
            << "This shop is out of cheese!" << endl
            << "--------------------------" << endl;
      }

         //CHEESE1 DETAILS
         //CHEESE2 DETAILS
         //...
         //--------------------------
      return os;
   }

}
