#include <assert.h>
#include <exception>
#include <iostream>
#include <limits> 


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
		(n < std::numeric_limits<T>::max()) ?
			++n : throw std::overflow_error{"Integer type overflow"};
		
		return *this;
	}

	u_counter_t& operator--() {
		(n > 0) ? --n : throw std::overflow_error{"Integer type overflow"};
		return *this;
	}

	u_counter_t operator--(int) {
		u_counter_t tmp = *this;
		(this->n > 0) ? this->operator--() : throw std::overflow_error{"Integer type overflow"};
		return tmp;
	}

	u_counter_t operator++(int) {
		u_counter_t tmp = this->n;
		(this->n < std::numeric_limits<T>::max()) ?
			this->operator++() : throw std::overflow_error{"Integer type overflow"};

		return tmp;
	}

	bool operator<(T other) const noexcept {
		return n < other;
	}

	bool operator==(T other) const noexcept {
		return n == other;
	}

	T get() const noexcept { return n; }
private:
	T n{};
};

template<class T>
std::ostream& operator<<(std::ostream& stream, const u_counter_t<T>& counter) {
	stream << counter.get();
	return stream;
}

template<class T>
void basicTestCase() {
	constexpr T almostMax = std::numeric_limits<T>::max() - 3;
	constexpr T max = std::numeric_limits<T>::max();

	std::cout << typeid(almostMax).name() << std::endl;

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

	i = 3;
	try {
		for (;; i--) {
			std::cout << i << std::endl;
		}
	}
	catch(const std::exception& e) {
		assert(i == 0);
		std::cerr << e.what() << '\n';
	}
}


int main() {
	basicTestCase<short>();
	basicTestCase<int>();
	basicTestCase<unsigned>();
	basicTestCase<size_t>();
	return 0;
}
