#pragma once
#include <string>
#include <map>
#include "Color.h"

class ItemTracker {
	public:
		void printList();
		void printHistogram();
		void printMenu();
		void loadFile(std::string fileName);
		int searchForItem(std::string itemName);
		void printItemByName(std::string intemName);
		Color calculateColor(int quantity);

	private:
		std::map<std::string, int> inventory_;

		// Functions
		void saveBackup();
		std::string toLower(std::string originalText);

};
