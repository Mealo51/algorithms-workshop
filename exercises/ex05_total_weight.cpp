#include <gtest/gtest.h>
#include <vector>
#include <numeric>

// Challenge 5: total_weight
//		https://compiler-explorer.com/z/cTEjT5o5r
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.

struct Item {
    float weight;
};

//TODO: refactor to take span
float total_weight(const std::vector<Item>& items) {
    // TODO: refactor this to use std::accumulate
    float result = 0.0f;
    for (size_t i = 0; i < items.size(); ++i) {
        result += items[i].weight;
    }
    return result;
}

TEST(TotalWeightTest, EmptyInventoryIsZero) {
    std::vector<Item> items;
    EXPECT_FLOAT_EQ(total_weight(items), 0.0f);
}

TEST(TotalWeightTest, SumsWeights) {
    std::vector<Item> items{
        {1.5f},
        {2.0f},
        {0.5f}
    };
    EXPECT_FLOAT_EQ(total_weight(items), 4.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
