# Corner Grocer

CS 210 Project that allows a user to select from the following options:
1. Search for Product - uses a loop to find a matching name string in a map [string int]
2. Display List - writes a list to the screen of the items stored in the map and their quantity
3. Display Histogram - writes a list with colored bars representing the amount in inventory
4. Exit Program
5. 
The data is obtained from a file when the program begins and parsed into a map, then the parsed file is save with the .dat extension.

I created an error logger class to save to *.log files.  I am happy with the way it works, and can be successfully tests.  I think it’s a great addition to the project and to my future code and projects, designing it with OOP techniques allow me to work on it without touching the project it serves, and to attach it to future projects quickly.

I would have enhanced the program’s code to eliminate repetitive lines when producing the reports.  At this level I think it would have introduced the possibility of bugs and pushed the time to completion outside a realistic timetable.  The program functions without it, but I would have liked to reduced the bloat.

The most challenging part of this assignment was the search function.  It look a while to accomplish the function to change the word to lowercase.  I was familiar with languages that do that for entire words, but in this case I needed to write one that looped char to char and changed the case one letter at a time.

At the beginning of the class I admitted my weakness in I/O stream, and now I feel very comfortable.  I think future projects will benefit from the ability to write backup save files or simply load and parse files to get the information I need.  This is a great skill that I will carry forward.

The code was written to be easy to follow, and that was a major consideration when writing it.  The comments were in places over documented, but it was to help those who didn’t follow the way I thought.  I thought of each function as a way that could get and return data without being to tightly coupled to the program.
