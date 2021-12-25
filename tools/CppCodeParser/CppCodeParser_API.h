
#ifndef CppCodeParser_API_H
#define CppCodeParser_API_H

#ifdef CppCodeParser_BUILT_AS_STATIC
#  define CppCodeParser_API
#  define CPPCODEPARSER_NO_EXPORT
#else
#  ifndef CppCodeParser_API
#    ifdef CppCodeParser_EXPORTS
        /* We are building this library */
#      define CppCodeParser_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define CppCodeParser_API __declspec(dllimport)
#    endif
#  endif

#  ifndef CPPCODEPARSER_NO_EXPORT
#    define CPPCODEPARSER_NO_EXPORT 
#  endif
#endif

#ifndef CPPCODEPARSER_DEPRECATED
#  define CPPCODEPARSER_DEPRECATED __declspec(deprecated)
#endif

#ifndef CPPCODEPARSER_DEPRECATED_EXPORT
#  define CPPCODEPARSER_DEPRECATED_EXPORT CppCodeParser_API CPPCODEPARSER_DEPRECATED
#endif

#ifndef CPPCODEPARSER_DEPRECATED_NO_EXPORT
#  define CPPCODEPARSER_DEPRECATED_NO_EXPORT CPPCODEPARSER_NO_EXPORT CPPCODEPARSER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CPPCODEPARSER_NO_DEPRECATED
#    define CPPCODEPARSER_NO_DEPRECATED
#  endif
#endif

#endif /* CppCodeParser_API_H */
