#include "Game.h"

Game::Game(const int id, const std::string& title)
    : id {id}, title { title }
{}

int Game::get_id() const { return id; }
const std::string &Game::get_title() const { return title; }
