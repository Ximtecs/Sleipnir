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


    int size = 10000000; 

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




    // Start the timer
    auto startGPU = std::chrono::high_resolution_clock::now();

    arrayGPU.initValue(5);

    // Stop the timer and calculate the elapsed time
    auto stopGPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedGPU = stopGPU - startGPU;
    std::cout << "Time to update GPU array: " << elapsedGPU.count() << " seconds\n";


    int* gpu_data_ptr = arrayGPU.getDevicePtr();

    startGPU = std::chrono::high_resolution_clock::now();
    #pragma omp target teams distribute parallel for is_device_ptr(gpu_data_ptr)
    for (int i = 0; i < size; i++){ 
        gpu_data_ptr[i] = gpu_data_ptr[i] * i;
    }
    stopGPU = std::chrono::high_resolution_clock::now();
    elapsedGPU = stopGPU - startGPU;
    std::cout << "Time to update GPU array: " << elapsedGPU.count() << " seconds\n";
    


    std::cout << "arrayGPU[1] before sync = " << arrayGPU[1] << std::endl;
    std::cout << "arrayGPU[2] before sync = " << arrayGPU[2] << std::endl;

    //arrayGPU.syncDeviceToHost();
    arrayGPU.syncDeviceToHostAsync();
    
    std::cout << "arrayGPU[1] after sync = " << arrayGPU[1] << std::endl;
    std::cout << "arrayGPU[2] after sync = " << arrayGPU[2] << std::endl;



    return 0;
}
