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

#ifndef ZL_SHARED_PTR_HPP
#define ZL_SHARED_PTR_HPP

namespace std {
	/* Semi-conforming implementation of std::shared_ptr<>. Does not implement weak_ptr yet. */
	template<typename T>
	class shared_ptr {
	public:
		using element_type = T;
		// No weak ptr
	public:
		constexpr shared_ptr() noexcept : ptr{}, counter(new long{}) {}
		template<typename OtherType>
		explicit shared_ptr(OtherType *pointer) : ptr(pointer), counter(new long{1}) {}
		
	private:
		T* ptr;
		long *counter;		
	};
}

#endif /* ZL_SHARED_PTR_HPP */