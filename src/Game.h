#include <string>

class Game{
    private:
    int id;
    std::string title;

    public:
    Game(const int id, const std::string& title);
    int get_id() const;
    const std::string& get_title() const;
};