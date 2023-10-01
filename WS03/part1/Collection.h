/* ****************************************************************************
   OOP345 NFF WS03
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 1
**************************************************************************** */

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <type_traits>  // for std::is_same<>
#include <iomanip>

namespace sdds {
   template <typename T, unsigned C>
   class Collection {
      // *** PRIVATE INSTANCE MEMBERS ***
      T m_items[C]{};        // The items of the collection
      size_t m_size{};       // The current size of the collection (number of items)

      // *** PRIVATE CLASS MEMBERS ***
      static T m_smallestItem;  // to store smallest item. Initialize to 9999 outside class.
      static T m_largestItem;   // to store largest item. Initialize to -9999 outside class.

   protected:
      // *** PROTECTED INSTANCE MEMBERS ***:
      // Check if T is double, then set precision
      void setPrec() const {
         if constexpr (std::is_same_v<T, double>) { 
            std::cout.setf(std::ios::fixed);
            std::cout.precision(1);
         }
      }

      // Updates m_smallestItem if the new item is smaller
      void setSmallestItem(const T& item) {
         if (item < m_smallestItem){
            setPrec();
            m_smallestItem = item;
         }
      }

      // Updates m_largestItem if the new item is larger
      void setLargestItem(const T& item) {
         if (item > m_largestItem){
            setPrec();
            m_largestItem = item;
         }
      }
   public:
      // *** PUBLIC CLASS MEMBERS ***
      static T getSmallestItem() {
         return m_smallestItem;
      }
      static T getLargestItem() {
         return m_largestItem;
      }
      // *** PUBLIC INSTANCE MEMBERS ***
      size_t size() const {
         return m_size; // Returns current number of items
      }
      size_t capacity() const {
         return C; // Returns the capacity of the collection
      }

      // Adds an item and updates size and smallest/largest items
      bool operator+=(const T& item) {
         bool updated = false;
         if (C > m_size) {
            m_items[m_size] = item;
            m_size++;
            setSmallestItem(item);
            setLargestItem(item);
            updated = true;
         }
         return updated;
      }


      // Prints all items in the collection
      void print(std::ostream& os) const {
         os << "[";
         for (size_t i = 0; i < m_size; i++) {
            os << m_items[i];
            if (i<m_size-1) {
               os << ',';
            }
         }
         os << "]";
         os << std::endl;
      }
   };

   // *** INITIALIZATION OUTSIDE CLASS ***:
   template <typename T, unsigned C>
   T Collection<T, C>::m_smallestItem = 9999;
   template <typename T, unsigned C>
   T Collection<T, C>::m_largestItem = -9999;

   // *** TEMPLATE SPECIALIZATIONS ***:
   template <>
   Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
   template <>
   Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

}

#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// JUST IN CASE I NEED IT BACK:

//template <>
//class Collection<Book, 10> {
//   Book m_items[10]{};
//   size_t m_size{};

//   static Book m_smallestItem;
//   static Book m_largestItem;
//};
