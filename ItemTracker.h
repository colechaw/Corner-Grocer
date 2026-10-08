#pragma once
#include <string>
#include <map>

class ItemTracker {
	public:
		void printList();
		void printHistogram();
		void printMenu();
		void loadFile(std::string fileName);
		int searchForItem(std::string itemName);
		void printItemByName(std::string intemName);

	private:
		std::map<std::string, int> inventory_;

		// Functions
		void saveBackup();
		std::string toLower(std::string originalText);

};
