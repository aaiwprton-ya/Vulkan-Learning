#include "vklvk.h"

/*
    ERROR
*/

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
    this->size += 1;
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

/*
    INSTANCE
*/

bool vkl_vk::initVklVkInstance(vkl_vk::VklVkInstance* p_instance)
{
    if (!p_instance)
    {
        return false;
    }
    VkResult result;
    
    // set used allocator
    if (p_instance->allocator)
    {
        delete p_instance->allocator;
    }
    p_instance->allocator = nullptr;
#if VKLVK_PROP_CASTOMALLOCATOR > 0
    p_instance->allocator = new vkl_vk::VklVkAllocator();
#endif
    VkAllocationCallbacks* vkAllocationCallbacks = nullptr;
    if (p_instance->allocator)
    {
        vkAllocationCallbacks = (VkAllocationCallbacks*)*(p_instance->allocator);
    }
    
    // get instance layer count
    result = vkEnumerateInstanceLayerProperties(
        &(p_instance->instanceLayerPropertyCount), 
        nullptr); // pProperties
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get instance layers
    if (p_instance->p_instanceLayerProperties)
    {
        delete[] p_instance->p_instanceLayerProperties;
    }
    p_instance->p_instanceLayerProperties = 
        new VkLayerProperties[p_instance->instanceLayerPropertyCount];
    
    result = vkEnumerateInstanceLayerProperties(
        &(p_instance->instanceLayerPropertyCount), 
        p_instance->p_instanceLayerProperties);
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get instance extension count
    result = vkEnumerateInstanceExtensionProperties(
        nullptr, // pLayerName
        &(p_instance->instanceExtensionPropertyCount), 
        nullptr); // pProperties
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get instance extensions
    if (p_instance->p_instanceExtensionProperties)
    {
        delete[] p_instance->p_instanceExtensionProperties;
    }
    p_instance->p_instanceExtensionProperties = 
        new VkExtensionProperties[p_instance->instanceExtensionPropertyCount];
    
    result = vkEnumerateInstanceExtensionProperties(
        nullptr, // pLayerName
        &(p_instance->instanceExtensionPropertyCount), 
        p_instance->p_instanceExtensionProperties);
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // set requered instance layers
    if (p_instance->pp_enabledInstanceLayerNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledInsatnceLayerCount; ++i)
        {
            delete[] p_instance->pp_enabledInstanceLayerNames[i];
        }
        delete[] p_instance->pp_enabledInstanceLayerNames;
    }
    p_instance->enabledInsatnceLayerCount = VKLVK_PROP_ENABLEDINSTANCELAYERCOUNT;
    if (p_instance->enabledInsatnceLayerCount > 0)
    {
        p_instance->pp_enabledInstanceLayerNames = 
            new char*[p_instance->enabledInsatnceLayerCount];
    }
    
    for (uint32_t i = 0; i < p_instance->enabledInsatnceLayerCount; ++i)
    {
        size_t lengthName = 0;
        __initString(VKLVK_PROP_INSTANCELAYERNAMES[i], 
            &lengthName, 
            nullptr); // dest
        p_instance->pp_enabledInstanceLayerNames[i] = new char[lengthName];
        __initString(VKLVK_PROP_INSTANCELAYERNAMES[i], 
            &lengthName, 
            p_instance->pp_enabledInstanceLayerNames[i]);
    }
    
    // set required instance extensions
    if (p_instance->pp_enabledInstanceExtensionNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledInsatnceExtensionCount; ++i)
        {
            delete[] p_instance->pp_enabledInstanceExtensionNames[i];
        }
        delete[] p_instance->pp_enabledInstanceExtensionNames;
    }
    p_instance->enabledInsatnceExtensionCount = VKLVK_PROP_ENABLEDINSTANCEEXTENSIONCOUNT;
    if (p_instance->enabledInsatnceExtensionCount > 0)
    {
        p_instance->pp_enabledInstanceExtensionNames = 
            new char*[p_instance->enabledInsatnceExtensionCount];
    }
    
    for (uint32_t i = 0; i < p_instance->enabledInsatnceExtensionCount; ++i)
    {
        size_t lengthName = 0;
        __initString(VKLVK_PROP_INSTANCEEXTENSIONNAMES[i], 
            &lengthName, 
            nullptr); // dest
        p_instance->pp_enabledInstanceExtensionNames[i] = new char[lengthName];
        __initString(VKLVK_PROP_INSTANCEEXTENSIONNAMES[i], 
            &lengthName, 
            p_instance->pp_enabledInstanceExtensionNames[i]);
    }
    
    // set application info
    p_instance->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    p_instance->appInfo.pApplicationName = VKLVK_PROP_APPLICATIONNAME;
    p_instance->appInfo.applicationVersion = VKLVK_PROP_APPLICATIONVERSION;
    p_instance->appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 0);
    
    // init instance
    p_instance->instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    p_instance->instanceCreateInfo.pNext = nullptr;
    p_instance->instanceCreateInfo.flags = 0;
    p_instance->instanceCreateInfo.pApplicationInfo = &(p_instance->appInfo);
    p_instance->instanceCreateInfo.enabledLayerCount = p_instance->enabledInsatnceLayerCount;
    p_instance->instanceCreateInfo.ppEnabledLayerNames = p_instance->pp_enabledInstanceLayerNames;
    p_instance->instanceCreateInfo.enabledExtensionCount = 
        p_instance->enabledInsatnceExtensionCount;
    p_instance->instanceCreateInfo.ppEnabledExtensionNames = 
        p_instance->pp_enabledInstanceExtensionNames;
    
    result = vkCreateInstance(
        &(p_instance->instanceCreateInfo), 
        vkAllocationCallbacks, 
        &(p_instance->vkInstance));
    
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // TODO get instance extension function address
    // PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName);
    
    // get physical device count
    result = vkEnumeratePhysicalDevices(
        p_instance->vkInstance, 
        &(p_instance->physicalDeviceCount), 
        nullptr); // physicalDevices
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get phisycal devices
    if (p_instance->p_physicalDevices)
    {
        delete[] p_instance->p_physicalDevices;
    }
    p_instance->p_physicalDevices = new VkPhysicalDevice[p_instance->physicalDeviceCount];
    result = vkEnumeratePhysicalDevices(
        p_instance->vkInstance, 
        &(p_instance->physicalDeviceCount), 
        p_instance->p_physicalDevices);
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_INITERROR);
        return false;
    }
    
    // get physical device properties
    if (p_instance->p_physicalDeviceProperties)
    {
        delete[] p_instance->p_physicalDeviceProperties;
    }
    p_instance->p_physicalDeviceProperties = 
        new VkPhysicalDeviceProperties[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceProperties(
            p_instance->p_physicalDevices[i],
            &(p_instance->p_physicalDeviceProperties[i]));
    }
    
    // get physical device features
    if (p_instance->p_physicalDeviceFeatures)
    {
        delete[] p_instance->p_physicalDeviceFeatures;
    }
    p_instance->p_physicalDeviceFeatures = 
        new VkPhysicalDeviceFeatures[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceFeatures(
            p_instance->p_physicalDevices[i],
            &(p_instance->p_physicalDeviceFeatures[i]));
    }
    
    // get physical device memory properties
    if (p_instance->p_physicalDeviceMemoryProperties)
    {
        delete[] p_instance->p_physicalDeviceMemoryProperties;
    }
    p_instance->p_physicalDeviceMemoryProperties = 
        new VkPhysicalDeviceMemoryProperties[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceMemoryProperties(
            p_instance->p_physicalDevices[i],
            &(p_instance->p_physicalDeviceMemoryProperties[i]));
    }
    
    // get phisycal device queue family property count
    if (p_instance->p_queueFamilyPropertyCount)
    {
        delete[] p_instance->p_queueFamilyPropertyCount;
    }
    p_instance->p_queueFamilyPropertyCount = new uint32_t[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        vkGetPhysicalDeviceQueueFamilyProperties(
            p_instance->p_physicalDevices[i], 
            &(p_instance->p_queueFamilyPropertyCount[i]),
            nullptr); // VkQueueFamilyProperties*
    }
    
    // get phisycal device queue family properties
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
    p_instance->pp_queueFamilyProperties = 
        new VkQueueFamilyProperties*[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        p_instance->pp_queueFamilyProperties[i] = 
            new VkQueueFamilyProperties[p_instance->p_queueFamilyPropertyCount[i]];
        vkGetPhysicalDeviceQueueFamilyProperties(
            p_instance->p_physicalDevices[i], 
            &(p_instance->p_queueFamilyPropertyCount[i]),
            p_instance->pp_queueFamilyProperties[i]);
    }
    
    // get physical device layer count
    if (p_instance->p_deviceLayerPropertyCounts)
    {
        delete[] p_instance->p_deviceLayerPropertyCounts;
    }
    p_instance->p_deviceLayerPropertyCounts = new uint32_t[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        result = vkEnumerateDeviceLayerProperties(
            p_instance->p_physicalDevices[i], 
            &(p_instance->p_deviceLayerPropertyCounts[i]), 
            nullptr); // pProperties
        if (result != VK_SUCCESS)
        {
            p_instance->error.setText(VKLVK_TEXT_INITERROR);
            return false;
        }
    }
    
    // getting physical device layers
    if (p_instance->pp_deviceLayerProperties)
    {
        for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
        {
            delete[] p_instance->pp_deviceLayerProperties[i];
        }
        delete[] p_instance->pp_deviceLayerProperties;
    }
    p_instance->pp_deviceLayerProperties = 
        new VkLayerProperties*[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        p_instance->pp_deviceLayerProperties[i] = 
            new VkLayerProperties[p_instance->p_deviceLayerPropertyCounts[i]];
    }
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        result = vkEnumerateDeviceLayerProperties(
            p_instance->p_physicalDevices[i], 
            &(p_instance->p_deviceLayerPropertyCounts[i]), 
            p_instance->pp_deviceLayerProperties[i]);
        if (result != VK_SUCCESS)
        {
            p_instance->error.setText(VKLVK_TEXT_INITERROR);
            return false;
        }
    }
    
    // get physical device extension count
    if (p_instance->p_deviceExtensionPropertyCounts)
    {
        delete[] p_instance->p_deviceExtensionPropertyCounts;
    }
    p_instance->p_deviceExtensionPropertyCounts = new uint32_t[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        result = vkEnumerateDeviceExtensionProperties(
            p_instance->p_physicalDevices[i], 
            nullptr, // pLayerName
            &(p_instance->p_deviceExtensionPropertyCounts[i]), 
            nullptr); // pProperties
        if (result != VK_SUCCESS)
        {
            p_instance->error.setText(VKLVK_TEXT_INITERROR);
            return false;
        }
    }
    
    // get physical device extensions
    if (p_instance->pp_deviceExtensionProperties)
    {
        for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
        {
            delete[] p_instance->pp_deviceExtensionProperties[i];
        }
        delete[] p_instance->pp_deviceExtensionProperties;
    }
    p_instance->pp_deviceExtensionProperties = 
        new VkExtensionProperties*[p_instance->physicalDeviceCount];
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        p_instance->pp_deviceExtensionProperties[i] = 
            new VkExtensionProperties[p_instance->p_deviceExtensionPropertyCounts[i]];
    }
    for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
    {
        result = vkEnumerateDeviceExtensionProperties(
            p_instance->p_physicalDevices[i],
            nullptr, // pLayerName 
            &(p_instance->p_deviceExtensionPropertyCounts[i]), 
            p_instance->pp_deviceExtensionProperties[i]);
        if (result != VK_SUCCESS)
        {
            p_instance->error.setText(VKLVK_TEXT_INITERROR);
            return false;
        }
    }
    
    // set required physical device layers
    if (p_instance->pp_enabledDeviceLayerNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledDeviceLayerCount; ++i)
        {
            delete[] p_instance->pp_enabledDeviceLayerNames[i];
        }
        delete[] p_instance->pp_enabledDeviceLayerNames;
    }
    p_instance->enabledDeviceLayerCount = VKLVK_PROP_ENABLEDDEVICELAYERCOUNT;
    if (p_instance->enabledDeviceLayerCount > 0)
    {
        p_instance->pp_enabledDeviceLayerNames = 
            new char*[p_instance->enabledDeviceLayerCount];
    }
    
    for (uint32_t i = 0; i < p_instance->enabledDeviceLayerCount; ++i)
    {
        size_t lengthName = 0;
        __initString(VKLVK_PROP_DEVICELAYERNAMES[i], 
            &lengthName, 
            nullptr); // dest
        p_instance->pp_enabledDeviceLayerNames[i] = new char[lengthName];
        __initString(VKLVK_PROP_DEVICELAYERNAMES[i], 
            &lengthName, 
            p_instance->pp_enabledDeviceLayerNames[i]);
    }

    // set required physical device extensions
    if (p_instance->pp_enabledDeviceExtensionNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledDeviceExtensionCount; ++i)
        {
            delete[] p_instance->pp_enabledDeviceExtensionNames[i];
        }
        delete[] p_instance->pp_enabledDeviceExtensionNames;
    }
    p_instance->enabledDeviceExtensionCount = VKLVK_PROP_ENABLEDDEVICEEXTENSIONCOUNT;
    if (p_instance->enabledDeviceExtensionCount > 0)
    {
        p_instance->pp_enabledDeviceExtensionNames = 
            new char*[p_instance->enabledDeviceExtensionCount];
    }
    
    for (uint32_t i = 0; i < p_instance->enabledDeviceExtensionCount; ++i)
    {
        size_t lengthName = 0;
        __initString(VKLVK_PROP_DEVICEEXTENSIONNAMES[i], 
            &lengthName, 
            nullptr); // dest
        p_instance->pp_enabledDeviceExtensionNames[i] = new char[lengthName];
        __initString(VKLVK_PROP_DEVICEEXTENSIONNAMES[i], 
            &lengthName, 
            p_instance->pp_enabledDeviceExtensionNames[i]);
    }
    
    // set queue priorities
    p_instance->queueCreateInfoCount = VKLVK_PROP_DEVISEQUEUECREATEINFOCOUNT;
    if (p_instance->pp_queueCreateInfoPriorities)
    {
        for (uint32_t i = 0; i < p_instance->queueCreateInfoCount; ++i)
        {
            delete[] p_instance->pp_queueCreateInfoPriorities[i];
        }
        delete[] p_instance->pp_queueCreateInfoPriorities;
    }
    p_instance->pp_queueCreateInfoPriorities = new float*[p_instance->queueCreateInfoCount];

#if VKLVK_PROP_DEVISEQUEUECREATEINFOCOUNT >= 1
{
    uint32_t index = 0;
        p_instance->pp_queueCreateInfoPriorities[index] = 
            new float[VKVKL_PROP_REQUIREDQUEUECOUNT_VAL0];
    for (uint32_t j = 0; j < VKVKL_PROP_REQUIREDQUEUECOUNT_VAL0; ++j)
    {
        p_instance->pp_queueCreateInfoPriorities[index][j] = 1.0f;
    }
}
#endif
    
    // create queue info
    if (p_instance->p_queueCreateInfos)
    {
        delete[] p_instance->p_queueCreateInfos;
    }
    p_instance->p_queueCreateInfos = 
        new VkDeviceQueueCreateInfo[p_instance->queueCreateInfoCount];
    
#if VKLVK_PROP_DEVISEQUEUECREATEINFOCOUNT >= 1
{
    uint32_t index = 0;
    p_instance->p_queueCreateInfos[index].sType = 
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    p_instance->p_queueCreateInfos[index].pNext = nullptr;
    p_instance->p_queueCreateInfos[index].flags = 0;
    p_instance->p_queueCreateInfos[index].queueFamilyIndex = 
        VKVKL_PROP_REQUIREDQUEUEFAMILYINDEX_VAL0;
    p_instance->p_queueCreateInfos[index].queueCount = VKVKL_PROP_REQUIREDQUEUECOUNT_VAL0;
    p_instance->p_queueCreateInfos[index].pQueuePriorities = 
        p_instance->pp_queueCreateInfoPriorities[index];
}
#endif
    
    // set required physical device features
    p_instance->requiredPhysicalDeviceFeatures.multiDrawIndirect = 
        p_instance->p_physicalDeviceFeatures[VKLVK_PROP_PHYSICALDEVICEINDEX].multiDrawIndirect;
    p_instance->requiredPhysicalDeviceFeatures.tessellationShader = VK_TRUE;
    p_instance->requiredPhysicalDeviceFeatures.geometryShader = VK_TRUE;
    
    // create device
    p_instance->deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    p_instance->deviceCreateInfo.pNext = nullptr;
    p_instance->deviceCreateInfo.flags = 0;
    p_instance->deviceCreateInfo.queueCreateInfoCount = p_instance->queueCreateInfoCount;
    p_instance->deviceCreateInfo.pQueueCreateInfos = p_instance->p_queueCreateInfos;
    p_instance->deviceCreateInfo.enabledLayerCount = p_instance->enabledDeviceLayerCount;
    p_instance->deviceCreateInfo.ppEnabledLayerNames = p_instance->pp_enabledDeviceLayerNames;
    p_instance->deviceCreateInfo.enabledExtensionCount = p_instance->enabledDeviceExtensionCount;
    p_instance->deviceCreateInfo.ppEnabledExtensionNames = p_instance->pp_enabledDeviceExtensionNames;
    p_instance->deviceCreateInfo.pEnabledFeatures = &(p_instance->requiredPhysicalDeviceFeatures);
    
    result = vkCreateDevice(
        p_instance->p_physicalDevices[VKLVK_PROP_PHYSICALDEVICEINDEX], 
        &(p_instance->deviceCreateInfo), 
        vkAllocationCallbacks, 
        &(p_instance->device));
        
    if (result != VK_SUCCESS)
    {
        p_instance->error.setText(VKLVK_TEXT_CREATEDEVICEERROR);
        return false;
    }
    
    // TODO get device extension function address
    // PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName);
    
    // init resource manager
    if (p_instance->p_resourceManager)
    {
        delete p_instance->p_resourceManager;
    }
    p_instance->p_resourceManager = 
        new vkl_vk::VklVkResourceManager(p_instance->device, vkAllocationCallbacks);
    
    // test resource manager
    // create resources
    VklVkResourcePoolDesc bufferPool;
    p_instance->p_resourceManager->createPool(VKLVK_POOLTYPE_BUFFER_STANDARD, &bufferPool);
    
    VklVkResource buffer;
    p_instance->p_resourceManager->createResource(bufferPool, &buffer);
    
    VklVkResourcePoolDesc imagePool;
    p_instance->p_resourceManager->createPool(VKLVK_POOLTYPE_IMAGE_STANDARD, &imagePool);
    
    VklVkResource image;
    p_instance->p_resourceManager->createResource(imagePool, &image);
    
    VklVkResourcePoolDesc bufferViewPool;
    p_instance->p_resourceManager->createPool(VKLVK_POOLTYPE_BUFFERVIEW_STANDARD, &bufferViewPool);
    
    VklVkResource bufferView; // don't work becouse no memory bound
    // p_instance->p_resourceManager->createResource(bufferViewPool, &buffer, &bufferView);
    
    VklVkResourcePoolDesc imageViewPool;
    p_instance->p_resourceManager->createPool(VKLVK_POOLTYPE_IMAGEVIEW_STANDARD, &imageViewPool);
    
    VklVkResource imageView; // don't work becouse no memory bound 
    // p_instance->p_resourceManager->createResource(imageViewPool, &image, &imageView);
    
    // destroy resources
    p_instance->p_resourceManager->freeResource(&buffer);
    p_instance->p_resourceManager->freeResource(&image);
    // p_instance->p_resourceManager->freeResource(&bufferView);
    // p_instance->p_resourceManager->freeResource(&imageView);
    
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
    
    // get used allocator
    VkAllocationCallbacks* vkAllocationCallbacks = nullptr;
    if (p_instance->allocator)
    {
        vkAllocationCallbacks = (VkAllocationCallbacks*)*(p_instance->allocator);
    }
    
    vkDeviceWaitIdle(p_instance->device);
    vkDestroyDevice(
        p_instance->device, 
        vkAllocationCallbacks);
    
    vkDestroyInstance(
        p_instance->vkInstance, 
        vkAllocationCallbacks);
    
    if (p_instance->allocator)
    {
        delete p_instance->allocator;
    }
    if (p_instance->p_resourceManager)
    {
        delete p_instance->p_resourceManager;
    }
    if (p_instance->p_instanceLayerProperties)
    {
        delete[] p_instance->p_instanceLayerProperties;
    }
    if (p_instance->p_instanceExtensionProperties)
    {
        delete[] p_instance->p_instanceExtensionProperties;
    }
    if (p_instance->pp_enabledInstanceLayerNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledInsatnceLayerCount; ++i)
        {
            delete[] p_instance->pp_enabledInstanceLayerNames[i];
        }
        delete[] p_instance->pp_enabledInstanceLayerNames;
    }
    if (p_instance->pp_enabledInstanceExtensionNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledInsatnceExtensionCount; ++i)
        {
            delete[] p_instance->pp_enabledInstanceExtensionNames[i];
        }
        delete[] p_instance->pp_enabledInstanceExtensionNames;
    }
    if (p_instance->p_physicalDevices)
    {
        delete[] p_instance->p_physicalDevices;
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
    if (p_instance->p_deviceLayerPropertyCounts)
    {
        delete[] p_instance->p_deviceLayerPropertyCounts;
    }
    if (p_instance->pp_deviceLayerProperties)
    {
        for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
        {
            delete[] p_instance->pp_deviceLayerProperties[i];
        }
        delete[] p_instance->pp_deviceLayerProperties;
    }
    if (p_instance->pp_deviceExtensionProperties)
    {
        for (uint32_t i = 0; i < p_instance->physicalDeviceCount; ++i)
        {
            delete[] p_instance->pp_deviceExtensionProperties[i];
        }
        delete[] p_instance->pp_deviceExtensionProperties;
    }
    if (p_instance->pp_enabledDeviceLayerNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledDeviceLayerCount; ++i)
        {
            delete[] p_instance->pp_enabledDeviceLayerNames[i];
        }
        delete[] p_instance->pp_enabledDeviceLayerNames;
    }
    if (p_instance->pp_enabledDeviceExtensionNames)
    {
        for (uint32_t i = 0; i < p_instance->enabledDeviceExtensionCount; ++i)
        {
            delete[] p_instance->pp_enabledDeviceExtensionNames[i];
        }
        delete[] p_instance->pp_enabledDeviceExtensionNames;
    }
    if (p_instance->pp_queueCreateInfoPriorities)
    {
        for (uint32_t i = 0; i < p_instance->queueCreateInfoCount; ++i)
        {
            delete[] p_instance->pp_queueCreateInfoPriorities[i];
        }
        delete[] p_instance->pp_queueCreateInfoPriorities;
    }
    if (p_instance->p_queueCreateInfos)
    {
        delete[] p_instance->p_queueCreateInfos;
    }
    
    p_instance->error.setText(VKLVK_TEXT_CLOSED);
    return true;
}

void vkl_vk::__initString(const char* source, size_t* length, char* dest)
{
    if (!dest)
    {
        *length = 0;
        for (char* ch = (char*)source; *ch != '\0'; ++ch)
        {
            ++(*length);
        }
        ++(*length);
    } else
    {
        for (uint32_t i = 0; i < *length; ++i)
        {
            dest[i] = source[i];
        }
    }
}

