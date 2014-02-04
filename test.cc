#include "trie.h"

#include <cassert>
#include <cstdint>

int main() {
	Trie<uint8_t> test;

	test.add({1, 2, 3});
	test.add({1, 2, 4});
	test.add({2, 1});
	test.add({2, 1, 1});

	assert(test.resolve({1, 2}).second    != nullptr);
	assert(test.resolve({1, 2, 3}).second != nullptr);
	assert(test.resolve({1, 2, 4}).second != nullptr);
	assert(test.resolve({3}).second       == nullptr);

	test.remove({1, 2});

	assert(test.resolve({1, 2, 4}).second == nullptr);
	assert(test.resolve({1, 2, 3}).second == nullptr);
	assert(test.resolve({1, 2}).second    == nullptr);
}
