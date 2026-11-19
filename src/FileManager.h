#pragma once
#include <fstream>
#include "Collection.h"

class FileManager{
    private:
        Collection &collection;
        std::string file_path{"tests/test_data.json"};

    public:
        FileManager(Collection &collection);
        std::expected<void, std::string> load();
        std::expected<void, std::string> save();
};