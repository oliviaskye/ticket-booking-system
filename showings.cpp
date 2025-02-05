#include <iostream>
#include <fstream>
#include <map>
#include <string>

int showings () {

    std::map <int, std::string> showings = {{1, "The Big Country"}, {2, "Monty Python and the Holy Grail"}, {3, "The Truman Show"}, {4, "Bambi II"}};
    std::cout << "Today's showings:\n";

    for (auto showing : showings) {
        std::cout << showing.first << ". " << showing.second << "\n";
    };
    std::cout << "-----------------------\n";

    return 0;
};
