#ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#if defined(_MSC_VER)

#define GO_COMP_MSVC 1

#define GO_MSVC_VER _MSC_VER

#if _MSC_FULL_VER > 100000000
#define GO_MSVC_FULL_VER _MSC_FULL_VER
#else
#define GO_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

#if (_MSC_VER == 1500)
#define GO_COMP_MSVC_VC9 1
#elif (_MSC_VER == 1600)
#define GO_COMP_MSVC_VC10 1
#elif (_MSC_VER == 1700)
#define GO_COMP_MSVC_VC11 1
#elif (_MSC_VER == 1800)
#define GO_COMP_MSVC_VC12 1
#elif (_MSC_VER == 1900)
#define GO_COMP_MSVC_VC14 1
#endif

// C/C++ support according to http://en.cppreference.com/w/cpp/compiler_support
#if (_MSC_VER < 1600)
#define GO_NO_CXX_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS 1
#endif

// C++11 support
#if (_MSC_VER)
#define GO_NO_CXX11_CONSTEXPR 1
#endif
#if (_MSC_VER < 1900)
#define GO_NO_CXX11_ALIGNAS 1
#define GO_NO_CXX11_ALIGNOF 1
#define GO_NO_CXX11_INHERITING_CONSTRUCTORS 1
#define GO_NO_CXX11_INLINE_NAMESPACES 1
#define GO_NO_CXX11_NEW_CHARACTER_TYPES 1
#define GO_NO_CXX11_UNICODE_STRING_LITERALS 1
#define GO_NO_CXX11_USER_DEFINED_LITERALS 1
#define GO_NO_CXX11_THREAD_LOCAL_STORAGE 1
#define GO_NO_CXX11_UNRESTRICTED_UNIONS 1
#define GO_NO_CXX11_ATTRIBUTES 1
#define GO_NO_CXX11_REF_QUALIFIERS 1
#define GO_NO_CXX11_MAGIC_STATICS 1
#define GO_NO_CXX11_NOEXCEPT 1
#endif
#if (_MSC_VER < 1800)
#define GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS 1
#define GO_NO_CXX11_DELEGATING_CONSTRUCTORS 1
#define GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS 1
#define GO_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS 1
#define GO_NO_CXX11_INITIALIZER_LISTS 1
#define GO_NO_CXX11_RAW_STRING_LITERALS 1
#define GO_NO_CXX11_TEMPLATE_ALIASES 1
#define GO_NO_CXX11_VARIADIC_TEMPLATES 1
#define GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS 1
#endif
#if (_MSC_VER < 1700)
#define GO_NO_CXX11_ATOMIC_OPERATIONS 1
#define GO_NO_CXX11_FORWARD_ENUM_DECLARATIONS 1
#define GO_NO_CXX11_STRONGLY_TYPED_ENUM 1
#define GO_NO_CXX11_RANGE_FOR_LOOP 1
#define GO_NO_CXX11_OVERRIDE_AND_FINAL 1
#define GO_NO_CXX11_CONCURRENCY_SUPPORT 1
#endif
#if (_MSC_VER < 1600)
#define GO_NO_CXX11_AUTO 1
#define GO_NO_CXX11_DECLTYPE 1
#define GO_NO_CXX11_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES 1
#define GO_NO_CXX11_NULLPTR 1
#define GO_NO_CXX11_R_VALUE_REFERENCES 1
#define GO_NO_CXX11_STATIC_ASSERT 1
#define GO_NO_CXX11 1
#endif

// C++14 support
#if (_MSC_VER)
#define GO_NO_CXX14_EXTENDED_CONSTEXPR 1
#define GO_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES 1
#define GO_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION 1
#endif
#if (_MSC_VER < 1900)
#define GO_NO_CXX14_BINARY_LITERALS 1
#define GO_NO_CXX14_DECLTYPE_AUTO 1
#define GO_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES 1
#define GO_NO_CXX14_GENERIC_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX14_VARIABLE_TEMPLATES 1
#define GO_NO_CXX14_DEPRECATED_ATTRIBUTE 1
#define GO_NO_CXX14_SIZED_DEALLOCATION 1
#define GO_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR 1
#define GO_NO_CXX14_STD_RESULT_OF_AND_SFINAE 1
#define GO_NO_CXX14_CONSTEXPR_FOR_COMPLEX 1
#define GO_NO_CXX14_CONSTEXPR_FOR_CHRONO 1
#define GO_NO_CXX14_CONSTEXPR_FOR_ARRAY 1
#define GO_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE 1
#define GO_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT 1
#define GO_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING 1
#define GO_NO_CXX14_NULL_FORWARD_ITERATORS 1
#define GO_NO_CXX14_STD_QUOTED 1
#define GO_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP 1
#define GO_NO_CXX14_STD_INTEGER_SEQUENCE 1
#define GO_NO_CXX14_STD_SHARED_MUTEX_TIMED 1
#define GO_NO_CXX14_STD_EXCHANGE 1
#define GO_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST 1
#define GO_NO_CXX14_STD_GET_T 1
#define GO_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH 1
#endif
#if (_MSC_VER < 1800)
#define GO_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS 1
#define GO_NO_CXX14 1
#endif

// C++17 support
#if (_MSC_VER)
#define GO_NO_CXX17_HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS 1
#endif
#if (_MSC_VER < 1900)
#define GO_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE 1
#define GO_NO_CXX17_STD_SHARED_MUTEX_UNTIMED 1
#define GO_NO_CXX17 1
#endif

// C99 support
#if (_MSC_VER)
#define GO_NO_C99_PREPROCESSOR 1
#endif

// ATL support
#if defined(_ATL_VER)

#define GO_ATL 1

#define GO_ATL_VER _MFX_VER

#endif  // if defined(_ATL_VER)

// MFC support
#if defined(_MFC_VER)

#define GO_MFC 1

#define GO_MFC_VER _MFX_VER

#endif  // if defined(_MFC_VER)

// Unicode support
#if defined(_UNICODE) || defined(UNICODE)

#define GO_UNICODE 1

#endif  // if defined(_UNICODE) || defined(UNICODE)

#endif  // defined(_MSC_VER)

#endif  // #ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
