#pragma once
#include "Collection.h"
#include <string>

// Handles user interaction to promote modularity
class UI
{
    private:
        Collection &collection;
        bool exit;  // program closes on next loop when true

        std::string get_input() const;
        void handle_output(const std::string &user_output) const;
        void handle_input(const std::string &user_input);

    public:
        UI(Collection &collection);
        void run();
};