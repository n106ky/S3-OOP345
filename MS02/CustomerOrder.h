// Name                 : Ka Ying, Chan
// Seneca Student ID    : 123231227
// Seneca email         : kchan151@myseneca.ca
// Date of completion   : NOV 13, 2023
//
// I confirm that I am the only author of this file and the content was created entirely by me.
#pragma once 
#include "Station.h"

namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src): m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};			// the name of the customer(e.g., John, Sara, etc)
		std::string m_orderName{};			// ADDED: orderName
		std::string m_product{};		// the name of the product being assembled(e.g., Desktop, Laptop, etc)
		size_t m_cntItem{};				// a count of the number of items in the customer's order
		Item** m_lstItem{};				// a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item(see below).This is the resource that your class must manage.
		static size_t m_widthField;	// the maximum width of a field, used for display purposes
	public:
		// Member Functions
		
		// default constructor
		CustomerOrder() {};

		/*
		+ A custom 1 - argument constructor that takes a reference to an unmodifiable string.
		+ This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance.
		+ The fields in the string are(separated by a delimiter) :
			- Customer Name
			- Order Name
			- The list of items making up the order(at least one item)
		+ After finishing extraction, this constructor updates CustomerOrder::m_widthField if the current value is smaller than the value stored in Utilities::m_widthField.
		*/
		CustomerOrder(const std::string&);

		// RULE OF FIVE
		CustomerOrder(const CustomerOrder&); // a CustomerOrder object should not allow copy operations.The copy constructor should throw an exception if called.
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&) noexcept; // a move constructor.This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
		CustomerOrder& operator=(CustomerOrder&&) noexcept; // a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
		~CustomerOrder();

		bool isOrderFilled() const; //  returns true if all the items in the order have been filled; false otherwise
		bool isItemFilled(const std::string& itemName) const; // returns true if all items specified by itemName have been filled.If the item doesn't exist in the order, this query returns true.
		
		/*
		* This modifier fills one item in the current order that the Station specified in the first parameter handles.
		+ if the order doesn't contain the item handled, this function does nothing
		+ if the order contains items handled, and the Station's inventory contains at least one item, this function fills the order with one single item. It subtracts 1 from the inventory and updates Item::m_serialNumber and Item::m_isFilled. It also prints the message     Filled NAME, PRODUCT [ITEM_NAME].
		+ if the order contains items handled but unfilled, and the inventory is empty, this function prints the message     Unable to fill NAME, PRODUCT[ITEM_NAME].
		+ all messages printed are terminated by an endline
		*/
		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;

	};
}
