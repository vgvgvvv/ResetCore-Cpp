
#ifndef ReHeaderTool_API_H
#define ReHeaderTool_API_H

#ifdef ReHeaderTool_BUILT_AS_STATIC
#  define ReHeaderTool_API
#  define REHEADERTOOL_NO_EXPORT
#else
#  ifndef ReHeaderTool_API
#    ifdef ReHeaderTool_EXPORTS
        /* We are building this library */
#      define ReHeaderTool_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ReHeaderTool_API __declspec(dllimport)
#    endif
#  endif

#  ifndef REHEADERTOOL_NO_EXPORT
#    define REHEADERTOOL_NO_EXPORT 
#  endif
#endif

#ifndef REHEADERTOOL_DEPRECATED
#  define REHEADERTOOL_DEPRECATED __declspec(deprecated)
#endif

#ifndef REHEADERTOOL_DEPRECATED_EXPORT
#  define REHEADERTOOL_DEPRECATED_EXPORT ReHeaderTool_API REHEADERTOOL_DEPRECATED
#endif

#ifndef REHEADERTOOL_DEPRECATED_NO_EXPORT
#  define REHEADERTOOL_DEPRECATED_NO_EXPORT REHEADERTOOL_NO_EXPORT REHEADERTOOL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef REHEADERTOOL_NO_DEPRECATED
#    define REHEADERTOOL_NO_DEPRECATED
#  endif
#endif

#endif /* ReHeaderTool_API_H */
