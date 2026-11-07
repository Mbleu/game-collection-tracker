#include "Collection.h"
#include <sstream>
#include <iostream>

void Collection::take_action(const std::string &line)
{
    std::istringstream ss{line};
    std::string command;
    ss >> command;
    std::string data{std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>()};
    if (command == "add")
    {

        add_game();
    }
    else if (command == "remove"){

    }
    else if (command == "list"){

    }
    else{
        std::cout << "Command unrecognised" << std::endl;
    }
}
void Collection::add_game(const std::string &game_title)
{
    games.push_back(Game{next_game_id++, game_title});
}
void Collection::remove_game(const int game_id)
{
    bool id_found{false};

    for (auto it{games.begin()}; !id_found && it < games.end(); ++it)
    {
        if (it->get_id() == game_id)
        {
            id_found = true;
            games.erase(it);
            std::cout << '#' << game_id << " erased" << std::endl;
        }
    }

    if (!id_found)
        std::cout << '#' << game_id << " not found" << std::endl;
}