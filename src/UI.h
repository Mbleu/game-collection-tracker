#pragma once
#include "Collection.h"
#include <string>

// Handles user interaction to promote modularity
class UI
{
    private:
        Collection &collection;
        bool exit_flag{false}; // program closes on next loop when true

        std::string get_input() const;
        void handle_output(const std::string &user_output) const;
        void handle_input(const std::string &user_input);
        void exit();
        void add(const std::string &title);
        void remove(const std::string &title);
        void list();
        void search(const std::string &title);
        void modify(const std::string &title_from);

    public:
        UI(Collection &collection);
        void run();
};