#include "ArrayGPU.hpp"

template <typename T>
ArrayGPU<T>::ArrayGPU(std::size_t size) : BaseArray<T>(size) {
    // Allocate memory on the CPU using new
    this->data_ = new T[size];

    // Allocate memory on the GPU using OpenMP
    this->data_gpu = static_cast<T*>(omp_target_alloc(size * sizeof(T), omp_get_default_device()));
}

template <typename T>
ArrayGPU<T>::~ArrayGPU() {
    // Free memory on the CPU using delete[]
    delete[] this->data_;

    // Free memory on the GPU using OpenMP
    omp_target_free(this->data_gpu, omp_get_default_device());
}

// Add a definition for the getSize function
template <typename T>
std::size_t ArrayGPU<T>::getSize() const {
    return this->size_;
}

template <typename T>
void ArrayGPU<T>::initValue(T value) {
    T* data_gpu = this->data_gpu;
    std::size_t size = this->size_;
    #pragma omp target teams distribute parallel for is_device_ptr(data_gpu)
    for (std::size_t i = 0; i < size; ++i) {
        data_gpu[i] = value;
    }
}

// Add definitions for operator[]
// Note that they access the CPU memory only
template <typename T>
T& ArrayGPU<T>::operator[](std::size_t index) {
    return this->data_[index];
}

template <typename T>
const T& ArrayGPU<T>::operator[](std::size_t index) const {
    return this->data_[index];
}


template <typename T>
void ArrayGPU<T>::syncHostToDevice() {
    // Copy data from host to device
    omp_target_memcpy(this->data_gpu, this->data_, this->size_ * sizeof(T), 0, 0, omp_get_default_device(), omp_get_initial_device());
}

template <typename T>
void ArrayGPU<T>::syncDeviceToHost() {
    // Copy data from device to host
    omp_target_memcpy(this->data_, this->data_gpu, this->size_ * sizeof(T), 0, 0, omp_get_initial_device(), omp_get_default_device());
}


template <typename T>
void ArrayGPU<T>::syncHostToDeviceAsync() {
    // Asynchronous copy from host to device
    omp_target_memcpy_async(this->data_gpu, this->data_, this->size_ * sizeof(T), 0, 0, omp_get_default_device(), omp_get_initial_device(), this->event,NULL);
}

template <typename T>
void ArrayGPU<T>::syncDeviceToHostAsync() {
    // Asynchronous copy from device to host
    omp_target_memcpy_async(this->data_, this->data_gpu, this->size_ * sizeof(T), 0, 0, omp_get_initial_device(), omp_get_default_device(), this->event,NULL);
}



template <typename T>
T* ArrayGPU<T>::getDevicePtr() const {
    // Return the device pointer
    return this->data_gpu;
}


// Explicit instantiation
template class ArrayGPU<int>;