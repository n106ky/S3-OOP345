/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 23
*/

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

namespace sdds {
   class Timer {

   public:
      std::chrono::steady_clock::time_point start_time;
      std::chrono::steady_clock::time_point end_time;
      void start();
      long long stop();
   };
}
#endif // !SDDS_TIMER_H
