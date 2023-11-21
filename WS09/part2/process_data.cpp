// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"

namespace sdds
{
	/*
		+ The following function receives:
			1st argument: array (pointer),
			2nd argument: number of array elements (size)
			3rd argument: divisor
			4th argument: avg

		+ size and divisor are not necessarily same.
			- When size and divisor hold same value, avg will hold average of the array elements.
			- When they are different, avg will hold a value called as average-factor.
		+ For part 1, you will be using same value for size and double.
		+ Use of different values for size and divisor will be useful for multi-threaded implementation in part-2.
	*/
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	/*
		The following function receives:
			1st argument: array (pointer),
			2nd argument : number of array elements(size)
			3rd argument : divisor
			4th argument : average value of the data items
			5th argument : var
		+ Size and divisor are not necessarily same as in the case of computeAvgFactor.
			- When size and divisor hold same value, var will get total variance of the array elements.
			- When they are different, var will hold a value called as variance factor.
		+ For part 1, you will be using same value for size and double.
		+ Use of different values for size and divisor will be useful for multi-threaded implementation in part-2.
	*/
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	/*
	* The following constructor of the functor receives name of the data file
	+ It prints first five data items and the last three data items as data samples.
		* TODO:
		+ Open the file whose name was received as parameter and
		+ read the content into variables "total_items" and "data".
		+ Don't forget to allocate memory for "data".
		+ The file is binary and has the format described in the specs.
	*/
	ProcessData::ProcessData(const std::string& filename, int n_threads) {  
		std::ifstream infile(filename, std::ios::binary | std::ios::in);

		if (!infile.is_open()) {
			throw std::runtime_error("Error: incorrect filename");
		}

		try {
			infile.read(reinterpret_cast<char*>(&total_items), sizeof(total_items)); // reading 4 bytes data form the file, sizeof(int) = 4 bytes.
			if (infile.fail()) {
				throw std::runtime_error("Error: failed to read to total_items");
			}
			data = new int[total_items];
			infile.read(reinterpret_cast<char*>(data), total_items * sizeof(int));
			if (infile.fail()) {
				delete[] data;
				data = nullptr;
				throw std::runtime_error("Error: cannot read to data");
			}
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		infile.close();


		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads; i++)
			p_indices[i] = i * (total_items / num_threads);
		p_indices[num_threads] = total_items;
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.

	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {
		computeAvgFactor(data, total_items, total_items, avg);
		computeVarFactor(data, total_items, total_items, avg, var);

		std::ofstream outfile(target_file, std::ios::binary | std::ios::out);


		outfile.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));

		if (outfile.fail()) {
			throw std::runtime_error("Failed to write the total number of items to the file.");
		}

		outfile.write(reinterpret_cast<char*>(data), total_items * sizeof(int));
		if (outfile.fail()) {
			throw std::runtime_error("Failed to write the data to the file.");
		}

		outfile.close();

		return 0;
	}


}
