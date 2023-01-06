#include <iostream>
#include "vklglm.h"
#include "vklglfw.h"
#include "vklvk.h"

using namespace vkl_glm;
using namespace vkl_glfw;
using namespace vkl_vk;

void printPropertyBits(
        const char* name, 
        VkFlags flag, 
        VkFlags target)
{
    std::cout << name << ": ";
    if ((target & flag) == target)
    {
        std::cout << "true" << std::endl;
    } else
    {
        std::cout << "false" << std::endl;
    }
}
    
int main(int argc, char** argv)
{
    VklGlmInstance* p_glmInstance = new VklGlmInstance();
    VklGlfwInstance* p_glfwInstance = new VklGlfwInstance();
    VklVkInstance* p_vkInstance = new VklVkInstance();
    
    if (!initVklGlmInstance(p_glmInstance))
    {
        std::cerr << p_glmInstance->error.get() << std::endl;
        return 1;
    }
    if (!initVklGlfwInstance(p_glfwInstance))
    {
        std::cerr << p_glfwInstance->error.get() << std::endl;
        return 1;
    }
    if (!initVklVkInstance(p_vkInstance))
    {
        std::cerr << p_vkInstance->error.get() << std::endl;
        return 1;
    }
    
    // print instance layers
    std::cout << "Available " << p_vkInstance->instanceLayerPropertyCount 
        << " instance layers" << std::endl;
    for (uint32_t i = 0; i < p_vkInstance->instanceLayerPropertyCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "Layer " << i << ": " << std::endl;
        std::cout << "layerName: " 
            << p_vkInstance->p_instanceLayerProperties[i].layerName << std::endl
            << "specVersion: " 
            << p_vkInstance->p_instanceLayerProperties[i].specVersion << std::endl
            << "implementationVersion: " 
            << p_vkInstance->p_instanceLayerProperties[i].implementationVersion << std::endl
            << "description: " 
            << p_vkInstance->p_instanceLayerProperties[i].description << std::endl;
    }
    
    // print instance extensions
    std::cout << "Available " << p_vkInstance->instanceExtensionPropertyCount 
        << " instance extensions" << std::endl;
    for (uint32_t i = 0; i < p_vkInstance->instanceExtensionPropertyCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "Extension " << i << ": " << std::endl;
        std::cout << "extensionName: " 
            << p_vkInstance->p_instanceExtensionProperties[i].extensionName << std::endl
            << "specVersion: " 
            << p_vkInstance->p_instanceLayerProperties[i].specVersion << std::endl;
    }
            
    // print physical device properties
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::string deviceType;
        switch (p_vkInstance->p_physicalDeviceProperties[i].deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            deviceType = "VK_PHYSICAL_DEVICE_TYPE_OTHER";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            deviceType = "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            deviceType = "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            deviceType = "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            deviceType = "VK_PHYSICAL_DEVICE_TYPE_CPU";
            break;
        default:
            deviceType = "None";
            break;
        }
        
        std::cout << std::endl;
        std::cout << "Properties of physicalDevice " << i << ": " << std::endl
            << "\tapiVersion: " 
            << p_vkInstance->p_physicalDeviceProperties[i].apiVersion << std::endl
            << "\tdriverVersion: " 
            << p_vkInstance->p_physicalDeviceProperties[i].driverVersion << std::endl
            << "\tvendorID: " 
            << p_vkInstance->p_physicalDeviceProperties[i].vendorID << std::endl
            << "\tdeviceID: " 
            << p_vkInstance->p_physicalDeviceProperties[i].deviceID << std::endl
            << "\tdeviceType: " 
            << deviceType << std::endl
            << "\tdeviceName: " 
            << p_vkInstance->p_physicalDeviceProperties[i].deviceName << std::endl;
    }
    
    // print memory types
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "In " << p_vkInstance->p_physicalDeviceProperties[i].deviceName 
            << " memoryTypeCount: " 
            << p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryTypeCount << std::endl;
        
        for (uint32_t j = 0; 
            j < p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryTypeCount; 
            ++j)
        {
            VkMemoryPropertyFlags typeFlags = 
                p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryTypes[j].propertyFlags;
            
            std::cout << std::endl;
            std::cout << "\tMemory type " << j << ": " << std::endl;
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_HOST_VISIBLE_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_HOST_COHERENT_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_HOST_CACHED_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_HOST_CACHED_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_PROTECTED_BIT",
                typeFlags, 
                VK_MEMORY_PROPERTY_PROTECTED_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD",
                typeFlags, 
                VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD",
                typeFlags, 
                VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD);
            
            printPropertyBits(
                "\t\tVK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV",
                typeFlags, 
                VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV);
        }
    }
    
    // print memory heaps
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "In " << p_vkInstance->p_physicalDeviceProperties[i].deviceName 
            << " memoryHeapCount: " 
            << p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryHeapCount << std::endl;
        
        for (uint32_t j = 0; 
            j < p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryHeapCount; 
            ++j)
        {
            uint64_t heapSize = 
                p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryHeaps[j].size;
                
            VkMemoryHeapFlags heapFlags = 
                p_vkInstance->p_physicalDeviceMemoryProperties[i].memoryHeaps[j].flags;
            
            std::cout << "\tMemory heap " << j << ": " << std::endl;
            std::cout << "\tSize: " << heapSize / (1024 * 1024) << " Mb" << std::endl;
            
            printPropertyBits(
                "\t\tVK_MEMORY_HEAP_DEVICE_LOCAL_BIT",
                heapFlags, 
                VK_MEMORY_HEAP_DEVICE_LOCAL_BIT);
            
            printPropertyBits(
                "\t\tVK_MEMORY_HEAP_MULTI_INSTANCE_BIT",
                heapFlags, 
                VK_MEMORY_HEAP_MULTI_INSTANCE_BIT);
        }
    }
    
    // print physical device queue family properties
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "In " << p_vkInstance->p_physicalDeviceProperties[i].deviceName
            << " queueFamilyPropertyCount: " 
            << p_vkInstance->p_queueFamilyPropertyCount[i] << std::endl;
            
        for (uint32_t j = 0; j < p_vkInstance->p_queueFamilyPropertyCount[i]; ++j)
        {
            VkQueueFlags queueFlags = p_vkInstance->pp_queueFamilyProperties[i][j].queueFlags;
            std::cout << std::endl;
            std::cout << "\tQueue family " << j << ": " << std::endl
                << "\t\tQueue family count: " 
                << p_vkInstance->pp_queueFamilyProperties[i][j].queueCount << std::endl
                << "\t\ttimestampValidBits: " 
                << p_vkInstance->pp_queueFamilyProperties[i][j].timestampValidBits << std::endl;
            
            printPropertyBits(
                "\t\tVK_QUEUE_GRAPHICS_BIT",
                queueFlags, 
                VK_QUEUE_GRAPHICS_BIT);
            
            printPropertyBits(
                "\t\tVK_QUEUE_COMPUTE_BIT",
                queueFlags, 
                VK_QUEUE_COMPUTE_BIT);
            
            printPropertyBits(
                "\t\tVK_QUEUE_TRANSFER_BIT",
                queueFlags, 
                VK_QUEUE_TRANSFER_BIT);
            
            printPropertyBits(
                "\t\tVK_QUEUE_SPARSE_BINDING_BIT",
                queueFlags, 
                VK_QUEUE_SPARSE_BINDING_BIT);
            
            printPropertyBits(
                "\t\tVK_QUEUE_PROTECTED_BIT",
                queueFlags, 
                VK_QUEUE_PROTECTED_BIT);
            
#ifdef TODO_UNDEFINE // Provided by VK_KHR_video_decode_queue
            printPropertyBits(
                "\t\tVK_QUEUE_VIDEO_DECODE_BIT_KHR",
                queueFlags, 
                VK_QUEUE_VIDEO_DECODE_BIT_KHR);
#endif
            
#ifdef VK_ENABLE_BETA_EXTENSIONS // Provided by VK_KHR_video_encode_queue
            printPropertyBits(
                "\t\tVK_QUEUE_VIDEO_ENCODE_BIT_KHR",
                queueFlags, 
                VK_QUEUE_VIDEO_ENCODE_BIT_KHR);
#endif
            
#ifdef TODO_UNDEFINE // Provided by VK_NV_optical_flow
            printPropertyBits(
                "\t\tVK_QUEUE_OPTICAL_FLOW_BIT_NV",
                queueFlags, 
                VK_QUEUE_OPTICAL_FLOW_BIT_NV);
#endif
        }
    }
    
    // print device layers
    std::cout << std::endl;
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "In " << p_vkInstance->p_physicalDeviceProperties[i].deviceName
            << " available " << p_vkInstance->p_deviceLayerPropertyCounts[i] 
            << " device layers" << std::endl;
        
        for (uint32_t j = 0; j < p_vkInstance->p_deviceLayerPropertyCounts[i]; ++j)
        {
            std::cout << std::endl;
            std::cout << "Layer " << j << ": " << std::endl;
            std::cout << "layerName: " 
                << p_vkInstance->pp_deviceLayerProperties[i][j].layerName << std::endl
                << "specVersion: " 
                << p_vkInstance->pp_deviceLayerProperties[i][j].specVersion << std::endl
                << "implementationVersion: " 
                << p_vkInstance->pp_deviceLayerProperties[i][j].implementationVersion << std::endl
                << "description: " 
                << p_vkInstance->pp_deviceLayerProperties[i][j].description << std::endl;
        }
    }
    
    // print device extensions
    std::cout << std::endl;
    for (uint32_t i = 0; i < p_vkInstance->physicalDeviceCount; ++i)
    {
        std::cout << std::endl;
        std::cout << "In " << p_vkInstance->p_physicalDeviceProperties[i].deviceName
            << " available " << p_vkInstance->p_deviceExtensionPropertyCounts[i] 
            << " device extensions" << std::endl;
        
        for (uint32_t j = 0; j < p_vkInstance->p_deviceExtensionPropertyCounts[i]; ++j)
        {
            std::cout << std::endl;
            std::cout << "Extension " << j << ": " << std::endl;
            std::cout << "extensionName: " 
                << p_vkInstance->pp_deviceExtensionProperties[i][j].extensionName << std::endl
                << "specVersion: " 
                << p_vkInstance->pp_deviceExtensionProperties[i][j].specVersion << std::endl;
        }
    }
    
    bool isExit = false;
    while (!isExit)
    {
        isExit = !execVklGlmInstance(p_glmInstance) || isExit;
        isExit = !execVklGlfwInstance(p_glfwInstance) || isExit;
        isExit = !execVklVkInstance(p_vkInstance) || isExit;
    }
    
    closeVklGlmInstance(p_glmInstance);
    closeVklGlfwInstance(p_glfwInstance);
    closeVklVkInstance(p_vkInstance);
    
    delete p_glmInstance;
    delete p_glfwInstance;
    delete p_vkInstance;

    return 0;
}
