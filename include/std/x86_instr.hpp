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

#ifndef X86_INSTR_HPP
#define X86_INSTR_HPP

#include "os.hpp"

namespace zl {
#if defined __GNUC__ && defined X86
	namespace x87 {
		/* Load PI to FPU stack */
		inline void fldpi() {
			asm volatile(
				"fldpi"
			);
		}
		inline void fld(float x) {
			asm volatile(
				"fld %0;"
				: 
				: "m"(x)
			);
		}
		inline void fldl(double x) {
			asm volatile(
				"fldl %0;"
				:
				: "m"(x)
			);
		}
		inline float fstp() {
			float out;
			asm volatile(
				"fstp %0;"
				: "=m"(out)
			);
			return out;
		}
		inline double fstpl() {
			double out;
			asm volatile(
				"fstpl %0"
				: "=m"(out)
			);
			return out;
		} 

		inline void fsin() {
			asm volatile(
				"fsin;"
			);
		}
		inline void fcos() {
			asm volatile(
				"fcos;"
			);
		}
		inline void fptan() {
			asm volatile(
				"fptan;"
			);
		}
		inline void fpatan() {
			asm volatile(
				"fpatan;"
			);
		}

		/* Other math functions */
		inline void fprem() {
			asm volatile(
				"fprem;"
			);
		}
		inline void fprem1() {
			asm volatile(
				"fprem1;"
			);
		}
		
		inline void fscale() {
			asm volatile(
				"fscale;"
			);
		}
	}
	namespace math_instr {
		inline float sin(float x) {
			x87::fld(x);
			x87::fsin();
			return x87::fstp();
		}
		inline double sin(double x) {
			x87::fldl(x);
			x87::fsin();
			return x87::fstpl();
		}

		inline float cos(float x) {
			x87::fld(x);
			x87::fcos();
			return x87::fstp();
		}
		inline double cos(double x) {
			x87::fldl(x);
			x87::fcos();
			return x87::fstpl();
		}

		inline float tan(float x) {
			x87::fld(x);
			x87::fptan();
			x87::fstpl();
			return x87::fstp();
		}
		inline double tan(double x) {
			x87::fldl(x);
			x87::fptan();
			x87::fstpl();
			return x87::fstpl();
		}

		inline float atan(float x) {
			x87::fld(x);
			x87::fld(1);
			x87::fpatan();
			return x87::fstp();
		}
		inline double atan(double x) {
			x87::fldl(x);
			x87::fldl(1);
			x87::fpatan();
			return x87::fstpl();
		}

		/* fprem() finds the partial remainder, not the full remainder */ 
		inline float fmod(float dividend, float divisor) {
			x87::fld(divisor);
			x87::fld(dividend);
			x87::fprem();
			float res = x87::fstp();
			x87::fstp();
			return res;
		}
		inline double fmod(double dividend, double divisor) {
			x87::fldl(divisor);
			x87::fldl(dividend);
			x87::fprem();
			double res = x87::fstpl();
			x87::fstpl();
			return res;
		}

		inline float ieee_remainder(float dividend, float divisor) {
			x87::fld(divisor);
			x87::fld(dividend);
			x87::fprem1();
			float res = x87::fstp();
			x87::fstp();
			return res;
		}
		inline double ieee_remainder(double dividend, double divisor) {
			x87::fldl(divisor);
			x87::fldl(dividend);
			x87::fprem1();
			double res = x87::fstpl();
			x87::fstpl();
			return res;
		}

		inline float scale(float num, float factor) {
			x87::fld(num);
			x87::fld(factor);
			x87::fscale();
			auto res = x87::fstp();
			x87::fstp();
			return res;
		}
		inline double scale(double num, double factor) {
			x87::fldl(num);
			x87::fldl(factor);
			x87::fscale();
			auto res = x87::fstpl();
			x87::fstpl();
			return res;
		}
	}
#else
#error "Functions, such as fsin(), fcos(), etc. used in std::sin() and std::cos() are not available in your platform/compiler!"
#endif
}

#endif /* X86_INSTR_HPP */