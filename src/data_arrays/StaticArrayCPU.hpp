#ifndef STATIC_ARRAY_CPU_HPP
#define STATIC_ARRAY_CPU_HPP

#include "StaticArrayBase.hpp"
#include <vector>

template <typename T>
class StaticArrayCPU : public StaticArrayBase<T> {
private:
    std::vector<T> data; // Data stored in a vector

public:
    StaticArrayCPU(std::size_t size); // Constructor
    T& operator[](std::size_t index) override; // Overridden access operator
    const T& operator[](std::size_t index) const override; // Overridden const access operator
    std::size_t size() const override; // Overridden size function
};

#endif // STATIC_ARRAY_CPU_HPP