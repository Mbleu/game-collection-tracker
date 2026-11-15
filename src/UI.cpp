#include "UI.h"
#include <iostream>
#include <sstream>

// UI constructor. Stores reference to a collection.
UI::UI(Collection &collection)
    : collection{collection}, exit{false} {}

// Runs the UI
void UI::run()
{
    handle_output("Collection tracker running, please enter commands.\n");

    while(!exit)
    {
        std::string user_input{get_input()};
        handle_input(user_input);
    }
}

// Waits for user input from console and returns it
std::string UI::get_input() const
{
    // Prompt user
    handle_output("> ");

    std::string user_input;
    if (!std::getline(std::cin, user_input))
        throw "Input stream entered bad state";
    return user_input;
}

void UI::handle_output(const std::string &user_output) const
{
    std::cout << user_output;
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
    {
        exit = true;
        handle_output("exiting\n");
    }
    else if (command == "add")                      // add game
    {
        auto result{collection.add_game(data)};

        if (result)
            handle_output(data + " added\n");
        else
            handle_output(result.error() + '\n');
    }
    else if (command == "remove")                   // remove game
    {
        auto result{collection.remove_game(data)};

        if (result)
            handle_output(data + " removed\n");
        else
            handle_output(result.error() + '\n');
    }
    else if (command == "list")                     // list games
    {
        const auto &games{collection.get_games()};

        if (games.empty())
            handle_output("no games to list\n");
        else
        {
            std::string user_output;

            // Put each title on a newline
            for (auto it{games.begin()}; it < games.end(); ++it)
            {
                // Newline for all but the first title
                if (it != games.begin())
                    user_output.push_back('\n');

                user_output.append(it->title);
            }

            handle_output(user_output + '\n');
        }
    }
    else if (command == "search")
    {
        const auto &result{collection.search(data)};

        if (result.empty())
            handle_output("no games match search\n");
        else
        {
            std::string user_output;

            // Put each title on a newline
            for (auto it{result.begin()}; it < result.end(); ++it)
            {
                // Newline for all but the first title
                if (it != result.begin())
                    user_output.push_back('\n');

                user_output.append((*it)->title);
            }

            handle_output(user_output + '\n');
        }
    }
    else if (command == "modify")
    {
        // Split user input into command and data
        const std::string &current_title{data};

        std::string new_title{get_input()};

        auto result{collection.modify_game(current_title, new_title)};

        if (result)
            handle_output("new title set\n");
        else
            handle_output(result.error() + '\n');
    }
    else                                            // unrecognised
        handle_output("command not recognised\n");
}