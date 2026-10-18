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

enum class Color { Red, Green, Yellow, Cyan, White, Reset };

// This class accepts a string, lets the user choose a color, then returns
// the string wrapped with ANSI code.  It will change the color first and
// set the color back to default after the message.
class AnsiColor {

    public:
        // Returns text wrapped in color codes. Original string is unchanged.
        // This will not print to screen, that is handled in the main().  
        // The color may be used in main or ItemTracker
        static std::string colorize(Color color, const std::string& text) {
            return getCode(color) + text + getCode(Color::Reset);
        }

    private:
        static std::string getCode(Color color) {

            switch (color) {
                case Color::Red:    return "\033[31m";
                case Color::Green:  return "\033[32m";
                case Color::Yellow: return "\033[33m";
                case Color::Cyan:   return "\033[36m";
                case Color::White:  return "\033[37m";
                case Color::Reset:  return "\033[0m";
            }

            return "\033[0m";
        }
};
