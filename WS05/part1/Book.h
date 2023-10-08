/* ****************************************************************************
   OOP345 NFF WS05   | PROF. HONG HUANG   |

   KA YING, CHAN     | #123231227         | kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 8
**************************************************************************** */
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

namespace sdds {
   class Book {            // holds information about a single book.
      std::string m_author{};
      std::string m_title{};
      std::string m_country{};
      int m_year{};
      double m_price{};
      std::string m_desc{};     // a short summary of the book

      // OTHERS:
      std::string findStr(std::string& found, const std::string& str);
      std::string trimStr(std::string& str);
      // std::string changeStr(std::string& features);

   public:
      Book() {};
      Book(const std::string& strBook);      /* a constructor that receives a reference to an unmodifiable string that contains information about the book;
                                                this constructor extracts the information about the book from the string by parsing it
                                                and stores the tokens in the object's attributes.*/

      // RULE OF FIVE:
      //Book(const Book& bkSrc);
      //Book& operator=(const Book& bkSrc);
      //Book(const Book&& bkSrc);
      //Book& operator=(const Book&& bkSrc);
      //~Book();

      // QUERIES:
      const std::string& title() const;      // a query that returns the title of the book
      const std::string& country() const;    // a query that returns the publication country
      const size_t& year() const;            // a query that returns the publication year

      double& price(double rate);                       // a function that returns the price by reference, allowing the client code to update the price.

      friend std::ostream& operator<<(std::ostream& os, const Book& bkSrc); // But we should not use friend... 
   };

}
#endif // !SDDS_BOOK_H