#include "vklvk.h"

vkl_vk::VklVkError::VklVkError()
    : p_text(nullptr), size(0)
{}

vkl_vk::VklVkError::~VklVkError()
{
    this->clear();
}

void vkl_vk::VklVkError::clear()
{
    if (this->p_text)
    {
        delete[] this->p_text;
        this->p_text = nullptr;
        this->size = 0;
    }
}

void vkl_vk::VklVkError::setText(const char* p_text)
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

const char* vkl_vk::VklVkError::get()
{
    return this->p_text;
}

bool vkl_vk::initVklVkInstance(vkl_vk::VklVkInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    p_instance->extensionCount = extensionCount;
    
    p_instance->error.setText(VKLVK_TEXT_SUCCES);
    return true;
}

bool vkl_vk::execVklVkInstance(vkl_vk::VklVkInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    return true;
}

bool vkl_vk::closeVklVkInstance(vkl_vk::VklVkInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    p_instance->error.setText(VKLVK_TEXT_CLOSED);
    return true;
}

