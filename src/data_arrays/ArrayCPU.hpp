#ifndef ARRAYCPU_HPP
#define ARRAYCPU_HPP

#include "ArrayBase.hpp"

template <typename T>
class ArrayCPU : public BaseArray<T> {
public:
    ArrayCPU(std::size_t size);
    ArrayCPU(const std::vector<std::size_t>& dimensions);

    ~ArrayCPU() override;

    // Add operator[]
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // Override initValue
    void initValue(T value) override;
};


#endif // ARRAYCPU_HPP