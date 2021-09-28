
#ifndef D3D11RHI_API_H
#define D3D11RHI_API_H

#ifdef D3D11RHI_BUILT_AS_STATIC
#  define D3D11RHI_API
#  define D3D11RHI_NO_EXPORT
#else
#  ifndef D3D11RHI_API
#    ifdef D3D11RHI_EXPORTS
        /* We are building this library */
#      define D3D11RHI_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define D3D11RHI_API __declspec(dllimport)
#    endif
#  endif

#  ifndef D3D11RHI_NO_EXPORT
#    define D3D11RHI_NO_EXPORT 
#  endif
#endif

#ifndef D3D11RHI_DEPRECATED
#  define D3D11RHI_DEPRECATED __declspec(deprecated)
#endif

#ifndef D3D11RHI_DEPRECATED_EXPORT
#  define D3D11RHI_DEPRECATED_EXPORT D3D11RHI_API D3D11RHI_DEPRECATED
#endif

#ifndef D3D11RHI_DEPRECATED_NO_EXPORT
#  define D3D11RHI_DEPRECATED_NO_EXPORT D3D11RHI_NO_EXPORT D3D11RHI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef D3D11RHI_NO_DEPRECATED
#    define D3D11RHI_NO_DEPRECATED
#  endif
#endif

#endif /* D3D11RHI_API_H */
