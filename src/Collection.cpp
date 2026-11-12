#include "Collection.h"
#include <iostream>

// Find a game in collection.
// Returns game index if found.
// Returns games.end() if not found.
std::vector<Game>::iterator Collection::find_game(const std::string& game_title)
{
    // Find game by title
    for (auto it{games.begin()}; it < games.end(); ++it)
    {
        // Return iterator to game when found
        if (it->get_title() == game_title)
            return it;
    }

    // Return end iterator when game not found
    return games.end();
}

// Add a new game to the collection
bool Collection::add_game(const std::string &game_title)
{
    // Reject duplicate titles
    if (find_game(game_title) == games.end())
    {
        std::cout << game_title << " already exists, command disregarded" << std::endl;
        return;
    }

    // Add record to collection
    games.push_back(Game{next_game_id++, game_title});
}

// Remove a game from the collection
bool Collection::remove_game(const std::string& game_title)
{
    auto it{find_game(game_title)};

    // Check if record exists
    if (it == games.end())
    {
        std::cout << game_title << " not found, command disregarded" << std::endl;
        return;
    }

    // Erase record
    games.erase(it);
    std::cout << game_title << " erased." << std::endl;
}

// Output a list of all games in the collection
bool Collection::list_games() const
{
    if (games.empty()){
        std::cout << "No games to list." << std::endl;
        return;
    }

    for(const Game& game : games)
        std::cout << game.get_title() << std::endl;
}