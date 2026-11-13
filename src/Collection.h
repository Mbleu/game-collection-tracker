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
    unsigned int next_game_id;

    std::vector<Game>::iterator find_game(const std::string& game_title);

public:
    Collection();
    const std::vector<Game> &get_games() const;
    std::vector<const Game*> search(const std::string &game_title) const;
    std::expected<void, std::string> add_game(const std::string &game_title);
    std::expected<void, std::string> remove_game(const std::string &game_title);
};