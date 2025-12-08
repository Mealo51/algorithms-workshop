#include <gtest/gtest.h>
#include <vector>
#include <string>

// Challenge 10: low_hp_enemy_names
//		https://compiler-explorer.com/z/v9E4G9cq1
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.
struct Enemy {
    std::string name;
    int hp;
};

//TODO: refactor to take std::span
std::vector<std::string> low_hp_enemy_names(const std::vector<Enemy>& enemies, int threshold) {
    // TODO: refactor to use std::copy_if + std::transform
    std::vector<std::string> result;

    for (size_t i = 0; i < enemies.size(); ++i) {
        const Enemy& e = enemies[i];
        if (e.hp < threshold) {
            result.push_back(e.name);
        }
    }

    return result;
}

TEST(LowHpEnemyNamesTest, EmptyGivesEmpty) {
    std::vector<Enemy> enemies;
    auto names = low_hp_enemy_names(enemies, 50);
    EXPECT_TRUE(names.empty());
}

TEST(LowHpEnemyNamesTest,CollectsNamesBelowThresholdInOrder) {
    std::vector<Enemy> enemies{
        {"Goblin", 30},
        {"Orc", 60},
        {"Slime", 10},
        {"Dragon", 200},
        {"Bat", 40}
    };

    auto names = low_hp_enemy_names(enemies, 50);

    ASSERT_EQ(names.size(), 3u);
    EXPECT_EQ(names[0], "Goblin");
    EXPECT_EQ(names[1], "Slime");
    EXPECT_EQ(names[2], "Bat");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}