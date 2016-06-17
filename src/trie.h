#ifndef TRIE_SRC_TRIE_H_
#define TRIE_SRC_TRIE_H_

#include <vector>
#include <map>

#include "utility.h"

template <
	typename Key,
	typename Value = std::nullptr_t
>
class Trie {
	public:
		typedef std::vector<Key> key_list;

		Trie():
			value_(false, Value{}),
			children_() { }

		void add(key_list path) {
			this->add(path.cbegin(), path.cend());
		}

		void add(key_list path, Value value) {
			Trie* const target = this->add(path.cbegin(), path.cend());

			target->value_.first  = true;
			target->value_.second = value;
		}

		void remove(key_list path) {
			this->remove(path.cbegin(), path.cend());
		}

		bool check(key_list path) {
			return this->resolve(path);
		}

		detail::optional_ptr<Value> get() {
			if ( this->value_.first ) {
				return detail::optional_ptr<Value>(&this->value_.second);
			} else {
				return detail::optional_ptr<Value>();
			}
		}

		detail::optional_ptr<Value> get(key_list path) {
			if ( const auto source = this->resolve(path) ) {
				return source.get()->get();
			} else {
				return detail::optional_ptr<Value>();
			}
		}

		void set(const Value& value) {
			this->value_.first  = true;
			this->value_.second = value;
		}

		bool set(key_list path, const Value& value) {
			if ( auto target = this->resolve(path) ) {
				target.get()->set(value);

				return true;
			} else {
				return false;
			}
		}

	private:
		std::pair<bool, Value> value_;
		std::map<Key, Trie> children_;

		Trie* add(
			typename key_list::const_iterator current,
			typename key_list::const_iterator end
		) {
			if ( current != end ) {
				auto element = *current;
				return this->children_[element].add(++current, end);
			} else {
				return this;
			}
		}

		void remove(
			typename key_list::const_iterator current,
			typename key_list::const_iterator end
		) {
			if ( current != end ) {
				typename std::map<Key, Trie>::iterator matching(
					this->children_.find(*current)
				);

				if ( matching != this->children_.cend() ) {
					typename key_list::const_iterator next(
						++current
					);

					if ( next == end ) {
						this->children_.erase(matching);
					} else {
						(*matching).second.remove(next, end);
					}
				}
			}
		}

		detail::optional_ptr<Trie> resolve(key_list path) {
			return this->resolve(path.cbegin(), path.cend());
		}

		detail::optional_ptr<Trie> resolve(
			typename key_list::const_iterator current,
			typename key_list::const_iterator end
		) {
			typename std::map<Key, Trie>::iterator matching(
				this->children_.find(*current)
			);

			if ( matching != this->children_.cend() ) {
				typename key_list::const_iterator next(
					++current
				);

				if ( next == end ) {
					return detail::optional_ptr<Trie>(
						&(*matching).second
					);
				} else {
					return (*matching).second.resolve(next, end);
				}
			} else {
				return detail::optional_ptr<Trie>();
			}
		}

};

#endif  // TRIE_SRC_TRIE_H_
