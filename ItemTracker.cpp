#include "ItemTracker.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

using enum Color;
TextColor TC;

void ItemTracker::printMenu() {
	std::cout << "Welcome to Corner Grocer, select from the following options:\n" <<
		"  1. Search for product\n" <<
		"  2. View Inventory\n" <<
		"  3. View Inventory Histogram\n" <<
		"  4. Exit\n\n";
}

void ItemTracker::loadFile(std::string fileName) {
	std::ifstream inFS;
	std::string name;

	inFS.open(fileName);

	if (inFS.is_open()) {
		std::cout << "*** File successfully loaded.\n\n";
		while (!inFS.eof()) {

			inFS >> name;

			// Add to map, or increase count
			inventory_[name]++;

		}
	}
	else {
		std::cout << "Could NOT load.\n\n";
	}

	inFS.close();

	saveBackup(); // Create Dat File

}

void ItemTracker::saveBackup() {
	// frequency.dat
	std::ofstream oFS;

	oFS.open("frequency.dat");

	if (oFS.is_open()) {
		std::cout << "*** File successfully opened.\n\n";

			for (const auto& item : inventory_) {
				oFS << item.first << " ";
				oFS << item.second << std::endl;
			}

		oFS.close();
		std::cout << "File saved!";
	}
	else {
		std::cout << "Could NOT save.\n\n";
	}
}


void ItemTracker::printItemByName() {
	std::string itemName;

	std::cout << "Seach for Item\n" << std::endl;
	std::cout << " Type the item name: ";
	std::cin >> itemName;

	auto item = inventory_.find(itemName);

	// Compare the index of item against the last index of the inventory_
	// If those match, the item is empty, return a 'Item not found' message
	if (item != inventory_.end()) {
		std::cout << "  " << itemName << ": " << item->second << std::endl << std::endl;
	}
	else
	{
		std::cout << "  Item not found\n\n";
	}
}


// Prints the list with numeric count
void ItemTracker::printList() {
	
	// Title
	std::cout << "List\n" << std::endl;

	// Print each line, name and then the number on hand.
	// Center all numbers on each other for readability
	for (const auto& [name, quantity] : inventory_) {
		std::cout << " "
				  << std::left << std::setw(15) << name
				  << ": " << quantity
				  << "\n";
	}
	
}

// Accept the user input and evaluate which report to return
void ItemTracker::runReport(int userInput) {
	switch (userInput) {
		case 1:	printItemByName(); break;
		case 2:	printList(); break;
		case 3:	printHistogram(); break;
		case 4:	std::exit(0); // Exit program, no break required
		default: printMenu();
	}
}


// *****************************
// *****************************
// Sort by value high to low
// *****************************
// *****************************




// Prints histogram with * for each count
void ItemTracker::printHistogram() {
	// Title
	std::cout << "Histogram\n" << std::endl;


	for (const auto& [name, quantity] : inventory_) {

		
		//Color color = calculateColor(quantity);
		std::string line = std::string(quantity, '*');
		line = colorLine(line, quantity);

		std::cout << " "
			<< std::left << std::setw(15) << name
			<< ": " << line
			<< "\n";
	}
}



/*
Ternary operator, accept count and return the color to
quickly see if they have a low count in the store
*/
std::string ItemTracker::colorLine(std::string text, int quantity) {

	auto theColor = quantity < 4 ? Red :
		quantity < 7 ? Yellow : 
		Green;

	return TC.changeColor(theColor, text);
}



// Accept input and return as all lower case to prevent
// errors in user capitaliztion
std::string toLower(std::string originalText) {
	std::string result;

	for (char c : originalText) {
		result += std::tolower(c);
	}

	return result;
}

std::string toTitle(std::string originalText) {

	// Start with the toLower() we made so we do not need
	// to loop here.
	originalText = toLower(originalText);

	// Check to make sure it's not an empty string before
	// we try to manipulate addresses that do not exist
	if (originalText.empty())
		return originalText;
	
	// The first letter to uppercase, 
	originalText.at(0) = std::toupper(static_cast<unsigned char>(originalText.at(0)));

	return originalText;
}
