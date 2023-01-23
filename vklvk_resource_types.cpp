#include "vklvk_resource_types.h"

void vkl_vk::initResourceTypes(VklVkCreateResourcePoolInfo* p_resourceTypes)
{
    VklVkCreateResourcePoolInfo* p_resourceType;
    
    // buffers
    p_resourceType = &(p_resourceTypes[VKLVK_POOLTYPE_BUFFER_STANDARD]);
    p_resourceType->length = 2;
    
    p_resourceType->sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    p_resourceType->pNext = nullptr;
    p_resourceType->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    p_resourceType->queueFamilyIndexCount = 0;
    p_resourceType->pQueueFamilyIndices = nullptr;
    p_resourceType->bufferFlags = 0;
    p_resourceType->size = 1024 * 1024;
    p_resourceType->bufferUsage = 
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT | 
        VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    
    // images
    p_resourceType = &(p_resourceTypes[VKLVK_POOLTYPE_IMAGE_STANDARD]);
    p_resourceType->length = 2;
    
    p_resourceType->sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    p_resourceType->pNext = nullptr;
    p_resourceType->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    p_resourceType->queueFamilyIndexCount = 0;
    p_resourceType->pQueueFamilyIndices = nullptr;
    p_resourceType->format = VK_FORMAT_R8G8B8A8_UNORM;
    p_resourceType->imageFlags = 0;
    p_resourceType->imageType = VK_IMAGE_TYPE_2D;
    p_resourceType->extent = {1024, 1024, 1};
    p_resourceType->mipLevels = 10;
    p_resourceType->arrayLayers = 1;
    p_resourceType->samples = VK_SAMPLE_COUNT_1_BIT;
    p_resourceType->tiling = VK_IMAGE_TILING_OPTIMAL;
    p_resourceType->imageUsage = VK_IMAGE_USAGE_SAMPLED_BIT;
    p_resourceType->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    
    // buffer views
    p_resourceType = &(p_resourceTypes[VKLVK_POOLTYPE_BUFFERVIEW_STANDARD]);
    p_resourceType->length = 2;
    
    p_resourceType->sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    p_resourceType->pNext = nullptr;
    p_resourceType->format = VK_FORMAT_R8G8B8A8_UNORM;
    p_resourceType->bufferViewFlags = 0;
    p_resourceType->offset = 0;
    p_resourceType->range = 1024 * 1024;
    
    // image views
    p_resourceType = &(p_resourceTypes[VKLVK_POOLTYPE_IMAGEVIEW_STANDARD]);
    p_resourceType->length = 2;
    
    p_resourceType->sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    p_resourceType->pNext = 0;
    p_resourceType->format = VK_FORMAT_R8G8B8A8_UNORM;
    p_resourceType->imageViewFlags = 0;
    p_resourceType->viewType = VK_IMAGE_VIEW_TYPE_2D;
    p_resourceType->components = {
        VK_COMPONENT_SWIZZLE_R, 
        VK_COMPONENT_SWIZZLE_G, 
        VK_COMPONENT_SWIZZLE_B, 
        VK_COMPONENT_SWIZZLE_A};
    p_resourceType->subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    p_resourceType->subresourceRange.baseMipLevel = 0;
    p_resourceType->subresourceRange.levelCount = 1;
    p_resourceType->subresourceRange.baseArrayLayer = 0;
    p_resourceType->subresourceRange.layerCount = 1;
}

