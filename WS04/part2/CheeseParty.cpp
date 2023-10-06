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

// PARTY RELATIONSHIP WITH CHEESE IS AGGREGATION => JUST HAVING THE ADDRESS OF IT.
// PARTY RELATIONSHIP WITH CHEESESHOP IS COMPOSITION => TOTAL CONTROL.

using namespace std;
namespace sdds {
   CheeseParty::CheeseParty() {}
   CheeseParty& CheeseParty::addCheese(const Cheese& chz) {
      /*
      Search in the array of already stored cheeses to find if the parameter is already in there (compare the address of the parameter with the addresses stored in the array).
      If the parameter is already in the array, this function does nothing.
      If the parameter is not in the array, this function resizes the array to make room for the parameter (if necessary) 
      And stores the address of the parameter in the array (your function should not make a copy of the parameter).
      */

      bool check = false;
      for (size_t i = 0; i < m_ptySize; i++) { // FIRST WE WANT TO FIND IF THE CHEESE IS INSIDE THE ARRAY.
         if (m_pChz[i] == &chz) {
            check = true;
         }
      }

      if (!check) {
         const Cheese** temp_chz = new const Cheese * [m_ptySize + 1];
         for (size_t i = 0; i < m_ptySize; i++) {
            temp_chz[i] = m_pChz[i];
         }
         //temp_chz[i] = new Cheese(chz); => SHOULDN'T MAKE COPY
         temp_chz[m_ptySize] = &chz;

         delete[] m_pChz;
         m_pChz = temp_chz;
         m_ptySize++;
      }
      return *this;
   }


   CheeseParty& CheeseParty::removeCheese() { // DIDN'T ASK CHAT.
      size_t reduceCnt = 0;
      for (size_t i = 0; i < m_ptySize; i++) {
         if (m_pChz[i]->getWeight() == 0) {
            m_pChz[i] = nullptr;
            for (size_t j = i+1; j < m_ptySize; j++) { // IF NOT CHANGING, THE FIRST ONE WILL BE NULLPTR AND CANNOT PRINT.
               if (m_pChz[j]->getWeight() != 0) {
                  m_pChz[i] = m_pChz[j];
               }
            }
            reduceCnt++;
         }
      }
      m_ptySize -= reduceCnt;

      const Cheese** tempChzArray = new Cheese * [m_ptySize];
      for (size_t i = 0; i < m_ptySize; i++) { // WHEN DO WE NEED FOR LOOP, WHEN WE DO NOT?
         tempChzArray[i] = m_pChz[i]; // FOR LOOP FOR DEEP COPY?
      }
      delete[] m_pChz;
      m_pChz = tempChzArray;

      return *this;
   }


   CheeseParty::CheeseParty(const CheeseParty& ptySrc) {
      *this = ptySrc;
   }
   CheeseParty& CheeseParty::operator=(const CheeseParty& ptySrc) {
      if (this != &ptySrc) {
         // Clean up old data
         // Note: Do NOT delete the individual Cheese objects
         delete[] m_pChz;
         m_ptySize = ptySrc.m_ptySize;
         m_pChz = new const Cheese * [m_ptySize];
         for (size_t i = 0; i < m_ptySize; i++) {
            m_pChz[i] = ptySrc.m_pChz[i]; 
         }
      }
      return *this;
   }

   /*
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
   */

   CheeseParty::CheeseParty(CheeseParty&& ptySrc) {
      *this = move(ptySrc);
   }
   CheeseParty& CheeseParty::operator=(CheeseParty&& ptySrc) {
      if (this != &ptySrc) {
         //for (size_t i = 0; i < m_ptySize; i++) { // SHOULD NOT CHANGE THE CHEESE MODULE
         //   delete m_pChz[i];
         //}
         delete[] m_pChz;

         m_ptySize = move(ptySrc.m_ptySize);
         m_pChz = move(ptySrc.m_pChz);

         ptySrc.m_ptySize = 0;
         ptySrc.m_pChz = nullptr;
      }
      return *this;
   }
   CheeseParty::~CheeseParty() {
      //for (size_t i = 0; i < m_ptySize; i++) { // SHOULD NOT CHANGE THE CHEESE MODULE
      //   delete m_pChz[i];
      //}
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