# transform-reduce-performance-test
A functional infrastructure for transform-reduce algorithm performance testing in C++17

This repo is a functional test for knowing which execution policy of the transform-reduce algorithm would be run more performant in different situations.
Testing criteria are data type, container data structure (default is std::valarray which is better for numerical data types), transformation and reduction algorithms, number of repetitions, data chunk size.

Requirements:

Activate -std=c++17 language standard

Install Greek language package on OS
