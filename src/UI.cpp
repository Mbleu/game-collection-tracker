#include "UI.h"
#include <iostream>
#include <sstream>

// UI constructor. Stores reference to a collection.
UI::UI(Collection &collection)
    : collection{collection} {}

// Runs the UI
void UI::run()
{
    handle_output("Collection tracker running, please enter commands.\n");

    while(!exit_flag)
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

// Outputs a string to console
void UI::handle_output(const std::string &user_output) const
{
    std::cout << user_output;
}

// Splits input into command and data, then calls the corresponding function
void UI::handle_input(const std::string& user_input)
{
    // Split user input into command and data
    std::istringstream iss{user_input};
    std::string command;
    std::string data;
    iss >> command;
    std::getline(iss >> std::ws, data);

    // Call function based on command
    if (command == "exit")
        exit();
    else if (command == "add")
        add(data);
    else if (command == "remove")
        remove(data);
    else if (command == "list")
        list();
    else if (command == "search")
        search(data);
    else if (command == "modify")
        modify(data);
    else // unrecognised
        handle_output("command not recognised\n");
}

// Exit, close the program
void UI::exit()
{
    exit_flag = true;
    handle_output("exiting\n");
}

// Add game to collection
void UI::add(const std::string &title)
{
    auto result{collection.add_game(title)};

    if (result)
        handle_output(title + " added\n");
    else
        handle_output(result.error() + '\n');
}

// Remove game from collection
void UI::remove(const std::string &title)
{
    auto result{collection.remove_game(title)};

    if (result)
        handle_output(title + " removed\n");
    else
        handle_output(result.error() + '\n');
}

// List all games in collection
void UI::list()
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

// Search for a game in the collection by title
void UI::search(const std::string &title)
{
    const auto &result{collection.search(title)};

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

// Modify a title in the collection
void UI::modify(const std::string &title_from)
{
    std::string title_to{get_input()};

    auto result{collection.modify_game(title_from, title_to)};

    if (result)
        handle_output("new title set\n");
    else
        handle_output(result.error() + '\n');
}