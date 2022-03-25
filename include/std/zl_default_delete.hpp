#ifndef ZL_DEFAULT_DELETE_HPP
#define ZL_DEFAULT_DELETE_HPP

namespace std {
	template<typename T>
	struct default_delete {
		void operator()(T *ptr) const { delete ptr; }
	};
	template<typename T>
	struct default_delete<T[]> {
		void operator()(T *ptr) const { delete[] ptr; }
	};
}

#endif /* ZL_DEFAULT_DELETE_HPP */