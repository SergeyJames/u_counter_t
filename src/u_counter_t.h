#pragma once

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

	bool operator=(const u_counter_t<T>& other) noexcept {
		if (this->n == other) {
			return this->n;
		}
		this->n = other.get();
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

	bool operator<(const u_counter_t<T>& other) const noexcept {
		return n < other.n;
	}

	bool operator==(T other) const noexcept {
		return n == other;
	}

	bool operator==(const u_counter_t<T>& other) const noexcept {
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
