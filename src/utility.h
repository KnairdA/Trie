#ifndef TRIE_SRC_UTILITY_H_
#define TRIE_SRC_UTILITY_H_

namespace detail {

template <
	typename Value
>
struct Result {
	Result():
		value_(false, Value()) { }

	Result(Value value):
		value_(true, value) { }

	inline operator bool() const {
		return this->value_.first;
	}

	inline Value get() const {
		return this->value_.second;
	}

	const std::pair<bool, Value> value_;
};

}

#endif  // TRIE_SRC_UTILITY_H_
