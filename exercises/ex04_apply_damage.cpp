#include <gtest/gtest.h>
#include <vector>
#include <algorithm> 

// Challenge 4: apply_damage
//		https://compiler-explorer.com/z/GGrYrhxGb
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.
struct Enemy {
    int hp;
};

//TODO: refactor to take std::span
void apply_damage(std::vector<Enemy>& enemies, int damagePerEnemy) {
    // TODO: refactor this to use std::transform + std::clamp
    for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].hp -= damagePerEnemy;
        if (enemies[i].hp < 0) enemies[i].hp = 0;
        if (enemies[i].hp > 100) enemies[i].hp = 100;
    }
}

TEST(ApplyDamageTest, DamageReducesHpAndClampsAtZero) {
    std::vector<Enemy> enemies{
        {50},
        {10},
        {5}
    };

    apply_damage(enemies, 20);

    EXPECT_EQ(enemies[0].hp, 30);
    EXPECT_EQ(enemies[1].hp, 0);
    EXPECT_EQ(enemies[2].hp, 0);
}

TEST(ApplyDamageTest, NegativeDamageHealsAndClampsAtHundred) {
    std::vector<Enemy> enemies{
        {90},
        {50}
    };

    apply_damage(enemies, -20);

    EXPECT_EQ(enemies[0].hp, 100);
    EXPECT_EQ(enemies[1].hp, 70);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
