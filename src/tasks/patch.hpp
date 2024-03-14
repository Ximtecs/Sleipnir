#ifndef PATCH_HPP
#define PATCH_HPP

#include "task.hpp"
#include "ArrayGPU.hpp"
#include "ArrayCPU.hpp"

class Patch : public Task {
protected:
    int patchSize = 0;
    std::vector<std::size_t> dim_size; // Stores the size of each dimension
    int dimensionality;


#ifdef USE_GPU
    ArrayGPU<float> *mem;
#else
    ArrayCPU<float> *mem;
#endif

public:
    Patch() : Task() {} // Constructor that calls the base class constructor

    // Override the update function
    void update() override;


    void AllocateMemory();
    void FreeMemory();

    void SetPatchSize(int size);
    void SetPatchSize(const std::vector<std::size_t>& dimensions);

    int GetPatchSize();

};

#endif // PATCH_HPP
