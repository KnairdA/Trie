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

	EXPECT_EQ(trie.get({1, 1, 1, 1}).first,  true);
	EXPECT_EQ(*trie.get({1, 1, 1, 1}).second, 42);
	EXPECT_EQ(trie.get({1, 2, 1, 2}).first,  true);
	EXPECT_EQ(*trie.get({1, 2, 1, 2}).second, 43);
	EXPECT_EQ(trie.get({2, 3, 4, 5}).first,  true);
	EXPECT_EQ(*trie.get({2, 3, 4, 5}).second, 44);
	EXPECT_EQ(trie.get({2, 3, 4, 5}).first,  true);
	EXPECT_EQ(*trie.get({2, 3, 1, 2}).second, 45);

	EXPECT_EQ(trie.get({1, 2}).first,        false);
	EXPECT_EQ(trie.get({1, 2}).second,       nullptr);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
