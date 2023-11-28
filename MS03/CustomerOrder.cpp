// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 13, 2023
// Modified					: NOV 28, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	size_t sdds::CustomerOrder::m_widthField{};
	/*
	+ A custom 1 - argument constructor that takes a reference to an unmodifiable string.
	+ This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance.
	+ The fields in the string are(separated by a delimiter) :
		- Customer Name
		- Order Name
		- The list of items making up the order(at least one item)
	+ After finishing extraction, this constructor updates CustomerOrder::m_widthField if the current value is smaller than the value stored in Utilities::m_widthField.
	*/
	CustomerOrder::CustomerOrder(const std::string& str) {
		//cout << str << endl;
		Utilities utils{};
		size_t pos{};
		bool more{};
		try {
			m_name = utils.extractToken(str, pos, more);
			m_orderName = utils.extractToken(str, pos, more);
			size_t savePos = pos;
			//cout << "m_name     : |" << m_name << "|" << endl;
			//cout << "m_orderName: |" << m_orderName << "|" << endl ;

			while (more) {
				utils.extractToken(str, pos, more);
				m_cntItem++;
			}
			//cout << "COUNT: " << m_cntItem << endl;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(utils.extractToken(str, savePos, more));
			}
			//for (size_t i = 0; i < m_cntItem; i++) {
			//	cout << m_lstItem[i] << endl;
			//}
			m_widthField = max(m_widthField, utils.getFieldWidth());
		}
		catch (const exception& e) {
			cerr << "Error: " << e.what() << endl;
		}
	}

	// RULE OF FIVE
		CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "ERROR: No Copy!";
	} 
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = std::move(src); 
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			// Delete existing resources
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			// Move all scalar members
			m_name = std::move(src.m_name);
			m_orderName = std::move(src.m_orderName);
			m_product = std::move(src.m_product);
			m_cntItem = src.m_cntItem;

			// Move the pointer and set src's pointer to nullptr
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;

			// Set the count of items in src to zero
			src.m_cntItem = 0;
		}
		return *this;
	}
		CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	
	//  returns true if all the items in the order have been filled; false otherwise
	bool CustomerOrder::isOrderFilled() const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				isFilled = false;
			}
		}
		return isFilled;
	}
	
	// returns true if all items specified by itemName have been filled.
	// If the item doesn't exist in the order, this query returns true.
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				isFilled = false;
			}
		}
		return isFilled;
	}

	/*
	* This modifier fills one item in the current order that the Station specified in the first parameter handles.
	+ if the order doesn't contain the item handled, this function does nothing
	+ if the order contains items handled, and the Station's inventory contains at least one item, this function fills the order with one single item. 
		- It subtracts 1 from the inventory and updates Item::m_serialNumber and Item::m_isFilled. 
		- It also prints the message     Filled NAME, PRODUCT [ITEM_NAME].
	+ if the order contains items handled but unfilled, and the inventory is empty, this function prints the message     Unable to fill NAME, PRODUCT[ITEM_NAME].
	+ all messages printed are terminated by an endline
	*/
	/*
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool itemFound = false;
		for (size_t i = 0; i < m_cntItem && !itemFound; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				itemFound = true;
				if (station.getQuantity() > 0) {
					// Update the serial number, status, and quantity
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
				}
			}
			if (itemFound) {
				os << setw(11) << right;
				m_lstItem[i]->m_isFilled ? os << "Filled " : os << "    Unable to fill ";
				os << m_name << ", " << m_orderName << " ["
					<< station.getItemName() << "]" << endl;
			}
		}
	}
	*/
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					// Update the serial number, status, and quantity
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					i = m_cntItem; // to stop printing
					os << "    Filled " << m_name << ", " << m_orderName << " [" << station.getItemName() << "]" << endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_orderName << " [" << station.getItemName() << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_orderName << endl;
			for (size_t i = 0; i < m_cntItem; i++) {
				os << "[" << setw(6) << right << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
					<< setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - "; // m_widthField
				m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";
				os << endl;
			}

	}

}