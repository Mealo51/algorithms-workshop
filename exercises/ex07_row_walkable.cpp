#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Challenge 7: is_row_walkable + has_lava
//		https://compiler-explorer.com/z/qad6KToee
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

enum class TileType {
    Floor,
    Wall,
    Lava,
};

// TODO: prefer std::span
bool is_row_walkable(const std::vector<TileType>& row) {
    // TODO: refactor this to use std::all_of
    if (row.empty()) return false;

    for (size_t i = 0; i < row.size(); ++i) {
        if (row[i] == TileType::Wall || row[i] == TileType::Lava) {
            return false;
        }
    }
    return true;
}

// TODO: prefer std::span
bool has_lava(const std::vector<TileType>& row) {
    // TODO: refactor this to use std::any_of
    for (size_t i = 0; i < row.size(); ++i) {
        if (row[i] == TileType::Lava) {
            return true;
        }
    }
    return false;
}

TEST(RowWalkableTest, EmptyRowIsNotWalkable) {
    std::vector<TileType> row;
    EXPECT_FALSE(is_row_walkable(row));
}

TEST(RowWalkableTest, OnlyFloorIsWalkable) {
    std::vector<TileType> row{
        TileType::Floor,
        TileType::Floor
    };
    EXPECT_TRUE(is_row_walkable(row));
}

TEST(RowWalkableTest, WallsOrLavaMakeRowNotWalkable) {
    std::vector<TileType> row1{
        TileType::Floor,
        TileType::Wall,
        TileType::Floor
    };
    EXPECT_FALSE(is_row_walkable(row1));

    std::vector<TileType> row2{
        TileType::Floor,
        TileType::Lava
    };
    EXPECT_FALSE(is_row_walkable(row2));
}

TEST(HasLavaTest, DetectsPresenceOfLava) {
    std::vector<TileType> row1{
        TileType::Floor,
        TileType::Wall
    };
    EXPECT_FALSE(has_lava(row1));

    std::vector<TileType> row2{
        TileType::Floor,
        TileType::Lava,
        TileType::Floor
    };
    EXPECT_TRUE(has_lava(row2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
