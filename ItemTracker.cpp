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
#include "Logger.h"

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
	int itemCount = 0;

	inFS.open(fileName);

	if (inFS.is_open()) {

		Logger::event(fileName + " successfully opened."); // log event

		while (inFS >> name) {			
			inventory_[name]++; // Add to map, or increase count
			itemCount++; // keep track of each 
		}

		// Log loading results
		if (itemCount == 0) {
			Logger::event("WARNING- no items loaded."); // log event
		}
		else {
			Logger::event(std::to_string(itemCount) + " items successfully parsed."); // log event
		}

		inFS.close();
		Logger::event(fileName + " closed."); // log event
		saveDat(); // Create Dat File
	}
	else {
		Logger::error("ERROR- unable to open " + fileName + " file"); // log ERROR
	}
}


void ItemTracker::saveDat() {
	
	// Create a file 'frequency.dat' after opening a stream
	std::ofstream oFS;
	oFS.open("frequency.dat");

	if (oFS.is_open()) {

		Logger::event("frequency.dat successfully created."); // log event

			for (const auto& item : inventory_) {
				oFS << item.first << " ";
				oFS << item.second << std::endl;
			}

		oFS.close();
		Logger::event(std::to_string(inventory_.size()) + " items saved."); // log event
		Logger::event("frequency.dat saved."); // log event
	}
	else {
		Logger::error("ERROR: frequency.dat failed to open."); // log ERROR
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

	// ** Validation **
	// Display a meaningful message rather than blank page
	if (inventory_.empty()) {
		std::cout << "\nNo inventory data available.\n";
		Logger::error("Empty inventory_ in Name Search"); // log ERROR
		return;
	}

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

	// ** Validation **
	// Display a meaningful message rather than blank page
	if (inventory_.empty()) {
		std::cout << "\nNo inventory data available.\n";
		Logger::error("Empty inventory_ in List Report"); // log ERROR
		return;
	}

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

	// ** Validation **
	// Display a meaningful message rather than blank page
	if (inventory_.empty()) {
		std::cout << "\nNo inventory data available.\n";
		Logger::error("Empty inventory_ in Histogram Report"); // log ERROR
		return;
	}

	for (const auto& [name, quantity] : inventory_) {
		

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


// Call char tolower() on each char in the string
// creating an easy way to capitalize entire strings
////////////////// cast<> Resoning handle unexpected behavior if char is negative
std::string ItemTracker::toLower(std::string originalText) {

	std::string result;

	for (unsigned char c : originalText) {
		result += static_cast<char>(std::tolower(c));
	}

	return result;
}