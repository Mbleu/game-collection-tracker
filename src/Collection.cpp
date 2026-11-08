#include "Collection.h"
#include <iostream>

// Add a new game to the collection
void Collection::add_game(const std::string &game_title)
{
    games.push_back(Game{next_game_id++, game_title});
}

// Remove a game from the collection
void Collection::remove_game(const std::string& game_title)
{
    bool title_found{false};

    // Find game by title
    for (auto it{games.begin()}; !title_found && it < games.end(); ++it)
    {
        // Erase game once found
        if (it->get_title() == game_title){
            title_found = true;
            games.erase(it);
            std::cout << game_title << " erased." << std::endl;
        }
    }

    if (!title_found)
        std::cout << game_title << " not found." << std::endl;
}

// Output a list of all games in the collection
void Collection::list_games() const
{
    if (games.empty()){
        std::cout << "No games to list." << std::endl;
        return;
    }

    for(const Game& game : games)
        std::cout << game.get_title() << std::endl;
}