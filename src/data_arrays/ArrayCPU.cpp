#include "ArrayCPU.hpp"

template <typename T>
ArrayCPU<T>::ArrayCPU(std::size_t size) : BaseArray<T>(size) {
    this->data_ = new T[size];
}

template <typename T>
ArrayCPU<T>::~ArrayCPU() {
    delete[] this->data_;
}

// Add a definition for the getSize function
template <typename T>
std::size_t ArrayCPU<T>::getSize() const {
    return this->size_;
}

// Explicit instantiation
template class ArrayCPU<int>;