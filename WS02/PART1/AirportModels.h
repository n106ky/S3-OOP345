/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 20
*/

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

namespace sdds {
   struct Airport { // stores data about a single airport
      std::string ap_code{};
      std::string ap_name{};
      std::string ap_city{};
      std::string ap_state{};
      std::string ap_country{};
      double ap_lat{};
      double ap_long{};
      std::ostream& write(std::ostream& os) const;
   };
   std::ostream& operator<<(std::ostream& os, const Airport& rA);

   ////////////////////////////////////////////////////////////

   class AirportLog{ // : public Airport, manages a collection of airports
      Airport* m_airport{}; // dynamic array of Airport objects and keep a count of how many are being stored.
      static int ap_count;
   public:
      AirportLog();
      AirportLog(const char* filename);

      // RULE OF FIVE:
      AirportLog(const AirportLog& src);
      AirportLog& operator=(const AirportLog& src);
      AirportLog(AirportLog&& src)noexcept;
      AirportLog& operator=(AirportLog&& src)noexcept;
      ~AirportLog();

      // operator bool();

      // METHODS:
      void read(const char* filename);
      void addAirport(const Airport& ap);
      AirportLog& findAirport(const std::string& state, const std::string& country);
      AirportLog& operator[](size_t ap);
      operator size_t();
   };
}


#endif
