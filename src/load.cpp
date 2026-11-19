#include <filesystem>
#include <fstream>
#include <expected>
#include <nlohmann/json.hpp>
#include "load.h"

// Load collection from file
std::expected<void, std::string> load(Collection &collection)
{
    // File path to library
    std::ifstream ifs{"tests/test_data.json"};

    // Fail if file can't be opened
    if (!ifs)
        return std::unexpected{"Failed to load file."}; // fail

    // Input file data into json data object
    nlohmann::json data;
    ifs >> data;

    // Add the entries from the json object as games in collection
    for (const auto &game : data)
        collection.add_game(game["title"]);

    return {};                                          // success
}