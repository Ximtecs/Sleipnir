#ifndef ARRAYCPU_HPP
#define ARRAYCPU_HPP

#include "ArrayBase.hpp"

template <typename T>
class ArrayCPU : public BaseArray<T> {
public:
    ArrayCPU(std::size_t size);
    ~ArrayCPU() override;
    // Add a getSize function
    std::size_t getSize() const;
};


#endif // ARRAYCPU_HPP