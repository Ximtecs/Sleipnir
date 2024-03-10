#include "StaticArrayCPU.hpp"

template <typename T>
StaticArrayCPU<T>::StaticArrayCPU(std::size_t size) : data(size) {}

template <typename T>
T& StaticArrayCPU<T>::operator[](std::size_t index) {
    return data[index];
}

template <typename T>
const T& StaticArrayCPU<T>::operator[](std::size_t index) const {
    return data[index];
}

template <typename T>
std::size_t StaticArrayCPU<T>::size() const {
    return data.size();
}