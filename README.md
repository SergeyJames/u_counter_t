# u_counter_t: Avoiding integer type overflows/underflows in C++

## Overview

`u_counter_t` is a C++ utility designed to help developers avoid integer type overflow/underflow. \
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
