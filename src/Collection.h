#include "Game.h"
#include <vector>
#include <string>

// Class for tracking games
class Collection
{
private:
    std::vector<Game> games;
    unsigned int next_game_id{0};

    std::vector<Game>::iterator find_game(const std::string& game_title);

public:
    bool add_game(const std::string &game_title);
    bool remove_game(const std::string &game_title);
    bool list_games() const;
};