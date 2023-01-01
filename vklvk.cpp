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
    
    p_instance->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    p_instance->appInfo.pApplicationName = VKLVK_PROP_APPLICATIONNAME;
    p_instance->appInfo.applicationVersion = VKLVK_PROP_APPLICATIONVERSION;
    p_instance->appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 0);
    
    p_instance->instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    p_instance->instanceCreateInfo.pApplicationInfo = &(p_instance->appInfo);
    
    VkResult result = vkCreateInstance(
        &(p_instance->instanceCreateInfo), 
        nullptr, // allocator
        &(p_instance->vkInstance));
    
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get extension count
    uint32_t extensionCount = 0;
    result = vkEnumerateInstanceExtensionProperties(
        nullptr, // ???
        &extensionCount, 
        nullptr); // ???
    
    p_instance->extensionCount = extensionCount;

    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // TODO geting extensions
    
    // get physical device count
    uint32_t physicalDeviceCount = 0;
    result = vkEnumeratePhysicalDevices(
        p_instance->vkInstance, 
        &physicalDeviceCount, 
        nullptr); // physicalDevices
    
    p_instance->physicalDeviceCount = physicalDeviceCount;
    
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get phisycal devices
    if (p_instance->physicalDevices)
    {
        delete[] p_instance->physicalDevices;
    }
    p_instance->physicalDevices = new VkPhysicalDevice[physicalDeviceCount];
    vkEnumeratePhysicalDevices(
        p_instance->vkInstance, 
        &physicalDeviceCount, 
        p_instance->physicalDevices); // physicalDevices
    
    // get physical device properties
    if (p_instance->p_physicalDeviceProperties)
    {
        delete[] p_instance->p_physicalDeviceProperties;
    }
    p_instance->p_physicalDeviceProperties = new VkPhysicalDeviceProperties[physicalDeviceCount];
    for (uint32_t i = 0; i < physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceProperties(
            p_instance->physicalDevices[i],
            &(p_instance->p_physicalDeviceProperties[i]));
    }
    
    // get physical device features
    if (p_instance->p_physicalDeviceFeatures)
    {
        delete[] p_instance->p_physicalDeviceFeatures;
    }
    p_instance->p_physicalDeviceFeatures = new VkPhysicalDeviceFeatures[physicalDeviceCount];
    for (uint32_t i = 0; i < physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceFeatures(
            p_instance->physicalDevices[i],
            &(p_instance->p_physicalDeviceFeatures[i]));
    }
    
    // get physical device memory properties
    if (p_instance->p_physicalDeviceMemoryProperties)
    {
        delete[] p_instance->p_physicalDeviceMemoryProperties;
    }
    p_instance->p_physicalDeviceMemoryProperties = 
        new VkPhysicalDeviceMemoryProperties[physicalDeviceCount];
    for (uint32_t i = 0; i < physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceMemoryProperties(
            p_instance->physicalDevices[i],
            &(p_instance->p_physicalDeviceMemoryProperties[i]));
    }
    
    // get phisycal device queue family property count
    if (p_instance->p_queueFamilyPropertyCount)
    {
        delete[] p_instance->p_queueFamilyPropertyCount;
    }
    p_instance->p_queueFamilyPropertyCount = new uint32_t[physicalDeviceCount];
    for (uint32_t i = 0; i < physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceQueueFamilyProperties(
            p_instance->physicalDevices[i], 
            &(p_instance->p_queueFamilyPropertyCount[i]),
            nullptr); // VkQueueFamilyProperties*
    }
    
    // get phisycal device queue family properties
    if (p_instance->pp_queueFamilyProperties)
    {
        for (uint32_t i = 0; i < physicalDeviceCount; ++i)
        {
            if (p_instance->pp_queueFamilyProperties[i])
            {
                delete[] p_instance->pp_queueFamilyProperties[i];
            }
        }
        delete[] p_instance->pp_queueFamilyProperties;
    }
    p_instance->pp_queueFamilyProperties = new VkQueueFamilyProperties*[physicalDeviceCount];
    for (uint32_t i = 0; i < physicalDeviceCount; ++i)
    {
        p_instance->pp_queueFamilyProperties[i] = 
            new VkQueueFamilyProperties[p_instance->p_queueFamilyPropertyCount[i]];
        vkGetPhysicalDeviceQueueFamilyProperties(
            p_instance->physicalDevices[i], 
            &(p_instance->p_queueFamilyPropertyCount[i]),
            p_instance->pp_queueFamilyProperties[i]);
    }
    
    p_instance->error.setText(VKLVK_TEXT_SUCCESS);
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
    
    if (p_instance->physicalDevices)
    {
        delete[] p_instance->physicalDevices;
    }
    if (p_instance->p_physicalDeviceProperties)
    {
        delete[] p_instance->p_physicalDeviceProperties;
    }
    if (p_instance->p_physicalDeviceFeatures)
    {
        delete[] p_instance->p_physicalDeviceFeatures;
    }
    if (p_instance->p_physicalDeviceMemoryProperties)
    {
        delete[] p_instance->p_physicalDeviceMemoryProperties;
    }
    if (p_instance->p_queueFamilyPropertyCount)
    {
        delete[] p_instance->p_queueFamilyPropertyCount;
    }
    if (p_instance->pp_queueFamilyProperties)
    {
        for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
        {
            if (p_instance->pp_queueFamilyProperties[i])
            {
                delete[] p_instance->pp_queueFamilyProperties[i];
            }
        }
        delete[] p_instance->pp_queueFamilyProperties;
    }
    
    p_instance->error.setText(VKLVK_TEXT_CLOSED);
    return true;
}

