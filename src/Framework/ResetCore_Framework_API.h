
#ifndef ResetCore_Framework_API_H
#define ResetCore_Framework_API_H

#ifdef ResetCore_Framework_BUILT_AS_STATIC
#  define ResetCore_Framework_API
#  define RESETCORE_FRAMEWORK_NO_EXPORT
#else
#  ifndef ResetCore_Framework_API
#    ifdef ResetCore_Framework_EXPORTS
        /* We are building this library */
#      define ResetCore_Framework_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ResetCore_Framework_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RESETCORE_FRAMEWORK_NO_EXPORT
#    define RESETCORE_FRAMEWORK_NO_EXPORT 
#  endif
#endif

#ifndef RESETCORE_FRAMEWORK_DEPRECATED
#  define RESETCORE_FRAMEWORK_DEPRECATED __declspec(deprecated)
#endif

#ifndef RESETCORE_FRAMEWORK_DEPRECATED_EXPORT
#  define RESETCORE_FRAMEWORK_DEPRECATED_EXPORT ResetCore_Framework_API RESETCORE_FRAMEWORK_DEPRECATED
#endif

#ifndef RESETCORE_FRAMEWORK_DEPRECATED_NO_EXPORT
#  define RESETCORE_FRAMEWORK_DEPRECATED_NO_EXPORT RESETCORE_FRAMEWORK_NO_EXPORT RESETCORE_FRAMEWORK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RESETCORE_FRAMEWORK_NO_DEPRECATED
#    define RESETCORE_FRAMEWORK_NO_DEPRECATED
#  endif
#endif

#endif /* ResetCore_Framework_API_H */
