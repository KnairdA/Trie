#include <cstdint>
#include <forward_list>
#include <map>

#include <cassert>
#include <iostream>

template <
	typename Key
>
class Trie {
	public:
		Trie():
			children_() { }

		inline void add(std::forward_list<Key> path) {
			this->add(path, path.begin());
		}

		inline void add(std::forward_list<Key>& path,
		                typename std::forward_list<Key>::const_iterator curr) {
			if ( curr != path.end() ) {
				Trie& trie = this->children_[*curr];

				trie.add(path, ++curr);
			}
		}

		inline std::pair<bool, const Trie*> resolve(
			std::forward_list<Key> path
		) const {
			return this->resolve(path, path.begin());
		}

		inline std::pair<bool, const Trie*> resolve(
			std::forward_list<Key>& path,
			typename std::forward_list<Key>::const_iterator currStep
		) const {
			auto matchingTrie = this->children_.find(*curr);

			if ( matchingTrie != this->children_.end() ) {
				auto nextStep = ++currStep;

				if ( nextStep == path.end() ) {
					return std::make_pair(true, &(*trie).second);
				} else {
					return (*trie).second.resolve(path, nextStep);
				}
			} else {
				return std::make_pair(false, nullptr);
			}
		}

	private:
		std::map<Key, Trie> children_;

};

int main() {
	Trie<uint8_t> test;

	test.add({1, 2, 3});
	test.add({1, 2, 4});
	test.add({2, 1});
	test.add({2, 1, 1});

	assert(test.resolve({1, 2}).second    != nullptr);
	assert(test.resolve({1, 2, 4}).second != nullptr);
	assert(test.resolve({3}).second       == nullptr);
}