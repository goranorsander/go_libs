#ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
//
//  Copyright 2015-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if defined(_MSC_VER)

#define GO_COMP_MSVC 1

#define GO_MSVC_VER _MSC_VER

#if _MSC_FULL_VER > 100000000
#define GO_MSVC_FULL_VER _MSC_FULL_VER
#else
#define GO_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif  // #if _MSC_FULL_VER > 100000000

#if (_MSC_VER == 1500)
#define GO_COMP_MSVC_VC90 1
#define GO_IDE_MS_VS2008 1
#elif (_MSC_VER == 1600)
#define GO_COMP_MSVC_VC100 1
#define GO_IDE_MS_VS2010 1
#elif (_MSC_VER == 1700)
#define GO_COMP_MSVC_VC110 1
#define GO_IDE_MS_VS2012 1
#elif (_MSC_VER == 1800)
#define GO_COMP_MSVC_VC120 1
#define GO_IDE_MS_VS2013 1
#elif (_MSC_VER == 1900)
#define GO_COMP_MSVC_VC140 1
#define GO_IDE_MS_VS2015 1
#elif (_MSC_VER >= 1910)
#define GO_COMP_MSVC_VC141 1
#define GO_IDE_MS_VS2017 1
#if (_MSC_VER == 1910)
#define GO_IDE_MS_VS2017_15_0 1
#elif (_MSC_VER == 1911)
#define GO_IDE_MS_VS2017_15_3 1
#elif (_MSC_VER == 1912)
#define GO_IDE_MS_VS2017_15_5 1
#elif (_MSC_VER == 1913)
#define GO_IDE_MS_VS2017_15_6 1
#elif (_MSC_VER == 1914)
#define GO_IDE_MS_VS2017_15_7 1
#endif  // #if (_MSC_VER == 1910)
#endif  // #if (_MSC_VER == 1500)

// Compiler message
#define GO_MESSAGE(_message_) \
__pragma(message(_message_))

// C++ keyword typename support
#if (_MSC_VER < 1900)
#define GO_TYPENAME
#else
#define GO_TYPENAME typename
#define GO_TYPENAME_REQUIRED 1
#endif  // #if (_MSC_VER < 1900)

// C++ issue workarounds
#if (_MSC_VER < 1900)
#define GO_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE 1
#define GO_CANNOT_CREATE_U2STRING_ISSUE 1
#endif  // #if (_MSC_VER < 1900)

// C/C++ support according to http://en.cppreference.com/w/cpp/compiler_support
#if (_MSC_VER < 1600)
#define GO_NO_CXX_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS 1
#endif  // #if (_MSC_VER < 1600)

// C++11 support
#if (_MSC_VER)
#define GO_NO_CXX11_DYNAMIC_POINTER_SAFETY 1
#endif  // #if (_MSC_VER)
#if (_MSC_VER < 1900)
#define GO_NO_CXX11_ALIGNAS 1
#define GO_NO_CXX11_ALIGNOF 1
#define GO_NO_CXX11_CONSTEXPR 1
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
#define GO_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS 1
#define GO_NO_CXX11_DELEGATING_CONSTRUCTORS 1
#define GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS 1
#define GO_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS 1
#define GO_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS 1
#define GO_NO_CXX11_INITIALIZER_LISTS 1
#define GO_NO_CXX11_RAW_STRING_LITERALS 1
#define GO_NO_CXX11_TEMPLATE_ALIASES 1
#define GO_NO_CXX11_VARIADIC_TEMPLATES 1
#define GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS 1
#endif  // #if (_MSC_VER < 1800)
#if (_MSC_VER < 1700)
#define GO_NO_CXX11_ATOMIC_OPERATIONS 1
#define GO_NO_CXX11_FORWARD_ENUM_DECLARATIONS 1
#define GO_NO_CXX11_STRONGLY_TYPED_ENUM 1
#define GO_NO_CXX11_RANGE_FOR_LOOP 1
#define GO_NO_CXX11_OVERRIDE_AND_FINAL 1
#define GO_NO_CXX11_CONCURRENCY_SUPPORT 1
#endif  // #if (_MSC_VER < 1700)
#if (_MSC_VER < 1600)
#define GO_NO_CXX11_AUTO 1
#define GO_NO_CXX11_DECLTYPE 1
#define GO_NO_CXX11_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX11_LONG_LONG 1
#define GO_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES 1
#define GO_NO_CXX11_NULLPTR 1
#define GO_NO_CXX11_R_VALUE_REFERENCES 1
#define GO_NO_CXX11_STATIC_ASSERT 1
#define GO_NO_CXX11 1
#endif  // #if (_MSC_VER < 1600)

#if defined(GO_NO_CXX11_CONSTEXPR)
#define GO_CONSTEXPR
#else
#define GO_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR)

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_COMP_MSVC_VC120)
#define GO_DEFAULT_CONSTRUCTOR {}
#define GO_DEFAULT_DESTRUCTOR {}
#else
#define GO_DEFAULT_CONSTRUCTOR = default;
#define GO_DEFAULT_DESTRUCTOR = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#if defined(GO_NO_CXX11_NOEXCEPT)
#define GO_NOEXCEPT
#define GO_NOEXCEPT_OR_NOTHROW throw()
#define GO_NOEXCEPT_IF(_predicate_)
#define GO_NOEXCEPT_EXPR(_expression_) false
#else
#define GO_NOEXCEPT noexcept
#define GO_NOEXCEPT_OR_NOTHROW noexcept
#define GO_NOEXCEPT_IF(_predicate_) noexcept((_predicate_))
#define GO_NOEXCEPT_EXPR(_expression_) noexcept((_expression_))
#endif  // #if defined(GO_NO_CXX11_NOEXCEPT)

#if defined(GO_NO_CXX11_OVERRIDE_AND_FINAL)
#define GO_FINAL
#define GO_OVERRIDE
#else
#define GO_FINAL final
#define GO_OVERRIDE override
#endif  // #if defined(GO_NO_CXX11_OVERRIDE_AND_FINAL)

// C++14 support
#if (_MSC_VER)
#define GO_NO_CXX14_EXTENDED_CONSTEXPR 1
#define GO_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES 1
#define GO_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION 1
#endif  // #if (_MSC_VER)
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
#define GO_NO_CXX14_STD_SHARED_TIMED_MUTEX 1
#define GO_NO_CXX14_STD_EXCHANGE 1
#define GO_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST 1
#define GO_NO_CXX14_STD_GET_T 1
#define GO_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS 1
#define GO_NO_CXX14 1
#endif  // #if (_MSC_VER < 1800)

// C++17 support
#if (_MSC_VER < 1910)
#define GO_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE 1
#define GO_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR 1
#define GO_NO_CXX17_FALLTHROUGH_ATTRIBUTE 1
#endif  // #if (_MSC_VER < 1910)
#if (_MSC_VER < 1900)
#define GO_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION 1
#define GO_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER 1
#define GO_NO_CXX17_NESTED_NAMESPACE_DEFINITION 1
#define GO_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS 1
#define GO_NO_CXX17_U8_CHARACTER_LITERALS 1
#define GO_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS 1
#define GO_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE 1
#define GO_NO_CXX17_STD_SHARED_MUTEX_UNTIMED 1
#define GO_NO_CXX17 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1600)
#define GO_NO_CXX17_REMOVING_TRIGRAPHS 1
#define GO_NO_CXX17 1
#endif  // #if (_MSC_VER < 1600)
#if (_MSC_VER)
#define GO_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NONTYPE_TEMPLATE_ARGUMENTS 1
#define GO_NO_CXX17_FOLD_EXPRESSIONS 1
#define GO_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD 1
#define GO_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUSPLUS_BOOL 1
#define GO_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS 1
#define GO_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM 1
#define GO_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES 1
#define GO_NO_CXX17_LAMBDA_CAPTURE_OF_INDIRECTED_THIS 1
#define GO_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION 1
#define GO_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVERALIGNED_DATA 1
#define GO_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS 1
#define GO_NO_CXX17_HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS 1
#define GO_NO_CXX17_TEMPLATE_ARGUMENT_DEDUCTION_FOR_CLASS_TEMPLATES 1
#define GO_NO_CXX17_NONTYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE 1
#define GO_NO_CXX17_GUARANTEED_COPY_ELISION 1
#define GO_NO_CXX17_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS 1
#define GO_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS 1
#define GO_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER 1
#define GO_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX17_NODISCARD_ATTRIBUTE 1
#define GO_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS 1
#define GO_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE 1
#define GO_NO_CXX17_STRUCTURED_BINDINGS 1
#define GO_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS 1
#define GO_NO_CXX17_IGNORE_UNKNOWN_ATTRIBUTES 1
#define GO_NO_CXX17_CONSTEXPR_IF_STATEMENTS 1
#define GO_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH 1
#define GO_NO_CXX17_INLINE_VARIABLES 1
#define GO_NO_CXX17_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES 1
#define GO_NO_CXX17_SPLICING_MAPS_AND_SETS 1
#endif  // #if (_MSC_VER)

// C99 support
#if (_MSC_VER)
#define GO_NO_C99_PREPROCESSOR 1
#endif  // #if (_MSC_VER)

// ATL support
#if defined(_ATL_VER)
#define GO_MSVC_ATL 1
#define GO_MSVC_ATL_VER _MFX_VER
#endif  // if defined(_ATL_VER)

// MFC support
#if defined(_MFC_VER)
#define GO_MSVC_MFC 1
#define GO_MSVC_MFC_VER _MFX_VER
#endif  // if defined(_MFC_VER)

// Unicode support
#if defined(_UNICODE) || defined(UNICODE)
#define GO_UNICODE 1
#endif  // if defined(_UNICODE) || defined(UNICODE)

#endif  // defined(_MSC_VER)

#endif  // #ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
