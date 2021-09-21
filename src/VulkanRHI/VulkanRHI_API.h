
#ifndef VulkanRHI_API_H
#define VulkanRHI_API_H

#ifdef VulkanRHI_BUILT_AS_STATIC
#  define VulkanRHI_API
#  define VULKANRHI_NO_EXPORT
#else
#  ifndef VulkanRHI_API
#    ifdef VulkanRHI_EXPORTS
        /* We are building this library */
#      define VulkanRHI_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define VulkanRHI_API __declspec(dllimport)
#    endif
#  endif

#  ifndef VULKANRHI_NO_EXPORT
#    define VULKANRHI_NO_EXPORT 
#  endif
#endif

#ifndef VULKANRHI_DEPRECATED
#  define VULKANRHI_DEPRECATED __declspec(deprecated)
#endif

#ifndef VULKANRHI_DEPRECATED_EXPORT
#  define VULKANRHI_DEPRECATED_EXPORT VulkanRHI_API VULKANRHI_DEPRECATED
#endif

#ifndef VULKANRHI_DEPRECATED_NO_EXPORT
#  define VULKANRHI_DEPRECATED_NO_EXPORT VULKANRHI_NO_EXPORT VULKANRHI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VULKANRHI_NO_DEPRECATED
#    define VULKANRHI_NO_DEPRECATED
#  endif
#endif

#endif /* VulkanRHI_API_H */
