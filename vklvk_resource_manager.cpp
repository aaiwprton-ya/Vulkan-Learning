#include "vklvk_resource_manager.h"

using namespace vkl_vk;

// VklVkResourcePool
VklVkResourceDesc VklVkResourcePool::take()
{
    VklVkResourceDesc ret = 0;
    for (uint32_t i = 0; i < this->p_info->length; ++i)
    {
        if (this->p_descManager[i])
        {
            ret = p_descManager[i];
            this->p_descManager[i] = 0;
            break;
        }
    }
    return ret;
}

void VklVkResourcePool::ret(VklVkResourceDesc desc)
{
    for (uint32_t i = 0; i < this->p_info->length; ++i)
    {
        if (!this->p_descManager[i])
        {
            this->p_descManager[i] = desc;
            break;
        }
    }
}

VklVkResourcePool::VklVkResourcePool()
{}

VklVkResourcePool::VklVkResourcePool(
        VkDevice device, 
        VkAllocationCallbacks* pAllocator, 
        const VklVkCreateResourcePoolInfo* p_info)
    : device(device), pAllocator(pAllocator), p_info(p_info)
{
    this->p_resources = new VklVkResource[p_info->length];
    this->p_descManager = new VklVkResourceDesc[p_info->length];
    for (uint32_t i = 0; i < p_info->length; ++i)
    {
        this->p_descManager[i] = i + 1;
    }
    
    switch (this->p_info->sType)
    {
    case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO:
        this->p_bufferCreateInfo = new VkBufferCreateInfo();
        this->p_bufferCreateInfo->sType = p_info->sType;
        this->p_bufferCreateInfo->pNext = p_info->pNext;
        this->p_bufferCreateInfo->sharingMode = p_info->sharingMode;
        this->p_bufferCreateInfo->queueFamilyIndexCount = p_info->queueFamilyIndexCount;
        this->p_bufferCreateInfo->pQueueFamilyIndices = p_info->pQueueFamilyIndices;
        this->p_bufferCreateInfo->flags = p_info->bufferFlags;
        this->p_bufferCreateInfo->size = p_info->size;
        this->p_bufferCreateInfo->usage = p_info->bufferUsage;
        this->mfp_create = &VklVkResourcePool::createBuffer;
        this->mfp_free = &VklVkResourcePool::freeBuffer;
        break;
    case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO:
        this->p_imageCreateInfo = new VkImageCreateInfo();
        this->p_imageCreateInfo->sType = p_info->sType;
        this->p_imageCreateInfo->pNext = p_info->pNext;
        this->p_imageCreateInfo->sharingMode = p_info->sharingMode;
        this->p_imageCreateInfo->queueFamilyIndexCount = p_info->queueFamilyIndexCount;
        this->p_imageCreateInfo->pQueueFamilyIndices = p_info->pQueueFamilyIndices;
        this->p_imageCreateInfo->format = p_info->format;
        this->p_imageCreateInfo->flags = p_info->imageFlags;
        this->p_imageCreateInfo->imageType = p_info->imageType;
        this->p_imageCreateInfo->extent = p_info->extent;
        this->p_imageCreateInfo->mipLevels = p_info->mipLevels;
        this->p_imageCreateInfo->arrayLayers = p_info->arrayLayers;
        this->p_imageCreateInfo->samples = p_info->samples;
        this->p_imageCreateInfo->tiling = p_info->tiling;
        this->p_imageCreateInfo->usage = p_info->imageUsage;
        this->p_imageCreateInfo->initialLayout = p_info->initialLayout;
        this->mfp_create = &VklVkResourcePool::createImage;
        this->mfp_free = &VklVkResourcePool::freeImage;
        break;
    case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO:
        this->p_bufferViewCreateInfo = new VkBufferViewCreateInfo();
        this->p_bufferViewCreateInfo->sType = p_info->sType;
        this->p_bufferViewCreateInfo->pNext = p_info->pNext;
        this->p_bufferViewCreateInfo->format = p_info->format;
        this->p_bufferViewCreateInfo->flags = p_info->bufferViewFlags;
        this->p_bufferViewCreateInfo->offset = p_info->offset;
        this->p_bufferViewCreateInfo->range = p_info->range;
        this->mfp_create = &VklVkResourcePool::createBufferView;
        this->mfp_free = &VklVkResourcePool::freeBufferView;
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO:
        this->p_imageViewCreateInfo = new VkImageViewCreateInfo();
        this->p_imageViewCreateInfo->sType = p_info->sType;
        this->p_imageViewCreateInfo->pNext = p_info->pNext;
        this->p_imageViewCreateInfo->format = p_info->format;
        this->p_imageViewCreateInfo->flags = p_info->imageViewFlags;
        this->p_imageViewCreateInfo->viewType = p_info->viewType;
        this->p_imageViewCreateInfo->components = p_info->components;
        this->p_imageViewCreateInfo->subresourceRange = p_info->subresourceRange;
        this->mfp_create = &VklVkResourcePool::createImageView;
        this->mfp_free = &VklVkResourcePool::freeImageView;
        break;
    default:
        break;
    }
}

VklVkResourcePool::~VklVkResourcePool()
{
    if (this->p_info)
    {
        for (uint32_t i = 0; i < this->p_info->length; ++i)
        {
            if (this->p_resources[i].resource)
            {
                (this->*mfp_free)(this->p_resources + i);
            }
        }
        this->p_info = nullptr;
    }
    if (p_bufferCreateInfo)
    {
        delete p_bufferCreateInfo;
        p_bufferCreateInfo = nullptr;
    }
    if (p_imageCreateInfo)
    {
        delete p_imageCreateInfo;
        p_imageCreateInfo = nullptr;
    }
    if (p_bufferViewCreateInfo)
    {
        delete p_bufferViewCreateInfo;
        p_bufferViewCreateInfo = nullptr;
    }
    if (p_imageViewCreateInfo)
    {
        delete p_imageViewCreateInfo;
        p_imageViewCreateInfo = nullptr;
    }
    if (p_resources)
    {
        delete[] p_resources;
        p_resources = nullptr;
    }
    if (p_descManager)
    {
        delete[] p_descManager;
        p_descManager = nullptr;
    }
}

bool VklVkResourcePool::createBuffer(VklVkResource* resource, const VklVkResource* target)
{
    if (vkCreateBuffer(
        this->device, 
        this->p_bufferCreateInfo, 
        this->pAllocator, 
        &(resource->vkRes.buffer)) == VK_SUCCESS)
    {
        resource->resource = this->take();
        this->p_resources[resource->resource - 1] = *resource;
        return true;
    }
    return false;
}

bool VklVkResourcePool::createImage(VklVkResource* resource, const VklVkResource* target)
{
    if (vkCreateImage(
        this->device, 
        this->p_imageCreateInfo, 
        this->pAllocator, 
        &(resource->vkRes.image)) == VK_SUCCESS)
    {
        resource->resource = this->take();
        this->p_resources[resource->resource - 1] = *resource;
        return true;
    }
    return false;
}

bool VklVkResourcePool::createBufferView(VklVkResource* resource, const VklVkResource* target)
{
    if (!target)
    {
        return false;
    }
    this->p_bufferViewCreateInfo->buffer = target->vkRes.buffer;
    if (vkCreateBufferView(
        this->device, 
        this->p_bufferViewCreateInfo, 
        this->pAllocator, 
        &(resource->vkRes.bufferView)) == VK_SUCCESS)
    {
        resource->resource = this->take();
        this->p_resources[resource->resource - 1] = *resource;
        return true;
    }
    return false;
}

bool VklVkResourcePool::createImageView(VklVkResource* resource, const VklVkResource* target)
{
    if (!target)
    {
        return false;
    }
    this->p_imageViewCreateInfo->image = target->vkRes.image;
    if (vkCreateImageView(
        this->device, 
        this->p_imageViewCreateInfo, 
        this->pAllocator, 
        &(resource->vkRes.imageView)) == VK_SUCCESS)
    {
        resource->resource = this->take();
        this->p_resources[resource->resource - 1] = *resource;
        return true;
    }
    return false;
}

void VklVkResourcePool::freeBuffer(const VklVkResource* resource)
{
    if (resource->resource)
    {
        vkDestroyBuffer(
            this->device, 
            this->p_resources[resource->resource - 1].vkRes.buffer, 
            this->pAllocator);
        this->p_resources[resource->resource - 1].resource = 0;
        this->ret(resource->resource);
    }
}

void VklVkResourcePool::freeImage(const VklVkResource* resource)
{
    if (resource->resource)
    {
        vkDestroyImage(
            this->device, 
            this->p_resources[resource->resource - 1].vkRes.image, 
            this->pAllocator);
        this->p_resources[resource->resource - 1].resource = 0;
        this->ret(resource->resource);
    }
}

void VklVkResourcePool::freeBufferView(const VklVkResource* resource)
{
    if (resource->resource)
    {
        vkDestroyBufferView(
            this->device, 
            this->p_resources[resource->resource - 1].vkRes.bufferView, 
            this->pAllocator);
        this->p_resources[resource->resource - 1].resource = 0;
        this->ret(resource->resource);
    }
}

void VklVkResourcePool::freeImageView(const VklVkResource* resource)
{
    if (resource->resource)
    {
        vkDestroyImageView(
            this->device, 
            this->p_resources[resource->resource - 1].vkRes.imageView, 
            this->pAllocator);
        this->p_resources[resource->resource - 1].resource = 0;
        this->ret(resource->resource);
    }
}

bool VklVkResourcePool::create(VklVkResource* resource, const VklVkResource* target)
{
    return (this->*mfp_create)(resource, target);
}

void VklVkResourcePool::free(const VklVkResource* resource)
{
    (this->*mfp_free)(resource);
}

// VklVkResourceManager
VklVkResourcePoolDesc VklVkResourceManager::take()
{
    VklVkResourcePoolDesc ret = 0;
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        if (this->p_descManager[i])
        {
            ret = p_descManager[i];
            this->p_descManager[i] = 0;
            break;
        }
    }
    return ret;
}

void VklVkResourceManager::ret(VklVkResourcePoolDesc desc)
{
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        if (!this->p_descManager[i])
        {
            this->p_descManager[i] = desc;
            break;
        }
    }
}

VklVkResourceManager::VklVkResourceManager(VkDevice device, VkAllocationCallbacks* pAllocator)
    : device(device), pAllocator(pAllocator)
{
    initResourceTypes(this->p_resourcePoolTypes);
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        this->p_descManager[i] = i + 1;
    }
}

VklVkResourceManager::~VklVkResourceManager()
{
    VklVkResourcePoolDesc p_poolDescs[VKLVK_PROP_RESOURCEPOOL_MAXCOUNT];
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        p_poolDescs[i] = i + 1;
    }
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        if (this->p_descManager[i])
        {
            p_poolDescs[this->p_descManager[i] - 1] = 0;
        }
    }
    for (uint32_t i = 0; i < VKLVK_PROP_RESOURCEPOOL_MAXCOUNT; ++i)
    {
        if (p_poolDescs[i])
        {
            this->freePool((VklVkResourcePoolDesc)(i + 1));
        }
    }
}

bool VklVkResourceManager::createPool(
    const VklVkCreateResourcePoolInfo* createInfo, 
    VklVkResourcePoolDesc* resourcePool)
{
    *resourcePool = this->take();
    if (*resourcePool)
    { 
        new (&(p_resourcePools[*resourcePool - 1])) VklVkResourcePool(
            this->device, 
            this->pAllocator, 
            createInfo);
        return true;
    } else
    {
        return false;
    }
}

bool VklVkResourceManager::createPool(
    VklVkResourcePoolType poolType, 
    VklVkResourcePoolDesc* resourcePool)
{
    return this->createPool(&(p_resourcePoolTypes[poolType]), resourcePool);
}

void VklVkResourceManager::freePool(VklVkResourcePoolDesc resourcePool)
{
    this->p_resourcePools[resourcePool - 1].~VklVkResourcePool();
    this->ret(resourcePool);
}

bool VklVkResourceManager::createResource(
    VklVkResourcePoolDesc resourcePool,
    const VklVkResource* target, 
    VklVkResource* resource)
{
    resource->pool = resourcePool;
    return this->p_resourcePools[resourcePool - 1].create(resource, target);
}

bool VklVkResourceManager::createResource(
    VklVkResourcePoolDesc resourcePool, 
    VklVkResource* resource)
{
    resource->pool = resourcePool;
    return this->p_resourcePools[resourcePool - 1].create(resource);
}

void VklVkResourceManager::freeResource(const VklVkResource* resource)
{
    this->p_resourcePools[resource->pool - 1].free(resource);
}

