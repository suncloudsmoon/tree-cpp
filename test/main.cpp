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

#include "../include/std/memory"
#include "../include/std/cmath"

#include <stdio.h>

/* Using C-style printing functions to avoid conflicts with the C++'s std namespace */
int main() {
	// auto p1 = std::make_unique<int>(1);
	// std::unique_ptr<int> p2{ new int{2} };
	// std::unique_ptr<int[]> p3{ new int[3]{} }; 

	// std::swap(p1, p2);

	// printf("Pointer #1: %d\n", *p1.get());
	// printf("Pointer #2: %d\n", *p2.get());

	float num = 10e+50;
	int ch = std::isinf(num);
	printf("Ch is %d\n", ch);
}
