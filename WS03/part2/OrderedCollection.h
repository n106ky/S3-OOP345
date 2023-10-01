/* ****************************************************************************
   OOP345 NFF WS03
   PROF. HONG HUANG

   KA YING, CHAN #123231227
   kchan151@myseneca.ca

   I have done all the coding by myself and only copied the code
   that my professor provided to complete my workshops and assignments.

   Completed on 2023 OCT 1
**************************************************************************** */

#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

namespace sdds {

	template <typename T, unsigned C>
	using CO = Collection<T, 72>;

   template <typename T>
	class OrderedCollection : public CO<T, 72> {
	public:

		bool operator+=(const T& item) {
			bool updated = CO<T,72>::operator+=(item);
			for (size_t i = 0; i < CO<T, 72>::size() - 1; i++) {
				for (size_t j = 0; j < CO<T, 72>::size() - i - 1; j++) {
					if (CO<T, 72>::operator[](j) > CO<T, 72>::operator[](j + 1)) {
						auto temp = CO<T, 72>::operator[](j);
						CO<T, 72>::operator[](j) = CO<T, 72>::operator[](j + 1);
						CO<T, 72>::operator[](j + 1) = temp;
					}
				}
			}
			return updated;
		}
	};
} 

#endif