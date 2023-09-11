/*
   OOP345 NFF WS01
   HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 11
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "RideRequest.h"
using namespace std;

double g_discount;
double g_taxrate;
static int counter = 1;

namespace sdds {
   RideRequest::RideRequest() {}
   void RideRequest::read(istream& is) {
      char tempDiscount{};
      if (is.good()) {
         is.getline(customerName, CUST_NAME_SIZE, ',');
         is.getline(rideDesc, RIDE_DESC_SIZE, ',');
         is >> priceOfRide;
         is.ignore();
         is >> tempDiscount;
      }
      if (tempDiscount == 'Y') {
         isDiscounted = true;
      }
      else {
         isDiscounted = false;
      }
   }
   void RideRequest::display() {
      cout
         << left << setw(2) << counter++ << ". ";
      if (customerName[0] != '\0') {
         cout
            << left << setw(10) << customerName << "|"
            << left << setw(25) << rideDesc << "|"
            << fixed << setprecision(2) << setw(12) << priceOfRide * (1 + g_taxrate) << "|";
         if (isDiscounted) {
            cout << right << setw(13) << priceOfRide * (1 + g_taxrate) - g_discount << endl;
         }
         else {
            cout << endl;
         }
      }
      else {
         cout << "No Ride Request" << endl;
      }

   }
}