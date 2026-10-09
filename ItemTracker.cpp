#include "ItemTracker.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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

void ItemTracker::printItemByName(std::string itemName) {
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
	std::cout << "List\n" << std::endl;

	for (const auto& item : inventory_) {
		std::cout << " "
			<< std::left << std::setw(15) << item.first
			<< ": "
			<< item.second
			<< std::endl;
	}
}


// *****************************
// *****************************
// Sort by value high to low
// *****************************
// *****************************




// Prints histogram with * for each count
void ItemTracker::printHistogram() {
	std::string name;
	std::string line;
	int count;

	std::cout << "Histogram\n" << std::endl;

	for (const auto& item : inventory_) {
		name = item.first;
		count = item.second;
		line = std::string(count, '*');
		Color color = calculateColor(count);

		std::cout << " "
			<< std::left << std::setw(15) << name
			<< ": "
			<< TC.changeColor(color, line)
			<< std::endl;
	}
}

/*
Ternary operator, accept count and return the color to
quickly see if they have a low count in the store
*/
Color ItemTracker::calculateColor(int quantity) {
	return quantity < 4 ? Red :
		quantity < 7 ? Yellow : 
		Green;
}

// Accept input and return as all lower case to prevent
// errors in user capitaliztion
std::string toLower(std::string originalText) {
	return "";
}
