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
    // Prompt user
    handle_output("> ");

    // Split user input into command and data
    std::istringstream iss{user_input};
    std::string command;
    std::string data;
    iss >> command;
    std::getline(iss >> std::ws, data);

    bool fail{false};
    std::string user_output;

    // Call function based on command
    if (command == "exit")                          // exit, close the program
    {
        exit = true;
        user_output = "Exiting.";
    }
    else if (command == "add")                      // add game
    {
        auto result{collection.add_game(data)};

        if (result)
            user_output = data + " added.";
        else
        {
            fail = true;
            user_output = result.error();
        }
    }
    else if (command == "remove")                   // remove game
    {
        auto result{collection.remove_game(data)};

        if (result)
            user_output = data + "removed.";
        else
        {
            fail = true;
            user_output = result.error();
        }
    }
    else if (command == "list")                     // list games
    {
        const auto &games{collection.get_games()};

        if (games.empty())
            user_output = "No games to list.";
        else
        {  
            // Put each title on a newline
            for (auto it{games.begin()}; it < games.end(); ++it)
            {
                // Newline for all but the first title
                if (it != games.begin())
                    user_output.push_back('\n');

                user_output.append(it->get_title());
            }
        }
    }
    else                                            // unrecognised
        user_output = "Command not recognised.";

    if (fail)
        user_output.append(" Command disregarded.");

    handle_output(user_output);
}