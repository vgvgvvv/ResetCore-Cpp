
#ifndef OpenGLRHI_API_H
#define OpenGLRHI_API_H

#ifdef OpenGLRHI_BUILT_AS_STATIC
#  define OpenGLRHI_API
#  define OPENGLRHI_NO_EXPORT
#else
#  ifndef OpenGLRHI_API
#    ifdef OpenGLRHI_EXPORTS
        /* We are building this library */
#      define OpenGLRHI_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define OpenGLRHI_API __declspec(dllimport)
#    endif
#  endif

#  ifndef OPENGLRHI_NO_EXPORT
#    define OPENGLRHI_NO_EXPORT 
#  endif
#endif

#ifndef OPENGLRHI_DEPRECATED
#  define OPENGLRHI_DEPRECATED __declspec(deprecated)
#endif

#ifndef OPENGLRHI_DEPRECATED_EXPORT
#  define OPENGLRHI_DEPRECATED_EXPORT OpenGLRHI_API OPENGLRHI_DEPRECATED
#endif

#ifndef OPENGLRHI_DEPRECATED_NO_EXPORT
#  define OPENGLRHI_DEPRECATED_NO_EXPORT OPENGLRHI_NO_EXPORT OPENGLRHI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENGLRHI_NO_DEPRECATED
#    define OPENGLRHI_NO_DEPRECATED
#  endif
#endif

#endif /* OpenGLRHI_API_H */
