#include "Game.h"
#include <vector>

class Collection{
    private:
        std::vector<Game> games;
        unsigned int next_game_id{0};

    public:
        void take_action(const std::string &line);
        void add_game(const std::string &game_title);
        void remove_game(const int game_id);
        void list_games() const;
};