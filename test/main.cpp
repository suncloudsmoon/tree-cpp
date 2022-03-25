#include "../include/std/memory"

#include <stdio.h>

/* Using C-style printing functions to avoid conflicts with the C++'s std namespace */
int main() {
	std::unique_ptr<int> p1 = std::make_unique<int>(1);
	std::unique_ptr<int> p2{ new int{2} };
	std::unique_ptr<int[]> p3{ new int[3]{} }; 

	std::swap(p1, p2);

	printf("Pointer #1: %d\n", *p1.get());
	printf("Pointer #2: %d\n", *p2.get());
}
