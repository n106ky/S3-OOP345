// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

#include <vector>
#include <algorithm>

using namespace std;

namespace sdds {

	// TODO: Add your code here to build a collection of Profiles.
	//         The result should contain only profiles from `allProfiles`
	//         which are not in `bannedProfiles` using Raw Pointers.

	/*
	Implement the excludeRaw() function.
	This function compares the profiles in the two received DataBase objects.
	Two profiles are considered same if they have same age and name.

	+ For each profile from the first parameter that is not banned,
	+ your function allocates dynamic memory of Profile type and copies the profile.
	+ Your function then validates the Profile object (using validateAddress() you created above) and adds it to result.
	+ Your function returns a copy of result.
	*/

	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
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


}