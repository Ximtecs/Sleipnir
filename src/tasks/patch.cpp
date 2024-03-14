#include "patch.hpp"
    
// Correctly override the update function in the Patch class
void Patch::update() {
    Timing::start("patch_update"); // Start timing the patch update
    // Custom behavior for Patch before calling Task's update
    //std::cout << "Patch with ID " << getId() << " is updating." << std::endl;
    


#ifdef USE_GPU
    float* device_ptr = mem->getDevicePtr();
    Timing::start("patch_update_kernel"); // Start timing the patch update kernel
    #pragma omp target teams distribute parallel for is_device_ptr(device_ptr)
    for (int i = 0; i < patchSize; i++) {
        device_ptr[i] = device_ptr[i] + 1;
    }
    Timing::end("patch_update_kernel"); // End timing the patch update kernel
#else
    Timing::start("patch_update_loop"); // Start timing the patch update kernel
    for (int i = 0; i < patchSize; i++) {
        (*mem)[i] = (*mem)[i] + 1;
    }
    Timing::end("patch_update_loop"); // End timing the patch update kernel

#endif

    // Call the base class update method
    Task::update();
    
    Timing::end("patch_update"); // End timing the patch update
}



int Patch::GetPatchSize() {
    return patchSize;
}

void Patch::SetPatchSize(int size) {
    patchSize = size;
    this->patchSize = size;
    this->dimensionality = 1;
}

void Patch::SetPatchSize(const std::vector<std::size_t>& dimensions) {
    patchSize = 1;
    for (std::size_t i = 0; i < dimensions.size(); i++) {
        patchSize *= dimensions[i];
    }
    this->patchSize = patchSize;
    this->dim_size = dimensions;
    this->dimensionality = dimensions.size();
}

void Patch::FreeMemory() {
    delete mem;
}

void Patch::AllocateMemory() {
#ifdef USE_GPU
    if (dimensionality == 1) {
        mem = new ArrayGPU<float>(patchSize);
    } else {
        mem = new ArrayGPU<float>(dim_size);
    }
    mem = new ArrayGPU<float>(patchSize);
    mem->initValue(0);
#else
    if (dimensionality == 1) {
        mem = new ArrayCPU<float>(patchSize);
    } else {
        mem = new ArrayCPU<float>(dim_size);
    }

    mem->initValue(0);   
#endif
}