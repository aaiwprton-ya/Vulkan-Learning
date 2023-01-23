#ifndef VKL_VK_RESOURCE_MANAGER_H
#define VKL_VK_RESOURCE_MANAGER_H

#include <stdint.h>
#include <new>
#include <vulkan/vulkan.h>
#include "vklvk_memory_manager.h"
#include "vklvk_resource_types.h"

#define VKLVK_PROP_RESOURCEPOOL_MAXCOUNT 4

namespace vkl_vk
{

typedef uint32_t VklVkResourceDesc;
typedef uint32_t VklVkResourcePoolDesc;

struct VklVkResource
{
    VklVkResourcePoolDesc pool = 0;
    VklVkResourceDesc resource = 0;
    union VkResource
    {
        VkBuffer buffer;
        VkImage image;
        VkBufferView bufferView;
        VkImageView imageView;
    };
    VkResource vkRes;
};

class VklVkResourcePool
{
private:
    VkDevice device;
    VkAllocationCallbacks* pAllocator = nullptr;
    const VklVkCreateResourcePoolInfo* p_info = nullptr;
    const VklVkMemoryPool* p_memoryPool = nullptr;
    VkBufferCreateInfo* p_bufferCreateInfo = nullptr;
    VkImageCreateInfo* p_imageCreateInfo = nullptr;
    VkBufferViewCreateInfo* p_bufferViewCreateInfo = nullptr;
    VkImageViewCreateInfo* p_imageViewCreateInfo = nullptr;
private:
    VklVkResource* p_resources = nullptr;
    VklVkResourceDesc* p_descManager = nullptr;
private:
    VklVkResourceDesc take();
    void ret(VklVkResourceDesc desc);
public:
    VklVkResourcePool();
    VklVkResourcePool(
        VkDevice device, 
        VkAllocationCallbacks* pAllocator, 
        const VklVkCreateResourcePoolInfo* p_resourcePoolType);
    ~VklVkResourcePool();
private:
    bool createBuffer(VklVkResource* resource, const VklVkResource* target = nullptr);
    bool createImage(VklVkResource* resource, const VklVkResource* target = nullptr);
    bool createBufferView(VklVkResource* resource, const VklVkResource* target);
    bool createImageView(VklVkResource* resource, const VklVkResource* target);
    void freeBuffer(const VklVkResource* resource);
    void freeImage(const VklVkResource* resource);
    void freeBufferView(const VklVkResource* resource);
    void freeImageView(const VklVkResource* resource);
private:
    bool (VklVkResourcePool::*mfp_create)(VklVkResource* resource, const VklVkResource* target);
    void (VklVkResourcePool::*mfp_free)(const VklVkResource* resource);
public:
    bool create(VklVkResource* resource, const VklVkResource* target = nullptr);
    void free(const VklVkResource* resource);
};

class VklVkResourceManager
{
private:
    VkDevice device;
    VkAllocationCallbacks* pAllocator;
    VklVkMemoryManager memoryManager = {};
private:
    VklVkCreateResourcePoolInfo p_resourcePoolTypes[VKLVK_PROP_POOLTYPECOUNT];
    VklVkResourcePool p_resourcePools[VKLVK_PROP_RESOURCEPOOL_MAXCOUNT];
    VklVkResourcePoolDesc p_descManager[VKLVK_PROP_RESOURCEPOOL_MAXCOUNT];
private:
    VklVkResourcePoolDesc take();
    void ret(VklVkResourcePoolDesc desc);
public:
    VklVkResourceManager(VkDevice device, VkAllocationCallbacks* pAllocator);
    ~VklVkResourceManager();
public:
    bool createPool(
        const VklVkCreateResourcePoolInfo* createInfo, 
        VklVkResourcePoolDesc* resourcePool);
    bool createPool(VklVkResourcePoolType poolType, VklVkResourcePoolDesc* resourcePool);
    void freePool(VklVkResourcePoolDesc resourcePool);
    bool createResource(
        VklVkResourcePoolDesc resourcePool,
        const VklVkResource* target, 
        VklVkResource* resource);
    bool createResource(VklVkResourcePoolDesc resourcePool, VklVkResource* resource);
    void freeResource(const VklVkResource* resource);
};

} // vkl_vk
 
#endif // VKL_VK_RESOURCE_MANAGER_H

