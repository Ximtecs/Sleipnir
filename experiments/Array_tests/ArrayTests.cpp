#include "ArrayCPU.hpp"
#include "ArrayGPU.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>

int main() {

    // Get the number of OpenMP devices
    int numDevices = omp_get_num_devices();
    std::cout << "Number of OpenMP devices: " << numDevices << std::endl;

    // Get the default OpenMP device
    int defaultDevice = omp_get_default_device();
    std::cout << "Default OpenMP device: " << defaultDevice << std::endl;


    int size = 1000000; 

    // Create a StaticArrayCPU of size 
    ArrayCPU<int> array(size);
    std::cout << "array.size() = " << array.getSize() << std::endl;

    // Start the timer
    auto startCPU = std::chrono::high_resolution_clock::now();

    // Initialize the array with a value
    array.initValue(5);

    // Stop the timer and calculate the elapsed time
    auto stopCPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedCPU = stopCPU - startCPU;
    std::cout << "Time to update CPU array: " << elapsedCPU.count() << " seconds\n";


    // Create a StaticArrayGPU of size 
    ArrayGPU<int> arrayGPU(size);
    std::cout << "arrayGPU.size() = " << arrayGPU.getSize() << std::endl;



    int* data = static_cast<int*>(omp_target_alloc(size * sizeof(int), omp_get_default_device()));


    // Start the timer
    auto startGPU = std::chrono::high_resolution_clock::now();

    // Initialize the array with a value
    //arrayGPU.initValue(5);

    #pragma omp target teams distribute parallel for is_device_ptr(data)
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = 5; // Use the passed value for initialization
    }

    

    // Stop the timer and calculate the elapsed time
    auto stopGPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedGPU = stopGPU - startGPU;
    std::cout << "Time to update GPU array: " << elapsedGPU.count() << " seconds\n";



    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
