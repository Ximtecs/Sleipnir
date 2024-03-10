#ifndef ARRAY_BASE_HPP
#define ARRAY_BASE_HPP

#include <cstddef>

template <typename T>
class BaseArray {
public:
    BaseArray(std::size_t size) : size_(size) {}
    virtual ~BaseArray() {} // Provide an empty definition for the destructor
    virtual std::size_t getSize() const = 0;


protected:
    std::size_t size_;
    T* data_;
};

#endif // ARRAY_BASE_HPP