#include "vklglfw.h"

vkl_glfw::VklGlfwError::VklGlfwError()
    : p_text(nullptr), size(0)
{}

vkl_glfw::VklGlfwError::~VklGlfwError()
{
    this->clear();
}

void vkl_glfw::VklGlfwError::clear()
{
    if (this->p_text)
    {
        delete[] this->p_text;
        this->p_text = nullptr;
        this->size = 0;
    }
}

void vkl_glfw::VklGlfwError::setText(const char* p_text)
{
    this->clear();
    if (!p_text)
    {
        return;
    }
    for (const char* ptr = p_text; *ptr != 0; ++ptr)
    {
        this->size += 1;
    }
    this->p_text = new char[this->size];
    char* p_dest = this->p_text;
    const char* p_data = p_text;
    for (size_t i = 0; i < this->size; ++i, ++p_dest, ++p_data)
    {
        *p_dest = *p_data;
    }
    return;
}

const char* vkl_glfw::VklGlfwError::get()
{
    return this->p_text;
}

bool vkl_glfw::initVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* p_window = glfwCreateWindow(
        VKLGLFW_PROP_WNDWIDTH, 
        VKLGLFW_PROP_WNDHEIGHT, 
        VKLGLFW_PROP_WNDTITLE, 
        nullptr, 
        nullptr);
    if (!p_window)
    {
        p_instance->error.setText(VKLGLFW_TEXT_INITERROR);
        return false;
    }
    p_instance->p_window = p_window;
    
    p_instance->error.setText(VKLGLFW_TEXT_SUCCESS);
    return true;
}

bool vkl_glfw::execVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    
    if (glfwWindowShouldClose(p_instance->p_window))
    {
        return false;
    }
    glfwPollEvents();
    
    return true;
}

bool vkl_glfw::closeVklGlfwInstance(vkl_glfw::VklGlfwInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    
    glfwDestroyWindow(p_instance->p_window);
    glfwTerminate();
    
    p_instance->error.setText(VKLGLFW_TEXT_CLOSED);
    return true;
}

