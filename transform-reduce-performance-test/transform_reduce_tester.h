
/*************************************************************************************************/
/*                                                                                               */
/*         An infrastructure for transform-reduce algorithm performance tests based on           */
/*          data type, data container, and different standard transformation-reduction           */
/*                                 algorithm implementations.                                    */
/*                                                                                               */
/*                                      Pooria Yousefi                                           */
/*                                   pooriayousefi@aol.com                                       */
/*                         https://www.linkedin.com/in/pooriayousefi/                            */
/*                                          2021                                                 */
/*                                                                                               */
/*************************************************************************************************/

#pragma once

#include <functional>
#include <algorithm>
#include <execution>
#include <valarray>
#include <iterator>
#include <numeric>
#include <random>
#include <chrono>
#include <vector>
#include <limits>
#include <tuple>

namespace {

	// a platform for testing diverse transform and reduce
	// functions with distinct execution policies
	template<typename T, 
		template<typename> typename BinOpReduce, 
		template<typename> typename BinOpTransform>
	auto transform_reduce_test(
		const std::vector<size_t>& nIter,
		const std::vector<size_t>& szData)->std::tuple<
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >, 
		std::vector<std::tuple<size_t, size_t, double> >, 
		std::vector<std::tuple<size_t, size_t, double> >, 
		std::vector<std::tuple<size_t, size_t, double> >, 
		std::vector<std::tuple<size_t, size_t, double> >, 
		std::vector<std::tuple<size_t, size_t, double> > 
		> {
		if constexpr (std::is_arithmetic_v<T> &&
			std::is_invocable_r_v<T, BinOpReduce<T>, const T&, const T&> &&
			std::is_invocable_r_v<T, BinOpTransform<T>, const T&, const T&>) {

			// tests result
			std::vector<std::tuple<size_t, size_t, double> > test_2_results;
			std::vector<std::tuple<size_t, size_t, double> > test_3_results;
			std::vector<std::tuple<size_t, size_t, double> > test_4_results;
			std::vector<std::tuple<size_t, size_t, double> > test_5_results;
			std::vector<std::tuple<size_t, size_t, double> > test_6_results;
			std::vector<std::tuple<size_t, size_t, double> > test_7_results;
			std::vector<std::tuple<size_t, size_t, double> > test_8_results;

			// correctness of results validation
			auto validation = [n = szData[0u]]()-> bool {

				// test cases data structures
				std::valarray<T> a(T(0), n), b(T(0), n);

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

				// correctness-test 2
				auto correctness_test_2 = [n](const std::valarray<T>& a, const std::valarray<T>& b) {
					std::valarray<T> c(T(0), n);
					std::transform(std::execution::seq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
					return std::accumulate(std::begin(c), std::end(c), T(0), BinOpReduce<T>());
				};
				auto res2{ correctness_test_2(a, b) };

				// correctness-test 3
				auto correctness_test_3 = [n](const std::valarray<T>& a, const std::valarray<T>& b) {
					std::valarray<double> c(T(0), n);
					std::transform(std::execution::seq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
					return std::reduce(std::execution::seq, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
				};
				auto res3{ correctness_test_3(a, b) };

				// correctness-test 4
				auto correctness_test_4 = [](const std::valarray<T>& a, const std::valarray<T>& b) {
					return std::transform_reduce(std::execution::seq,
						std::begin(a),
						std::end(a),
						std::begin(b),
						T(0),
						BinOpReduce<T>(),
						BinOpTransform<T>());
				};
				auto res4{ correctness_test_4(a, b) };

				// correctness-test 5
				auto correctness_test_5 = [n](const std::valarray<T>& a, const std::valarray<T>& b) {
					std::valarray<double> c(T(0), n);
					std::transform(std::execution::par, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
					return std::reduce(std::execution::par, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
				};
				auto res5{ correctness_test_5(a, b) };

				// correctness-test 6
				auto correctness_test_6 = [](const std::valarray<T>& a, const std::valarray<T>& b) {
					return std::transform_reduce(std::execution::par,
						std::begin(a),
						std::end(a),
						std::begin(b),
						T(0),
						BinOpReduce<T>(),
						BinOpTransform<T>());
				};
				auto res6{ correctness_test_6(a, b) };

				// correctness-test 7
				auto correctness_test_7 = [n](const std::valarray<T>& a, const std::valarray<T>& b) {
					std::valarray<T> c(T(0), n);
					std::transform(std::execution::par_unseq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
					return std::reduce(std::execution::par_unseq, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
				};
				auto res7{ correctness_test_7(a, b) };

				// correctness-test 8
				auto correctness_test_8 = [](const std::valarray<T>& a, const std::valarray<T>& b) {
					return std::transform_reduce(std::execution::par_unseq,
						std::begin(a),
						std::end(a),
						std::begin(b),
						T(0),
						BinOpReduce<T>(),
						BinOpTransform<T>());
				};
				auto res8{ correctness_test_8(a, b) };

				if ((res2 == res3) &&
					(res3 == res4) &&
					(res4 == res5) &&
					(res5 == res6) &&
					(res6 == res7) &&
					(res7 == res8))
					return true;
				else
					return false;
			};
			if (validation()) {

				// test procedure...
				for (auto i : nIter) {
					for (auto j : szData) {

						// test cases data structures
						std::valarray<double> a(T(0), j), b(T(0), j);

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

						/*******************************************************************************/
						/*          test 2 { std::transform(seq,...) / std::accumulate(...) }          */
						/*******************************************************************************/

						// speed-test 2
						auto speed_test_2 = [i, j](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::valarray<T> c(T(0), j);
								std::transform(std::execution::seq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
								std::accumulate(std::begin(c), std::end(c), T(0), BinOpReduce<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt2{ speed_test_2(a, b) };

						test_2_results.push_back(std::make_tuple(i, j, Δt2));

						/*******************************************************************************/
						/*          test 3 { std::transform(seq,...) / std::reduce(seq,...) }          */
						/*******************************************************************************/

						// speed-test 3
						auto speed_test_3 = [i, j](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::valarray<T> c(T(0), j);
								std::transform(std::execution::seq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
								std::reduce(std::execution::seq, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt3{ speed_test_3(a, b) };

						test_3_results.push_back(std::make_tuple(i, j, Δt3));

						/*******************************************************************************/
						/*                  test 4 { std::transform_reduce(seq,...) }                  */
						/*******************************************************************************/

						// speed-test 4
						auto speed_test_4 = [i](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::transform_reduce(std::execution::seq,
									std::begin(a),
									std::end(a),
									std::begin(b),
									T(0),
									BinOpReduce<T>(),
									BinOpTransform<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt4{ speed_test_4(a, b) };

						test_4_results.push_back(std::make_tuple(i, j, Δt4));

						/*******************************************************************************/
						/*          test 5 { std::transform(par,...) / std::reduce(par,...) }          */
						/*******************************************************************************/

						// speed-test 5
						auto speed_test_5 = [i, j](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::valarray<T> c(T(0), j);
								std::transform(std::execution::par, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
								std::reduce(std::execution::par, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt5{ speed_test_5(a, b) };

						test_5_results.push_back(std::make_tuple(i, j, Δt5));

						/*******************************************************************************/
						/*                  test 6 { std::transform_reduce(par,...) }                  */
						/*******************************************************************************/

						// speed-test 6
						auto speed_test_6 = [i](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::transform_reduce(std::execution::par,
									std::begin(a),
									std::end(a),
									std::begin(b),
									T(0),
									BinOpReduce<T>(),
									BinOpTransform<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt6{ speed_test_6(a, b) };

						test_6_results.push_back(std::make_tuple(i, j, Δt6));

						/*******************************************************************************/
						/*    test 7 { std::transform(par_unseq,...) / std::reduce(par_unseq,...) }    */
						/*******************************************************************************/

						// speed-test 7
						auto speed_test_7 = [i, j](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::valarray<T> c(T(0), j);
								std::transform(std::execution::par_unseq, std::begin(a), std::end(a), std::begin(b), std::begin(c), BinOpTransform<T>());
								std::reduce(std::execution::par_unseq, std::begin(c), std::end(c), T(0), BinOpReduce<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt7{ speed_test_7(a, b) };

						test_7_results.push_back(std::make_tuple(i, j, Δt7));

						/*******************************************************************************/
						/*               test 8 { std::transform_reduce(par_unseq,...) }               */
						/*******************************************************************************/

						// speed-test 8
						auto speed_test_8 = [i](const std::valarray<T>& a, const std::valarray<T>& b) {
							auto ti{ std::chrono::high_resolution_clock::now() };

							for (auto ii{ 0u }; ii < i; ++ii) {
								std::transform_reduce(std::execution::par_unseq,
									std::begin(a),
									std::end(a),
									std::begin(b),
									T(0),
									BinOpReduce<T>(),
									BinOpTransform<T>());
							}

							auto tf{ std::chrono::high_resolution_clock::now() };
							auto Δt{ std::chrono::duration<double>(tf - ti).count() };
							return Δt;
						};
						auto Δt8{ speed_test_8(a, b) };

						test_8_results.push_back(std::make_tuple(i, j, Δt8));
					}
				}

				return std::make_tuple(
					std::move(test_2_results),
					std::move(test_3_results),
					std::move(test_4_results),
					std::move(test_5_results),
					std::move(test_6_results),
					std::move(test_7_results),
					std::move(test_8_results));
			}
			else
				throw std::exception("Exception: Correcteness test results don't have same values.");
		}
	}
}
