#include <iostream>
#include "vklglm.h"
#include "vklglfw.h"
#include "vklvk.h"

using namespace vkl_glm;
using namespace vkl_glfw;
using namespace vkl_vk;

int main(int argc, char** argv)
{
    VklGlmInstance* p_glmInstance = new VklGlmInstance();
    VklGlfwInstance* p_glfwInstance = new VklGlfwInstance();
    VklVkInstance* p_vkInstance = new VklVkInstance();
    
    if (!initVklGlmInstance(p_glmInstance))
    {
        std::cerr << p_glmInstance->error.get() << std::endl;
    }
    if (!initVklGlfwInstance(p_glfwInstance))
    {
        std::cerr << p_glfwInstance->error.get() << std::endl;
    }
    if (!initVklVkInstance(p_vkInstance))
    {
        std::cerr << p_vkInstance->error.get() << std::endl;
    }
    
    std::cout << "Available " 
            << p_vkInstance->extensionCount 
            << " extensions in this Vulkan" 
            << std::endl;
    
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
