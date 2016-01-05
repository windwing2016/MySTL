#ifndef __STL_CONFIG_H
#define __STL_CONFIG_H



#ifdef _PTHREADS
#   define __STL_PTHREADS
#endif

//如果编译器不提供STL需要的功能 则定义 __STL_NEED_XXX
#if defined(__sgi) && !defined(__GUNC__)
#  if !defined(_BOOL)
#      define __STL_NEED_BOOL
#  endif

//(4)  如果编译器不支持'typename'关键字, 则将'typename'定义为空(null macro)
#  if !defined(_TYPENAME_IS_KEYWORD)
#     define __STL_NEED_TYPENAME
#  endif

//如果编译器支持partial specialization of class templates(模板类偏特化),
//则定义__STL_CLASS_PARTIAL_SPECIALIZATION
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#      define  __STL_CLASS_PARTIAL_SPECIALIZATION
#   endif

// 如果编译器支持template members of classes(类模板成员),
// 定义__STL_MEMBER_TEMPLATES
#   ifdef _MEMBER_TEMPLATES
#     define __STL_MEMBER_TEMPLATES
#   endif

//  (9)  如果编译器不支持'explicit'关键字, 则将'explicit'定义为空(null macro)
#   if !defined(_EXPLICIT_IS_KEYWORD)
#     define __STL_NEED_EXPLICIT
#   endif

//如果编译器(在当前编译模式下)支持异常,
//       则定义__STL_USE_EXCEPTIONS

#   ifdef __EXCEPTIONS
#     define __STL_USE_EXCEPTIONS
#   endif

//  (14) 如果我们将STL放进命名空间中,
//       则定义__STL_USE_NAMESPACES
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define __STL_USE_NAMESPACES
#   endif

//(15) 如果本STL在SGI的编译器上编译, 并且用户没有选择pthreads或者no threads,
//       则默认使用__STL_SGI_THREADS
#   if !defined(_NOTHREADS) && !defined(__STL_PTHREADS)
#     define __STL_SGI_THREADS
#   endif
#endif


#ifdef __GNUC__
#     include<_G_config.h>
#     if __GNUC__<2 ||(__GNUC__=2&&__GNUC__<8)
#         define  __STL_STATIC_TEMPLATE_MEMBER_BUG
#         define  __STL_NEED_TYPENAME
#         define  __STL_NEED_EXPLICTIT
#     else
#         define  ____STL_CLASS_PARTIAL_SPECIALIZATION
#         define __STL_CLASS_PARTIAL_SPECIALIZATION
#         define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#         define __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#         define __STL_MEMBER_TEMPLATES
#endif


// Sun C++ compiler
# if defined(__SUNPRO_CC)
#   define __STL_NEED_BOOL
#   define __STL_NEED_TYPENAME
#   define __STL_NEED_EXPLICIT
#   define __STL_USE_EXCEPTIONS
# endif

// TODO: 这个我没找到资料, 如果你知道或者有相关资料请联系我, Thank U
# if defined(__COMO__)
#   define __STL_MEMBER_TEMPLATES
#   define __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_USE_EXCEPTIONS
#   define __STL_USE_NAMESPACES
# endif

// _MSC_VER 定义微软编译器的版本
// MS VC++ 10.0 _MSC_VER = 1600
// MS VC++ 9.0 _MSC_VER = 1500
// MS VC++ 8.0 _MSC_VER = 1400
// MS VC++ 7.1 _MSC_VER = 1310
// MS VC++ 7.0 _MSC_VER = 1300
// MS VC++ 6.0 _MSC_VER = 1200
// MS VC++ 5.0 _MSC_VER = 1100


# if defined(_MSC_VER)
#   if _MSC_VER > 1000
#     include <yvals.h>
#   else
#     define __STL_NEED_BOOL
#   endif
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   if _MSC_VER < 1100
#     define __STL_NEED_EXPLICIT
#   endif
#   define __STL_NON_TYPE_TMPL_PARAM_BUG
#   define __SGI_STL_NO_ARROW_OPERATOR
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
# endif



# if defined(__BORLANDC__)
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   define __STL_LIMITED_DEFAULT_TEMPLATES
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define __STL_NON_TYPE_TMPL_PARAM_BUG
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef __MT__
#     define __STL_WIN32THREADS
#   endif
# endif


# if defined(__STL_NEED_BOOL)
typedef int bool;
#   define true 1
#   define false 0
# endif

# ifdef __STL_NEED_TYPENAME
#   define typename
# endif

# ifdef __STL_NEED_EXPLICIT
#   define explicit
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_NULL_TMPL_ARGS
# endif

# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_TEMPLATE_NULL template<>
# else
#   define __STL_TEMPLATE_NULL
# endif

// __STL_NO_NAMESPACES is a hook so that users can disable namespaces
 // without having to edit library headers.
# if defined(__STL_USE_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
#   define __STD std
#   define __STL_BEGIN_NAMESPACE namespace std {
#   define __STL_END_NAMESPACE }
#   define __STL_USE_NAMESPACE_FOR_RELOPS
#   define __STL_BEGIN_RELOPS_NAMESPACE namespace std {
#   define __STL_END_RELOPS_NAMESPACE }
#   define __STD_RELOPS std
# else
#   define __STD
#   define __STL_BEGIN_NAMESPACE
#   define __STL_END_NAMESPACE
#   undef  __STL_USE_NAMESPACE_FOR_RELOPS
#   define __STL_BEGIN_RELOPS_NAMESPACE
#   define __STL_END_RELOPS_NAMESPACE
#   define __STD_RELOPS
# endif

# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __STL_TRY
#   define __STL_CATCH_ALL if (false)
#   define __STL_RETHROW
#   define __STL_NOTHROW
#   define __STL_UNWIND(action)
# endif

#ifdef __STL_ASSERTIONS
# include <stdio.h>
# define __stl_assert(expr) \
if (!(expr)) { fprintf(stderr, "%s:%d STL assertion failure: %s\n", \
         __FILE__, __LINE__, # expr); abort(); }
#else
# define __stl_assert(expr)
#endif













#endif // STL_CONFIG_H
