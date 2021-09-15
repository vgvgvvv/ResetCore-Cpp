
#ifndef ResetCore_CommonLib_API_H
#define ResetCore_CommonLib_API_H

#ifdef ResetCore_CommonLib_BUILT_AS_STATIC
#  define ResetCore_CommonLib_API
#  define RESETCORE_COMMONLIB_NO_EXPORT
#else
#  ifndef ResetCore_CommonLib_API
#    ifdef ResetCore_CommonLib_EXPORTS
        /* We are building this library */
#      define ResetCore_CommonLib_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ResetCore_CommonLib_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RESETCORE_COMMONLIB_NO_EXPORT
#    define RESETCORE_COMMONLIB_NO_EXPORT 
#  endif
#endif

#ifndef RESETCORE_COMMONLIB_DEPRECATED
#  define RESETCORE_COMMONLIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef RESETCORE_COMMONLIB_DEPRECATED_EXPORT
#  define RESETCORE_COMMONLIB_DEPRECATED_EXPORT ResetCore_CommonLib_API RESETCORE_COMMONLIB_DEPRECATED
#endif

#ifndef RESETCORE_COMMONLIB_DEPRECATED_NO_EXPORT
#  define RESETCORE_COMMONLIB_DEPRECATED_NO_EXPORT RESETCORE_COMMONLIB_NO_EXPORT RESETCORE_COMMONLIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RESETCORE_COMMONLIB_NO_DEPRECATED
#    define RESETCORE_COMMONLIB_NO_DEPRECATED
#  endif
#endif

#endif /* ResetCore_CommonLib_API_H */
