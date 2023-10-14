#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <string>

namespace sdds {

   template<typename T>
   class Collection {
      std::string m_name{};
      size_t m_size{};
      T* m_items{};

      /*
      A pointer to a function that returns void and receives two parameters of type const Collection<T>& and const T& in that order.
      This is the observer function (it observes an event): when an item has been added to the collection,
      the class Collection<T> will call this function informing the client about the addition.
      */
      void (*m_observer)(const Collection<T>&, const T&) {};



      // observer is the callback

   public:
      Collection() {}; // IF I HAVE TEMPLATE, I NEED TO HAVE DEFAULT CONSTRUCTOR
      Collection(const std::string& name) :m_name(name), m_size(0), m_items(nullptr), m_observer(nullptr) {};

      // RULE OF FIVE:
      Collection(const Collection& cSrc) = delete;
      Collection& operator=(const Collection& cSrc) = delete;
      Collection(const Collection&& cSrc) = delete;
      Collection& operator=(const Collection&& cSrc) = delete;
      ~Collection() {};

      // QUERIES:
      const std::string& name() const {
         return m_name;
      }
      size_t size() const {
         return m_size;
      }

      void setObserver(void (*observer)(const Collection<T>& collection, const T& item)) {
         m_observer = observer;
      }

      Collection<T>& operator+=(const T& item) {
         T* temp_items = new T[m_size + 1];
         if (this->operator[](item.title()) == nullptr) {
            size_t i = 0;
            for (i = 0; i < m_size; i++) {
               temp_items[i] = m_items[i];   // new T(m_items[i]);
            }
            temp_items[i] = item;            // new T(item);

            delete[] m_items;

            m_items = temp_items;
            m_size++;
            if (m_observer) {
               m_observer(*this, item);
            }
         }
         return *this;
      }

      T& operator[](size_t idx) const {
         /*
         returns the item at index idx.
         if the index is out of range, this operator throws an exception of type std::out_of_range with the message Bad index [IDX]. 
         Collection has [SIZE] items.. Use operator + to concatenate strings.
         */
         if (idx >= m_size) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
         }
         return m_items[idx];
      }
      T* operator[](const std::string& title) const {
         T *temp_items{};
         for (size_t i = 0; i < m_size; i++) {
            if (m_items[i].title() == title) {  // Assuming T has a member function title()
               temp_items = &m_items[i];
            }
         }
         return temp_items;  // If no matching title is found
      }
   };

   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Collection<T>& cSrc) {
      for (size_t i = 0; i < cSrc.size(); i++) {
         os << cSrc[i];
      }
      return os;
   }

}

#endif // !SDDS_COLLECTION_H