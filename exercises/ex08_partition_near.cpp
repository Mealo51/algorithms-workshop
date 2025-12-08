#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>

// Challenge 8: partition_near_enemies
//		https://compiler-explorer.com/z/aoodb83Ye
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

size_t partition_near_enemies(std::vector<Enemy>& enemies, Vec2 playerPos, float radius) {
    // TODO: refactor this to use std::partition
    const float radiusSq = radius * radius;
    size_t firstFar = 0;

    for (size_t i = 0; i < enemies.size(); ++i) {
        float d2 = distance_sq(enemies[i].position, playerPos);
        if (d2 <= radiusSq) {
            std::swap(enemies[i], enemies[firstFar]);
            ++firstFar;
        }
    }
    return firstFar; // number of near enemies at front
}

TEST(PartitionNearEnemiesTest, NearEnemiesComeFirst) {
    Vec2 player{0.0f, 0.0f};
    std::vector<Enemy> enemies{
        {{10.0f, 0.0f}}, // far (10)
        {{1.0f, 1.0f}},  // near (sqrt(2))
        {{3.0f, 4.0f}},  // near (5)
        {{20.0f, 0.0f}}  // far (20)
    };

    size_t countNear = partition_near_enemies(enemies, player, 6.0f);

    EXPECT_EQ(countNear, 2u);

    // Check that first countNear are near
    for (size_t i = 0; i < countNear; ++i) {
        float d2 = distance_sq(enemies[i].position, player);
        EXPECT_LE(d2, 36.0f);
    }

    // And the rest are far
    for (size_t i = countNear; i < enemies.size(); ++i) {
        float d2 = distance_sq(enemies[i].position, player);
        EXPECT_GT(d2, 36.0f);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
