/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 18
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AirportModels.h"
using namespace std;
namespace sdds{
   ostream& Airport::write(ostream& os) const {
      if (os) {
         cout
            << right << setw(20) << setfill('.') << "Airport Code : " << left << setw(30) << ap_code << endl
            << right << setw(20) << setfill('.') << "Airport Name : " << left << setw(30) << ap_name << endl
            << right << setw(20) << setfill('.') << "City : " << left << setw(30) << ap_city << endl
            << right << setw(20) << setfill('.') << "State : " << left << setw(30) << ap_state << endl
            << right << setw(20) << setfill('.') << "Country : " << left << setw(30) << ap_country << endl
            << right << setw(20) << setfill('.') << "Latitude : " << left << setw(30) << ap_lat << endl
            << right << setw(20) << setfill('.') << "Longitude : " << left << setw(30) << ap_long << endl;
      }
      return os;
   }
   ostream& operator<< (ostream & os, const Airport & rA) {
      return rA.write(os);
   }

////////////////////////////////////////////////////////////////
      // CONSTRUCTORS:
   AirportLog::AirportLog() {}
   AirportLog::AirportLog(const char* filename) {
      read(filename);
   }

   // RULE OF FIVE:
   AirportLog::AirportLog(const AirportLog& src) {
      *this = src;
   }
   AirportLog& AirportLog::operator=(const AirportLog& src) {
      if (this != &src) {
         ap_code = src.ap_code;
         ap_name = src.ap_name;
         ap_city = src.ap_city;
         ap_state = src.ap_state;
         ap_country = src.ap_country;
         ap_lat = src.ap_lat;
         ap_long = src.ap_long;
      }
      return *this;
   }
   AirportLog::AirportLog(AirportLog&& src) noexcept{

   }
   AirportLog& AirportLog::operator=(AirportLog&& src) noexcept {

      return *this;
   }

   //AirportLog::operator bool() {
   //   return 1;
   //}

   // Move constr / assign
   /*
   Playdoh(Playdoh&& src) {
      cout << "Playdoh MoveConstr" << endl;
      *this = std::move(src); // note the move call
   }

   Playdoh& operator=(Playdoh&& src) {
      cout << "Playdoh MoveA" << endl;
      if (this != &src) {
         delete[] colour;
         colour = src.colour;
         src.colour = nullptr;
         weight = src.weight;
         src.weight = 0;
      }
      return *this;
   }
   */
   AirportLog::~AirportLog() {

   }

   // METHODS:
   void AirportLog::read(const char* filename) {
      ifstream inFile(filename);
      if (!inFile.is_open()) {
         cout << "Cannot open file!";
      }
      else {
         string firstline;
         getline(inFile, firstline); // Skip the first line

         while (inFile) {
            getline(inFile, ap_code, ',');
            getline(inFile, ap_name, ',');
            getline(inFile, ap_city, ',');
            getline(inFile, ap_state, ',');
            getline(inFile, ap_country, ',');
            inFile>> ap_lat;
            inFile >> ap_long;
         }
      }

   }
   void AirportLog::addAirport(const Airport& ap) {

   }
   AirportLog& AirportLog::findAirport(const string& state, const string& country) {
      return *this;
   }
   AirportLog& AirportLog::operator[](size_t ap) {
      return *this;
   }
   AirportLog::operator size_t() {
      return 1;
   }
}