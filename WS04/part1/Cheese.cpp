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

      // DO WE NEED SAFE CHECK FOR DATA MEMBERS?
      m_name = name;
      m_weight = stoul(weight);
      m_price = stod(price);
      m_features = features;

      //cout << "name     :|" << m_name << '|' << endl;
      //cout << "weight   :|" << m_weight << '|' << endl;
      //cout << "price    :|" << m_price << '|' << endl;
      //cout << "features :|" << m_features << '|' << endl << endl;
      
      // TYPE CHECK
      //cout << "name     :|" << typeid(m_name).name() << '|' << endl;
      //cout << "weight   :|" << typeid(m_weight).name() << '|' << endl;
      //cout << "price    :|" << typeid(m_price).name() << '|' << endl;
      //cout << "features :|" << typeid(m_features).name() << '|' << endl << endl;
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
      Cheese chz;

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
      //os << "chz name     :|" << chz.getName() << '|' << endl;
      //os << "chz weight   :|" << chz.getWeight() << '|' << endl;
      //os << "chz price    :|" << chz.getPrice() << '|' << endl;
      //os << "chz features :|" << chz.getFeatures() << '|' << endl << endl;
      os
         << '|' << setw(21) << left << chz.getName()
         << '|' << setw(5) << chz.getWeight()
         << '|' << setw(5) << fixed << setprecision(2) << chz.getPrice()
         << '|' << setw(34) << right << chz.getFeatures() << endl;
      return os;
   }



}

/*
FOR LATER USE:
   // std::string cheeseAttributes[4]; // 4 for name, weight, price, and features
   //while (line.find(',')) {
   //}
   //const int NAME = 0;
   //const int WEIGHT = 1;
   //const int PRICE = 2;
   //const int FEATURES = 3;
   //cheeseAttributes[NAME] = "Buffalo Gouda";
   //cheeseAttributes[WEIGHT] = "500";
   //cheeseAttributes[PRICE] = "2.99";
   //cheeseAttributes[FEATURES] = "Sweet, Creamy";
   //enum CheeseAttributes { NAME, WEIGHT, PRICE, FEATURES };
   //cheeseAttributes[NAME] = "Buffalo Gouda";
   //cheeseAttributes[WEIGHT] = "500";
   //cheeseAttributes[PRICE] = "2.99";
   //cheeseAttributes[FEATURES] = "Sweet, Creamy";
*/