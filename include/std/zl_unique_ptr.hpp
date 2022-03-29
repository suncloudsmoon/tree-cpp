/*
 * Copyright (c) 2022, suncloudsmoon and the tree-cpp contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ZL_UNIQUE_PTR_HPP
#define ZL_UNIQUE_PTR_HPP

#include "zl_default_delete.hpp"

#include <utility>

namespace std {
	template<typename DataType, typename Deleter = default_delete<DataType>>
	class unique_ptr {
	public:
		using pointer = DataType*;
		using element_type = DataType;
		using deleter_type = Deleter;
	public:
		explicit unique_ptr(pointer p = pointer()) noexcept : ptr(p), del(deleter_type()) {}
		unique_ptr(pointer p, const Deleter &de) noexcept : ptr(p), del(de) {}
		unique_ptr(pointer p, Deleter &&de) noexcept : ptr(p), del(de) {}
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr(unique_ptr &&other) noexcept {
			ptr = other.ptr;
			del = std::move(other.del);
			other.ptr = nullptr;
		}
		~unique_ptr() { if (get()) del(get()); }
		unique_ptr& operator=(const unique_ptr&) = delete;
		template<typename OtherType, typename OtherDeleter>
		unique_ptr& operator=(unique_ptr<OtherType, OtherDeleter> &&other) noexcept {
			del(ptr);
			ptr = other.ptr;
			del = std::move(other.del);
			
			other.ptr = nullptr;
			return *this;
		}

		pointer get() const noexcept { return ptr; }
		deleter_type& get_deleter() noexcept { return del; }
		const deleter_type& get_deleter() const noexcept { return del; }
		/* Releases the ownership of the pointer */
		pointer release() noexcept {
			auto *temp = get();
			get() = nullptr;
			return temp;
		}
		/* Calls the deleter of existing pointer and sets the new pointer */
		void reset(pointer p = pointer()) noexcept {
			auto *temp = get();
			get() = p;
			if (temp) get_deleter()(temp);
		}
		void swap(unique_ptr &other) noexcept {
			auto *temp_ptr = get();
			auto temp_deleter = std::move(get_deleter());
			
			ptr = other.ptr;
			del = std::move(other.del);

			other.ptr = temp_ptr;
			other.del = std::move(temp_deleter);
		}

		// Operators
		explicit operator bool() const noexcept { return get(); }
		element_type& operator*() const {
			assert(get(), "[std::unique_ptr<T>::operator*() error] -> trying to deference a null pointer!");
			return *get();
		}
		pointer operator->() const noexcept {
			assert(get(), "[std::unique_ptr<T>::operator->() error] -> trying to access null pointer!");
			return get();
		}
	private:
		pointer ptr;
		deleter_type del;
	};

	template<typename DataType, typename Deleter>
	class unique_ptr<DataType[], Deleter> {
	public:
		using pointer = DataType*;
		using element_type = DataType;
		using deleter_type = Deleter;
	public:
		explicit unique_ptr(pointer p = pointer()) noexcept : ptr(p), del(deleter_type()) {}
		unique_ptr(pointer p, const Deleter &de) noexcept : ptr(p), del(de) {}
		unique_ptr(pointer p, Deleter &&de) noexcept : ptr(p), del(de) {}
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr(unique_ptr &&other) noexcept {
			ptr = other.ptr;
			del = std::move(other.del);
			other.ptr = nullptr;
		}
		~unique_ptr() { if (get()) del(get()); }
		unique_ptr& operator=(const unique_ptr&) = delete;
		template<typename OtherType, typename OtherDeleter>
		unique_ptr& operator=(unique_ptr<OtherType, OtherDeleter> &&other) noexcept {
			del(ptr);
			ptr = other.ptr;
			del = std::move(other.del);
			
			other.ptr = nullptr;
			return *this;
		}

		pointer get() const noexcept { return ptr; }
		deleter_type& get_deleter() noexcept { return del; }
		const deleter_type& get_deleter() const noexcept { return del; }
		/* Releases the ownership of the pointer */
		pointer release() noexcept {
			auto *temp = get();
			get() = nullptr;
			return temp;
		}
		/* Calls the deleter of existing pointer and sets the new pointer */
		void reset(pointer p = pointer()) noexcept {
			auto *temp = get();
			get() = p;
			if (temp) get_deleter()(temp);
		}
		void swap(unique_ptr &other) noexcept {
			auto *temp_ptr = get();
			auto temp_deleter = std::move(get_deleter());
			
			ptr = other.ptr;
			del = std::move(other.del);

			other.ptr = temp_ptr;
			other.del = std::move(temp_deleter);
		}

		// Operators
		explicit operator bool() const noexcept { return get(); }
		element_type& operator[](size_t index) const { return get()[index]; }
	private:
		pointer ptr;
		deleter_type del;
	};

	template<typename T, typename... Args>
	inline unique_ptr<T> make_unique(Args&&... args) { return unique_ptr<T>{ new T{ args... } }; }
	template<typename T>
	inline unique_ptr<T> make_unique(size_t count) { return unique_ptr<T>{ new T[count]() }; }

	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator==(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() == s.get());
	}
	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator!=(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() != s.get());
	}
	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator<(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() < s.get());
	}
	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator<=(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() <= s.get());
	}
	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator>(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() > s.get());
	}
	template<typename FirstType, typename FirstDeleter, typename SecondType, typename SecondDeleter>
	inline bool operator>=(const unique_ptr<FirstType, FirstDeleter> &f, 
							const unique_ptr<SecondType, SecondDeleter> &s) {
		return (f.get() >= s.get());
	}

	template<typename DataType, typename Deleter>
	inline void swap(unique_ptr<DataType, Deleter> &f, unique_ptr<DataType, Deleter> &s) noexcept {
		f.swap(s);
	}
}

#endif /* ZL_UNIQUE_PTR_HPP */