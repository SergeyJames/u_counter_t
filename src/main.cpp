#include <assert.h>
#include <exception>
#include <iostream>
#include <limits>
#include <limits.h>

#include <stdbool.h>

template<class T>
struct u_counter_t final {
	u_counter_t (T a) noexcept : n{a} {}

	u_counter_t (const u_counter_t& other) noexcept : n{other.n} {}
	u_counter_t (u_counter_t&& other) noexcept : n{std::move(other.n)} {}

	T& operator=(const T& other) noexcept {
		if (this->n == other) {
			return this->n;
		}
		this->n = other;
		return this->n;
	}

	T& operator=(T&& other) noexcept {
		if (this->n == other) {
			return this->n;
		}

		this->n = std::forward<T>(other);
		return this->n;
	}

	u_counter_t& operator++() {
		(n < _max) ? ++n : throw std::overflow_error{"Integer type overflow"};
		return *this;
	}

	u_counter_t& operator--() {
		(n > _min) ? --n : throw std::underflow_error{"Integer type underflow"};
		return *this;
	}

	u_counter_t operator--(int) {
		u_counter_t tmp = *this;
		(this->n > _min) ? this->operator--() : throw std::underflow_error{"Integer type underflow"};
		return tmp;
	}

	u_counter_t operator++(int) {
		u_counter_t tmp = this->n;
		(this->n < _max) ? this->operator++() : throw std::overflow_error{"Integer type overflow"};
		return tmp;
	}

	bool operator<(T other) const noexcept {
		return n < other;
	}

	bool operator==(T other) const noexcept {
		return n == other;
	}

	u_counter_t& operator+=(const u_counter_t& other) {
		T res{};
		if (__builtin_add_overflow(this->n, other.n, &res)) {
			throw std::overflow_error{"Integer type overflow"};
		}

		this->n = res;
		return *this;
	}

	u_counter_t& operator-=(const u_counter_t& other) {
		T res{};
		if (__builtin_sub_overflow(this->n, other.n, &res)) {
			throw std::overflow_error{"Integer type underflow"};
		}

		this->n = res;
		return *this;
	}

	T get() const noexcept { return n; }
private:
	T n{};

	const T _min{std::numeric_limits<T>::min()};
	const T _max{std::numeric_limits<T>::max()};
};

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
