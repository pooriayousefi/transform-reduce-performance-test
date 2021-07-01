
#pragma once

#include "transform_reduce_tester.h"

namespace {

	/*******************************************************************************/
	/*                     addition-trasform/addition-reduce                       */
	/*******************************************************************************/
	template<typename T>
	auto addition_addition_test(
		const std::vector<size_t> & nIter,
		const std::vector<size_t> & szData)->std::tuple<
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >
		> {

		if constexpr (std::is_arithmetic_v<T>) {

			// test 1 { std::valarray.operator+(...) / std::valarray.sum() }
			std::vector<std::tuple<size_t, size_t, double> > test_1_results;

			// test procedure...
			for (auto i : nIter) {
				for (auto j : szData) {

					// test cases data structures
					std::valarray<T> a(T(0), j), b(T(0), j);

					// random number distribution preparation
					std::random_device rd;
					std::default_random_engine rng{ rd() };

					if constexpr (std::is_integral_v<T>) {
						constexpr T lower_limit = std::numeric_limits<T>::min(), upper_limit = std::numeric_limits<T>::max();
						std::uniform_int_distribution<T> rnd(lower_limit, upper_limit);

						// test case std::valarrays initialization by uniform distributed random numbers
						std::generate(std::begin(a), std::end(a), [&rng, &rnd]() { return rnd(rng); });
						std::generate(std::begin(b), std::end(b), [&rng, &rnd]() { return rnd(rng); });
					}
					else if constexpr (std::is_floating_point_v<T>) {
						constexpr T lower_limit = T(0), upper_limit = T(1);
						std::uniform_real_distribution<T> rnd(lower_limit, upper_limit);

						// test case std::valarrays initialization by uniform distributed random numbers
						std::generate(std::begin(a), std::end(a), [&rng, &rnd]() { return rnd(rng); });
						std::generate(std::begin(b), std::end(b), [&rng, &rnd]() { return rnd(rng); });
					}

					// correctness-test 1
					auto correctness_test_1 = [](const std::valarray<T> & a, const std::valarray<T> & b) {
						auto addval{ a + b };
						auto sum{ addval.sum() };
						return sum;
					};
					auto res1{ correctness_test_1(a, b) };

					// speed-test 1
					auto speed_test_1 = [i](const std::valarray<T> & a, const std::valarray<T> & b) {
						auto ti{ std::chrono::high_resolution_clock::now() };

						for (auto ii{ 0u }; ii < i; ++ii) (a - b).sum();

						auto tf{ std::chrono::high_resolution_clock::now() };
						auto Δt{ std::chrono::duration<double>(tf - ti).count() };
						return Δt;
					};
					auto Δt1{ speed_test_1(a, b) };

					test_1_results.push_back(std::make_tuple(i, j, Δt1));
				}
			}

			// addition-trasform/addition-reduce performance test
			auto test_2_3_4_5_6_7_8_results{ transform_reduce_test<T, std::plus, std::plus>(nIter, szData) };

			return std::make_tuple(
				test_1_results,
				std::get<0u>(test_2_3_4_5_6_7_8_results),
				std::get<1u>(test_2_3_4_5_6_7_8_results),
				std::get<2u>(test_2_3_4_5_6_7_8_results),
				std::get<3u>(test_2_3_4_5_6_7_8_results),
				std::get<4u>(test_2_3_4_5_6_7_8_results),
				std::get<5u>(test_2_3_4_5_6_7_8_results),
				std::get<6u>(test_2_3_4_5_6_7_8_results));
		}
	}
}
