#ifndef VKL_VK_ALLOCATOR_H
#define VKL_VK_ALLOCATOR_H

#include <cstddef>
#include <cstdlib>
#include <vulkan/vulkan.h>

namespace vkl_vk
{

class VklVkAllocator
{
private:
    VkAllocationCallbacks* callbacks = nullptr;
public:
    VklVkAllocator();
    ~VklVkAllocator();
public:
    inline operator VkAllocationCallbacks*() const
    {
        return callbacks;
    }
private:
    static void* VKAPI_CALL mVkAllocation(
        void* pUserData, 
        size_t size, 
        size_t alignment, 
        VkSystemAllocationScope allocationScope);
    static void* VKAPI_CALL mVkReallocation(
        void* pUserData, 
        void* pOriginal,
        size_t size, 
        size_t alignment, 
        VkSystemAllocationScope allocationScope);
    static void VKAPI_CALL mVkFree(
        void* pUserData, 
        void* pMemory);
        
    void* mAllocation(
        size_t size, 
        size_t alignment, 
        VkSystemAllocationScope allocationScope);
    void* mReallocation(
        void* pOriginal,
        size_t size, 
        size_t alignment, 
        VkSystemAllocationScope allocationScope);
    void mFree(
        void* pMemory);
};

} // vkl_vk

#endif // VKL_VK_ALLOCATOR_H
