#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

/*
   OOP345 NFF WS01
   HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 11
*/
extern double g_discount; // HAS TO DEFINE IT OUTSIDE SDDS
extern double g_taxrate;

namespace sdds {

   const int CUST_NAME_SIZE = 10;   // Included NULL terminator
   const int RIDE_DESC_SIZE = 25;   // Included NULL terminator

   class RideRequest {
      char customerName[CUST_NAME_SIZE]{};
      char rideDesc[RIDE_DESC_SIZE]{};
      double priceOfRide{};         // Not yet taxed
      bool isDiscounted{};
   public:
      RideRequest();
      void read(std::istream& is);
      void display();
   };
}

#endif