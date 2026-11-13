#include "Collection.h"
#include <iostream>

// Collection constructor
Collection::Collection()
    : next_game_id{0} {}

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

// Return reference to games in collection
const std::vector<Game> &Collection::get_games() const
{
    return games;
}

// Return pointers to games that fully or partially match the search
// e.g. search("Runescape") would return both Runescape and Oldschool Runescape
std::vector<const Game*> Collection::search(const std::string& game_title) const
{
    std::vector<const Game *> matching_games;

    // Find matches and store pointers in vector
    for (const auto &game : games)
    {
        if (game.get_title().find(game_title) != std::string::npos)
            matching_games.push_back(&game);
    }

    return matching_games;
}

// Add a new game to the collection
std::expected<void, std::string> Collection::add_game(const std::string &game_title)
{
    // Reject duplicate titles
    if (find_game(game_title) == games.end())
    {
        // Fail
        return std::unexpected(game_title + " already exists, command disregarded");
    }

    // Add game to collection
    games.push_back(Game{next_game_id++, game_title});

    // Success
    return {};
}

// Remove a game from the collection
std::expected<void, std::string> Collection::remove_game(const std::string& game_title)
{
    // Try to find game
    auto it{find_game(game_title)};

    // Check if game exists
    if (it == games.end())
    {
        // Fail
        return std::unexpected{game_title + " not found, command disregarded"};
    }

    // Erase record
    games.erase(it);
    std::cout << game_title << " erased." << std::endl;

    // Success
    return {};
}