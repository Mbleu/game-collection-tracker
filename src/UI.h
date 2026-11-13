#include "Collection.h"
#include <string>

class UI
{
    private:
        Collection &collection;
        bool exit;

        std::string get_input() const;
        void handle_input(const std::string& user_input);

    public:
        UI(Collection &collection);
        void run();
};