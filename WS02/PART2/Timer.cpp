/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 23
*/

#include "Timer.h"

namespace sdds {
   void Timer::start() {
      start_time = std::chrono::steady_clock::now();
   }

   long long Timer::stop() {
      end_time = std::chrono::steady_clock::now();
      auto timetook = end_time - start_time;
      return timetook.count();
   }
}