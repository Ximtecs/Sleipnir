#include "ArrayCPU.hpp"

template <typename T>
ArrayCPU<T>::ArrayCPU(std::size_t size) : BaseArray<T>(size) {
    this->data_ = new T[size];
}

template <typename T>
ArrayCPU<T>::ArrayCPU(const std::vector<std::size_t>& dimensions) : BaseArray<T>(dimensions) {
    std::size_t size = BaseArray<T>::calculateTotalSize(dimensions);
    this->data_ = new T[size];
    this->size_ = size;
    this->dim_size = dimensions;
    this->dimensionality = dimensions.size();
}

template <typename T>
ArrayCPU<T>::~ArrayCPU() {
    delete[] this->data_;
}

// Add definitions for operator[]
template <typename T>
T& ArrayCPU<T>::operator[](std::size_t index) {
    return this->data_[index];
}

template <typename T>
const T& ArrayCPU<T>::operator[](std::size_t index) const {
    return this->data_[index];
}

// Add definition for initValue
template <typename T>
void ArrayCPU<T>::initValue(T value) {
    for (std::size_t i = 0; i < this->size_; ++i) {
        this->data_[i] = value;
    }
}


// Explicit instantiation
template class ArrayCPU<int>;
template class ArrayCPU<float>;
template class ArrayCPU<double>;