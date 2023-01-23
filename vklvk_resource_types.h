#ifndef VKL_VK_RESOURCE_TYPES_H
#define VKL_VK_RESOURCE_TYPES_H

#include <vulkan/vulkan.h>

#define VKLVK_PROP_POOLTYPECOUNT 4

namespace vkl_vk
{

enum VklVkResourcePoolType
{
    VKLVK_POOLTYPE_BUFFER_STANDARD, 
    VKLVK_POOLTYPE_IMAGE_STANDARD, 
    VKLVK_POOLTYPE_BUFFERVIEW_STANDARD, 
    VKLVK_POOLTYPE_IMAGEVIEW_STANDARD 
};

class VklVkCreateResourcePoolInfo
{
private:
    VkBufferCreateInfo* buffer = nullptr;
    VkImageCreateInfo* image = nullptr;
    VkBufferViewCreateInfo* bufferView = nullptr;
    VkImageViewCreateInfo* imageView = nullptr;
public:
    ~VklVkCreateResourcePoolInfo()
    {
        if (this->buffer)
        {
            delete this->buffer;
        }
        if (this->image)
        {
            delete this->image;
        }
        if (this->bufferView)
        {
            delete this->bufferView;
        }
        if (this->imageView)
        {
            delete this->imageView;
        }
    }
public:
    uint32_t length = 1;
    
    // all
    VkStructureType sType;
    const void* pNext;
    
    // buffer and image
    VkSharingMode sharingMode;
    uint32_t queueFamilyIndexCount;
    const uint32_t* pQueueFamilyIndices;
    
    // buffer view, image and image view
    VkFormat format;
    
    // buffer create info
    VkBufferCreateFlags bufferFlags;
    VkDeviceSize size;
    VkBufferUsageFlags bufferUsage;
    
    // buffer view create info
    VkBufferViewCreateFlags bufferViewFlags;
    VkDeviceSize offset;
    VkDeviceSize range;
    
    // image create info
    VkImageCreateFlags imageFlags;
    VkImageType imageType;
    VkExtent3D extent;
    uint32_t mipLevels;
    uint32_t arrayLayers;
    VkSampleCountFlagBits samples;
    VkImageTiling tiling;
    VkImageUsageFlags imageUsage;
    VkImageLayout initialLayout;
    
    // image view create info
    VkImageViewCreateFlags imageViewFlags;
    VkImageViewType viewType;
    VkComponentMapping components;
    VkImageSubresourceRange subresourceRange;
    
public:
    inline operator VkBufferCreateInfo*()
    {
        this->buffer = new VkBufferCreateInfo();
        this->buffer->sType = this->sType;
        this->buffer->pNext = this->pNext;
        this->buffer->sharingMode = this->sharingMode;
        this->buffer->queueFamilyIndexCount = this->queueFamilyIndexCount;
        this->buffer->pQueueFamilyIndices = this->pQueueFamilyIndices;
        this->buffer->flags = this->bufferFlags;
        this->buffer->size = this->size;
        this->buffer->usage = this->bufferUsage;
        return this->buffer;
    }
    inline operator VkImageCreateInfo*()
    {
        this->image = new VkImageCreateInfo();
        this->image->sType = this->sType;
        this->image->pNext = this->pNext;
        this->image->sharingMode = this->sharingMode;
        this->image->queueFamilyIndexCount = this->queueFamilyIndexCount;
        this->image->pQueueFamilyIndices = this->pQueueFamilyIndices;
        this->image->format = this->format;
        this->image->flags = this->imageFlags;
        this->image->imageType = this->imageType;
        this->image->extent = this->extent;
        this->image->mipLevels = this->mipLevels;
        this->image->arrayLayers = this->arrayLayers;
        this->image->samples = this->samples;
        this->image->tiling = this->tiling;
        this->image->usage = this->imageUsage;
        this->image->initialLayout = this->initialLayout;
        return this->image;
    }
    inline operator VkBufferViewCreateInfo*()
    {
        this->bufferView = new VkBufferViewCreateInfo();
        this->bufferView->sType = this->sType;
        this->bufferView->pNext = this->pNext;
        this->bufferView->format = this->format;
        this->bufferView->flags = this->bufferViewFlags;
        this->bufferView->offset = this->offset;
        this->bufferView->range = this->range;
        return this->bufferView;
    }
    inline operator VkImageViewCreateInfo*()
    {
        this->imageView = new VkImageViewCreateInfo();
        this->imageView->sType = this->sType;
        this->imageView->pNext = this->pNext;
        this->imageView->format = this->format;
        this->imageView->flags = this->imageViewFlags;
        this->imageView->viewType = this->viewType;
        this->imageView->components = this->components;
        this->imageView->subresourceRange = this->subresourceRange;
        return this->imageView;
    }
};

void initResourceTypes(VklVkCreateResourcePoolInfo* p_resourceTypes);

} // vkl_vk

#endif // VKL_VK_RESOURCE_TYPES_H

