/* ****************************************************************************
   OOP345 NFF WS04
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 3
**************************************************************************** */
#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

namespace sdds {
   class Cheese {
      std::string m_name{ "NaC" };  // "Not a Cheese"
      size_t m_weight{};            // the weight/amount in grams of the cheese
      double m_price{};             // the price per gram of the cheese
      std::string m_features{};     // a description of the features/qualities of the cheese

      // UPGRADE: Can we find and trim in one step?
      std::string findStr(std::string& found, const std::string& str);
      std::string trimStr(std::string& str);
      std::string changeStr(std::string& features);

   public:
      Cheese();
      Cheese(const std::string& str);

      // Copy:
      Cheese(const Cheese& chz);
      Cheese& operator=(const Cheese& chz);

      Cheese slice(size_t weight);

      // GETTERS:
      std::string getName() const;
      size_t getWeight() const;
      double getPrice() const;
      std::string getFeatures() const;
   };

   // HELPER FUNCTIONS:
   std::ostream& operator<<(std::ostream& os, const Cheese& chz);

}

#endif