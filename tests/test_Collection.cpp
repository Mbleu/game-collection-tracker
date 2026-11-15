#include <gtest/gtest.h>
#include "Collection.h"

// Test fixture class for common setup
class CollectionTest : public ::testing::Test {
    protected:
        Collection collection;
};

// Test fixture subclasses to give more expressive test failures
class AddGame : public CollectionTest {};
class RemoveGame :  public CollectionTest {};
class ModifyGame :  public CollectionTest {};
class Search :  public CollectionTest {};

// Collection test suite
TEST_F(AddGame, AddValidGame)
{
    auto result{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(result) << "Game not added, returned error: " << result.error();
    ASSERT_TRUE(collection.get_games().size() == 1) << "Wrong games size.";
    ASSERT_EQ(collection.get_games().back().title, "World of Warcraft") << "Added game title does not match what was passed.";
}
TEST_F(AddGame, RejectEmptyTitle)
{
    ASSERT_FALSE(collection.add_game("")) << "Empty title not rejected.";
    ASSERT_TRUE(collection.get_games().empty()) << "Wrong games size.";
}
TEST_F(AddGame, RejectWhitespaceTitle)
{
    ASSERT_FALSE(collection.add_game("         ")) << "Whitespace title not rejected.";
    ASSERT_TRUE(collection.get_games().empty()) << "Wrong games size.";
}
TEST_F(AddGame, RejectNewlineTitle)
{
    ASSERT_FALSE(collection.add_game("World\nof\nWarcraft")) << "Title containting newline chars not rejected.";
    ASSERT_TRUE(collection.get_games().empty()) << "Wrong games size.";
}
TEST_F(AddGame, RejectTooLongTitle)
{
    std::string long_title;
    for (int i{0}; i < 101; ++i)
        long_title.push_back('a');

    ASSERT_FALSE(collection.add_game(long_title)) << "Title longer than 100 characters not rejected.";
    ASSERT_TRUE(collection.get_games().empty()) << "Wrong games size.";
}
TEST_F(AddGame, RejectDuplicateTitle)
{
    auto result{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(result) << "Game needed for test setup not added, returned error: " << result.error();

    ASSERT_FALSE(collection.add_game("World of Warcraft")) << "Duplicate title not rejected.";
    ASSERT_TRUE(collection.get_games().size() == 1) << "Wrong games size.";
}
TEST_F(RemoveGame, RemoveValidGame)
{
    auto add_result{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(add_result) << "Game needed for test setup not added, returned error: " << add_result.error();

    auto remove_result{collection.remove_game("World of Warcraft")};
    ASSERT_TRUE(remove_result) << "Game not removed, returned error: " << remove_result.error();
    ASSERT_TRUE(collection.get_games().empty()) << "Wrong games size.";
}
TEST_F(RemoveGame, RemoveNonExistantGame)
{
    auto add_result{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(add_result) << "Game needed for test setup not added, returned error: " << add_result.error();
    
    ASSERT_FALSE(collection.remove_game("Runescape")) << "Non-existant game not rejected.";
    ASSERT_TRUE(collection.get_games().size() == 1) << "Wrong games size.";
}
TEST_F(ModifyGame, ModifyValidGame)
{
    auto add_result{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(add_result) << "Game needed for test setup not added, returned error: " << add_result.error();

    auto modify_result(collection.modify_game("World of Warcraft", "WoW"));
    ASSERT_TRUE(modify_result) << "Game not modified, returned error: " << modify_result.error();
    ASSERT_TRUE(collection.get_games().front().title == "WoW") << "Modified title does not match what was passed.";
}
TEST_F(ModifyGame, ModifyNonExistantGame)
{
    ASSERT_FALSE(collection.modify_game("World of Warcraft", "WoW")) << "Non-existant game not rejected.";
}
TEST_F(Search, SearchByTitle)
{
    auto add_result1{collection.add_game("World of Warcraft")};
    ASSERT_TRUE(add_result1) << "Game1 needed for test setup not added, returned error: " << add_result1.error();
    auto add_result2{collection.add_game("World of Warcraft Classic")};
    ASSERT_TRUE(add_result2) << "Game2 needed for test setup not added, returned error: " << add_result2.error();
    auto add_result3{collection.add_game("Runescape")};
    ASSERT_TRUE(add_result3) << "Game3 needed for test setup not added, returned error: " << add_result3.error();

    auto search_results{collection.search("World of Warcraft")};

    ASSERT_TRUE(search_results.size() == 2) << "Incorrect number of results.";

    bool full_match_returned{false};
    for (const auto &game : search_results)
        if (game->title == "World of Warcraft")
            full_match_returned = true;
    ASSERT_TRUE(full_match_returned) << "Full match not in results.";

    bool partial_match_returned{false};
    for (const auto &game : search_results)
        if (game->title == "World of Warcraft Classic")
            partial_match_returned = true;
    ASSERT_TRUE(partial_match_returned) << "Partial match not in results.";
}