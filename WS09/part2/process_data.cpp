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
#include <numeric>
#include <execution>
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
		//std::cout << "COMPUTE AVG: " << std::endl;
		//std::cout << "arr: " << arr << std::endl;
		//std::cout << "siz: " << size << std::endl;
		//std::cout << "div: " << divisor<< std::endl << std::endl;
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

	/*
	+ Computation of average through multi-threading: 
	  to compute average, you call the function computeAvgFactor in different threads with different parts of the data items divided by partition-indices (the indices are stored in p_indices).
		- bind total_items to the function computeAvgFactor as the divisor parameter.
		- create threads by passing the following arguments to the function:
			- address of the first element of each partition as arr, number of elements in the partition as size, and an element of the resource variable created to hold average-factors as avg.
		- join the threads.
		- add all the average-factors into the variable to hold total average; this should be one of the parameters of the operator() function.

	+ Computation of variance through multi-threading: 
	  to compute variance, you call the function computeVarFactor in different threads with different parts of the data items divided by partition-indices. 
		  You follow a procedure similar to the one you followed while computing the average, with following exceptions:
		- use the average value computed in the previous step as the 4th parameter.
		- bind total_items and the computed average as divisor and avg, respectively, to the function before creating the threads.
		- the last parameter should be an element of the resource variable created to store variance-factors.
		- you add the variance-factors computed by threads to compute the total variance.

	+ You open the target data file and write the data (total_items, and data) in the format of the input data file data_int.dat.
	
	+ Your code must be free from memory leaks.
	+ When binding an argument to a function, consider the following reference:
		- std::bind(...)
	*/
	
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {

		std::vector<std::thread> avgThreads;
		auto bFuncAvg = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3); // std::ref(avg)
		for (int i = 0; i < num_threads; ++i) {
			int start_index = p_indices[i];
			int end_index = p_indices[i + 1];
			int partition_size = end_index - start_index;

			//// RESULTS ARE DIFFERENT: 
			//std::cout << "partition size A - Items/threads : " << total_items / num_threads << std::endl;
			//std::cout << "partition size B - p_indices[i]  : " << partition_size << std::endl;
			//// -> Cannot use total_items/num_threads in placeholder 2

			avgThreads.emplace_back(bFuncAvg, &data[p_indices[i]], partition_size, std::ref(averages[i]));
			avgThreads[i].join();
		}
		//// ALTERNATIVE JOIN THREADS:
		//for (auto& t : threads) {
		//	if (t.joinable()) 
		//		t.join();
		//}
		for (int i = 0; i < num_threads; ++i) {
			avg += averages[i];
		}

		std::vector<std::thread> varThreads;
		auto bFuncVar = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3, std::placeholders::_4); // std::ref(avg)
		for (int i = 0; i < num_threads; ++i) {
			int start_index = p_indices[i];
			int end_index = p_indices[i + 1];
			int partition_size = end_index - start_index;

			varThreads.emplace_back(bFuncVar, &data[p_indices[i]], partition_size, avg, std::ref(variances[i]));
			varThreads[i].join();
		}
		for (int i = 0; i < num_threads; ++i) {
			var += variances[i];
		}


		// WRITE TO FILES:
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
/*
	double s = std::reduce(std::execution::seq, x.begin(), x.end());
	thread when empty state is non-joinable, coz no task (function) assigned.
	Synchronize point = promise, wait for the child to finish

* Does not gurantee which thread comes first
	task(){};
	std::thread t1(task); // the moment we create thread, it is already spawned
	std::thread t2(tasktwo);

	std::cout << "t1's thread id: " << t1.get_id() << std::endl;
	std::cout << "t2's thread id: " << t2.get_id() << std::endl;

	// !!!Synchronize
	t1.join();
	t2.join();

	std::cout << "after join main says HI" << std::endl; // always at last becoz it's execute after synchronize point.

* Functions might be related:
	std:: thread t;
	t.joinable();
	std::thread::hardware_concurrency();
	std::this_thread::get_id();
*/

/*
* Not useful for reading binary files:
	while (std::getline(infile, line)) {
		std::cout << line << std::endl;
	}
*/

/*
	* read():
	+ The first parameter is a pointer to a block of memory where the read data should be stored.
	+ The second parameter is the number of bytes to read from the file.

	* reinterpret_cast<char*>(&total_items):
	+ &total_items takes the address of the variable total_items.
	+ Assuming total_items is an integer, this gives you a pointer to an int.
	+ reinterpret_cast<char*> is a type of casting in C++ that allows you to convert one pointer type to another.
	+ Here, it's converting the pointer to int into a pointer to char.
		- This is necessary because the .read() function expects a char* pointer,
		- which is a pointer to a sequence of bytes
		- (since files are read as a sequence of bytes, regardless of the actual data type).
	+ The reason for using char* is that in the context of I/O operations,
		- data is treated as a raw sequence of bytes.
		- A char is typically the same size as a byte, so a char* is effectively a byte pointer.
*/