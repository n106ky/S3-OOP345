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
//using namespace std;
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
		* The following constructor of the functor receives name of the data file, 
			- opens it in binary mode for reading, 
			- reads first int data as total_items, 
			- allocate memory space to hold the data items, 
			- and reads the data items into the allocated memory space.
		+ It prints first five data items and the last three data items as data samples.
	*/

	ProcessData::ProcessData(const std::string& filename) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		std::ifstream infile(filename, std::ios::binary | std::ios::in);
		std::string line{};

		if (!infile.is_open()) {
			throw std::runtime_error("Incorrect filename");
		}

		//while (std::getline(infile, line)) {
		//	std::cout << line << std::endl;
		//}

		try {
			infile.read(reinterpret_cast<char*>(&total_items), sizeof(total_items)); // sizeof(int) is typically 4 bytes
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Runtime error: " << e.what() << std::endl;
			// Additional error handling
		}
		


		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		//std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		//          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		//          << data[total_items - 1] << "]" << std::endl;
	}

	ProcessData::~ProcessData() {
		delete[] data;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

	// TODO You create implementation of function operator(). See workshop instructions for details.
	/*
		The first parameter of this function receives target-filename to which the data is to be written in binary format. 
		The second parameter is a double reference variable for holding computed average value. 
		The third parameter is double reference variable for holding computed variance value.

		You compute the average value by calling computeAvgFactor with the following parameters: data, total_items as the size of the array, and again total_items as divisor. 
		The fourth argument is going to be a variable in which the computed average value is to be stored (received as parameter by this operator).
		
		You compute variance value by calling computeVarFactor with first, second and third arguments same as before, 
		i.e., in the case of computeAvgFactor. 
		The fourth argument is the average value computed by computeAvgFactor and fifth argument is the variable in which the computed variance is to be stored (received as parameter by this operator).
		
		You open the target data file and write the data (total_items, and data) in the format of the input data file data_int.dat.
		
		If the file cannot be opened, raise an exception to inform the client.
	*/
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {
		return 1;
	}




}

// double s = std::reduce(std::execution::seq, x.begin(), x.end());
// thread when empty state is non-joinable, coz no task (function) assigned. 

// Synchronize point = promise, wait for the child to finish
/*
* Do not gurantee which thread comes first
	task(){};
	std::thread t1(task); // the moment we create thread, it is already spawned
	std::thread t2(tasktwo);

	std::cout << "t1's thread id: " << t1.get_id() << std::endl;
	std::cout << "t2's thread id: " << t2.get_id() << std::endl;

	// !!!Synchronize
	t1.join();
	t2.join();

	std::cout << "after join main says HI" << std::endl; // always at last becoz it's execute after synchronize point. 
 
*/

/*
* Functions related:
	std:: thread t;
	t.joinable();
	std::thread::hardware_concurrency();
	std::this_thread::get_id();
*/