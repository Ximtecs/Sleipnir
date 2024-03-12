#include "patch.hpp"
    
// Correctly override the update function in the Patch class
void Patch::update() {
    // Custom behavior for Patch before calling Task's update
    std::cout << "Patch with ID " << getId() << " is updating." << std::endl;
    


#ifdef USE_GPU
    float* device_ptr = mem->getDevicePtr();
    #pragma omp target teams distribute parallel for is_device_ptr(device_ptr)
    for (int i = 0; i < patchSize; i++) {
        device_ptr[i] = device_ptr[i] + 1;
    }
#else
    for (int i = 0; i < patchSize; i++) {
        (*mem)[i] = (*mem)[i] + 1;
    }
#endif

    // Call the base class update method
    Task::update();
}



int Patch::GetPatchSize() {
    return patchSize;
}

void Patch::SetPatchSize(int size) {
    patchSize = size;
}

void Patch::FreeMemory() {
    delete mem;
}

void Patch::AllocateMemory() {
#ifdef USE_GPU
    printf("Allocating memory on the GPU\n");
    mem = new ArrayGPU<float>(patchSize);
    mem->initValue(0);
#else
    printf("Allocating memory on the CPU\n");
    mem = new ArrayCPU<float>(patchSize);
    mem->initValue(0);   
#endif
}