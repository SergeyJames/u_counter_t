#include <benchmark/benchmark.h>

#include "u_counter_t.h"

template <typename T>
static void BM_u_counter_t_Increment(benchmark::State& state) {
	u_counter_t<T> counter = 0;
	for (auto _ : state) {
		++counter;
	}
}

template <typename T>
static void BM_u_counter_t_Decrement(benchmark::State& state) {
	u_counter_t<T> counter = std::numeric_limits<T>::max();
	for (auto _ : state) {
		--counter;
	}
}

template <typename T>
static void BM_u_counter_t_PlusEquals(benchmark::State& state) {
	u_counter_t<T> counter1 = 0;
	u_counter_t<T> counter2 = 1;
	for (auto _ : state) {
		counter1 += counter2;
	}
}

template <typename T>
static void BM_u_counter_t_MinusEquals(benchmark::State& state) {
	u_counter_t<T> counter1 = std::numeric_limits<T>::max();
	u_counter_t<T> counter2 = 1;
	for (auto _ : state) {
		counter1 -= counter2;
	}
}

template <typename T>
static void BM_BuiltIn_Increment(benchmark::State& state) {
	T counter = 0;
	for (auto _ : state) {
		++counter;
	}
}

template <typename T>
static void BM_BuiltIn_Decrement(benchmark::State& state) {
	T counter = std::numeric_limits<T>::max();
	for (auto _ : state) {
		--counter;
	}
}

template <typename T>
static void BM_BuiltIn_PlusEquals(benchmark::State& state) {
	T counter1 = 0;
	T counter2 = 1;
	for (auto _ : state) {
		counter1 += counter2;
	}
}

template <typename T>
static void BM_BuiltIn_MinusEquals(benchmark::State& state) {
	T counter1 = std::numeric_limits<T>::max();
	T counter2 = 1;
	for (auto _ : state) {
		counter1 -= counter2;
	}
}

BENCHMARK_TEMPLATE(BM_u_counter_t_Increment, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_Decrement, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_PlusEquals, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_MinusEquals, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Increment, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Decrement, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_PlusEquals, short)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_MinusEquals, short)->Iterations(1000);

BENCHMARK_TEMPLATE(BM_u_counter_t_Increment, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_Decrement, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_PlusEquals, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_MinusEquals, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Increment, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Decrement, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_PlusEquals, int)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_MinusEquals, int)->Iterations(1000);

BENCHMARK_TEMPLATE(BM_u_counter_t_Increment, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_Decrement, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_PlusEquals, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_u_counter_t_MinusEquals, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Increment, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_Decrement, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_PlusEquals, uint64_t)->Iterations(1000);
BENCHMARK_TEMPLATE(BM_BuiltIn_MinusEquals, uint64_t)->Iterations(1000);

BENCHMARK_MAIN();
