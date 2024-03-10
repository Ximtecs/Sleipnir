#ifndef STATIC_ARRAY_GPU_HPP
#define STATIC_ARRAY_GPU_HPP

#include "StaticArrayBase.hpp"
#include <omp.h>

template <typename T>
class StaticArrayGPU;

template <typename T>
class GPUElementProxy {
private:
    T* data;
    std::size_t index;

public:
    GPUElementProxy(T* data, std::size_t index);
    GPUElementProxy& operator=(const T& value);
    GPUElementProxy& operator=(const GPUElementProxy& other);
    operator T() const;
};

template <typename T>
class StaticArrayGPU : public StaticArrayBase<T> {
private:
    T* data; // Pointer to the data on the GPU
    std::size_t dataSize; // Size of the array

public:
    StaticArrayGPU(std::size_t size); // Constructor
    ~StaticArrayGPU(); // Destructor

    GPUElementProxy<T> operator[](std::size_t index); // Overridden access operator
    const T& operator[](std::size_t index) const override; // Overridden const access operator
    std::size_t size() const override; // Overridden size function
};

#endif // STATIC_ARRAY_GPU_HPP