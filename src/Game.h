#include <string>

// Class for storing game metadata
class Game{
    private:
    const unsigned int id;
    std::string title;

    public:
    Game(const unsigned int id, const std::string& title);   // Create a Game by providing an ID and a title
    int get_id() const;
    const std::string& get_title() const;
};