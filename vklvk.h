#ifndef VKL_VK_H
#define VKL_VK_H

#include <cstddef>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VKLVK_TEXT_SUCCES "VklVk succes"
#define VKLVK_TEXT_CLOSED "VklVk closed"

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
     uint32_t extensionCount = 0;
};

} // vkl_vk

#endif // VKL_VK_H

