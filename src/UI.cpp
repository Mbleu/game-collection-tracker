#include "UI.h"
#include <iostream>

// UI constructor. Stores reference to a collection.
UI::UI(Collection &collection)
    : collection{collection}, exit{false} {}

// Runs the UI
void UI::run()
{
    while(!exit)
    {
        std::string user_input{get_input()};
        handle_input(user_input);
    }
}

// Waits for user input from console and returns it
std::string UI::get_input() const
{
    std::string user_input;
    if (!std::getline(std::cin, user_input))
        throw "Input stream entered bad state";
    return user_input;
}

void UI::handle_input(const std::string& user_input)
{
    std::istringstream iss{user_input};
    std::string command;
    std::string data;
    iss >> command;

    // Read command keywords and pass data to relevant functions
        
    std::getline(std::cin, data);

    if (command == "exit")              // exit command closes the program
        exit = true;
    else if (command == "add")          // add game
        collection.add_game(data);
    else if (command == "remove")       // remove game
        collection.remove_game(data);
    else if (command == "list")         // list games
    {
        const auto &games{collection.get_games()};

        if (games.empty())
            std::cout << "No games to list." << std::endl;

        for(const auto &game : games)
            std::cout << game.get_title() << std::endl;
    }

    else
        std::cout << "Command unrecognised, disregarded." << std::endl;
}