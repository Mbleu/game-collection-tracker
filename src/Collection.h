#pragma once
#include "Game.h"
#include <vector>
#include <string>
#include <expected>

// Class for tracking games
class Collection
{
private:
    std::vector<Game> games;
    unsigned int last_issued_game_id;

    std::vector<Game>::iterator find_game(const std::string &game_title);   // helper function for finding a game by title
    std::vector<Game>::const_iterator find_game(const std::string &game_title) const;
    std::expected<void, std::string> validate_game_title(const std::string &game_title) const;  // check title conforms to naming rules
    std::expected<unsigned int, std::string> generate_game_id();

public:
    Collection();
    const std::vector<Game> &get_games() const;
    std::vector<const Game*> search(const std::string &game_title) const;   // returns full and partial matches
    std::expected<void, std::string> add_game(const std::string &game_title);
    std::expected<void, std::string> remove_game(const std::string &game_title);
    std::expected<void, std::string> modify_game(const std::string &current_game_title, const std::string &new_game_title);
};