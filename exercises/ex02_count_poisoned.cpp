#include <gtest/gtest.h>
#include <vector>

// Challenge 2: count_poisoned
// 		https://compiler-explorer.com/z/qTWseobfM
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

struct Enemy {
    int hp;
    bool poisoned;
};

int count_poisoned(const std::vector<Enemy>& enemies) {
    // TODO: refactor this to use std::count_if
    int result = 0;
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].poisoned) {
            ++result;
        }
    }
    return result;
}

TEST(CountPoisonedTest, EmptyListIsZero) {
    std::vector<Enemy> enemies;
    EXPECT_EQ(count_poisoned(enemies), 0);
}

TEST(CountPoisonedTest, CountsOnlyPoisoned) {
    std::vector<Enemy> enemies{
        {10, false},
        {20, true},
        {30, true},
        {40, false}
    };
    EXPECT_EQ(count_poisoned(enemies), 2);
}

TEST(CountPoisonedTest, AllPoisoned) {
    std::vector<Enemy> enemies{
        {10, true},
        {20, true}
    };
    EXPECT_EQ(count_poisoned(enemies), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
