
#pragma once

#include <utility>
#include <iomanip>
#include <string>
#include <valarray>
#include <vector>
#include <tuple>

namespace {

	// display
	template<typename T>
	auto test_results_display(const std::string_view& data_type,
		const std::string_view& transform_op,
		const std::string_view& reduce_op,
		const std::tuple<
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >,
		std::vector<std::tuple<size_t, size_t, double> >
		>& test_results)->void {

		std::ofstream ofs;
		std::string filename{ data_type };
		filename += std::string("_") + std::string(transform_op);
		filename += std::string("_") + std::string(reduce_op);
		filename += std::string("_tests_results.txt");
		ofs.open(filename, std::ios::out);
		if (!ofs) throw std::exception("Exception: Cannot open output file.");

		ofs << "\n\t" << data_type << " - " << transform_op << " - " << reduce_op << " test results:\n";

		// test 1 display
		ofs << std::endl 
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by its member methods:"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_1_i : std::get<0u>(test_results)) {
			ofs << "\n\t"
				<< std::setprecision(9) << std::fixed << std::get<0u>(test_1_i) << "\t\t\t"
				<< std::get<1u>(test_1_i) << "\t\t\t"
				<< std::get<2u>(test_1_i);
		}
		ofs << std::endl;

		// test 2 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform(std::execution::seq, ...) and std::accumulate(...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_2_i : std::get<1u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_2_i) << "\t\t\t"
				<< std::get<1u>(test_2_i) << "\t\t\t"
				<< std::get<2u>(test_2_i);
		}
		ofs << std::endl;

		// test 3 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform(std::execution::seq, ...) and std::reduce(std::execution::seq, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_3_i : std::get<2u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_3_i) << "\t\t\t"
				<< std::get<1u>(test_3_i) << "\t\t\t"
				<< std::get<2u>(test_3_i);
		}
		ofs << std::endl;

		// test 4 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform_reduce(std::execution::seq, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_4_i : std::get<3u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_4_i) << "\t\t\t"
				<< std::get<1u>(test_4_i) << "\t\t\t"
				<< std::get<2u>(test_4_i);
		}
		ofs << std::endl;

		// test 5 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform(std::execution::par, ...) and std::reduce(std::execution::par, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_5_i : std::get<4u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_5_i) << "\t\t\t"
				<< std::get<1u>(test_5_i) << "\t\t\t"
				<< std::get<2u>(test_5_i);
		}
		ofs << std::endl;

		// test 6 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform_reduce(std::execution::par, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_6_i : std::get<5u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_6_i) << "\t\t\t"
				<< std::get<1u>(test_6_i) << "\t\t\t"
				<< std::get<2u>(test_6_i);
		}
		ofs << std::endl;

		// test 7 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform(std::execution::par_unseq, ...) and std::reduce(std::execution::par_unseq, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_7_i : std::get<6u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_7_i) << "\t\t\t"
				<< std::get<1u>(test_7_i) << "\t\t\t"
				<< std::get<2u>(test_7_i);
		}
		ofs << std::endl;

		// test 8 display
		ofs << std::endl
			<< "\tstd::valarray<" << data_type << "> - transformation: " << transform_op << " - reduction: " << reduce_op
			<< " - implemented by std::transform_reduce(std::execution::par_unseq, ...):"
			<< "\n\tnumber of tests\t\tsize of data\t\trun-time"
			<< "\n\t---------------\t\t------------\t\t--------";
		for (auto& test_8_i : std::get<7u>(test_results)) {
			ofs << "\n\t"
				<< std::get<0u>(test_8_i) << "\t\t\t"
				<< std::get<1u>(test_8_i) << "\t\t\t"
				<< std::get<2u>(test_8_i);
		}
		ofs << std::endl;
		
		ofs.close();
	}
}
