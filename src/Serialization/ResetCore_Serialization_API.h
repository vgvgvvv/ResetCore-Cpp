
#ifndef ResetCore_Serialization_API_H
#define ResetCore_Serialization_API_H

#ifdef ResetCore_Serialization_BUILT_AS_STATIC
#  define ResetCore_Serialization_API
#  define RESETCORE_SERIALIZATION_NO_EXPORT
#else
#  ifndef ResetCore_Serialization_API
#    ifdef ResetCore_Serialization_EXPORTS
        /* We are building this library */
#      define ResetCore_Serialization_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ResetCore_Serialization_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RESETCORE_SERIALIZATION_NO_EXPORT
#    define RESETCORE_SERIALIZATION_NO_EXPORT 
#  endif
#endif

#ifndef RESETCORE_SERIALIZATION_DEPRECATED
#  define RESETCORE_SERIALIZATION_DEPRECATED __declspec(deprecated)
#endif

#ifndef RESETCORE_SERIALIZATION_DEPRECATED_EXPORT
#  define RESETCORE_SERIALIZATION_DEPRECATED_EXPORT ResetCore_Serialization_API RESETCORE_SERIALIZATION_DEPRECATED
#endif

#ifndef RESETCORE_SERIALIZATION_DEPRECATED_NO_EXPORT
#  define RESETCORE_SERIALIZATION_DEPRECATED_NO_EXPORT RESETCORE_SERIALIZATION_NO_EXPORT RESETCORE_SERIALIZATION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RESETCORE_SERIALIZATION_NO_DEPRECATED
#    define RESETCORE_SERIALIZATION_NO_DEPRECATED
#  endif
#endif

#endif /* ResetCore_Serialization_API_H */
