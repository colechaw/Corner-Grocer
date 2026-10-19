/*
 * Name:        Charles Cole
 * Course:      CS 210 - Programming Languages
 * Date:        10/15/2026
 * Project:     Corner Grocer (Custom ANSI Colorer)
 * Description: Wrap string with ANSI color code to allow
 *              for coloring based on quantity.
 */

#pragma once
#include <string>

// ENUM so we don't rely on magic strings
enum class Color { Red, Green, Yellow };

// This class accepts a string, lets the user choose a color, then returns
// the string wrapped with ANSI code.  It will change the color first and
// set the color back to default after the message.
class AnsiColor {

    public:
        // Returns text wrapped in color codes. Original string is unchanged.
        static std::string colorize(Color color, const std::string& text) {
            return getCode(color) + text + "\033[0m";
        }

    private:
        static std::string getCode(Color color) {

            switch (color) {
                case Color::Red:    return "\033[31m";
                case Color::Green:  return "\033[32m";
                case Color::Yellow: return "\033[33m";
            }

            return "\033[0m";
        }
};
