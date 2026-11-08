#include "Game.h"
#include <vector>
#include <string>

// Class for tracking games
class Collection
{
private:
    std::vector<Game> games;
    unsigned int next_game_id{0};

public:
    void add_game(const std::string &game_title);
    void remove_game(const std::string &game_title);
    void list_games() const;
};