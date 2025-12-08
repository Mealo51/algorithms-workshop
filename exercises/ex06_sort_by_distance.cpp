#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>

// Challenge 6: sort_by_distance_to_player
//		https://compiler-explorer.com/z/Y7scnvjGe
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

struct Vec2 {
    float x, y;
};

struct Enemy {
    Vec2 position;
};

float distance_sq(const Vec2& a, const Vec2& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

//TODO: refactor to take std::span
void sort_by_distance_to_player(std::vector<Enemy>& enemies, Vec2 playerPos) {
    // TODO: refactor this to use std::sort with a lambda comparator
    for (size_t i = 0; i + 1 < enemies.size(); ++i) {
        for (size_t j = 0; j + 1 < enemies.size() - i; ++j) {
            float d1 = distance_sq(enemies[j].position, playerPos);
            float d2 = distance_sq(enemies[j + 1].position, playerPos);
            if (d1 > d2) {
                std::swap(enemies[j], enemies[j + 1]);
            }
        }
    }
}

TEST(SortByDistanceTest, SortsByIncreasingDistance) {
    Vec2 player{0.0f, 0.0f};
    std::vector<Enemy> enemies{
        {{10.0f, 0.0f}}, // distance 10
        {{3.0f, 4.0f}},  // distance 5
        {{1.0f, 1.0f}}   // distance sqrt(2)
    };

    sort_by_distance_to_player(enemies, player);

    ASSERT_EQ(enemies.size(), 3u);
    // After sorting: sqrt(2), 5, 10
    EXPECT_FLOAT_EQ(enemies[0].position.x, 1.0f);
    EXPECT_FLOAT_EQ(enemies[0].position.y, 1.0f);

    EXPECT_FLOAT_EQ(enemies[1].position.x, 3.0f);
    EXPECT_FLOAT_EQ(enemies[1].position.y, 4.0f);

    EXPECT_FLOAT_EQ(enemies[2].position.x, 10.0f);
    EXPECT_FLOAT_EQ(enemies[2].position.y, 0.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
