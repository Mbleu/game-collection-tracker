#include "Collection.h"
#include <string>
#include <iostream>

int main()
{
    Collection collection;
    std::string user_input;

    while (std::getline(std::cin, user_input))
    {
        if (user_input == "exit")
            break;

        collection.take_action(user_input);
    }
}