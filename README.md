# u_counter_t | Avoiding integer type overflows/underflows in C++

## Overview

`u_counter_t` is an experimental C++ utility designed to help developers avoid integer type overflow/underflow. \
This proposal aims to provide a simple and effective solution for safely handling integer operations, avoiding common pitfalls associated with integer overflows/underflows.

## Features

- Safe integer operations: Perform arithmetic operations on integers with overflow/underflow protection.
- Avoids `infinitive loops` and `undefined behavior` accorded with integer type overflow/underflow.

## Example

```CPP
try {
    u_counter_t<unsigned short> counter = USHRT_MAX - 1;
    while(1) {
        counter += 2; // This throws an overflow exception. The loop is no longer infinite.
    }
    } catch (const std::overflow_error& e) {
        std::cerr << "Overflow error: " << e.what() << std::endl;
    }
```

## Test

In this project used [googletest](https://github.com/google/googletest) framework.

```shell
$ ./Test/main_test 
[==========] Running 15 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 15 tests from u_counter_t
[ RUN      ] u_counter_t.TestIncrement
[       OK ] u_counter_t.TestIncrement (0 ms)
[ RUN      ] u_counter_t.TestDecrement
[       OK ] u_counter_t.TestDecrement (0 ms)
[ RUN      ] u_counter_t.TestPostIncrement
[       OK ] u_counter_t.TestPostIncrement (0 ms)
[ RUN      ] u_counter_t.TestPostDecrement
[       OK ] u_counter_t.TestPostDecrement (0 ms)
[ RUN      ] u_counter_t.TestOverflow
[       OK ] u_counter_t.TestOverflow (0 ms)
[ RUN      ] u_counter_t.TestUnderflow
[       OK ] u_counter_t.TestUnderflow (0 ms)
[ RUN      ] u_counter_t.TestLessThan
[       OK ] u_counter_t.TestLessThan (0 ms)
[ RUN      ] u_counter_t.TestEqual
[       OK ] u_counter_t.TestEqual (0 ms)
[ RUN      ] u_counter_t.TestPlusEquals
[       OK ] u_counter_t.TestPlusEquals (0 ms)
[ RUN      ] u_counter_t.TestMinusEquals
[       OK ] u_counter_t.TestMinusEquals (0 ms)
[ RUN      ] u_counter_t.TestConstructor
[       OK ] u_counter_t.TestConstructor (0 ms)
[ RUN      ] u_counter_t.TestCopyConstructor
[       OK ] u_counter_t.TestCopyConstructor (0 ms)
[ RUN      ] u_counter_t.TestMoveConstructor
[       OK ] u_counter_t.TestMoveConstructor (0 ms)
[ RUN      ] u_counter_t.TestAssignmentOperator
[       OK ] u_counter_t.TestAssignmentOperator (0 ms)
[ RUN      ] u_counter_t.TestMoveAssignmentOperator
[       OK ] u_counter_t.TestMoveAssignmentOperator (0 ms)
[----------] 15 tests from u_counter_t (0 ms total)

[----------] Global test environment tear-down
[==========] 15 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 15 tests.
```

## Benchmark

In this project used google [benchmark](https://github.com/google/benchmark) framework.

```shell
$ ./Benchmark/main_benchmark
Running ./Benchmark/main_benchmark
Run on (16 X 5000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 16384 KiB (x1)
Load Average: 1.32, 1.29, 1.37
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_u_counter_t_Increment<short>/iterations:1000            10.4 ns         6.35 ns         1000
BM_u_counter_t_Decrement<short>/iterations:1000            5.18 ns         4.43 ns         1000
BM_u_counter_t_PlusEquals<short>/iterations:1000           4.36 ns         3.99 ns         1000
BM_u_counter_t_MinusEquals<short>/iterations:1000          4.57 ns         4.05 ns         1000
BM_BuiltIn_Increment<short>/iterations:1000                1.82 ns         1.49 ns         1000
BM_BuiltIn_Decrement<short>/iterations:1000                1.91 ns         1.58 ns         1000
BM_BuiltIn_PlusEquals<short>/iterations:1000               1.83 ns         1.38 ns         1000
BM_BuiltIn_MinusEquals<short>/iterations:1000              1.93 ns         1.51 ns         1000
BM_u_counter_t_Increment<int>/iterations:1000              4.34 ns         3.99 ns         1000
BM_u_counter_t_Decrement<int>/iterations:1000              4.41 ns         4.10 ns         1000
BM_u_counter_t_PlusEquals<int>/iterations:1000             4.40 ns         4.03 ns         1000
BM_u_counter_t_MinusEquals<int>/iterations:1000            4.55 ns         4.18 ns         1000
BM_BuiltIn_Increment<int>/iterations:1000                  1.85 ns         1.48 ns         1000
BM_BuiltIn_Decrement<int>/iterations:1000                  1.94 ns         1.57 ns         1000
BM_BuiltIn_PlusEquals<int>/iterations:1000                 1.84 ns         1.37 ns         1000
BM_BuiltIn_MinusEquals<int>/iterations:1000                1.95 ns         1.53 ns         1000
BM_u_counter_t_Increment<uint64_t>/iterations:1000         4.47 ns         4.00 ns         1000
BM_u_counter_t_Decrement<uint64_t>/iterations:1000         6.96 ns         5.98 ns         1000
BM_u_counter_t_PlusEquals<uint64_t>/iterations:1000        6.74 ns         5.08 ns         1000
BM_u_counter_t_MinusEquals<uint64_t>/iterations:1000       4.67 ns         4.13 ns         1000
BM_BuiltIn_Increment<uint64_t>/iterations:1000             1.89 ns         1.40 ns         1000
BM_BuiltIn_Decrement<uint64_t>/iterations:1000             1.82 ns         1.48 ns         1000
BM_BuiltIn_PlusEquals<uint64_t>/iterations:1000            2.03 ns         1.49 ns         1000
BM_BuiltIn_MinusEquals<uint64_t>/iterations:1000           1.93 ns         1.52 ns         1000
```
