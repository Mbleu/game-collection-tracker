#include "Collection.h"
#include <string>
#include <iostream>

int main()
{
    Collection collection;
    std::string command;

    // Loop while input stream in good state
    // Read command keywords and pass data to relevant functions
    while (std::cin >> command)
    {
        std::string data;
        std::getline(std::cin, data);

        if (command == "exit")              // exit command closes the program
            break;
        else if (command == "add")          // add game
            collection.add_game(data);
        else if (command == "remove")       // remove game
            collection.remove_game(data);
        else if (command == "list")         // list games
            collection.list_games();
        else
            std::cout << "Command unrecognised, disregarded." << std::endl;
    }
}