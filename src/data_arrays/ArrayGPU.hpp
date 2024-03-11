#ifndef ARRAYGPU_HPP
#define ARRAYGPU_HPP

#include "ArrayBase.hpp"
#include <omp.h> // Include the OpenMP header

template <typename T>
class ArrayGPU : public BaseArray<T> {
public:
    ArrayGPU(std::size_t size);
    ~ArrayGPU() override;

    // Override the getSize function
    std::size_t getSize() const override;

    // Override initValue
    void initValue(T value) override;    
    
    
    // Add operator[]
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;


    void syncHostToDevice();
    void syncDeviceToHost();
    T* getDevicePtr() const;

protected:
    T* data_gpu;
};

#endif // ARRAYGPU_HPP