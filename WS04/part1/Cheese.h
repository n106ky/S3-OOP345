#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

namespace sdds {
   class Cheese {
      std::string m_name{ "NaC" }; // "Not a Cheese"
      size_t m_weight{};      // the weight/amount in grams of the cheese
      double m_price{};       // the price per gram of the cheese
      std::string m_features{};    // a description of the features/qualities of the cheese

      std::string findStr(std::string& found, const std::string& str);
      std::string trimStr(const std::string& str);
      std::string changeStr(const std::string& features);
   public:
      Cheese();
      Cheese(const std::string& str);

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