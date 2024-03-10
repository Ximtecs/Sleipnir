#include "StaticArrayGPU.hpp"

template <typename T>
GPUElementProxy<T>& GPUElementProxy<T>::operator=(const GPUElementProxy<T>& other) {
    T* otherData = other.data;
    std::size_t otherIndex = other.index;
    T value;
    #pragma omp target is_device_ptr(otherData)
    {
        value = otherData[otherIndex];
    }
    #pragma omp target is_device_ptr(data)
    {
        data[index] = value;
    }
    return *this;
}

template <typename T>
StaticArrayGPU<T>::StaticArrayGPU(std::size_t size) : dataSize(size) {
    data = new T[dataSize];
    #pragma omp target enter data map(alloc: data[0:dataSize])
}

template <typename T>
StaticArrayGPU<T>::~StaticArrayGPU() {
    #pragma omp target exit data map(delete: data[0:dataSize])
    delete[] data;
}

template <typename T>
GPUElementProxy<T> StaticArrayGPU<T>::operator[](std::size_t index) {
    return GPUElementProxy<T>(data, index);
}

template <typename T>
const T& StaticArrayGPU<T>::operator[](std::size_t index) const {
    T value;
    #pragma omp target map(from: value)
    {
        value = data[index];
    }
    return value;
}