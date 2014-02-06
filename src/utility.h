#ifndef TRIE_SRC_UTILITY_H_
#define TRIE_SRC_UTILITY_H_

namespace detail {

template <
	typename Type
>
class optional_ptr {
	public:
		typedef typename std::add_pointer<Type>::type pointer;
		typedef Type element_type;

		optional_ptr():
			value_(false, nullptr) { }

		optional_ptr(pointer ptr):
			value_(true, ptr) { }

		inline operator bool() const {
			return this->value_.first;
		}

		inline pointer get() const {
			return this->value_.second;
		}

	private:
		const std::pair<bool, pointer> value_;

};

}

#endif  // TRIE_SRC_UTILITY_H_
