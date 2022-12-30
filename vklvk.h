#ifndef VKL_VK_H
#define VKL_VK_H

#include <cstddef>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VKLVK_TEXT_SUCCESS "VklVk succes"
#define VKLVK_TEXT_CLOSED "VklVk closed"
#define VKLVK_TEXT_INITERROR "VklVk init error"

#define VKLVK_PROP_APPLICATIONNAME "Vulkan_Learning"
#define VKLVK_PROP_APPLICATIONVERSION 1

namespace vkl_vk
{

struct VklVkInstance;

bool initVklVkInstance(vkl_vk::VklVkInstance* p_instance);
bool execVklVkInstance(vkl_vk::VklVkInstance* p_instance);
bool closeVklVkInstance(vkl_vk::VklVkInstance* p_instance);

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
     vkl_vk::VklVkError error;
     VkApplicationInfo appInfo;
     VkInstanceCreateInfo instanceCreateInfo;
     VkInstance vkInstance;
     uint32_t extensionCount = 0;
     uint32_t physicalDeviceCount = 0;
     VkPhysicalDevice* physicalDevices = nullptr;
};

} // vkl_vk

#endif // VKL_VK_H

