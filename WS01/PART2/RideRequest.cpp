/*
   OOP345 NFF WS01
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 12
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "RideRequest.h"
using namespace std;

double g_discount;
double g_taxrate;

namespace sdds {
   RideRequest::RideRequest() {}
   void RideRequest::read(istream& is) {
      char tempDiscount{};
      string tempRideDesc{};
      if (is.good()) {
         is.getline(customerName, CUST_NAME_SIZE, ',');
         getline(is, tempRideDesc, ',');  // is.getline(rideDesc, RIDE_DESC_SIZE, ',');
         is >> priceOfRide;
         is.ignore();
         is >> tempDiscount;
         // is.ignore(); // ">>" will automatically skip whitespace characters, including newline characters ('\n')
         if (rideDesc) {
            delete[] rideDesc;
            rideDesc = nullptr;
         }
         // rideDesc = tempRideDesc.c_str(); // shallow copying
         //for (int i = 0; i < tempRideDesc.length(); i++) {
         //   rideDesc[i] = tempRideDesc.c_str()[i];
         //}
         //rideDesc[tempRideDesc.length()] = '\0';
         rideDesc = new char[tempRideDesc.length() + 1];
         strcpy(rideDesc, tempRideDesc.c_str());
         if (tempDiscount == 'Y') {
            isDiscounted = true;
         }
         else if (tempDiscount == 'N') {
            isDiscounted = false;
         }
      }
   }
   void RideRequest::display() {
      static int counter = 1;
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
   RideRequest::operator bool() const {
      return (customerName && customerName[0] != '\0');
   }
   RideRequest::RideRequest(const RideRequest& src) {
      *this = src;
   }
   RideRequest& RideRequest::operator=(const RideRequest& src) {
      if (this != &src) {
         if (src) {
            if (rideDesc) {
               delete[] rideDesc;
               rideDesc = nullptr;
            }
            rideDesc = new char[strlen(src.rideDesc) + 1];
            strcpy(rideDesc, src.rideDesc);
            strcpy(customerName, src.customerName);
            priceOfRide = src.priceOfRide;
            isDiscounted = src.isDiscounted;
         }
      }
      return *this;
   }
   RideRequest::~RideRequest() {
      delete[] rideDesc;
   }
}