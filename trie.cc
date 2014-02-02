#include <cstdint>
#include <forward_list>
#include <map>
#include <memory>

#include <cassert>
#include <iostream>

template <
	typename Key
>
class Trie {
	public:
		typedef std::unique_ptr<Trie> ptr;

		Trie():
			children_() { }

		inline void add(std::forward_list<Key> path) {
			this->add(path, path.begin());
		}

		inline void add(std::forward_list<Key>& path,
		                typename std::forward_list<Key>::const_iterator curr) {
			if ( curr != path.end() ) {
				Trie::ptr& trie = this->children_[*curr];

				if ( trie ) {
					trie->add(path, ++curr);
				} else {
					trie.reset(new Trie<Key>());
					trie->add(path, ++curr);
				}
			}
		}

		inline Trie* resolve(std::forward_list<Key> path) const {
			return this->resolve(path, path.begin());
		}

		inline Trie* resolve(
			std::forward_list<Key>& path,
			typename std::forward_list<Key>::const_iterator curr
		) const {
			auto trie = this->children_.find(*curr);

			if ( trie != this->children_.end() ) {
				auto next = ++curr;

				if ( next == path.end() ) {
					return (*trie).second.get();
				} else {
					return (*trie).second->resolve(path, next);
				}
			} else {
				return nullptr;
			}
		}

	protected:
		std::map<Key, Trie::ptr> children_;

};

int main() {
	Trie<uint8_t> test;

	test.add(std::forward_list<uint8_t>{1, 2, 3});
	test.add(std::forward_list<uint8_t>{1, 2, 4});
	test.add(std::forward_list<uint8_t>{2, 1});
	test.add(std::forward_list<uint8_t>{2, 1, 1});

	assert(test.resolve(std::forward_list<uint8_t>{1, 2})    != nullptr);
	assert(test.resolve(std::forward_list<uint8_t>{1, 2, 4}) != nullptr);
	assert(test.resolve(std::forward_list<uint8_t>{3})       == nullptr);
}
