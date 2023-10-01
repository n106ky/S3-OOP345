#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

namespace sdds {
   template <typename T, size_t C>
   class Collection {
      // *** PRIVATE INSTANCE MEMBERS ***
      T m_items[C]{};        // The items of the collection
      size_t m_size{};       // The current size of the collection (number of items)

      // *** PRIVATE CLASS MEMBERS ***
      static T m_smallestItem;  // to store smallest item. Initialize to 9999 outside class.
      static T m_largestItem;   // to store largest item. Initialize to -9999 outside class.

   protected:
      // *** PROTECTED INSTANCE MEMBERS ***:

      // Updates m_smallestItem if the new item is smaller
      void setSmallestItem(const T& item) {

      }

      // Updates m_largestItem if the new item is larger
      void setLargestItem(const T& item) {

      }

   public:
      // DEFAULT CONSTRUCTOR
      Collection(); 

      // *** PUBLIC CLASS MEMBERS ***
      
      // Returns m_smallestItem:
      static T getSmallestItem() {
         return m_smallestItem;
      }

      // Returns m_largestItem
      static T getLargestItem() {
         return m_largestItem;
      }

      // *** PUBLIC INSTANCE MEMBERS ***

      // Returns current number of items
      size_t size() const {
         return m_size;
      }

      // Returns the capacity of the collection
      size_t capacity() const {
         return C;
      }

      // Adds an item and updates size and smallest/largest items
      bool operator+=(const T& item) {

      }

      // Prints all items in the collection
      void print(std::ostream& os) const {

      }
   };

   // *** INITIALIZATION OUTSIDE CLASS ***:
   template <typename T, size_t C>
   T Collection<T,C>::m_smallestItem = 9999;
   template <typename T, size_t C>
   T Collection<T,C>::m_largestItem = -9999;

  
   // *** TEMPLATE SPECIALIZATIONS ***:
   template <>
   class Collection<Book, 10> {
      Book m_items[10]{};
      size_t m_size{};

      static Book m_smallestItem;
      static Book m_largestItem;
   };

   Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
   Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);


}

#endif
