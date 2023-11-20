/* ****************************************************************************
	OOP345 NFF WS08   | PROF. HONG HUANG   |
	KA YING, CHAN     | #123231227         | kchan151@myseneca.ca

	I have done all the coding by myself and only copied the code that
	my professor provided to complete my workshops and assignments.

	Completed on 2023 NOV 17
**************************************************************************** */
#ifndef SDDS_DATABASE_H
#define SDDS_DATABASE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
    template <typename T>
    class DataBase {
		std::vector<T> database;
		// reflect Q3:
		// std::vector<std::shared_ptr<T>> databaseii;

	public:
		DataBase() { }
		DataBase(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
            while (file) {
                T e;
				try {
					if (e.load(file))
						database.push_back(T(e));
				}
				catch (...) {
					break;
				}
            }
		}
		size_t size() const { return database.size(); }
		const T& operator[](size_t i) const { return database[i]; }

		// Overload the += operator with a raw pointer as a second operand.
		DataBase& operator+=(const T* obj) { // DataBase&, if use DataBase it will make another copy
			database.push_back(*obj);
			return *this;
		}

		// TODO: Overload the += operator with a smart pointer as a second operand.
		DataBase& operator+=(const std::unique_ptr<T>& obj) { // uniqueptr cannot be copied, cannot copied by value.
			database.push_back(*obj);
			return *this;
		}

		// reflect Q3:
		/*
		DataBase& operator+=(const std::shared_ptr<T>& obj) {
			databaseii.push_back(obj);
			return *this;
		}
		*/

		// reflect Q4:
		// database.push_back(std::move(*obj));

		void display(std::ostream& os) const {
            os << std::fixed << std::setprecision(2);
			for (auto& e : database)
				os << e;
        }
	};

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const DataBase<T>& db) {
		db.display(os);
		return os;
	}
}
#endif