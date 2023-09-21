/*
   OOP345 NFF WS02
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Completed on 2023 SEP 21
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AirportModels.h"
using namespace std;
namespace sdds{
   
   ostream& Airport::write(ostream& os) const {
      // empty check
      if (os) {
         if (ap_code.empty() || ap_code == "") {
            cout << "Empty Airport";
         }
         else {
         cout
            << right << setw(20) << setfill('.') << "Airport Code : " << left << setw(30) << ap_code << endl
            << right << setw(20) << setfill('.') << "Airport Name : " << left << setw(30) << ap_name << endl
            << right << setw(20) << setfill('.') << "City : " << left << setw(30) << ap_city << endl
            << right << setw(20) << setfill('.') << "State : " << left << setw(30) << ap_state << endl
            << right << setw(20) << setfill('.') << "Country : " << left << setw(30) << ap_country << endl
            << right << setw(20) << setfill('.') << "Latitude : " << left << setw(30) << ap_lat << endl
            << right << setw(20) << setfill('.') << "Longitude : " << left << setw(30) << ap_long << endl;
         }
      }
         return os;
   }
   ostream& operator<< (ostream & os, const Airport & rA) {
      return rA.write(os);
   }

////////////////////////////////////////////////////////////////
   // CONSTRUCTORS:
   AirportLog::AirportLog() {}

   // int AirportLog::ap_count = 0;
   AirportLog::AirportLog(const char* filename) {
      // cout << "Constructing a log..." << endl;

      ifstream inFile(filename);

      if (!inFile.is_open()) {
         cout << "Cannot open file!" << endl;
      }
      else {
         // cout << "File opened successfully!" << endl;

         string lines;
         while (getline(inFile,lines)) {
            ap_count++;
         }
         ap_count--; // Skip the first line
         // cout << "Airport count: " << ap_count << endl; 
         
         // Dynamically allocate size of the airport array
         m_airport = new Airport[ap_count]; // NO AIRPORT*

         // Re-read the file
         inFile.clear();
         inFile.seekg(0);

         // Skip the first line
         string firstline;
         getline(inFile, firstline); 

         for (int i = 0; i < ap_count; i++) {
            getline(inFile, m_airport[i].ap_code, ',');
            getline(inFile, m_airport[i].ap_name, ',');
            getline(inFile, m_airport[i].ap_city, ',');
            getline(inFile, m_airport[i].ap_state, ',');
            getline(inFile, m_airport[i].ap_country, ',');
            inFile >> m_airport[i].ap_lat;
            inFile.ignore();
            inFile >> m_airport[i].ap_long;
            inFile.ignore();
            // m_airport[i].write(cout); // check if all record are well retrieved: ABE to YUM 322 records
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
         if (src.m_airport != nullptr) 
         {
            if (m_airport) {
               delete[] m_airport;
               m_airport = nullptr;
            }

            // DMA
            m_airport = new Airport[src.ap_count];

            // FOR-loop to assign
            for (size_t i = 0; i < src.ap_count; i++) {
               // Version I:
               m_airport[i].ap_code = src.m_airport[i].ap_code;
               m_airport[i].ap_name = src.m_airport[i].ap_name;
               m_airport[i].ap_city = src.m_airport[i].ap_city;
               m_airport[i].ap_state = src.m_airport[i].ap_state;
               m_airport[i].ap_country = src.m_airport[i].ap_country;
               m_airport[i].ap_lat = src.m_airport[i].ap_lat;
               m_airport[i].ap_long = src.m_airport[i].ap_long;

               // Version II:
               //!src.m_airport->ap_code.empty() ? m_airport->ap_code = src.m_airport->ap_code : m_airport->ap_code = nullptr;
               //!src.m_airport->ap_name.empty() ? m_airport->ap_name = src.m_airport->ap_name : m_airport->ap_name = nullptr;
               //!src.m_airport->ap_city.empty() ? m_airport->ap_city = src.m_airport->ap_city : m_airport->ap_city = nullptr;
               //!src.m_airport->ap_state.empty() ? m_airport->ap_state = src.m_airport->ap_state : m_airport->ap_state = nullptr;
               //!src.m_airport->ap_country.empty() ? m_airport->ap_country = src.m_airport->ap_country : m_airport->ap_country = nullptr;
               //src.m_airport->ap_lat != 0 ? m_airport->ap_lat = src.m_airport->ap_lat : m_airport->ap_lat = 0;
               //src.m_airport->ap_long != 0 ? m_airport->ap_long = src.m_airport->ap_long : m_airport->ap_long = 0;
            }
         }
      }
      return *this;
   }
   //AirportLog::AirportLog(AirportLog&& src) noexcept{
   //   *this = move(src);
   //}
   //AirportLog& AirportLog::operator=(AirportLog&& src) noexcept {
   //   if (this != &src) {
   //      // delete[] xxx;
   //      // ...
   //   }
   //   return *this;
   //}

   AirportLog::~AirportLog() {
      delete[] m_airport;
   }

   // METHODS:
   void AirportLog::addAirport(const Airport& ap) {
      Airport* temp_ap = new Airport[ap_count++];

      for (size_t i = 0; i < ap_count; i++) {
         temp_ap[i] = m_airport[i];
      }
      temp_ap[ap_count - 1] = ap;

      m_airport = temp_ap;
   }

   AirportLog& AirportLog::findAirport(const string& state, const string& country) {
      AirportLog* aLog{};
      if (!(state.empty()&&country.empty())){ // if empty, no need to find
         for (size_t i = 0; i < ap_count; i++) {
            if (state == m_airport[i].ap_state && country == m_airport[i].ap_country) {
               aLog->addAirport(m_airport[i]);
            }
         }
      }
      return *aLog;
   }

   Airport AirportLog::operator[](size_t index) { // Cannot &, because it need to copy?
      // cout << "Received index: " << index << endl;
      Airport ap{};
      if (m_airport) {
         if (index >= 0 && index <= ap_count) {
            ap = m_airport[index];
         }
      }
      //else {
      //   cout << "Empty airport in index function" << endl;
      //}
      return ap;
   }

   AirportLog::operator size_t() {
      return ap_count;
   }

   //AirportLog::operator bool() {
   //   return !(m_airport->ap_code.empty() && m_airport->ap_name.empty());
   //}
}