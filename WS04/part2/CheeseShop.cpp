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
            m_chz[i] = new Cheese(*(shopSrc.m_chz[i])); // WHY DO WE HAVE TO DO IT LIKE THIS??? WHY WE NEED TO CONSTRUCT?
         }
      }
      return *this;
   }
   CheeseShop::CheeseShop(CheeseShop&& shopSrc) noexcept { //  WHY noexcept? WHY SHOULD NOT THROW?
      *this = move(shopSrc);
   }

   /*
   CheeseShop& CheeseShop::operator=(CheeseShop&& shopSrc) noexcept { // ERROR WITH THIS CODE: DEBUG_HEAP.CPP - A breakpoint instruction (__debugbreak() statement or a similar call) was executed in WS04.exe.
      //if (this!=&shopSrc) {
      //   delete[] m_chz;
      //   m_shopname = shopSrc.m_shopname;
      //   shopSrc.m_shopname.clear();
      //   m_chz = shopSrc.m_chz;
      //   shopSrc.m_chz = nullptr;
      //}
      if (this != &shopSrc) {
         for (size_t i = 0; i < m_size; i++) {
            delete m_chz[i];
         }
         delete[] m_chz;
         m_shopname = shopSrc.m_shopname;
         shopSrc.m_shopname.clear();
         m_size = shopSrc.m_size;
         shopSrc.m_size = 0;
         m_chz = new const Cheese * [m_size]; //const
         for (size_t i = 0; i < m_size; i++) {
            m_chz[i] = new Cheese(*(shopSrc.m_chz[i]));
         }
         for (size_t i = 0; i < m_size; i++) {
            delete shopSrc.m_chz[i];
         }
         delete[] shopSrc.m_chz;
      }
      return *this;
   }
   */

   CheeseShop& CheeseShop::operator=(CheeseShop&& shopSrc) noexcept {
      // 0. Check if duplicated
      if (this != &shopSrc) {
         // 1. Delete current resources
         for (size_t i = 0; i < m_size; i++) {
            delete m_chz[i];
         }
         delete[] m_chz;

         // 2. Transfer ownership of shopSrc's resources
         m_shopname = move(shopSrc.m_shopname);
         m_size = shopSrc.m_size;   // SO WHY I DO NOT NEED move() HERE?
         m_chz = shopSrc.m_chz;     // AND HERE?

         // 3. Set shopSrc's members to default state
         shopSrc.m_shopname.clear();
         shopSrc.m_size = 0;
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
      // temp_chz[i] = chz; // NOT WORKING.
      // temp_chz[i] = &chz; // AM I USING MOVE()?
      temp_chz[i] = new Cheese(chz); // WHY WE NEED TO CONSTRUCT?

      //for (i = 0; i < m_size; i++) { // BIG QUESTION: WHY I DON'T NEED IT?????????
      //   delete m_chz[i];
      //}
      //delete[] m_chz;

      m_chz = temp_chz; // STH WRONG HERE, CANNOT STORE STRING PROPERLY // UPDATE: NTH IS WRONG HERE
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
            os // CAN I USE THE OPERATOR<< IN CHEESE MODULE?
               << '|' << setw(21) << left << chzShop.m_chz[i]->getName()
               << '|' << setw(5) << chzShop.m_chz[i]->getWeight()
               << '|' << setw(5) << fixed << setprecision(2) << chzShop.m_chz[i]->getPrice()
               << '|' << setw(33) << right << chzShop.m_chz[i]->getFeatures()
               << " |" << endl;
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

/*
ASK CHAT:

The function you've provided is the move assignment operator, which is meant to transfer ownership of resources from one object (shopSrc) to another (the current object). 
Given the nature of move semantics, we aim to achieve this transfer of ownership without unnecessary deep copying.

Your current implementation, however, is more akin to the copy assignment operator, especially this section:

   m_chz = new const Cheese * [m_size]; //const
   for (size_t i = 0; i < m_size; i++) {
       m_chz[i] = new Cheese(*(shopSrc.m_chz[i]));
   }

You're allocating new memory and creating deep copies of each Cheese object, which defeats the purpose of move semantics.

Here's how you can improve the move assignment operator for your CheeseShop class:

Delete the current resources of the object (the array and the Cheese objects it points to).
Transfer ownership of shopSrc's resources to the current object.
Set shopSrc's members to a default state to prevent double deletion.

This approach effectively transfers ownership without deep copying and ensures that the shopSrc object is left in a valid but unspecified state, 
which is the typical contract for moved-from objects.

Note: If Cheese objects have dynamically-allocated resources, make sure Cheese has an appropriate move constructor to prevent double deletions and other issues.

*/