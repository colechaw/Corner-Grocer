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
		void printItemByName();
		std::string colorLine(std::string text, int quantity);
		void runReport(int userInput);

	private:
		std::map<std::string, int> inventory_;

		// Functions
		void saveBackup();
		std::string toLower(std::string originalText);

};
