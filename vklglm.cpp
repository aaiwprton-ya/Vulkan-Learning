#include "vklglm.h"

vkl_glm::VklGlmError::VklGlmError()
    : p_text(nullptr), size(0)
{}

vkl_glm::VklGlmError::~VklGlmError()
{
    this->clear();
}

void vkl_glm::VklGlmError::clear()
{
    if (this->p_text)
    {
        delete[] this->p_text;
        this->p_text = nullptr;
        this->size = 0;
    }
}

void vkl_glm::VklGlmError::setText(const char* p_text)
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

const char* vkl_glm::VklGlmError::get()
{
    return this->p_text;
}

bool vkl_glm::initVklGlmInstance(vkl_glm::VklGlmInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    p_instance->error.setText(VKLGLM_TEXT_SUCCESS);
    return true;
}

bool vkl_glm::execVklGlmInstance(vkl_glm::VklGlmInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    return true;
}

bool vkl_glm::closeVklGlmInstance(vkl_glm::VklGlmInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    p_instance->error.setText(VKLGLM_TEXT_CLOSED);
    return true;
}

