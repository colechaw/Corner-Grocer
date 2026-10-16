#pragma once
#include <string>
#include <map>
#include "Color.h"

class ItemTracker {
	public:
		void printList();
		void printHistogram();
		void printMenu();
		void printItemByName();
		void loadFile(std::string fileName);
		void runReport(int userInput);

	private:
		std::map<std::string, int> inventory_;

		// Private Functions
		void saveDat();
		std::string colorLine(std::string text, int quantity);
		std::string toLower(std::string originalText);
};
