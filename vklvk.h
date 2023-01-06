#ifndef VKL_VK_H
#define VKL_VK_H

#include <cstddef>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vklvk_requireds.h"

#define VKLVK_TEXT_SUCCESS "VklVk success"
#define VKLVK_TEXT_CLOSED "VklVk closed"
#define VKLVK_TEXT_INITERROR "VklVk init error"
#define VKLVK_TEXT_CREATEDEVICEERROR "VklVk create device error"

#define VKLVK_PROP_APPLICATIONNAME "Vulkan_Learning"
#define VKLVK_PROP_APPLICATIONVERSION 1

#define VKLVK_PROP_DEVISEQUEUECREATEINFOCOUNT 1
#define VKVKL_PROP_REQUIREDQUEUEFAMILYINDEX_VAL0 0
#define VKVKL_PROP_REQUIREDQUEUECOUNT_VAL0 1

#define VKLVK_PROP_PHYSICALDEVICEINDEX 0

namespace vkl_vk
{

struct VklVkInstance;

bool initVklVkInstance(vkl_vk::VklVkInstance* p_instance);
bool execVklVkInstance(vkl_vk::VklVkInstance* p_instance);
bool closeVklVkInstance(vkl_vk::VklVkInstance* p_instance);

void __initString(const char* source, size_t* length, char* dest);

class VklVkError
{
    friend class VklVkInstance;
    friend bool initVklVkInstance(vkl_vk::VklVkInstance* p_instance);
    friend bool execVklVkInstance(vkl_vk::VklVkInstance* p_instance);
    friend bool closeVklVkInstance(vkl_vk::VklVkInstance* p_instance);
private:
    char* p_text;
    size_t size;
private:
    VklVkError();
    ~VklVkError();
private:
    void clear();
    void setText(const char* text);
public:
    const char* get();
};

struct VklVkInstance
{
public:
     vkl_vk::VklVkError error = {};
     uint32_t instanceLayerPropertyCount = 0;
     VkLayerProperties* p_instanceLayerProperties = nullptr;
     uint32_t instanceExtensionPropertyCount = 0;
     VkExtensionProperties* p_instanceExtensionProperties = nullptr;
     uint32_t enabledInsatnceLayerCount = 0;
     char** pp_enabledInstanceLayerNames = nullptr;
     uint32_t enabledInsatnceExtensionCount = 0;
     char** pp_enabledInstanceExtensionNames = nullptr;
     VkApplicationInfo appInfo = {};
     VkInstanceCreateInfo instanceCreateInfo = {};
     VkInstance vkInstance = {};
     uint32_t physicalDeviceCount = 0;
     VkPhysicalDevice* p_physicalDevices = nullptr;
     VkPhysicalDeviceProperties* p_physicalDeviceProperties = nullptr;
     VkPhysicalDeviceFeatures* p_physicalDeviceFeatures = nullptr;
     VkPhysicalDeviceMemoryProperties* p_physicalDeviceMemoryProperties = nullptr;
     uint32_t* p_queueFamilyPropertyCount = nullptr;
     VkQueueFamilyProperties** pp_queueFamilyProperties = nullptr;
     uint32_t queueCreateInfoCount = 0;
     float** pp_queueCreateInfoPriorities = nullptr;
     VkDeviceQueueCreateInfo* p_queueCreateInfos = nullptr;
     uint32_t* p_deviceLayerPropertyCounts = nullptr;
     VkLayerProperties** pp_deviceLayerProperties = nullptr;
     uint32_t* p_deviceExtensionPropertyCounts = nullptr;
     VkExtensionProperties** pp_deviceExtensionProperties = nullptr;
     uint32_t enabledDeviceLayerCount = 0;
     char** pp_enabledDeviceLayerNames = nullptr;
     uint32_t enabledDeviceExtensionCount = 0;
     char** pp_enabledDeviceExtensionNames = nullptr;
     VkPhysicalDeviceFeatures requiredPhysicalDeviceFeatures = {};
     VkDeviceCreateInfo deviceCreateInfo = {};
     VkDevice device = {};
};

} // vkl_vk

#endif // VKL_VK_H

