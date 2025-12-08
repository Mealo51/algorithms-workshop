#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Challenge 9: remove_consecutive_duplicates
//
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.
struct Frame {
    int spriteIndex;
    float duration;
};

//TODO: refactor to take std::span 
void remove_consecutive_duplicates(std::vector<Frame>& frames) {
    // TODO: refactor this to use std::unique with a custom predicate
    if (frames.empty()) return;

    size_t out = 0;
    for (size_t i = 1; i < frames.size(); ++i) {
        if (frames[i].spriteIndex != frames[out].spriteIndex) {
            ++out;
            frames[out] = frames[i];
        }
    }
    frames.resize(out + 1);
}

TEST(RemoveConsecutiveDuplicatesTest, KeepsFirstOfEachRun) {
    std::vector<Frame> frames{
        {1, 0.1f},
        {1, 0.2f}, // duplicate spriteIndex
        {2, 0.1f},
        {2, 0.1f}, // duplicate
        {3, 0.1f}
    };

    remove_consecutive_duplicates(frames);

    ASSERT_EQ(frames.size(), 3u);
    EXPECT_EQ(frames[0].spriteIndex, 1);
    EXPECT_EQ(frames[1].spriteIndex, 2);
    EXPECT_EQ(frames[2].spriteIndex, 3);
}

TEST(RemoveConsecutiveDuplicatesTest, NoDuplicatesLeavesVectorUnchangedSize) {
    std::vector<Frame> frames{
        {1, 0.1f},
        {2, 0.1f},
        {3, 0.1f}
    };

    remove_consecutive_duplicates(frames);

    EXPECT_EQ(frames.size(), 3u);
    EXPECT_EQ(frames[0].spriteIndex, 1);
    EXPECT_EQ(frames[1].spriteIndex, 2);
    EXPECT_EQ(frames[2].spriteIndex, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
