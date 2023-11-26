
#ifndef Test_Libraries_API_H
#define Test_Libraries_API_H

#ifdef Test_Libraries_BUILT_AS_STATIC
#  define Test_Libraries_API
#  define TEST_LIBRARIES_NO_EXPORT
#else
#  ifndef Test_Libraries_API
#    ifdef Test_Libraries_EXPORTS
        /* We are building this library */
#      define Test_Libraries_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define Test_Libraries_API __declspec(dllimport)
#    endif
#  endif

#  ifndef TEST_LIBRARIES_NO_EXPORT
#    define TEST_LIBRARIES_NO_EXPORT 
#  endif
#endif

#ifndef TEST_LIBRARIES_DEPRECATED
#  define TEST_LIBRARIES_DEPRECATED __declspec(deprecated)
#endif

#ifndef TEST_LIBRARIES_DEPRECATED_EXPORT
#  define TEST_LIBRARIES_DEPRECATED_EXPORT Test_Libraries_API TEST_LIBRARIES_DEPRECATED
#endif

#ifndef TEST_LIBRARIES_DEPRECATED_NO_EXPORT
#  define TEST_LIBRARIES_DEPRECATED_NO_EXPORT TEST_LIBRARIES_NO_EXPORT TEST_LIBRARIES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TEST_LIBRARIES_NO_DEPRECATED
#    define TEST_LIBRARIES_NO_DEPRECATED
#  endif
#endif

#endif /* Test_Libraries_API_H */
