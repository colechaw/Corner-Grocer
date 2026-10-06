#include "ItemTracker.h"
#include <iostream>
#include <fstream>

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

void ItemTracker::printList() {
	std::cout << "\bList" << std::endl;

	for (const auto& item : inventory_) {
		std::cout << "  " << item.first << ": " << item.second << std::endl;
	}
}
void ItemTracker::printHistogram() {
	std::cout << "\bHistogram" << std::endl;

	for (const auto& item : inventory_) {
		std::cout << " " << item.first << ": " << std::string(item.second, '*') << std::endl;
	}
}
