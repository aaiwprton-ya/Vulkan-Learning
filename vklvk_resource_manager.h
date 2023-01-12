#ifndef VKL_VK_RESOURCE_MANAGER_H
#define VKL_VK_RESOURCE_MANAGER_H

#include <stdint.h>
#include "vklvk_memory_manager.h"

namespace vkl_vk
{

typedef uint32_t VklVkResourceIndex;
typedef uint32_t VklVkResourcePoolIndex;

struct VklVkCreateResourcePoolInfo
{
public:
    uint32_t resourceNumbers = 1;
    // requireds memory proprties
    // optional memory proprties
    // type -> {buffer, image, array_image, buffer_view, image_view, array_image_view}
    // another properties of current type
};

struct VklVkResourcePool
{
private:
    const VklVkMemoryPool* p_memoryPool;
    // resource array[RESOURCE_NUMBERS]
    // resource index manager
public:
    bool create(VklVkResourceIndex* resourceIndex);
    void free(VklVkResourceIndex* resourceIndex);
};

class VklVkResourceManager // TODO ???
{
private:
    VklVkMemoryManager memoryManager = {};
    // resource pool array[POOL_NUMBERS] 
    // resource pool index manager
public:
    bool createPool(VklVkCreateResourcePoolInfo createInfo, VklVkResourcePoolIndex* resourcePoolIndex);
    bool createResource(VklVkResourcePoolIndex resourcePoolIndex, VklVkResourceIndex* resourceIndex);
    void freeResource(VklVkResourcePoolIndex resourcePoolIndex, VklVkResourceIndex resourceIndex);
};

} // vkl_vk
 
#endif // VKL_VK_RESOURCE_MANAGER_H
