#include <iostream>
#include <iomanip>
#include <string>
#include "Cheese.h"

using namespace std;
namespace sdds {
   Cheese::Cheese() {}
   Cheese::Cheese(const string& str) {
      string line = str;

      string name{};
      string weight{};
      string price{};
      string features{};

     //while (line.find(',')) {
     // }

      size_t pos = line.find(',');
      name = line.substr(0, pos);
      line.erase(0, pos + 1);

      pos = line.find(',');
      weight = line.substr(0, pos);
      line.erase(0, pos + 1);

      pos = line.find(',');
      price = line.substr(0, pos);
      line.erase(0, pos + 1);

      pos = line.find(',');
      features = line.substr(0, pos);
      line.erase(0, pos + 1);


      cout << "name     |:" << name << endl;
      cout << "weight   |:" << weight << endl;
      cout << "price    |:" << price << endl;
      cout << "features |:" << features << endl;

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
      //if (chz) {

      //}

      return os;
   }



}