#ifndef PATCH_HPP
#define PATCH_HPP

#include "task.hpp"
#include "ArrayGPU.hpp"
#include "ArrayCPU.hpp"

class Patch : public Task {
protected:
    int patchSize = 0;

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
    int GetPatchSize();

};

#endif // PATCH_HPP
