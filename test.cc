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

	EXPECT_EQ(trie.resolve({1, 1, 1, 1}).first,  true);
	EXPECT_NE(trie.resolve({1, 1, 1, 1}).second, nullptr);

	EXPECT_EQ(trie.resolve({1, 2, 1, 2}).first,  true);
	EXPECT_NE(trie.resolve({1, 2, 1, 2}).second, nullptr);

	EXPECT_EQ(trie.resolve({1, 2}).first,        true);
	EXPECT_NE(trie.resolve({1, 2}).second,       nullptr);

	EXPECT_EQ(trie.resolve({1, 1, 2, 3}).first,  false);
	EXPECT_EQ(trie.resolve({1, 1, 2, 3}).second, nullptr);

	EXPECT_EQ(trie.resolve({2, 1, 4}).first,     false);
	EXPECT_EQ(trie.resolve({2, 1, 4}).second,    nullptr);
}

TEST_F(TrieTest, Remove) {
	Trie<uint8_t> trie;

	trie.add({1, 1, 1, 1});
	trie.add({1, 2, 1, 2});
	trie.add({2, 3, 4, 5});
	trie.add({2, 3, 1, 2});

	trie.remove({1, 1, 1, 1});

	EXPECT_EQ(trie.resolve({1, 1, 1, 1}).first,  false);
	EXPECT_EQ(trie.resolve({1, 1, 1, 1}).second, nullptr);

	EXPECT_EQ(trie.resolve({1, 2, 1, 2}).first,  true);
	EXPECT_NE(trie.resolve({1, 2, 1, 2}).second, nullptr);

	trie.remove({2, 3});

	EXPECT_EQ(trie.resolve({2, 3, 4, 5}).first,  false);
	EXPECT_EQ(trie.resolve({2, 3, 4, 5}).second, nullptr);

	EXPECT_EQ(trie.resolve({2, 3}).first,        false);
	EXPECT_EQ(trie.resolve({2, 3}).second,       nullptr);

	EXPECT_EQ(trie.resolve({2}).first,           true);
	EXPECT_NE(trie.resolve({2}).second,          nullptr);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
