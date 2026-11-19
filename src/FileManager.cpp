#include <expected>
#include <nlohmann/json.hpp>
#include "FileManager.h"

FileManager::FileManager(Collection &collection)
    : collection{collection} 
{
    load();
}

// Load collection from file
std::expected<void, std::string> FileManager::load()
{
    // Open file
    std::ifstream ifs{file_path};

    // Fail if file can't be opened
    if (!ifs)
        return std::unexpected{"Failed to open load file."}; // fail

    // Input file into json data object
    nlohmann::json json_data;
    ifs >> json_data;

    // Convert json data into collection data
    for (const auto &game : json_data)
        collection.add_game(game["title"]);

    return {};                                          // success
}

// Save collection to file
std::expected<void, std::string> FileManager::save()
{
    // Open file
    std::ofstream ofs{file_path};   

    // Fail if file can't be opened
    if (!ofs)
        return std::unexpected{"Failed to open save file."}; // fail

    // Input file data into json data object
    nlohmann::json json_data;

    // Convert collection data into json data
    for (const auto &game : collection.get_games())
        json_data.push_back({
            {"title", game.title}
        });

    // Output 'pretty' json to file
    ofs << std::setw(4) << json_data;

    return {};
}