#ifndef TRIE_SRC_TRIE_H_
#define TRIE_SRC_TRIE_H_

#include <vector>
#include <map>

template <
	typename Key
>
class Trie {
	public:
		typedef std::vector<Key> key_list;

		Trie():
			children_() { }

		inline void add(key_list path) {
			this->add(path, path.begin());
		}

		inline void add(
			key_list& path,
			typename key_list::const_iterator currStep
		) {
			if ( currStep != path.end() ) {
				Trie& trie(
					this->children_[*currStep]
				);

				trie.add(path, ++currStep);
			}
		}

		inline void remove(key_list path) {
			this->remove(path, path.begin());
		}

		inline void remove(
			key_list& path,
			typename key_list::const_iterator currStep
		) {
			if ( currStep != path.end() ) {
				typename std::map<Key, Trie>::iterator matchingTrie(
					this->children_.find(*currStep)
				);

				if ( matchingTrie != this->children_.end() ) {
					typename key_list::const_iterator nextStep(
						++currStep
					);

					if ( (*matchingTrie).second.children_.empty() ||
					     nextStep == path.end() ) {
						this->children_.erase(matchingTrie);
					} else {
						(*matchingTrie).second.remove(path, nextStep);
					}
				}
			}
		}

		inline std::pair<bool, const Trie*> resolve(key_list path) const {
			return this->resolve(path, path.begin());
		}

		inline std::pair<bool, const Trie*> resolve(
			key_list& path,
			typename key_list::const_iterator currStep
		) const {
			typename std::map<Key, Trie>::const_iterator matchingTrie(
				this->children_.find(*currStep)
			);

			if ( matchingTrie != this->children_.end() ) {
				typename key_list::const_iterator nextStep(
					++currStep
				);

				if ( nextStep == path.end() ) {
					return std::make_pair(true, &(*matchingTrie).second);
				} else {
					return (*matchingTrie).second.resolve(path, nextStep);
				}
			} else {
				return std::make_pair(false, nullptr);
			}
		}

	private:
		std::map<Key, Trie> children_;

};

#endif  // TRIE_SRC_TRIE_H_
