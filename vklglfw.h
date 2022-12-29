#ifndef VKL_GLFW_H
#define VKL_GLFW_H

#include <cstddef>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VKLGLFW_TEXT_SUCCES "VklGlfw succes"
#define VKLGLFW_TEXT_CLOSED "VklGlfw closed"
#define VKLGLFW_TEXT_INITERROR "VklGlfw init error"

#define VKLGLFW_PROP_WNDWIDTH 800
#define VKLGLFW_PROP_WNDHEIGHT 600
#define VKLGLFW_PROP_WNDTITLE "GLFW window with Vulkan"

namespace vkl_glfw
{

struct VklGlfwInstance;

bool initVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);
bool execVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);
bool closeVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);

class VklGlfwError
{
    friend class VklGlfwInstance;
    friend bool initVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);
    friend bool execVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);
    friend bool closeVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance);
private:
    char* p_text;
    size_t size;
private:
    VklGlfwError();
    ~VklGlfwError();
private:
    void clear();
    void setText(const char* text);
public:
    const char* get();
};

struct VklGlfwInstance
{
public:
     vkl_glfw::VklGlfwError error;
     GLFWwindow* p_window = nullptr;
};

} // vkl_glfw

#endif // VKL_GLFW_H

