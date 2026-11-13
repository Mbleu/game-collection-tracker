#include "Game.h"
#include <string>
#include <exception>
#include <iostream>
#include <limits>

#include <gtest/gtest.h>

bool test_Game_constructor()
{
    bool test_pass{true};

    // Happy path
    std::cout << "Game constructor happy path test..." << std::endl;
    try
    {
        Game game{0, "Runescape"};
        std::cout << "PASS: Game constructed" << std::endl;
    }
    catch(...){
        test_pass = false;
        std::cout << "FAIL: Game failed to construct" << std::endl;
    }

    // Empty title
    std::cout << "Game constructor empty title test..." << std::endl;
    try{
        Game game{0, ""};
        test_pass = false;
        std::cout << "FAIL: Constructor accepted empty title" << std::endl;
    }
    catch(...){
        std::cout << "PASS: Constructor rejected empty title" << std::endl;
    }

    // Title with spaces
    std::cout << "Game constructor title with spaces test..." << std::endl;
    try{
        Game game{0, "Oldschool Runescape"};
        std::cout << "PASS: Constructor accepted title with spaces " << std::endl;
    }
    catch(...){
        test_pass = false;
        std::cout << "FAIL: Constructor rejected title with spaces" << std::endl;
    }

    // Title with numbers
    std::cout << "Game constructor title with numbers test..." << std::endl;
    try{
        Game game{0, "Runescape3"};
        std::cout << "PASS: Constructor accepted title with numbers " << std::endl;
    }
    catch(...){
        test_pass = false;
        std::cout << "FAIL: Constructor rejected title with numbers" << std::endl;
    }

    // Title with special characters
    std::cout << "Game constructor title with special characters test..." << std::endl;
    try{
        Game game{0, "Runescape!\"£$%^&*()_+{}[]@~'#,<.>/\\|"};
        std::cout << "PASS: Constructor accepted title with special characters" << std::endl;
    }
    catch(...){
        test_pass = false;
        std::cout << "FAIL: Constructor rejected title with special characters" << std::endl;
    }

    // Title with newline
    std::cout << "Game constructor title with newline test..." << std::endl;
    try{
        Game game{0, "Oldschool\nRunescape"};
        test_pass = false;
        std::cout << "FAIL: Constructor accepted title with newline" << std::endl;
    }
    catch(...){
        std::cout << "PASS: Constructor rejected title with newline" << std::endl;
    }

    return test_pass;
}