// Workshop 8 - Smart Pointers

#ifndef SDDS_PROFILE_H
#define SDDS_PROFILE_H

#include <iomanip>
#include <string>
#include <fstream>

#include <regex>

namespace sdds {

	const int Address_postal_code_length = 7;

	struct Address {
		unsigned number;
		std::string street;
		std::string postal_code;

		bool load(std::ifstream& f) {
			f >> number >> street;
			char postal_code_temp[1 + Address_postal_code_length + 1] = { 0 };
			f.read(postal_code_temp, Address_postal_code_length + 1);
			postal_code = std::string(postal_code_temp + 1);
			return f.good();
		}

		friend std::ostream& operator<<(std::ostream& os, const Address& ad) {
			os << std::setw(10) << ad.number << " " 
				<< std::setw(10) <<  ad.street << " "
				<< std::setw(7) << ad.postal_code;
			return os;
		}
	};

	struct Name {
		std::string first_name;
		std::string last_name;
		bool load(std::ifstream& f) {
			f >> first_name >> last_name;
			return f.good();
		}

		friend std::ostream& operator<<(std::ostream& os, const Name& n) {
			os << std::setw(10) << n.first_name << std::setw(10) << n.last_name;
			return os;
		}
	};

	struct Profile {
		static int m_idGenerator;
		int m_id{++m_idGenerator};
		Name m_name;
		Address m_address;
		unsigned m_age;
		// this variable is used to print trace messages from
		//     constructors/destructor
		static bool Trace;

		Profile() = default;

		bool load(std::ifstream& f) {
			m_name.load(f);
			m_address.load(f);
			f >> m_age;
			return f.good();
		}

		Profile(const Name& name, const Address& addr, unsigned age) {
			this->m_name = name;
			this->m_address = addr;
			this->m_age = age;
			if (Profile::Trace)
				std::cout << "     C [" << m_id << "][" << this->m_name << "]" << std::endl;
		}

		Profile(const Profile& other) {
			this->m_name = other.m_name;
			this->m_address = other.m_address;
			this->m_age = other.m_age;
			// we add this constructor for tracing messages
			if (Profile::Trace)
				std::cout << "    CC [" << m_id << "][" << m_name << "] copy of [" << other.m_id << "]\n";
		}
		/*
		Profile(Profile&& other) noexcept {
			// Transfer the resources
			m_name = std::move(other.m_name);
			m_address = std::move(other.m_address);
			m_age = other.m_age;

			// Optionally, set the moved-from object to a valid but "empty" state
			other.m_age = 0;

			// Tracing message (optional)
			if (Profile::Trace)
				std::cout << "    MC [" << m_id << "][" << m_name << "] move from [" << other.m_id << "]\n";
		}

		Profile& operator=(Profile&& other) noexcept {
			if (this != &other) {  // Protect against self-assignment
				// Release any resources if needed

				// Transfer the resources
				m_name = std::move(other.m_name);
				m_address = std::move(other.m_address);
				m_age = other.m_age;

				// Optionally, set the moved-from object to a valid but "empty" state
				other.m_age = 0;

				// Tracing message (optional)
				if (Profile::Trace)
					std::cout << "    MA [" << m_id << "][" << m_name << "] move from [" << other.m_id << "]\n";
			}
			return *this;
		}
		*/

		~Profile() {
			if (Profile::Trace)
				std::cout << "    ~D [" << m_id << "][" << this->m_name << "]" << std::endl;
		}

		// add a function here to validate the address
		bool validateAddress() { // bool
			bool isValid{ true };
			// Regex for postal code validation (assuming ANA NAN format)
			std::regex postalCodeRegex("[A-Z][0-9][A-Z] [0-9][A-Z][0-9]");
			if (!std::regex_match(m_address.postal_code, postalCodeRegex) || m_address.number < 0) {
				isValid = false;
			}
			if (!isValid) {
				throw std::string("*** Invalid Address ***");
			}
			return isValid;
		}


		friend std::ostream& operator<<(std::ostream& os, const Profile& p) {
			os << std::setw( 5) << p.m_id
			   << std::setw(10) << p.m_name
			   << std::setw(10) << p.m_address
			   << std::setw( 5) << p.m_age;
			return os << std::endl;
		}
	};
	
	inline int Profile::m_idGenerator{};
}
#endif
