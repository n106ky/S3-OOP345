/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 20
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
         cout << endl; // DELETE THIS LINE AFTER
      }
      return os;
   }
   ostream& operator<< (ostream & os, const Airport & rA) {
      return rA.write(os);
   }
   int AirportLog::ap_count = 0;
////////////////////////////////////////////////////////////////
   // CONSTRUCTORS:
   AirportLog::AirportLog() {}

   AirportLog::AirportLog(const char* filename) {
      cout << "Constructing a log..." << endl;

      ifstream inFile(filename);

      if (!inFile.is_open()) {
         cout << "Cannot open file!" << endl;
      }
      else {
         cout << "File opened successfully!" << endl;

         string lines;
         while (getline(inFile,lines)) {
            ap_count++;
         }
         cout << "Airport count: " << ap_count -1 << endl; // Skip the first line: 322

         // Dynamically allocate size of the airport array
         Airport* m_airport = new Airport[ap_count - 1];

         // Re-read the file
         inFile.clear();
         inFile.seekg(0);

         // Skip the first line
         string firstline;
         getline(inFile, firstline); 

         for (int i = 0; i < ap_count -1 ; i++) {
            getline(inFile, m_airport[i].ap_code, ',');
            getline(inFile, m_airport[i].ap_name, ',');
            getline(inFile, m_airport[i].ap_city, ',');
            getline(inFile, m_airport[i].ap_state, ',');
            getline(inFile, m_airport[i].ap_country, ',');
            inFile >> m_airport[i].ap_lat;
            inFile.ignore();
            inFile >> m_airport[i].ap_long;
            inFile.ignore();
            m_airport[i].write(cout);
         }
         inFile.close();
      }
   }

   // RULE OF FIVE:
   AirportLog::AirportLog(const AirportLog& src) {
      *this = src;
   }
   AirportLog& AirportLog::operator=(const AirportLog& src) {
      if (this != &src) {
      // ...
      }
      return *this;
   }
   AirportLog::AirportLog(AirportLog&& src) noexcept{
      *this = move(src);
   }
   AirportLog& AirportLog::operator=(AirportLog&& src) noexcept {
      if (this != &src) {
         // delete[] xxx;
         // ...
      }
      return *this;
   }
   //AirportLog::operator bool() {
   //   return ???;
   //}

   AirportLog::~AirportLog() {
      delete[] m_airport;
   }

   // METHODS:
   //void AirportLog::read(const char* filename) {

   //}

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