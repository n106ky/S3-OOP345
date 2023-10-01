#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

namespace sdds {
   template <typename T, size_t C>
   class Collection {
      // Private Instance Members
      T m_items[C]{};        // The items of the collection
      size_t m_size{};       // The current size of the collection (maximum number of items)

      // Private Class Members
      static T m_smallestItem;  // to store smallest item. Initialize to 9999 outside class.
      static T m_largestItem;   // to store largest item. Initialize to -9999 outside class.

   protected:
      // Protected Instance Members:
      void setSmallestItem(const T& item); // Updates m_smallestItem if the new item is smaller
      void setLargestItem(const T& item);  // Updates m_largestItem if the new item is larger

   public:
      Collection(); // Default constructor

      // Public Class Members
      static T getSmallestItem(); // Returns m_smallestItem
      static T getLargestItem();  // Returns m_largestItem

      // Public Instance Members
      size_t size() const;       // Returns current number of items
      size_t capacity() const;   // Returns the capacity of the collection

      bool operator+=(const T& item); // Adds an item and updates size and smallest/largest items
      void print(std::ostream& os) const; // Prints all items in the collection
   };

   // INITIALIZATION OUTSIDE CLASS:
   template <typename T, size_t C>
   T Collection<T,C>::m_smallestItem = 9999;
   template <typename T, size_t C>
   T Collection<T,C>::m_largestItem = -9999;

  
   // TEMPLATE SPECIALIZATIONS:
   template <>
   class Collection<Book, 10> {
      Book m_items[10]{};
      size_t m_size{};

      static Book m_smallestItem;
      static Book m_largestItem;
   };

   Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
   Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);














   ////////////////////////////////////////////////////////////////////////////////////////////////
   
   // PROTECTED PART II - PROTOTYPE:
   //T& operator[](size_t size);
   //void incrSize();
   // 
   // PROTECTED PART II - IMPLEMENTATION:
   //template <typename T, size_t C>
   //T& Collection<T, C>::operator[](size_t size) {
   //   return m_items[size];
   //}
   //template <typename T, size_t C>
   //void Collection<T, C>::incrSize() {
   //}











}

#endif
