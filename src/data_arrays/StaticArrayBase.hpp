#ifndef STATIC_ARRAY_BASE_HPP
#define STATIC_ARRAY_BASE_HPP

#include <cstddef> // for size_t

template <typename T>
class StaticArrayBase {
public:
    virtual ~StaticArrayBase() {} // Virtual destructor

    virtual T& operator[](std::size_t index) = 0; // Pure virtual access operator
    virtual const T& operator[](std::size_t index) const = 0; // Pure virtual const access operator
    virtual std::size_t size() const = 0; // Pure virtual size function
};

#endif // STATIC_ARRAY_BASE_HPP