#include <gtest/gtest.h>
#include <vector>
#include <optional>
#include <string>

// Challenge 1: find_first_dead
//  https://compiler-explorer.com/z/P5qd8hjsc
//
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

struct Enemy {
    std::string name;
    int hp;
};

// TODO: refactor to take std::span
// TODO: refactor this to use std::find_if
std::optional<Enemy> find_first_dead(const std::vector<Enemy>& enemies) {    
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].hp <= 0) {
            return enemies[i];
        }
    }
    return std::nullopt;
}

TEST(FindFirstDeadTest, EmptyListGivesNullopt) {
    std::vector<Enemy> enemies;
    auto result = find_first_dead(enemies);
    EXPECT_FALSE(result.has_value());
}

TEST(FindFirstDeadTest, AllAliveGivesNullopt) {
    std::vector<Enemy> enemies{
        {"Slime", 10},
        {"Orc", 20},
        {"Dragon", 200}
    };
    auto result = find_first_dead(enemies);
    EXPECT_FALSE(result.has_value());
}

TEST(FindFirstDeadTest, FindsFirstDeadInTheMiddle) {
    std::vector<Enemy> enemies{
        {"Slime", 10},
        {"Zombie", 0},
        {"Orc", -5},
        {"Dragon", 200}
    };
    auto result = find_first_dead(enemies);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->name, "Zombie");
    EXPECT_EQ(result->hp, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
