/*
 * Name:        Charles Cole
 * Course:      CS 210 - Programming Languages
 * Date:        09/25/2026
 * Project:     Airgead Banking
 * Description: Calculates investment growth with and without
 *              additional monthly deposits.
 */

#include <iostream>
#include "ItemTracker.h"
#include <limits>

// Prototype
void clearScreen();
void error(std::string message);
void pause(std::string message);
int validateInput(std::string prompt);

int main() {
	int userSelection = 0;
	ItemTracker itemTracker;

	itemTracker.loadFile("items.txt");

	while (userSelection != 4) {

		clearScreen();

		switch (userSelection) {
			case 0:
				break;

			case 1:
				break;

			case 2:
				itemTracker.printList();
				pause("Press Enter to return to main menu...");
				break;

			case 3:
				itemTracker.printHistogram();
				pause("Press Enter to return to main menu...");
				break;

			case 4:
				return 0;

			default:
				itemTracker.printMenu();
				error("Enter a valid choice: ");
		}

		clearScreen();
		itemTracker.printMenu();
		userSelection = validateInput("Enter menu choice: ");

	}

	return 0;
}

int validateInput(std::string prompt) {
	int userInput;

	// Repeat prompt until valid selection
	while (true) {
		std::cout << prompt;
		std::cin >> userInput;

		// Make sure they entered a positive number
		if (!std::cin.fail() && userInput < 5) {
			return userInput;
		}
		error("Please enter a positive number"); // Custom helper
	}
}

// Helper : Clean up screen for user experience
/*
Using your feedback, updated my code to check for OS then
accounted for Mac and Linux to clear the screen properly
*/
void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// Helper : colored error message, clear cin error
void error(std::string message) {
	std::cout << "\033[91m" << message << "\033[0m" << '\n';
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

void pause(std::string message) {
	std::cout << message;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}
