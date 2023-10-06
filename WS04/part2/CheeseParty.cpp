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
#include "CheeseParty.h"

using namespace std;
namespace sdds {
   CheeseParty::CheeseParty() {}
   CheeseParty& CheeseParty::addCheese(const Cheese& chz) {
      const Cheese** temp_chz = new const Cheese*[m_ptySize + 1];
      size_t i = 0;
      for (i = 0; i < m_ptySize; i++) {
         temp_chz[i] = m_pChz[i];
      }
      temp_chz[i] = new Cheese(chz);

      m_pChz = temp_chz;
      m_ptySize++;

      return *this;
   }
   CheeseParty& CheeseParty::removeCheese() {

      return *this;
   }



   CheeseParty::CheeseParty(const CheeseParty& ptySrc) {
      *this = ptySrc;
   }
   CheeseParty& CheeseParty::operator=(const CheeseParty& ptySrc) {
      if (this != &ptySrc){
         for (size_t i = 0; i < m_ptySize; i++) {
            delete m_pChz[i];
         }
         delete[] m_pChz;
         m_ptySize = ptySrc.m_ptySize;
         m_pChz = new const Cheese * [m_ptySize];
         for (size_t i = 0; i < m_ptySize; i++) {
            m_pChz[i] = new Cheese(*(ptySrc.m_pChz[i]));
         }
      }
      return *this;
   }
   CheeseParty::CheeseParty(CheeseParty&& ptySrc) {
      *this = move(ptySrc);
   }
   CheeseParty& CheeseParty::operator=(CheeseParty&& ptySrc) {
      if (this != &ptySrc) {
         for (size_t i = 0; i < m_ptySize; i++) {
            delete m_pChz[i];
         }
         delete[] m_pChz;

         m_ptySize = move(ptySrc.m_ptySize);
         m_pChz = move(ptySrc.m_pChz);

         ptySrc.m_ptySize = 0;
         ptySrc.m_pChz = nullptr;
      }
      return *this;
   }
   CheeseParty::~CheeseParty() {
      for (size_t i = 0; i < m_ptySize; i++) {
         delete m_pChz[i];
      }
      delete[] m_pChz;
   }

   ostream& operator<<(ostream& os, const CheeseParty& ptySrc) {
      os
         << "--------------------------" << endl
         << "Cheese Party" << endl
         << "--------------------------" << endl;
      if (ptySrc.m_ptySize > 0) {
         for (size_t i = 0; i < ptySrc.m_ptySize; i++) {
            os // CAN I USE THE OPERATOR<< IN CHEESE MODULE?
               << '|' << setw(21) << left << ptySrc.m_pChz[i]->getName()
               << '|' << setw(5) << ptySrc.m_pChz[i]->getWeight()
               << '|' << setw(5) << fixed << setprecision(2) << ptySrc.m_pChz[i]->getPrice()
               << '|' << setw(33) << right << ptySrc.m_pChz[i]->getFeatures()
               << " |" << endl;
         }
         os << "--------------------------" << endl;
      }
      else {
         os
            << "This party is just getting started!" << endl
            << "--------------------------" << endl;
      }
      return os;
   }







}