#include "UI.h"
#include <iostream>
#include <sstream>

// UI constructor. Stores reference to a collection.
UI::UI(Collection &collection)
    : collection{collection}, exit{false} {}

// Runs the UI
void UI::run()
{
    handle_output("Collection tracker running, please enter commands.");

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

void UI::handle_output(const std::string &user_output) const
{
    std::cout << user_output << std::endl;
}

void UI::handle_input(const std::string& user_input)
{
    // Split user input into command and data
    std::istringstream iss{user_input};
    std::string command;
    std::string data;
    iss >> command;
    std::getline(iss >> std::ws, data);

    // Call function based on command
    if (command == "exit")                          // exit, close the program
        exit = true;
    else if (command == "add")                      // add game
    {
        auto result{collection.add_game(data)};
        if (result)
            handle_output(data + "added.");
        else
            handle_output(result.error());
    }
    else if (command == "remove")                   // remove game
    {
        auto result{collection.remove_game(data)};
        if (result)
            handle_output(data + "removed.");
        else
            handle_output(result.error());
    }
    else if (command == "list")                     // list games
    {
        const auto &games{collection.get_games()};

        if (games.empty())
            handle_output("No games to list.");
        else
        {  
            // Create single string output to avoid multiple costly calls to handle_output
            std::string user_output;
            
            // Put each title on a newline
            for (const auto &game : games)
            {
                // Newline for all but the first title
                if (!user_output.empty())
                    user_output.push_back('\n');

                user_output.append(game.get_title());
            }

            handle_output(user_output);
        }
            
    }
    else
        handle_output("Command not recognised, disregarded.");
}