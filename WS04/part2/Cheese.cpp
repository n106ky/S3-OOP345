/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 3
   Modified on 2023 OCT 6
**************************************************************************** */
#include <iostream>
#include <iomanip>
#include <string>
#include "Cheese.h"
//#include <typeinfo>

using namespace std;
namespace sdds {
   Cheese::Cheese() {}
   Cheese::Cheese(const string& str) {

      string line = str;
      string name{};
      string weight{};  // std::stoul() to unsigned long integer
      string price{};   // std::stod() change it back to double
      string features{};

      line = findStr(name, line);
      line = findStr(weight, line);
      line = findStr(price, line);
      features = line;

      name = trimStr(name);
      weight = trimStr(weight);
      price = trimStr(price);
      features = changeStr(features);

      m_name = name;
      m_weight = stoul(weight);
      m_price = stod(price);
      m_features = features;
   }

   // COPY:
   Cheese::Cheese(const Cheese& chz) {
      *this = chz;
   }
   Cheese& Cheese::operator=(const Cheese& chz) {
      if (this != &chz) {
         m_name = chz.m_name;
         m_price = chz.m_price;
         m_weight = chz.m_weight;
         m_features = chz.m_features;
      }
      return *this;
   }

   string Cheese::findStr(string& found, const string& str) {
      string line = str;
      size_t comma = line.find(',');
      found = line.substr(0, comma);
      line.erase(0, comma + 1); // +1: erase ','
      return line;
   }
   string Cheese::trimStr(string& str) {
      size_t fCharPos = str.find_first_not_of(' ');
      size_t lCharPos = str.find_last_not_of(' ');
      return str.substr(fCharPos, (lCharPos - fCharPos + 1));
   }

   string Cheese::changeStr(string& features) {
      string newFts = features;
      size_t space = newFts.find(' ');
      while (space != std::string::npos) {
         newFts.erase(space, 1);
         space = newFts.find(' ');
      }
      size_t comma = newFts.find(',');
      while (comma != std::string::npos) {
         newFts[comma] = ' ';
         comma = newFts.find(',');
      }
      return newFts;
   }

   Cheese Cheese::slice(size_t weight){
      // Minus cheese, return the new cheese
      Cheese chz = *this;
      if (m_weight >= weight) {
         m_weight = m_weight - weight;
         chz.m_weight = weight;
      }
      else {
         // Set Empty
         chz.m_name = { "NaC" };
         chz.m_weight = 0;
         chz.m_price = 0;
         chz.m_features.clear();
      }
      return chz;
   }

   // GETTERS:
   string Cheese::getName() const {
      return m_name;
   }
   size_t Cheese::getWeight() const {
      return m_weight;
   }
   double Cheese::getPrice() const {
      return m_price;
   }
   string Cheese::getFeatures() const {
      return m_features;
   }

   ostream& operator<<(ostream& os, const Cheese& chz) {
      os
         << '|' << setw(21) << left << chz.getName()
         << '|' << setw(5) << chz.getWeight()
         << '|' << setw(5) << fixed << setprecision(2) << chz.getPrice()
         << '|' << setw(33) << right << chz.getFeatures() 
         << " |" << endl;
      return os;
   }
}