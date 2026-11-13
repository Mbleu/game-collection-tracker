#include <gtest/gtest.h>
#include "Collection.h"

// Test Collection class:
// Test add_game()
TEST(CollectionTests, add_game_works)
{
    Collection collection;
    ASSERT_TRUE(collection.add_game("World of Warcraft")) << "Function reported failure.";
    ASSERT_FALSE(collection.get_games().empty()) << "Games vector empty.";
    EXPECT_EQ(collection.get_games().size(), 1) << "More than 1 game added to vector.";
    EXPECT_EQ(collection.get_games().back().get_title(), "World of Warcraft") << "Created game has incorrect title.";
}
TEST(CollectionTests, add_game_rejects_empty_title)
{
    Collection collection;
    EXPECT_FALSE(collection.add_game("")) << "Function incorrectly accepted empty title.";
    EXPECT_TRUE(collection.get_games().empty()) << "Function added game.";
}
TEST(CollectionTests, add_game_rejects_title_with_newline)
{
    Collection collection;
    EXPECT_FALSE(collection.add_game("World\nof\nWarcraft")) << "Function incorrectly accepted title containing newline.";
    EXPECT_TRUE(collection.get_games().empty()) << "Function added game.";
}
// // Test remove_game()
// TEST(CollectionTests, remove_game)
// {
//     Collection collection;
//     EXPECT_FALSE(collection.remove_game("World of Warcraft")) << "Function reported success despite empty collection.";
//     ASSERT_TRUE(collection.add_game("World of Warcraft")) << ""
//     ASSERT_TRUE(collection.add_game("Runescape")) << "Test setup failed: add_game failed";
//     EXPECT_TRUE(collection.remove_game("Runescape")) << "Remove game";
//     EXPECT_FALSE(collection.remove_game("Runescape")) << "Remove game that has already been removed";
//     EXPECT_FALSE(collection.remove_game("Scaperune")) << "Remove game that doesn't exist";
// }
// // Test list_games()
// TEST(CollectionTests, list_games)
// {
//     Collection collection;
//     EXPECT_TRUE(collection.list_games()) << "Empty collection";
//     ASSERT_TRUE(collection.add_game("Runescape")) << "Test setup failed: add_game failed";
//     ASSERT_TRUE(collection.add_game("World of Warcraft")) << "Test setup failed: add_game failed";
//     EXPECT_TRUE(collection.list_games()) << "With games";
// }