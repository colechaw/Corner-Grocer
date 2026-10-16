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
#include <limits>
#include "ItemTracker.h"
#include "Color.h"

// Prototype
void clearScreen();
void pause(std::string message);
void error(std::string message);
int validateInput(std::string prompt);

int main() {
	int userSelection = 0;
	ItemTracker itemTracker;

	itemTracker.loadFile("items.txt");

	while (true) {

		clearScreen(); // Clear to display the menu
		itemTracker.printMenu();
		userSelection = validateInput("Enter menu choice: ");

		if (userSelection == 4) // Exit loop to exit program
			break;

		clearScreen(); // Clear to display report
		itemTracker.runReport(userSelection);

		pause("\nPress Enter to return to main menu...");

	}

	return 0;
}

int validateInput(std::string prompt) {
	int userInput;

	// Repeat prompt until valid selection
	while (true) {
		std::cout << prompt;
		std::cin >> userInput;

		// Make sure they entered a positive number less than 5
		if (!std::cin.fail() && userInput >= 1 && userInput <= 4) {
			return userInput;
		}
		else {

		}
		error("Please enter a valid menu choice"); // Custom helper
	}
}


// Helper : Clean up screen for user experience
void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// Helper : Stops the program for the user to view the report
void pause(std::string message) {
	std::cout << message;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

// Helper : Handles an input error by reseting the input stream
// Does not catch the error, simplifies recovering from it.
void error(std::string message) {
	
	std::cin.clear(); // Reset the input stream

	// Discard invalid input
	std::cin.ignore(
		std::numeric_limits<std::streamsize>::max(), '\n'
	);

	// Print a meaningful error message to help the user
	std::cout << TextColor::changeColor(Color::Red, message) << std::endl;
}
