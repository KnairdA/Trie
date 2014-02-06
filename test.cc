#include "trie.h"

#include "gtest/gtest.h"

#include <cstdint>

class TrieTest : public ::testing::Test { };

TEST_F(TrieTest, Basic) {
	Trie<uint8_t> trie;

	trie.add({1, 1, 1, 1});
	trie.add({1, 2, 1, 2});
	trie.add({2, 3, 4, 5});
	trie.add({2, 3, 1, 2});

	EXPECT_EQ(trie.check({1, 1, 1, 1}),  true);
	EXPECT_EQ(trie.check({1, 2, 1, 2}),  true);
	EXPECT_EQ(trie.check({1, 2}),        true);

	EXPECT_EQ(trie.check({1, 1, 2, 3}),  false);
	EXPECT_EQ(trie.check({2, 1, 4}),     false);
}

TEST_F(TrieTest, Remove) {
	Trie<uint8_t> trie;

	trie.add({1, 1, 1, 1});
	trie.add({1, 2, 1, 2});
	trie.add({2, 3, 4, 5});
	trie.add({2, 3, 1, 2});

	trie.remove({1, 1, 1, 1});

	EXPECT_EQ(trie.check({1, 1, 1, 1}),  false);
	EXPECT_EQ(trie.check({1, 2, 1, 2}),  true);

	trie.remove({2, 3});

	EXPECT_EQ(trie.check({2, 3, 4, 5}),  false);
	EXPECT_EQ(trie.check({2, 3}),        false);
	EXPECT_EQ(trie.check({2}),           true);
}

TEST_F(TrieTest, Value) {
	Trie<uint8_t, uint8_t> trie;

	trie.add({1, 1, 1, 1}, 42);
	trie.add({1, 2, 1, 2}, 43);
	trie.add({2, 3, 4, 5}, 44);
	trie.add({2, 3, 1, 2}, 45);

	EXPECT_EQ(trie.get({1, 1, 1, 1}),  true);
	EXPECT_EQ(*trie.get({1, 1, 1, 1}).get(), 42);
	EXPECT_EQ(trie.get({1, 2, 1, 2}),  true);
	EXPECT_EQ(*trie.get({1, 2, 1, 2}).get(), 43);
	EXPECT_EQ(trie.get({2, 3, 4, 5}),  true);
	EXPECT_EQ(*trie.get({2, 3, 4, 5}).get(), 44);
	EXPECT_EQ(trie.get({2, 3, 4, 5}),  true);
	EXPECT_EQ(*trie.get({2, 3, 1, 2}).get(), 45);

	EXPECT_EQ(trie.get({1, 2}),        false);
	EXPECT_EQ(trie.get({1, 2}).get(),  nullptr);

	trie.set({1, 2},       42);
	trie.set({1, 1, 1, 1}, 255);

	EXPECT_EQ(trie.get({1, 2}),         true);
	EXPECT_EQ(*trie.get({1, 2}).get(),       42);
	EXPECT_EQ(trie.get({1, 1, 1, 1}),   true);
	EXPECT_EQ(*trie.get({1, 1, 1, 1}).get(), 255);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
