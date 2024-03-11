#include "ArrayGPU.hpp"

template <typename T>
ArrayGPU<T>::ArrayGPU(std::size_t size) : BaseArray<T>(size) {
    // Allocate memory on the GPU using OpenMP
    this->data_ = static_cast<T*>(omp_target_alloc(size * sizeof(T), omp_get_default_device()));
}

template <typename T>
ArrayGPU<T>::~ArrayGPU() {
    // Free memory on the GPU using OpenMP
    omp_target_free(this->data_, omp_get_default_device());
}

// Add a definition for the getSize function
template <typename T>
std::size_t ArrayGPU<T>::getSize() const {
    return this->size_;
}

template <typename T>
void ArrayGPU<T>::initValue(T value) {
    T* data = this->data_;
    std::size_t size = this->size_;
    #pragma omp target teams distribute parallel for is_device_ptr(data)
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = value; // Use the passed value for initialization
    }
}
// Explicit instantiation
template class ArrayGPU<int>;