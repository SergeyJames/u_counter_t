#include <assert.h>
#include <exception>
#include <iostream>
#include <limits.h>
#include <limits>
#include <stdbool.h>

#include "u_counter_t.h"

template<class T>
std::ostream& operator<<(std::ostream& stream, const u_counter_t<T>& counter) {
	stream << counter.get();
	return stream;
}

template<class T>
void basicValuesTestCase() {
	if (std::is_unsigned<T>()) {
		constexpr T almostMin = std::numeric_limits<T>::min() + 3;
		constexpr T min = std::numeric_limits<T>::min();

		u_counter_t i = almostMin;
		try {
			for (;; i--) {
				std::cout << i << std::endl;
			}
		}
		catch(const std::exception& e) {
			assert(i == min);
			std::cerr << e.what() << '\n';
		}

		i = std::numeric_limits<T>::max() - 3;
		try {
			for (;; i++) {
				std::cout << i << std::endl;
			}
		}
		catch(const std::exception& e) {
			assert(i == std::numeric_limits<T>::max());
			std::cerr << e.what() << '\n';
		}
	}
	else {
		constexpr T almostMax = std::numeric_limits<T>::max() - 3;
		constexpr T max = std::numeric_limits<T>::max();

		u_counter_t i = almostMax;
		try {
			for (;; i++) {
				std::cout << i << std::endl;
			}
		}
		catch(const std::exception& e) {
			assert(i == max);
			std::cerr << e.what() << '\n';
		}

		i = std::numeric_limits<T>::min() + 3;
		try {
			for (;; i--) {
				std::cout << i << std::endl;
			}
		}
		catch(const std::exception& e) {
			assert(i == std::numeric_limits<T>::min());
			std::cerr << e.what() << '\n';
		}
	}
}

int main() {

	try {
		u_counter_t<uint64_t> counter1 = 0;
		u_counter_t<uint64_t> counter2 = 1;
		for (int i = 0; i < 10000; i++) {
			counter1 += counter2;
		}
	}
	catch(const std::exception& e) 	{
		std::cerr << e.what() << '\n';
	}


	basicValuesTestCase<short>();
	basicValuesTestCase<int>();
	basicValuesTestCase<unsigned>();
	basicValuesTestCase<size_t>();

	u_counter_t<uint64_t> testMax = std::numeric_limits<uint64_t>::max() - 1;
	try {
		while(1) {
			testMax += 2; // This throws an overflow exception. The loop is no longer infinite.
		}
	} catch (const std::overflow_error& e) {
		assert(testMax == std::numeric_limits<uint64_t>::max() - 1);
		std::cerr << "Overflow error: " << e.what() << std::endl;
	}


	u_counter_t<int64_t> testMin = std::numeric_limits<int64_t>::min() + 1;
	try {
		while(1) {
			testMin -= 2; // This throws an underflow exception. The loop is no longer infinite.
		}
	} catch (const std::overflow_error& e) {
		assert(testMin == std::numeric_limits<int64_t>::min() + 1);
		std::cerr << "Overflow error: " << e.what() << std::endl;
	}

	return 0;
}
