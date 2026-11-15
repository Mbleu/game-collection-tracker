#include "Collection.h"
#include <limits>
#include <cctype>

// Collection constructor
Collection::Collection()
    : last_issued_game_id{0} {}

// Find a game in collection and return iterator if found, otherwise returns end()
std::vector<Game>::iterator Collection::find_game(const std::string& game_title)
{
    // Find game by title and return iterator
    for (auto it{games.begin()}; it < games.end(); ++it)
        if (it->title == game_title)
            return it;

    // Return end iterator when game not found
    return games.end();
}

// Const overload for use by const functions
std::vector<Game>::const_iterator Collection::find_game(const std::string& game_title) const
{
    // Find game by title and return const iterator
    for (auto it{games.cbegin()}; it < games.cend(); ++it)
        if (it->title == game_title)
            return it;

    // Return end iterator when game not found
    return games.end();
}

// Check that game title conforms to naming rules
std::expected<void, std::string> Collection::validate_game_title(const std::string &game_title) const
{
    // Reject empty titles
    if (game_title.empty())
        return std::unexpected("Title cannot be empty.");                   // fail

    // Reject titles containing only whitespace
    bool only_whitespace{true};
    for (unsigned char c : game_title){
        if (!std::isspace(c)){
            only_whitespace = false;
            break;
        }
    }
    if (only_whitespace)
        return std::unexpected("Title cannot contain only whitespace.");    // fail

    // Reject titles containing newlines
    if (game_title.find('\n') != std::string::npos)
        return std::unexpected("Title cannot contain newline chars.");      // fail

    // Reject titles longer than 100chars
    if (game_title.length() > 100)
        return std::unexpected("Title cannot be longer than 100 chars.");   // fail

    // Reject duplicate titles
    if (find_game(game_title) != games.end())
        return std::unexpected(game_title + " already exists.");            // fail

    return {};                                                              // success
}

std::expected<unsigned int, std::string> Collection::generate_game_id()
{
    if (last_issued_game_id == std::numeric_limits<unsigned int>::max())
        return std::unexpected{"Game IDs exhausted."};

    return last_issued_game_id++;
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
        if (game.title.find(game_title) != std::string::npos)
            matching_games.push_back(&game);
    }

    return matching_games;
}

// Add a new game to the collection
std::expected<void, std::string> Collection::add_game(const std::string &game_title)
{
    // Validate title
    if (auto result{validate_game_title(game_title)}; !result)
        return std::unexpected{result.error()};                 // fail

    // Generate id
    auto game_id{generate_game_id()};
    if (!game_id)
        return std::unexpected{game_id.error()};                // fail

    // Add game to collection
    games.push_back(Game{game_id.value(), game_title});
    return {};                                                  // success
}

// Remove a game from the collection
std::expected<void, std::string> Collection::remove_game(const std::string& game_title)
{
    // Try to find game
    auto it{find_game(game_title)};

    // Check if game exists
    if (it == games.end())
        return std::unexpected{game_title + " not found"};  // fail

    // Erase record
    games.erase(it);

    return {};                                              // success
}

// Modifies a game title to something new
std::expected<void, std::string> Collection::modify_game(const std::string &current_game_title, const std::string &new_game_title)
{
    auto it{find_game(current_game_title)};

    // Check if game exists
    if (it == games.end())
        return std::unexpected{current_game_title + " not found"};  // fail

    // Validate new title
    if (auto result{validate_game_title(new_game_title)}; !result)
        return std::unexpected{result.error()};                     // fail
    
    // Set new title
    it->title = new_game_title;
    return {};                                                      // success
}