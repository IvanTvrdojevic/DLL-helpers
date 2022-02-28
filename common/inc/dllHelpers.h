#pragma once


//*****************************************************************************
// USER CONTROL MACROS
//*****************************************************************************
//.............................................................................
// MACROS FOR CONTROL OF dllHelpers - can be user defined
//.............................................................................
// ......... parameter passing convention - use cdecl by default .........
#ifndef __FUNC_PPC_TYPE
#define __FUNC_PPC_TYPE(ret) ret __cdecl
#endif

// define these macros in the project:
//  __USE_DLL : use library as dll (otherwise it will be exported as static LIB)
//    __DLL_EXPORT : export dll functions (otherwise dll functions are imported)









//*****************************************************************************
// GENERAL
//*****************************************************************************
#define __MACRO_JOIN__(x, y) __MACRO_JOIN_AGAIN__(x, y)
#define __MACRO_JOIN_AGAIN__(x, y) x ## y

#define __MACRO_STR__(s) __MACRO_STR_AGAIN__(s)
#define __MACRO_STR_AGAIN__(s) __MACRO_STR_AGAIN2__(s)
#define __MACRO_STR_AGAIN2__(s) #s

// __FOR_EACH__ generation (generates for upto 365 __FOR_EACH__ arguments)
// based on implementation from:
// https://www.scs.stanford.edu/~dm/blog/va-opt.html
#define __FE_PARENS__ ()
#define __FE_EXPAND__(...) __FE_EXPAND__4(__FE_EXPAND__4(__FE_EXPAND__4(__FE_EXPAND__4(__VA_ARGS__))))
#define __FE_EXPAND__4(...) __FE_EXPAND__3(__FE_EXPAND__3(__FE_EXPAND__3(__FE_EXPAND__3(__VA_ARGS__))))
#define __FE_EXPAND__3(...) __FE_EXPAND__2(__FE_EXPAND__2(__FE_EXPAND__2(__FE_EXPAND__2(__VA_ARGS__))))
#define __FE_EXPAND__2(...) __FE_EXPAND__1(__FE_EXPAND__1(__FE_EXPAND__1(__FE_EXPAND__1(__VA_ARGS__))))
#define __FE_EXPAND__1(...) __VA_ARGS__

#define __FOR_EACH_COMA2__(macro, ...)                                         \
        __VA_OPT__(__FOR_EACH_COMA2__GENFIRST__(macro, __VA_ARGS__))
#define __FOR_EACH_COMA2__GENFIRST__(macro, a1, a2, ...)                       \
        macro(a1, a2)                                                          \
        __FOR_EACH_COMA2__GENREST__(macro, __VA_ARGS__)
#define __FOR_EACH_COMA2__GENREST__(macro, ...)                                \
        __VA_OPT__(__FE_EXPAND__(__FOR_EACH_COMA2__HLP__(macro, __VA_ARGS__)))
#define __FOR_EACH_COMA2__HLP__(macro, a1, a2, ...)                            \
        , macro(a1, a2)                                                        \
        __VA_OPT__(__FOR_EACH_COMA2__AGN__ __FE_PARENS__(macro, __VA_ARGS__))
#define __FOR_EACH_COMA2__AGN__() __FOR_EACH_COMA2__HLP__


// constexpr compare of two const strings
// based on implementation from:
// https://stackoverflow.com/questions/27490858/how-can-you-compare-two-character-strings-statically-at-compile-time
constexpr bool strcmp_cexp(char const* a, char const* b)
{
    return *a == *b && (*a == '\0' || strcmp_cexp(a + 1, b + 1));
}

// return type of a function signature
// based on implementation from:
// https://stackoverflow.com/questions/18695564/deducing-a-function-pointer-return-type
template <typename Tfunc>
struct func_sig;

template <typename Tret, typename... Targs>
struct func_sig<Tret(Targs...)>
{
    typedef Tret type;
};

template <typename Tret, typename... Targs>
struct func_sig<Tret(Targs..., ...)>
{
    typedef Tret type;
};


//*****************************************************************************
// IMPLEMENTATION 1
//*****************************************************************************
//.............................................................................
// HELPERS
//.............................................................................
// ......... dummy prefixes .........
#define __DUMMY_PREF_T__ T
#define __DUMMY_PREF_FUNC__ __dummy_dll_helpers__

// creates __DUMMY_PREF_T____DUMMY_PREF_FUNC__
#define __DUMMY_PREF_TFUNC__ __MACRO_JOIN__(__DUMMY_PREF_T__, __DUMMY_PREF_FUNC__)
// len of __DUMMY_PREF_FUNC__
size_t const __DUMMY_PREF_FUNC_LEN__ = strlen(__MACRO_STR__(__DUMMY_PREF_FUNC__));

// ......... create dummy type names .........
// create dummy type name for function type
// creates __DUMMY_PREF_TFUNC__funcname
#define __DUMMY_TFUNC__(funcName) __MACRO_JOIN__(__DUMMY_PREF_TFUNC__, funcName)

// ......... return helpers .........
// generate return code depending on the return type - void vs non-void
#define __RETURN_HELPER__(retType, retVal)                                     \
    if constexpr(std::is_same<retType, void>::value)                           \
    {                                                                          \
        retVal;                                                                \
        return;                                                                \
    }                                                                          \
    else                                                                       \
        return retVal;
// return helper used within macro
#define __RETURN_HELPER_MACRO__(funcName, retVal)                              \
    __RETURN_HELPER__(func_sig<__DUMMY_TFUNC__(funcName)>::type, retVal)
// return helper used within function
#define __RETURN_HELPER_FUNC__(retVal)                                         \
    __RETURN_HELPER__(func_sig<Tfunc>::type, retVal)


//.............................................................................
// EXPORT/IMPORT
//.............................................................................
#ifdef __USE_DLL
// ......... use library as DLL .........
#ifdef __DLL_EXPORT
// ......... export DLL function .........
#define __LFA_MACRO__(a1, a2) a1 a2
#define __LIB_FUNCTION_API(ret, funcName, ...)                                 \
    __declspec(dllexport) __FUNC_PPC_TYPE(ret)                                 \
                          funcName(__FOR_EACH_COMA2__(__LFA_MACRO__,           \
                                                     __VA_ARGS__));

#else // !__DLL_EXPORT
// ......... import  DLL function .........
#define __LFA_MACRO__(a1, a2) a1
#define __LIB_FUNCTION_API(ret, funcName, ...)                                 \
    __declspec(dllimport) __FUNC_PPC_TYPE(ret)                                 \
                          funcName(__FOR_EACH_COMA2__(__LFA_MACRO__,           \
                                                      __VA_ARGS__));           \
                                                                               \
using __DUMMY_TFUNC__(funcName) = __FUNC_PPC_TYPE(ret)                         \
                                (__FOR_EACH_COMA2__(__LFA_MACRO__,             \
                                                    __VA_ARGS__));             \
__FUNC_PPC_TYPE(ret)                                                           \
    __MACRO_JOIN__(__DUMMY_PREF_FUNC__,                                        \
                   funcName(__FOR_EACH_COMA2__(__LFA_MACRO__,                  \
                                               __VA_ARGS__)))                  \
{                                                                              \
    dllHelpers::tmpFuncName = __FUNCDNAME__;                                   \
    __RETURN_HELPER_MACRO__(funcName, {})                                      \
}                                                                              \

#endif

#else // !__USE_DLL
// ......... use library as LIB .........
#define __LFA_MACRO__(a1, a2) a1 a2
#define __LIB_FUNCTION_API(ret, funcName, ...)                                 \
                            ret funcName(__FOR_EACH_COMA2__(__LFA_MACRO__,     \
                                                            __VA_ARGS__));
#endif


//.............................................................................
// DYNAMIC LOAD
//.............................................................................
// ......... temp global var for comunicating mangled func name .........
namespace dllHelpers
{
    static std::string tmpFuncName;
}

// ......... get mangled name of the function .........
#define __GET_MANGLED_NAME(nameSpace, funcName, ...)                           \
    __GET_MANGLED_NAME_HLP(nameSpace, funcName __VA_OPT__(,) __VA_ARGS__)
//
#define __GET_MANGLED_NAME_HLP(nameSpace, funcName, ...)                       \
[&](){                                                                         \
    nameSpace __MACRO_JOIN__(__DUMMY_PREF_FUNC__, funcName(__VA_ARGS__));      \
                                                                               \
    std::string tmp(dllHelpers::tmpFuncName);                                  \
    tmp.replace(tmp.find(__MACRO_STR__(__DUMMY_PREF_FUNC__)),                  \
                        __DUMMY_PREF_FUNC_LEN__, "");                          \
    return tmp;                                                                \
}()
//

#include <Windows.h>

// ......... get function pointer from lib .........
template<typename Tfunc, typename TfuncId>
Tfunc* getFuncPtr(HMODULE lib, TfuncId funcId)
{
    if(lib == nullptr) return nullptr;

    if constexpr(std::is_same<TfuncId, unsigned short>::value)
        return reinterpret_cast<Tfunc*>(GetProcAddress(lib, (char*)funcId));
    else if constexpr(std::is_same<TfuncId, const char*>::value)
        return reinterpret_cast<Tfunc*>(GetProcAddress(lib, funcId));
    else
        return nullptr;
}

// ......... call dll function (dynamic load) .........
#define __CALL_DLL_FUNCTION(lib, nameSpace, funcName, ...)                     \
 [&](){                                                                        \
    std::string mangledName =                                                  \
                __GET_MANGLED_NAME(nameSpace, funcName, __VA_ARGS__);          \
    __RETURN_HELPER_MACRO__(funcName,                                          \
                          __CALL_DLL_FUNCTION_HLP(lib, nameSpace, funcName,    \
                                                                __VA_ARGS__))  \
}()
//
#define __CALL_DLL_FUNCTION_HLP(lib, nameSpace,funcName, ...)                  \
    callDllFunc<nameSpace __DUMMY_TFUNC__(funcName)>                           \
                   (lib, mangledName.c_str() __VA_OPT__(,) __VA_ARGS__);

template<typename Tfunc, typename TfuncId, typename... Targs>
func_sig<Tfunc>::type callDllFunc(HMODULE lib, TfuncId funcId, Targs&&... args)
{
    Tfunc* funcPtr = getFuncPtr<Tfunc>(lib, funcId);

    if (funcPtr == nullptr)
        __RETURN_HELPER_FUNC__({});

    __RETURN_HELPER_FUNC__(funcPtr(std::forward<Targs>(args)...));
}
