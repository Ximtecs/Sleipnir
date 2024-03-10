#include "ArrayCPU.hpp"
#include <iostream>

int main() {
    // Create a StaticArrayCPU of size 10
    ArrayCPU<int> array(10);

    std::cout << "array.size() = " << array.getSize() << std::endl;

    // Fill the array with some values
//    for (std::size_t i = 0; i < array.size(); ++i) {
//        array[i] = i * 2;
//    }
//
//    // Print the contents of the array
//    for (std::size_t i = 0; i < array.size(); ++i) {
//        std::cout << "array[" << i << "] = " << array[i] << std::endl;
//    }

    return 0;
}