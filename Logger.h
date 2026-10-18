/*
 * Name:        Charles Cole
 * Course:      CS 210 - Programming Languages
 * Date:        10/17/2026
 * Project:     Corner Grocer (Custom Event Logger)
 * Description: Open and log into an event.log or an error.log
 *				file to allow for testing and error tracking.
 */

#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

class Logger {
public:
	static void error(std::string message) {
		logEvent(message, "error.log");
	}

	static void event(std::string message) {
		logEvent(message, "event.log");
	}

private:
	// Log for file events for texting and tracking down errors
	static void logEvent(std::string message, std::string fileName) {
		std::ofstream oSteam;
		oSteam.open(fileName, std::ios::app);

		if (oSteam.is_open()) {
			oSteam << "[" << getTimestamp() << "] "
				<< message << '\n';
		}
	}

	// Helper to return time for custom event log
	static std::string getTimestamp() {
		std::time_t now = std::time(nullptr);
		std::tm localTime{};

		localtime_s(&localTime, &now);

		std::ostringstream stream;
		stream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

		return stream.str();
	}
};