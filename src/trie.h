#ifndef TRIE_SRC_TRIE_H_
#define TRIE_SRC_TRIE_H_

#include <vector>
#include <map>

template <
	typename Key,
	typename Value = std::nullptr_t
>
class Trie {
	public:
		typedef std::vector<Key> key_list;

		Trie():
			value_(),
			children_() {
			this->value_.first = false;
		}

		inline void add(key_list path) {
			this->add(path, path.begin());
		}

		inline void add(key_list path, Value value) {
			Trie* tmp = this->add(path, path.begin());

			tmp->value_.first  = true;
			tmp->value_.second = value;
		}

		inline void remove(key_list path) {
			this->remove(path, path.begin());
		}

		inline bool check(key_list path) {
			return this->resolve(path).first;
		}

		inline std::pair<bool, Value*> get(key_list path) {
			std::pair<bool, Trie*> tmp(this->resolve(path));

			if ( tmp.first ) {
				if ( tmp.second->value_.first ) {
					return std::make_pair(true, &tmp.second->value_.second);
				} else {
					return std::make_pair(false, nullptr);
				}
			} else {
				return std::make_pair(false, nullptr);
			}
		}

		inline bool set(key_list path, Value value) {
			std::pair<bool, Trie*> tmp(this->resolve(path));

			if ( tmp.first ) {
				tmp.second->value_.first  = true;
				tmp.second->value_.second = value;

				return true;
			} else {
				return false;
			}
		}

	private:
		std::pair<bool, Value> value_;
		std::map<Key, Trie> children_;

		inline Trie* add(
			key_list& path,
			typename key_list::const_iterator currStep
		) {
			if ( currStep != path.end() ) {
				Trie& trie(
					this->children_[*currStep]
				);

				return trie.add(path, ++currStep);
			} else {
				return this;
			}
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

		inline std::pair<bool, Trie*> resolve(key_list path) {
			return this->resolve(path, path.begin());
		}

		inline std::pair<bool, Trie*> resolve(
			key_list& path,
			typename key_list::const_iterator currStep
		) {
			typename std::map<Key, Trie>::iterator matchingTrie(
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

};

#endif  // TRIE_SRC_TRIE_H_
