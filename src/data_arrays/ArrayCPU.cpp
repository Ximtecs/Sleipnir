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