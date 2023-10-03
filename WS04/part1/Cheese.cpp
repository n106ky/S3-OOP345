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
      string weight{}; // std::stoul() to unsigned long integer
      string price{}; // std::stod() change it back to double
      string features{};

      line = findStr(name, line);
      line = findStr(weight, line);
      line = findStr(price, line);
      features = line;

      //cout << "name     :|" << name<<'|' << endl;
      //cout << "weight   :|" << weight << '|' << endl;
      //cout << "price    :|" << price << '|' << endl;
      //cout << "features :|" << features << '|' << endl;

      // TRIM:
      //string trim_name{};
      //string trim_weight{};
      //string trim_price{};
      //string trim_features{};

      //trim_name = trimStr(name);
      //trim_weight = trimStr(weight);
      //trim_price = trimStr(price);
      //trim_features = changeStr(features);
      name = trimStr(name);
      weight = trimStr(weight);
      price = trimStr(price);
      features = changeStr(features);

      cout << "AFTER TRIM: " << endl;
      //cout << "name     :|" << trim_name << '|' << endl;
      //cout << "weight   :|" << trim_weight << '|' << endl;
      //cout << "price    :|" << trim_price << '|' << endl;
      //cout << "features :|" << trim_features << '|' << endl << endl;
      cout << "name     :|" << name<<'|' << endl;
      cout << "weight   :|" << weight << '|' << endl;
      cout << "price    :|" << price << '|' << endl;
      cout << "features :|" << features << '|' << endl << endl;
   }

   string Cheese::findStr(string& found, const string& str) {
      string line = str;
      size_t comma = line.find(',');
      //while (pos != std::string::npos) { // npos = not a position
      found = line.substr(0, comma);
      line.erase(0, comma + 1); // +1: erase ','
      //}
      return line;
   }
   //string Cheese::trimStr(const string& str) {
   //   size_t fCharPos = str.find_first_not_of(' ');
   //   size_t lCharPos = str.find_last_not_of(' ');
   //   return str.substr(fCharPos, (lCharPos - fCharPos + 1)); // substr(position of first character, length (how long) til the last char) | +1: position of first_char counts from 0.
   //}
   string Cheese::trimStr(string& str) {
      size_t fCharPos = str.find_first_not_of(' ');
      size_t lCharPos = str.find_last_not_of(' ');
      return str.substr(fCharPos, (lCharPos - fCharPos + 1));
   }

   //string Cheese::changeStr(const string& features) {
   //   string newFts = features;
   //   size_t space = newFts.find(' ');
   //   while (space != std::string::npos) {
   //      newFts.erase(space, 1);
   //      space = newFts.find(' ');
   //   }
   //   size_t comma = newFts.find(',');
   //   while (comma != std::string::npos) {
   //      newFts[comma] = ' ';
   //      comma = newFts.find(',');
   //   }
   //   return newFts;
   //}
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
      //if (chz) {

      //}

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

      // OLD:
      //size_t pos = line.find(',');
      //name = line.substr(0, pos);
      //line.erase(0, pos + 1);
      //pos = line.find(',');
      //weight = line.substr(0, pos);
      //line.erase(0, pos + 1);
      //pos = line.find(',');
      //price = line.substr(0, pos);
      //line.erase(0, pos + 1);
      //name = findStr(line);
      //weight = findStr(line);
      //price = findStr(line);
      //features = line;

      // ATTEMPT 1 - PROBLEM: CANNOT DEAL WITH MEMORY LEAK BECAUSE NO CONSTRUCTOR AND MEMBER VARIABLE HAS NO STRING* | AND ACTUALLY NOT NEEDED
      //string findStr(const string& str) {
      //   size_t num = 1;
      //   string *found = new string[num];
      //   size_t pos;
      //   while (pos = str.find(',')) {
      //      size_t i = 0;
      //   found[i] = str.substr(0, pos);
      //   found[i].erase(0, pos + 1);
      //   num++;
      //   }
      //   return *found;
      //}
*/