/*
 * Name:        Charles Cole
 * Course:      CS 210 - Programming Languages
 * Date:        10/10/2026
 * Project:     Corner Grocer
 * Description: Load a list of products, total that list into individual
 *              entires and allow the user to view a list by number or a
 *          	histogram.  Save the list as frequency.dat.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <sstream>
#include "ItemTracker.h"
#include "Color.h"

void ItemTracker::printMenu() const {
	std::cout << "Welcome to Corner Grocer, select from the following options:\n\n" <<
		"  1. Search for product\n" <<
		"  2. View Inventory List\n" <<
		"  3. View Inventory Histogram\n" <<
		"  4. Exit Program\n\n";
}


void ItemTracker::loadFile(std::string fileName) {
	std::ifstream inFS;

	std::string name;

	inFS.open(fileName);

	if (inFS.is_open()) {

		logEvent(fileName + " successfully opened.");

		while (inFS >> name) {			
			inventory_[name]++; // Add to map, or increase count
		}

		// Log loading results
		if (inventory_.size() == 0) {
			logEvent("ERROR- no items loaded.");
		}
		else {
			logEvent(std::to_string(inventory_.size()) + " items successfully loaded.");
		}

		inFS.close();
		logEvent(fileName + " closed.");
		saveDat(); // Create Dat File
	}
	else {
		logEvent("ERROR- unable to open " + fileName);
	}
}


void ItemTracker::saveDat() {
	
	// Create a file 'frequency.dat' after opening a stream
	std::ofstream oFS;
	oFS.open("frequency.dat");
	logEvent("frequency.dat successfully created."); // log event

	if (oFS.is_open()) {

			for (const auto& item : inventory_) {
				oFS << item.first << " ";
				oFS << item.second << std::endl;
			}

		oFS.close();
		logEvent(std::to_string(inventory_.size()) + " items saved."); // log event
		logEvent("frequency.dat saved."); // log event
	}
	else {
		logEvent("ERROR: frequency.dat failed to open."); // log event
	}
}


void ItemTracker::printItemByName() {

	std::cout << "Search for Item\n" << std::endl;
	std::cout << " Type the item name: ";

	std::string itemName;
	std::cin >> itemName;

	// Define and populate a variable with the lower case name of the item searched for
	// This allows multiple capitalization to all return the correct value
	std::string searchName = toLower(itemName);

	// Loop through the inventory_ comparing the search word to the name in the map in
	// lower case form
	for (const auto& [name, quantity] : inventory_) {

		// ** Validation **
		// Display a meaningful message rather than blank page
		if (inventory_.empty()) {
			std::cout << "\nNo inventory data available.\n";
			return;
		}

		if (toLower(name) == searchName) {
			std::cout << " " << name << ": " << quantity << std::endl;
			return; // Item was found, exit so the Not Found line is not printed
		}
	}

	std::cout << " Item not found\n\n";
}


// Accept the user input and evaluate which report to return
void ItemTracker::runReport(int userInput) {
	switch (userInput) {
		case 1:	printItemByName(); break;
		case 2:	printList(); break;
		case 3:	printHistogram(); break;
	default: printMenu();
	}
}


// Prints the list with numeric count
void ItemTracker::printList() const {
	
	// Title
	std::cout << "Numeric List\n" << std::endl;

	// Print each line, name and then the number on hand.
	// Center all numbers on each other for readability
	for (const auto& [name, quantity] : inventory_) {


		// ** Validation **
		// Display a meaningful message rather than blank page
		if (inventory_.empty()) {
			std::cout << "\nNo inventory data available.\n";
			return;
		}

		std::cout << " "
				  << std::left << std::setw(15) << name
				  << ": " << quantity
				  << "\n";
	}
	
}



// Prints histogram with * for each count
void ItemTracker::printHistogram() const {
	// Title
	std::cout << "Histogram\n" << std::endl;


	for (const auto& [name, quantity] : inventory_) {
		
		// ** Validation **
		// Display a meaningful message rather than blank page
		if (inventory_.empty()) {
			std::cout << "\nNo inventory data available.\n";
			return;
		}

		std::cout << " "
			<< std::left << std::setw(15) << name
			<< ": " << colorizeByQuantity(std::string(quantity, '*'), quantity)
			<< "\n";
	}
}




/*
Ternary operator, accept count and return the color to
quickly see if they have a low count in the store
*/
std::string ItemTracker::colorizeByQuantity(std::string text, int quantity) const {

	auto color = quantity < 4 ? Color::Red :
		quantity < 7 ? Color::Yellow : 
		Color::Green;

	return AnsiColor::colorize(color, text);
}


// Accept input and return as all lower case to prevent
// errors in user capitaliztion
////////////////// cast<> Resoning handle unexpected behavior if char is negative
std::string ItemTracker::toLower(std::string originalText) {

	std::string result;

	for (unsigned char c : originalText) {
		result += static_cast<char>(std::tolower(c));
	}

	return result;
}


// Log for file events for texting and tracking down errors
void ItemTracker::logEvent(std::string message) {
	std::ofstream oSteam;
	oSteam.open("Event.log", std::ios::app);

	if (oSteam.is_open()) {
		oSteam << "[" << getTimestamp() << "] "
			<< message << '\n';
	}
}


// Helper to return time for custom event log
std::string ItemTracker::getTimestamp() {
	std::time_t now = std::time(nullptr);
	std::tm localTime{};

	localtime_s(&localTime, &now);

	std::ostringstream stream;
	stream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

	return stream.str();
}