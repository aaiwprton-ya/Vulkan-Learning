#ifndef VKL_VK_MEMORY_MANAGER_H
#define VKL_VK_MEMORY_MANAGER_H

#include <stdint.h>

typedef uint32_t VklVkMemoryIndex;
typedef uint32_t VklVkMemoryPoolIndex;

namespace vkl_vk
{

struct VklVkCreateMemoryPoolInfo
{
public:
    uint32_t resourceNumbers = 1;
    // requireds memory proprties
    // optional memory proprties
    // size
};

struct VklVkMemoryPool
{
private:
    // size
    // current offset
public:
    bool create(VklVkMemoryIndex* memoryIndex);
    void free(VklVkMemoryIndex* memoryIndex);
};

class VklVkMemoryManager // TODO ???
{
private:
    // memory pool array[POOL_NUMBERS] 
    // memory pool index manager
public:
    // chose memory type
    // allocate memory
    // free memory
    bool createPool(VklVkCreateMemoryPoolInfo createInfo, VklVkMemoryPoolIndex* meomoryPoolIndex);
    bool allocateMemory(VklVkMemoryPoolIndex memoryPoolIndex, VklVkMemoryIndex* memoryIndex);
    void freeMemory(VklVkMemoryPoolIndex memoryPoolIndex, VklVkMemoryIndex memoryIndex);
};

} // vkl_vk
 
#endif // VKL_VK_MEMORY_MANAGER_H
