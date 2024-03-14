#ifndef ARRAY_BASE_HPP
#define ARRAY_BASE_HPP

#include <cstddef>
#include <vector>

template <typename T>
class BaseArray {
public:
    // Constructor for 1D arrays
    BaseArray(std::size_t size) : size_(size) {}
    
    // Constructor for multi-dimensional arrays
    BaseArray(const std::vector<std::size_t>& dimensions)
        : dim_size(dimensions), size_(calculateTotalSize(dimensions)) {}


    virtual ~BaseArray() {} // Provide an empty definition for the destructor
    // Add initValue
    virtual void initValue(T value) = 0;





    virtual std::size_t getSize() const {
        return size_;
    };
    // Get the dimensionality of the array
    std::size_t getDimensionality() const {
        return dimensionality;
    }

    // Get the size of each dimension
    const std::vector<std::size_t>& getDimensions() const {
        return dim_size;
    }

protected:
    std::size_t size_;
    std::vector<std::size_t> dim_size; // Stores the size of each dimension
    int dimensionality;

    T* data_;

    // Calculate the total size of the array from the size of each dimension
    static std::size_t calculateTotalSize(const std::vector<std::size_t>& dimensions) {
        std::size_t totalSize = 1;
        for (std::size_t dimSize : dimensions) {
            totalSize *= dimSize;
        }
        return totalSize;
    }
};

#endif // ARRAY_BASE_HPP