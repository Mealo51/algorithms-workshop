#include <gtest/gtest.h>
#include <vector>

// Challenge 3: remove_offscreen
//		https://compiler-explorer.com/z/Gj66nGcE3
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

struct Bullet {
    float x, y;
    bool alive;
};

void remove_offscreen(std::vector<Bullet>& bullets, float screenWidth, float screenHeight) {
    // TODO: refactor this to use std::remove_if + erase, or std::erase_if
    for (size_t i = 0; i < bullets.size(); ) {
        Bullet& b = bullets[i];
        bool offscreen =
            b.x < 0 || b.x > screenWidth ||
            b.y < 0 || b.y > screenHeight ||
            !b.alive;
        if (offscreen) {
            bullets.erase(bullets.begin() + static_cast<std::ptrdiff_t>(i));
        } else {
            ++i;
        }
    }
}

TEST(RemoveOffscreenTest, RemovesDeadAndOffscreenBullets) {
    std::vector<Bullet> bullets{
        {10, 10, true},   // keep
        {-1, 5, true},    // remove (left)
        {5, 501, true},   // remove (bottom)
        {100, 100, false} // remove (dead)
    };

    remove_offscreen(bullets, 500.0f, 500.0f);

    ASSERT_EQ(bullets.size(), 1u);
    EXPECT_FLOAT_EQ(bullets[0].x, 10.0f);
    EXPECT_FLOAT_EQ(bullets[0].y, 10.0f);
    EXPECT_TRUE(bullets[0].alive);
}

TEST(RemoveOffscreenTest,KeepsAllIfOnscreenAndAlive) {
    std::vector<Bullet> bullets{
        {0.0f, 0.0f, true},
        {250.0f, 250.0f, true},
        {500.0f, 500.0f, true}
    };

    remove_offscreen(bullets, 500.0f, 500.0f);

    EXPECT_EQ(bullets.size(), 3u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
