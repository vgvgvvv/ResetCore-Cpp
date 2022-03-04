
#ifndef ReflectionCodeGenerator_API_H
#define ReflectionCodeGenerator_API_H

#ifdef ReflectionCodeGenerator_BUILT_AS_STATIC
#  define ReflectionCodeGenerator_API
#  define REFLECTIONCODEGENERATOR_NO_EXPORT
#else
#  ifndef ReflectionCodeGenerator_API
#    ifdef ReflectionCodeGenerator_EXPORTS
        /* We are building this library */
#      define ReflectionCodeGenerator_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ReflectionCodeGenerator_API __declspec(dllimport)
#    endif
#  endif

#  ifndef REFLECTIONCODEGENERATOR_NO_EXPORT
#    define REFLECTIONCODEGENERATOR_NO_EXPORT 
#  endif
#endif

#ifndef REFLECTIONCODEGENERATOR_DEPRECATED
#  define REFLECTIONCODEGENERATOR_DEPRECATED __declspec(deprecated)
#endif

#ifndef REFLECTIONCODEGENERATOR_DEPRECATED_EXPORT
#  define REFLECTIONCODEGENERATOR_DEPRECATED_EXPORT ReflectionCodeGenerator_API REFLECTIONCODEGENERATOR_DEPRECATED
#endif

#ifndef REFLECTIONCODEGENERATOR_DEPRECATED_NO_EXPORT
#  define REFLECTIONCODEGENERATOR_DEPRECATED_NO_EXPORT REFLECTIONCODEGENERATOR_NO_EXPORT REFLECTIONCODEGENERATOR_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef REFLECTIONCODEGENERATOR_NO_DEPRECATED
#    define REFLECTIONCODEGENERATOR_NO_DEPRECATED
#  endif
#endif

#endif /* ReflectionCodeGenerator_API_H */
