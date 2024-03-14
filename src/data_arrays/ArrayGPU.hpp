#ifndef ARRAYGPU_HPP
#define ARRAYGPU_HPP

#include "ArrayBase.hpp"
#include <omp.h> // Include the OpenMP header

template <typename T>
class ArrayGPU : public BaseArray<T> {
public:
    ArrayGPU(std::size_t size);
    ArrayGPU(const std::vector<std::size_t>& dimensions);

    ~ArrayGPU() override;

    // Override initValue
    void initValue(T value) override;    
    
    
    // Add operator[]
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;


    // Synchronization functions
    void syncHostToDevice();
    void syncDeviceToHost();

    // Asynchronous functions
    //void syncHostToDeviceAsync();
    //void syncDeviceToHostAsync();
    //void waitForAsyncOperations(); // Wait for asynchronous operations to complete


    T* getDevicePtr() const;


protected:
    T* data_gpu;
   // omp_event_handle_t event; // Event handle for managing dependencies

};

#endif // ARRAYGPU_HPP