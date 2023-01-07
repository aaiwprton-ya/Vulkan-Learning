#include "vklvk_allocator.h"

/*
    ALLOCATOR
*/

vkl_vk::VklVkAllocator::VklVkAllocator()
{
    this->callbacks = new VkAllocationCallbacks();
    this->callbacks->pUserData = (void*)this;
    this->callbacks->pfnAllocation = (PFN_vkAllocationFunction)&mVkAllocation;
    this->callbacks->pfnReallocation = (PFN_vkReallocationFunction)&mVkReallocation;
    this->callbacks->pfnFree = (PFN_vkFreeFunction)&mVkFree;
    this->callbacks->pfnInternalAllocation = nullptr;
    this->callbacks->pfnInternalFree = nullptr;
}

vkl_vk::VklVkAllocator::~VklVkAllocator()
{
    delete this->callbacks;
}
    
void* VKAPI_CALL vkl_vk::VklVkAllocator::mVkAllocation(
    void* pUserData, 
    size_t size, 
    size_t alignment, 
    VkSystemAllocationScope allocationScope)
{
    return static_cast<vkl_vk::VklVkAllocator*>(pUserData)->mAllocation(
        size, 
        alignment, 
        allocationScope);
}
    
void* VKAPI_CALL vkl_vk::VklVkAllocator::mVkReallocation(
    void* pUserData, 
    void* pOriginal,
    size_t size, 
    size_t alignment, 
    VkSystemAllocationScope allocationScope)
{
    return static_cast<vkl_vk::VklVkAllocator*>(pUserData)->mReallocation(
        pOriginal, 
        size, 
        alignment, 
        allocationScope);
}
    
void VKAPI_CALL vkl_vk::VklVkAllocator::mVkFree(
    void* pUserData, 
    void* pMemory)
{
    static_cast<vkl_vk::VklVkAllocator*>(pUserData)->mFree(
        pMemory);
}
    
void* vkl_vk::VklVkAllocator::mAllocation(
    size_t size, 
    size_t alignment, 
    VkSystemAllocationScope allocationScope)
{
    return aligned_alloc(alignment, size);
}
    
void* vkl_vk::VklVkAllocator::mReallocation(
    void* pOriginal,
    size_t size, 
    size_t alignment, 
    VkSystemAllocationScope allocationScope)
{
    // WARNING: non aligned reallocation
    return realloc(pOriginal, size);
}
    
void vkl_vk::VklVkAllocator::mFree(
    void* pMemory)
{
    free(pMemory);
}

