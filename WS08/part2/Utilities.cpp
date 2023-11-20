/* ****************************************************************************
	OOP345 NFF WS08   | PROF. HONG HUANG   |
	KA YING, CHAN     | #123231227         | kchan151@myseneca.ca

	I have done all the coding by myself and only copied the code that
	my professor provided to complete my workshops and assignments.

	Completed on 2023 NOV 17
**************************************************************************** */
// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

#include <vector>
#include <string>

using namespace std;

namespace sdds {
	
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		// The result should contain only profiles from `allProfiles` which are not in `bannedProfiles` using Raw Pointers.

		bool isBanned = false;
		for (size_t i = 0; i < allProfiles.size(); i++) {
			isBanned = false;
			for (size_t j = 0; j < bannedProfiles.size() && !isBanned; j++) {
				if (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
					allProfiles[i].m_age == bannedProfiles[j].m_age) {
					isBanned = true;
				}
			}
			if (!isBanned) {
				Profile* newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				try {
					if (newProfile->validateAddress()) {
						result += newProfile;
						delete newProfile;
					}
				}
				catch (const std::string& msg) {
					delete newProfile;
					throw msg;
				}
			}
		}
		return result;
	}
	

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles` which are not in `bannedProfiles` using Smart Pointers.

		bool isBanned = false;
		for (size_t i = 0; i < allProfiles.size(); i++) {
			isBanned = false;
			for (size_t j = 0; j < bannedProfiles.size() && !isBanned; j++) {
				if (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
					allProfiles[i].m_age == bannedProfiles[j].m_age) {
					isBanned = true;
				}
			}
			
			if (!isBanned) {
				std::unique_ptr<Profile> newProfile = std::make_unique<Profile>(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				// or
				// std::unique_ptr<Profile> newProfile (new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));
				if (newProfile->validateAddress()) {
					result += move(newProfile);
				}
			}

			// reflect Q3:
			/*
			if (!isBanned) {
				auto newProfile = std::make_shared<Profile>(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				if (newProfile->validateAddress()) {
					result += newProfile;
				}
			}
			*/

		}
		return result;
	}
}
