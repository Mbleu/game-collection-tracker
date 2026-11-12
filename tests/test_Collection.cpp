#include <gtest/gtest.h>
#include "Collection.h"

// Test Collection class:
// Test add_game()
TEST(CollectionTests, add_game)
{
    Collection collection;
    EXPECT_TRUE(collection.add_game("Runescape")) << "Title regular";
    EXPECT_TRUE(collection.add_game("World of Warcraft")) << "Title with spaces";
    EXPECT_TRUE(collection.add_game(" Runescape")) << "Title with leading space";
    EXPECT_TRUE(collection.add_game("!\"£$%^&*()_+-=[]{}'#@~,./<>?")) << "Title with special characters";
    EXPECT_FALSE(collection.add_game("Runescape")) << "Duplicate title";
    EXPECT_FALSE(collection.add_game("\nRune\n\n\nscape\n")) << "Title with newlines";
    EXPECT_FALSE(collection.add_game("")) << "Empty title";
}
// Test remove_game()
TEST(CollectionTests, remove_game)
{
    Collection collection;
    ASSERT_TRUE(collection.add_game("Runescape")) << "Test setup failed: add_game failed";
    EXPECT_TRUE(collection.remove_game("Runescape")) << "Remove game";
    EXPECT_FALSE(collection.remove_game("Runescape")) << "Remove game that has already been removed";
    EXPECT_FALSE(collection.remove_game("Scaperune")) << "Remove game that doesn't exist";
}
// Test list_games()
TEST(CollectionTests, list_games)
{
    Collection collection;
    EXPECT_TRUE(collection.list_games()) << "Empty collection";
    ASSERT_TRUE(collection.add_game("Runescape")) << "Test setup failed: add_game failed";
    ASSERT_TRUE(collection.add_game("World of Warcraft")) << "Test setup failed: add_game failed";
    EXPECT_TRUE(collection.list_games()) << "With games";
}