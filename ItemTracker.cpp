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
#include <cctype>
#include "ItemTracker.h"
#include "Color.h"

using enum Color;

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
		std::cout << "*** File successfully loaded.\n\n";
		while (inFS >> name) {

			inFS >> name;

			// Add to map, or increase count
			inventory_[name]++;
		}
	}

	inFS.close();

	saveDat(); // Create Dat File

}


void ItemTracker::saveDat() {
	
	// Create a file 'frequency.dat' after opening a stream
	std::ofstream oFS;
	oFS.open("frequency.dat");

	if (oFS.is_open()) {

			for (const auto& item : inventory_) {
				oFS << item.first << " ";
				oFS << item.second << std::endl;
			}

		oFS.close();
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
		
		// Check if the inventory_ object, display meaningful 
		// message instead of blank screen
		////////////// Considered inventory_.size == 0 but went for 
		////////////// the shorter way
		if (inventory_.empty()) {
			std::cout << "No inventory data available.\n";
			return;
		}
		//std::string line = std::string(quantity, '*');
		//line = colorizeByQuantity(line, quantity);

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

	auto theColor = quantity < 4 ? Red :
		quantity < 7 ? Yellow : 
		Green;

	return TextColor::changeColor(theColor, text);
}


// Accept input and return as all lower case to prevent
// errors in user capitaliztion
std::string ItemTracker::toLower(std::string originalText) {
	std::string result;

	for (char c : originalText) {
		result += std::tolower(c);
	}

	return result;
}
