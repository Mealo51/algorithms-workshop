#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>

// Challenge 11: shuffle_deck
//		https://compiler-explorer.com/z/oqcW7aEdT
// Compiler Explorer normally recompiles automatically as you edit.
// If you turn that off or it gets stuck, press CTRL+K to build and run manually.
// Use the Output panel to see compiler messages and your program’s output.
enum class Card {
    A,
    B,
    C,
    D
};

void shuffle_deck(std::vector<Card>& deck) {
    // TODO: refactor this to use std::shuffle
    std::random_device rd;
    std::mt19937 rng{rd()};

    for (size_t i = deck.size(); i > 1; --i) {
        std::uniform_int_distribution<size_t> dist(0, i - 1);
        size_t j = dist(rng);
        std::swap(deck[i - 1], deck[j]);
    }
}

TEST(ShuffleDeckTest, ShuffledDeckHasSameCards) {
    std::vector<Card> original{
        Card::A, Card::B, Card::C, Card::D
    };
    auto deck = original;

    shuffle_deck(deck);

    // Sort both and compare to ensure it is a permutation
    auto sorter = [](Card c) { return static_cast<int>(c); };

    std::sort(original.begin(), original.end(),
              [&](Card lhs, Card rhs){ return sorter(lhs) < sorter(rhs); });

    std::sort(deck.begin(), deck.end(),
              [&](Card lhs, Card rhs){ return sorter(lhs) < sorter(rhs); });

    EXPECT_EQ(deck, original);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
