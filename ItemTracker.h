/*
 * Name:        Charles Cole
 * Course:      CS 210 - Programming Languages
 * Date:        10/10/2026
 * Project:     Corner Grocer
 * Description: Load a list of products, total that list into individual
 *              entires and allow the user to view a list by number or a
 *          	histogram.  Save the list as frequency.dat.
 */

#pragma once
#include <string>
#include <map>

class ItemTracker {
	public:
		void printMenu() const;
		void loadFile(std::string fileName);
		void runReport(int userInput);

	private:
		std::map<std::string, int> inventory_;

		// Private Functions
		void printItemByName();
		void printList() const;
		void printHistogram() const;
		void saveDat();
		std::string colorizeByQuantity(std::string text, int quantity) const;
		std::string toLower(std::string originalText);
};
