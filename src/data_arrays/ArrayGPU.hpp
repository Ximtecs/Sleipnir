#ifndef ARRAYGPU_HPP
#define ARRAYGPU_HPP

#include "ArrayBase.hpp"

template <typename T>
class ArrayGPU : public BaseArray<T> {
public:
    ArrayGPU(std::size_t size);
    ~ArrayGPU() override;

    // Override the getSize function
    std::size_t getSize() const override;

    // Override initValue
    void initValue(T value) override;
};

#endif // ARRAYGPU_HPP