/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 6
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
      if (this != &shopSrc) {
         for (size_t i = 0; i < m_size; i++) {
            delete m_chz[i];
         }
         delete[] m_chz;
         m_shopname = shopSrc.m_shopname;
         m_size = shopSrc.m_size;
         m_chz = new const Cheese * [m_size];
         for (size_t i = 0; i < m_size; i++) {
            m_chz[i] = new Cheese(*shopSrc.m_chz[i]); 
         }
      }
      return *this;
   }
   CheeseShop::CheeseShop(CheeseShop&& shopSrc) noexcept {
      *this = move(shopSrc);
   }

   CheeseShop& CheeseShop::operator=(CheeseShop&& shopSrc) noexcept {
      if (this != &shopSrc) {
         if (m_chz != nullptr) {
            for (size_t i = 0; i < m_size; i++) {
               delete m_chz[i];
            }
         }
         delete[] m_chz;
         m_chz = nullptr;

         m_shopname = shopSrc.m_shopname;
         m_size = shopSrc.m_size;
         m_chz = shopSrc.m_chz;

         shopSrc.m_shopname.clear(); // "";
         shopSrc.m_size = 0;
         shopSrc.m_chz = nullptr;
      }
      return *this;
   }

   CheeseShop::~CheeseShop() {
      for (size_t i = 0; i < m_size; i++) {
         delete m_chz[i];
      }
      delete[] m_chz;
   }

   CheeseShop& CheeseShop::addCheese(const Cheese& chz) {
      const Cheese** temp_chz = new const Cheese * [m_size + 1];
      size_t i = 0;
      for (i = 0; i < m_size; i++) {
         temp_chz[i] = new const Cheese(*m_chz[i]);
      }
      temp_chz[i] = new Cheese(chz); 

      for (i = 0; i < m_size; i++) {
         delete m_chz[i];
      }
      delete[] m_chz;

      m_chz = temp_chz;
      m_size++;

      return *this;
   }

   ostream& operator<<(ostream& os, const CheeseShop& chzShop) {
      os
         << "--------------------------" << endl
         << chzShop.m_shopname << endl
         << "--------------------------" << endl;
      if (chzShop.m_chz && chzShop.m_size > 0) { //.m_size > 0
         for (size_t i = 0; i < chzShop.m_size; i++) {
            if (chzShop.m_chz[i]) {
               os << *chzShop.m_chz[i];
            }
         }
         os << "--------------------------" << endl;
      }
      else {
         os
            << "This shop is out of cheese!" << endl
            << "--------------------------" << endl;
      }
      return os;
   }
}