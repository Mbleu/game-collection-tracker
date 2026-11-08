#include "Game.h"

// Constructor for Game that requires an ID and a title
Game::Game(const unsigned int id, const std::string& title)
    : id {id}, title { title }
{}

// Simple getter for returning game id without exposing it
unsigned int Game::get_id() const { return id; }

// Simple getter for returning game title without exposing it
const std::string &Game::get_title() const { return title; }
