
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "addition_addition_test.h"
#include "multiplication_addition_test.h"
#include "test_display.h"

auto main() -> int
{
	try {
		/*******************************************************************************/
		/*                            initial data preparation                         */
		/*******************************************************************************/

		// number of iterations in each test
		std::vector<size_t> nIter{ 100u, 1000u };

		// data size in each test
		std::vector<size_t> szData{ 100u, 1000u, 10000u, 100000u, 1000000u };

		/*******************************************************************************/
		/*     data type: double / transformation: addition / reduction: addition      */
		/*******************************************************************************/
		auto double_addition_addition_tests_results{ addition_addition_test<double>(nIter, szData) };
		test_results_display<double>("double", "addition", "addition", double_addition_addition_tests_results);

		/*******************************************************************************/
		/*  data type: double / transformation: multiplication / reduction: addition   */
		/*******************************************************************************/
		auto double_multiplication_addition_tests_results{ multiplication_addition_test<double>(nIter, szData) };
		test_results_display<double>("double", "multiplication", "addition", double_multiplication_addition_tests_results);

		return EXIT_SUCCESS;
	}
	catch (const std::exception& xxx) {
		std::cerr << xxx.what() << std::endl;
		return EXIT_FAILURE;
	}
}
