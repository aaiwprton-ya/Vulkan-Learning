#ifndef VKL_GLM_H
#define VKL_GLM_H

#include <cstddef>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define VKLGLM_TEXT_SUCCESS "VklGlm succes"
#define VKLGLM_TEXT_CLOSED "VklGlm closed"

namespace vkl_glm
{

struct VklGlmInstance;

bool initVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);
bool execVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);
bool closeVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);

class VklGlmError
{
    friend class VklGlmInstance;
    friend bool initVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);
    friend bool execVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);
    friend bool closeVklGlmInstance(vkl_glm::VklGlmInstance* p_instance);
private:
    char* p_text;
    size_t size;
private:
    VklGlmError();
    ~VklGlmError();
private:
    void clear();
    void setText(const char* text);
public:
    const char* get();
};

struct VklGlmInstance
{
public:
     vkl_glm::VklGlmError error;
};

} // vkl_glm

#endif // VKL_GLM_H

