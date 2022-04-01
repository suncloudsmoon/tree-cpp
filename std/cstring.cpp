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

#include <std/cstring>

#include <stddef.h>

#include <cstdlib>

namespace std {
	void* memcpy(void *dest, const void *src, size_t bytes) {
		if (!dest || !src) return dest;
		unsigned char *dest_ch = reinterpret_cast<unsigned char*>(dest);
		const unsigned char *src_ch = reinterpret_cast<const unsigned char*>(src);
		for (size_t i = 0; i < bytes; i++) { dest_ch[i] = src_ch[i]; }
		return dest;
	}
	void* memmove(void *dest, const void *src, size_t bytes) {
		return memcpy(dest, src, bytes);
	}
	void* memset(void *dest, int ch, size_t bytes) {
		/* NULL checking -> implementation-defined behavior */
		if (!dest) return dest;
		unsigned char *dest_ch = reinterpret_cast<unsigned char*>(dest);
		const unsigned char charac = static_cast<const unsigned char>(ch);
		for (size_t i = 0; i < bytes; i++) { dest_ch[i] = charac; }
		return dest;
	}

	int memcmp(const void *src1, const void *src2, size_t bytes) {
		if (!src1 || !src2) return (reinterpret_cast<int>(src1) - reinterpret_cast<int>(src2));
		const unsigned char* src1_ch = reinterpret_cast<const unsigned char*>(src1);
		const unsigned char* src2_ch = reinterpret_cast<const unsigned char*>(src2);
		for (size_t i = 0; i < bytes; i++) 
		{ if (src1_ch[i] != src2_ch[i]) return (src1_ch[i] - src2_ch[i]); }
		return 0;
	}
	const void* memchr(const void *src, int key, size_t bytes) {
		if (!src) return nullptr;
		const unsigned char* src_ch = reinterpret_cast<const unsigned char*>(src);
		const unsigned char key_ch = static_cast<unsigned char>(key);
		for (size_t i = 0; i < bytes; i++) 
		{ if (src_ch[i] == key_ch) return (src_ch + i); }
		return nullptr;
	}

	size_t strlen(const char *src) {
		if (!src) return 0;
		size_t len;
		for (len = 0; src[len]; len++);
		return len;
	}
	char* strcpy(char *dest, const char *src) {
		if (!dest || !src) return dest;
		size_t index;
		for (index = 0; char c = src[index]; index++) { dest[index] = c; }
		dest[index] = '\0';
		return dest;
	}
	char* strncpy(char *dest, const char *src, size_t count) {
		if (!dest || !src) return dest;
		size_t i;
		for (i = 0; i < count; i++) { dest[i] = src[i]; if (!src[i]) break;	}
		for (; i < count; i++) { dest[i] = '\0'; }
		return dest;
	}

	char* strcat(char *dest, const char *src) {
		if (!dest || !src) return dest;
		size_t dest_index = strlen(dest);
		size_t src_index = 0;
		while (char c = src[src_index++]) { dest[dest_index++] = c; }
		dest[dest_index] = '\0';
		return dest;
	}
	char* strncat(char *dest, const char *src, size_t count) {
		if (!dest || !src) return dest;
		size_t dest_index = strlen(dest);
		char c;
		for (size_t i = 0; (i < count) && (c = src[i]); i++) { dest[dest_index++] = c; }
		dest[dest_index] = '\0';
		return dest;
	}
	
	int strcmp(const char *src1, const char *src2) {
		if (!src1 || !src2) return (src1 - src2);
		size_t index = 0;
		unsigned char a, b;
		while ((a = src1[index]) && (b = src2[index])) 
		{ index++; if (a != b) break; }
		return (a - src2[index]);
	}
	int strncmp(const char *src1, const char *src2, size_t count) {
		if (!src1 || !src2) return (src1 - src2);
		char a = '\0', b = '\0';
		for (size_t i = 0; (i < count) && (a = src1[i]) != (b = src2[i]); i++);
		return (a - b);
	}
	const char* strchr(const char *str, int key) {
		if (!str) return nullptr;
		const char key_ch = static_cast<char>(key);
		for(size_t i = 0; ; i++) { 
			char c = str[i]; 
			if (c == key_ch)
				return (str + i);
			if (!c)
				break;
		}
		return nullptr;
	}
	const char* strpbrk(const char *src1, const char *src2) {
		if (!src1 || !src2) return nullptr;
		const size_t src2_len = strlen(src2);
		for (size_t i = 0; char c = src1[i]; i++) {
			for (size_t j = 0; j < src2_len; j++) { if (c == src2[j]) return (src1 + i); }
		}
		return nullptr;
	}

	const char* strrchr(const char *src, int key) {
		if (!src) return nullptr;
		const char key_ch = static_cast<char>(key);
		char *last_occur = nullptr;
		for (char *i = const_cast<char*>(src); char c = *i; i++) { if (c == key_ch) last_occur = i; }
		return last_occur;
	}

	const char* strstr(const char *src1, const char *src2) {
		if (!src1 || !src2) return nullptr;
		size_t src2_len = strlen(src2);
		if (!src2_len) return src1;
		for (char *ptr = const_cast<char*>(src1); char c = *ptr; ptr++) {
			size_t j;
			for (j = 0; j < src2_len; j++)
				if (c != src2[j]) break;
			if (j == src2_len) return ptr;
		}
		return nullptr;
	}

	size_t strspn(const char *src1, const char *src2) {
		if (!src1 || !src2) return 0;
		size_t len = 0;
		for (size_t i = 0; char c = src1[i]; i++) {
			for (size_t j = 0; char check = src2[j]; j++) {
				if (c == check) {
					len++;
					break;
				}
			}
		}
		return len;
	}
	size_t strcspn(const char *src1, const char *src2) {
		if (!src1 || !src2) return 0;
		const size_t src2_len = strlen(src2);
		size_t i;
		for (i = 0; ; i++) {
			if (memcmp(src1 + i, src2, src2_len) == 0) 
				return (i + 1);
			if (!src1[i])
				break;
		}
		return i;
	}
}
