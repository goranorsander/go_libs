#ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(BOOST_MSVC)

#define GO_BOOST_COMP_MSVC 1

#define GO_BOOST_MSVC_VER _MSC_VER

#if _MSC_FULL_VER > 100000000
#define GO_BOOST_MSVC_FULL_VER _MSC_FULL_VER
#else
#define GO_BOOST_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif  // #if _MSC_FULL_VER > 100000000

#if (_MSC_VER == 800)
#define GO_BOOST_COMP_MSVC_VC10 1
#elif (_MSC_VER == 900)
#define GO_BOOST_COMP_MSVC_VC20 1
#elif (_MSC_VER == 1000)
#define GO_BOOST_COMP_MSVC_VC40 1
#define GO_BOOST_IDE_MS_DS40 1
#elif (_MSC_VER == 1020)
#define GO_BOOST_COMP_MSVC_VC42 1
#define GO_BOOST_IDE_MS_DS42 1
#elif (_MSC_VER == 1100)
#define GO_BOOST_COMP_MSVC_VC50 1
#define GO_BOOST_IDE_MS_VS97 1
#elif (_MSC_VER == 1200)
#define GO_BOOST_COMP_MSVC_VC60 1
#define GO_BOOST_IDE_MS_VS60 1
#elif (_MSC_VER == 1300)
#define GO_BOOST_COMP_MSVC_VC70 1
#define GO_BOOST_IDE_MS_VS2002 1
#elif (_MSC_VER == 1310)
#define GO_BOOST_COMP_MSVC_VC71 1
#define GO_BOOST_IDE_MS_VS2003 1
#elif (_MSC_VER == 1400)
#define GO_BOOST_COMP_MSVC_VC80 1
#define GO_BOOST_IDE_MS_VS2005 1
#elif (_MSC_VER == 1500)
#define GO_BOOST_COMP_MSVC_VC90 1
#define GO_BOOST_IDE_MS_VS2008 1
#elif (_MSC_VER == 1600)
#define GO_BOOST_COMP_MSVC_VC100 1
#define GO_BOOST_IDE_MS_VS2010 1
#elif (_MSC_VER == 1700)
#define GO_BOOST_COMP_MSVC_VC110 1
#define GO_BOOST_IDE_MS_VS2012 1
#elif (_MSC_VER == 1800)
#define GO_BOOST_COMP_MSVC_VC120 1
#define GO_BOOST_IDE_MS_VS2013 1
#elif (_MSC_VER == 1900)
#define GO_BOOST_COMP_MSVC_VC140 1
#define GO_BOOST_IDE_MS_VS2015 1
#if (_MSC_FULL_VER == 190023506)
#define GO_BOOST_IDE_MS_VS2015_U1 1
#elif (_MSC_VER == 190023918)
#define GO_BOOST_IDE_MS_VS2015_U2 1
#elif (_MSC_VER == 190024210)
#define GO_BOOST_IDE_MS_VS2015_U3 1
#endif  // #if (_MSC_FULL_VER == 190023506)
#elif (_MSC_VER >= 1910) && (_MSC_VER < 1920)
#define GO_BOOST_COMP_MSVC_VC141 1
#define GO_BOOST_IDE_MS_VS2017 1
#if (_MSC_VER == 1910)
#define GO_BOOST_IDE_MS_VS2017_15_0 1
#elif (_MSC_VER == 1911)
#define GO_BOOST_IDE_MS_VS2017_15_3 1
#elif (_MSC_VER == 1912)
#define GO_BOOST_IDE_MS_VS2017_15_5 1
#elif (_MSC_VER == 1913)
#define GO_BOOST_IDE_MS_VS2017_15_6 1
#elif (_MSC_VER == 1914)
#define GO_BOOST_IDE_MS_VS2017_15_7 1
#elif (_MSC_VER == 1915)
#define GO_BOOST_IDE_MS_VS2017_15_8 1
#elif (_MSC_VER == 1916)
#define GO_BOOST_IDE_MS_VS2017_15_9 1
#endif  // #if (_MSC_VER == 1910)
#elif (_MSC_VER >= 1920)
#define GO_BOOST_COMP_MSVC_VC142 1
#define GO_BOOST_IDE_MS_VS2019 1
#if (_MSC_VER == 1920)
#define GO_BOOST_IDE_MS_VS2019_16_0 1
#elif (_MSC_VER == 1921)
#define GO_BOOST_IDE_MS_VS2019_16_1 1
#elif (_MSC_VER == 1922)
#define GO_BOOST_IDE_MS_VS2019_16_2 1
#elif (_MSC_VER == 1923)
#define GO_BOOST_IDE_MS_VS2019_16_3 1
#elif (_MSC_VER == 1924)
#define GO_BOOST_IDE_MS_VS2019_16_4 1
#elif (_MSC_VER == 1925)
#define GO_BOOST_IDE_MS_VS2019_16_5 1
#elif (_MSC_VER == 1926)
#define GO_BOOST_IDE_MS_VS2019_16_6 1
#elif (_MSC_VER == 1927)
#define GO_BOOST_IDE_MS_VS2019_16_7 1
#elif (_MSC_VER == 1928)
#define GO_BOOST_IDE_MS_VS2019_16_8 1
#endif  // #if (_MSC_VER == 1920)
#endif  // #if (_MSC_VER == 800)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__pragma(message(_message_))

// C++ keyword typename support
#if (_MSC_VER < 1900)
#define GO_BOOST_TYPENAME
#else
#define GO_BOOST_TYPENAME typename
#define GO_BOOST_CPP_TYPENAME_REQUIRED 1
#endif  // #if (_MSC_VER < 1900)

// C++ issue workarounds
#if (_MSC_VER < 1900)
#define GO_BOOST_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE 1
#define GO_BOOST_CANNOT_CREATE_U2STRING_ISSUE 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_BOOST_STD_MUTEX_ASSIGNMENT_OPERATOR_IS_PRIVATE_ISSUE 1
#endif  // #if (_MSC_VER < 1800)

// C++11 support
#if (_MSC_VER < 1200)
#define GO_BOOST_NO_CXX11 1
#endif  // #if (_MSC_VER < 1200)

// C++11 language support
#if (_MSC_VER < 1914)
#define GO_BOOST_NO_CXX11_EXPRESSION_SFINAE 1
#endif  // #if (_MSC_VER < 1914)
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX11_ALIGNAS 1
#define GO_BOOST_NO_CXX11_ALIGNOF 1
#define GO_BOOST_NO_CXX11_ATTRIBUTES 1
#define GO_BOOST_NO_CXX11_CHAR16_T_AND_CHAR32_T 1
#define GO_BOOST_NO_CXX11_CONSTEXPR 1
#define GO_BOOST_NO_CXX11_DYNAMIC_INITIALIZATION_AND_DESTRUCTION_WITH_CONCURRENCY_MAGIC_STATICS 1
#define GO_BOOST_NO_CXX11_INHERITING_CONSTRUCTORS 1
#define GO_BOOST_NO_CXX11_INLINE_NAMESPACES 1
#define GO_BOOST_NO_CXX11_NOEXCEPT 1
#define GO_BOOST_NO_CXX11_REF_QUALIFIERS 1
#define GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE 1
#define GO_BOOST_NO_CXX11_UNICODE_STRING_LITERALS 1
#define GO_BOOST_NO_CXX11_UNRESTRICTED_UNIONS 1
#define GO_BOOST_NO_CXX11_USER_DEFINED_LITERALS 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS 1
#define GO_BOOST_NO_CXX11_DELEGATING_CONSTRUCTORS 1
#define GO_BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS 1
#define GO_BOOST_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS 1
#define GO_BOOST_NO_CXX11_INITIALIZER_LISTS 1
#define GO_BOOST_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS 1
#define GO_BOOST_NO_CXX11_RAW_STRING_LITERALS 1
#define GO_BOOST_NO_CXX11_TEMPLATE_ALIASES 1
#define GO_BOOST_NO_CXX11_VARIADIC_TEMPLATES 1
#endif  // #if (_MSC_VER < 1800)
#if (_MSC_VER < 1700)
#define GO_BOOST_NO_CXX11_ATOMIC_OPERATIONS 1
#define GO_BOOST_NO_CXX11_FORWARD_ENUM_DECLARATIONS 1
#define GO_BOOST_NO_CXX11_MUTEX 1
#define GO_BOOST_NO_CXX11_OVERRIDE_AND_FINAL 1
#define GO_BOOST_NO_CXX11_RANGE_FOR_LOOP 1
#define GO_BOOST_NO_CXX11_STRONGLY_TYPED_ENUM 1
#endif  // #if (_MSC_VER < 1700)
#if (_MSC_VER < 1600)
#define GO_BOOST_NO_CXX11_AUTO 1
#define GO_BOOST_NO_CXX11_DECLTYPE 1
#define GO_BOOST_NO_CXX11_LAMBDA_EXPRESSIONS 1
#define GO_BOOST_NO_CXX11_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS 1
#define GO_BOOST_NO_CXX11_NULLPTR 1
#define GO_BOOST_NO_CXX11_RVALUE_REFERENCES 1
#define GO_BOOST_NO_CXX11_STATIC_ASSERT 1
#define GO_BOOST_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES 1
#endif  // #if (_MSC_VER < 1600)
#if (_MSC_VER < 1400)
#define GO_BOOST_NO_CXX11_COMPILER_SUPPORT_FOR_TYPE_TRAITS 1
#define GO_BOOST_NO_CXX11_LONG_LONG 1
#define GO_BOOST_NO_CXX11_RIGHT_ANGLE_BRACKETS 1
#endif  // #if (_MSC_VER < 1400)
#if (_MSC_VER < 1200)
#define GO_BOOST_NO_CXX11_EXTERN_TEMPLATE 1
#endif  // #if (_MSC_VER < 1200)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX11_C99_PREPROCESSOR 1
#define GO_BOOST_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION 1
#endif  // #if defined(_MSC_VER)

// C++11 library support
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION_LIBRARY_SUPPORT_NO_OP 1
#define GO_BOOST_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1400)
#define GO_BOOST_NO_CXX11_TYPE_TRAITS 1
#endif  // #if (_MSC_VER < 1400)

// C++11 cross platform support
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX11_CONDITION_VARIABLE 1
#define GO_BOOST_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR 1
#define GO_BOOST_NO_CXX11_DEFAULTED_COPY_CONSTRUCTOR 1
#define GO_BOOST_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR 1
#define GO_BOOST_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR 1
#define GO_BOOST_NO_CXX11_FIXED_WIDTH_INTEGER_TYPES 1
#define GO_BOOST_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST 1
#define GO_BOOST_NO_CXX11_SNPRINTF 1
#define GO_BOOST_NO_CXX11_STATIC_CONST_DATA_MEMBER_INITIALIZER 1
#define GO_BOOST_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS 1
#define GO_BOOST_NO_CXX11_TYPE_ALIASES 1
#endif  // #if (_MSC_VER < 1800)
#if (_MSC_VER < 1700)
#define GO_BOOST_NO_CXX11_CONCURRENCY_SUPPORT 1
#endif  // #if (_MSC_VER < 1700)
#if (_MSC_VER < 1600)
#define GO_BOOST_NO_CXX11_CHAR16_T 1
#define GO_BOOST_NO_CXX11_CHAR32_T 1
#define GO_BOOST_NO_CXX11_CODECVT 1
#endif  // #if (_MSC_VER < 1600)

#if defined(GO_BOOST_NO_CXX11_CONSTEXPR)
#define GO_BOOST_CONSTEXPR
#else
#define GO_BOOST_CONSTEXPR constexpr
#endif  // #if defined(GO_BOOST_NO_CXX11_CONSTEXPR)

#if defined(GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120)
#define GO_BOOST_DEFAULT_CONSTRUCTOR {}
#define GO_BOOST_DEFAULT_DESTRUCTOR {}
#else
#define GO_BOOST_DEFAULT_CONSTRUCTOR = default;
#define GO_BOOST_DEFAULT_DESTRUCTOR = default;
#endif  // #if defined(GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if defined(GO_BOOST_NO_CXX11_NOEXCEPT)
#define GO_BOOST_NOEXCEPT
#define GO_BOOST_NOEXCEPT_OR_NOTHROW throw()
#define GO_BOOST_NOEXCEPT_IF(_predicate_)
#define GO_BOOST_NOEXCEPT_EXPR(_expression_) false
#else
#define GO_BOOST_NOEXCEPT noexcept
#define GO_BOOST_NOEXCEPT_OR_NOTHROW noexcept
#define GO_BOOST_NOEXCEPT_IF(_predicate_) noexcept((_predicate_))
#define GO_BOOST_NOEXCEPT_EXPR(_expression_) noexcept((_expression_))
#endif  // #if defined(GO_BOOST_NO_CXX11_NOEXCEPT)

#if defined(GO_BOOST_NO_CXX11_NULLPTR)
#define GO_BOOST_NULLPTR NULL
#else
#define GO_BOOST_NULLPTR nullptr
#endif  // #if defined(GO_BOOST_NO_CXX11_NULLPTR)

#if defined(GO_BOOST_NO_CXX11_OVERRIDE_AND_FINAL)
#define GO_BOOST_FINAL
#define GO_BOOST_OVERRIDE
#else
#define GO_BOOST_FINAL final
#define GO_BOOST_OVERRIDE override
#endif  // #if defined(GO_BOOST_NO_CXX11_OVERRIDE_AND_FINAL)

#if defined(GO_BOOST_NO_CXX11_TEMPLATE_ALIASES)
#define GO_BOOST_USING(_alias_, _type_) typedef _type_ _alias_
#else
#define GO_BOOST_USING(_alias_, _type_) using _alias_ = _type_
#endif  // #if defined(GO_BOOST_NO_CXX11_TEMPLATE_ALIASES)

// C++14 support
#if (_MSC_VER < 1800)
#define GO_BOOST_NO_CXX14 1
#endif  // #if (_MSC_VER < 1800)

// C++14 language support
#if (_MSC_VER < 1910)
#define GO_BOOST_NO_CXX14_EXTENDED_CONSTEXPR 1
#define GO_BOOST_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES_NSDMI 1
#endif  // #if (_MSC_VER < 1910)
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX14_BINARY_LITERALS 1
#define GO_BOOST_NO_CXX14_DECLTYPE_AUTO_RETURN_TYPE_DEDUCTION_FOR_NORMAL_FUNCTIONS 1
#define GO_BOOST_NO_CXX14_DEPRECATED_ATTRIBUTE 1
#define GO_BOOST_NO_CXX14_GENERIC_POLYMORPHIC_LAMBDA_EXPRESSIONS 1
#define GO_BOOST_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES_INIT_CAPTURE 1
#define GO_BOOST_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR 1
#define GO_BOOST_NO_CXX14_SIZED_DEALLOCATION 1
#define GO_BOOST_NO_CXX14_VARIABLE_TEMPLATES 1
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1800)
#define GO_BOOST_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS 1
#endif  // #if (_MSC_VER < 1800)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION_AVOIDING_FUSING_ALLOCATIONS 1
#endif  // #if defined(_MSC_VER)

// C++14 library support
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX14_CONSTEXPR_FOR_ARRAY 1
#define GO_BOOST_NO_CXX14_CONSTEXPR_FOR_CHRONO 1
#define GO_BOOST_NO_CXX14_CONSTEXPR_FOR_COMPLEX 1
#define GO_BOOST_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE 1
#define GO_BOOST_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH 1
#define GO_BOOST_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST 1
#define GO_BOOST_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP 1
#define GO_BOOST_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT 1
#define GO_BOOST_NO_CXX14_NULL_FORWARD_ITERATORS 1
#define GO_BOOST_NO_CXX14_STD_EXCHANGE 1
#define GO_BOOST_NO_CXX14_STD_GET_T 1
#define GO_BOOST_NO_CXX14_STD_INTEGER_SEQUENCE 1
#define GO_BOOST_NO_CXX14_STD_QUOTED 1
#define GO_BOOST_NO_CXX14_STD_RESULT_OF_AND_SFINAE 1
#define GO_BOOST_NO_CXX14_STD_SHARED_TIMED_MUTEX 1
#define GO_BOOST_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING 1
#endif  // #if (_MSC_VER < 1900)

// C++14 cross platform support
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP 1
#endif  // #if (_MSC_VER < 1900)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS 1
#endif  // #if defined(_MSC_VER)

#if defined(GO_BOOST_NO_CXX14_EXTENDED_CONSTEXPR)
#define GO_BOOST_EXTENDED_CONSTEXPR
#else
#define GO_BOOST_EXTENDED_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR)

// C++17 support
#if (_MSC_VER < 1600)
#define GO_BOOST_NO_CXX17 1
#else
#ifndef GO_BOOST_NO_STD_AUTO_PTR
#define GO_BOOST_NO_STD_AUTO_PTR 1
#endif  // #ifndef GO_BOOST_NO_STD_AUTO_PTR
#endif  // #if (_MSC_VER < 1600)

// C++17 language support
#if (_MSC_VER < 1914)
#define GO_BOOST_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES
#define GO_BOOST_NO_CXX17_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
#define GO_BOOST_NO_CXX17_DR_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS_DR1941_ET_AL
#define GO_BOOST_NO_CXX17_NON_TYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE
#define GO_BOOST_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS
#define GO_BOOST_NO_CXX17_REPLACEMENT_OF_CLASS_OBJECTS_CONTAINING_REFERENCE_MEMBERS
#define GO_BOOST_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER
#endif  // #if (_MSC_VER < 1914)
#if (_MSC_VER < 1913)
#define GO_BOOST_NO_CXX17_GUARANTEED_COPY_ELISION
#endif  // #if (_MSC_VER < 1913)
#if (_MSC_VER < 1912)
#define GO_BOOST_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NON_TYPE_TEMPLATE_ARGUMENTS
#define GO_BOOST_NO_CXX17_DR_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES
#define GO_BOOST_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVER_ALIGNED_DATA
#define GO_BOOST_NO_CXX17_FOLD_EXPRESSIONS
#define GO_BOOST_NO_CXX17_INLINE_VARIABLES
#define GO_BOOST_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM
#define GO_BOOST_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS
#endif  // #if (_MSC_VER < 1912)
#if (_MSC_VER < 1911)
#define GO_BOOST_NO_CXX17___HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS
#define GO_BOOST_NO_CXX17_CONSTEXPR_IF_STATEMENTS
#define GO_BOOST_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS
#define GO_BOOST_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS
#define GO_BOOST_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS
#define GO_BOOST_NO_CXX17_IGNORE_UNKNOWN_ATTRIBUTES
#define GO_BOOST_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH
#define GO_BOOST_NO_CXX17_LAMBDA_CAPTURE_OF_THIS_DEREFERENCED_BY_VALUE
#define GO_BOOST_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE
#define GO_BOOST_NO_CXX17_NODISCARD_ATTRIBUTE
#define GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUS_PLUS_BOOL
#define GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD
#define GO_BOOST_NO_CXX17_STRUCTURED_BINDINGS
#define GO_BOOST_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION
#endif  // #if (_MSC_VER < 1911)
#if (_MSC_VER < 1910)
#define GO_BOOST_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR
#define GO_BOOST_NO_CXX17_FALLTHROUGH_ATTRIBUTE
#define GO_BOOST_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS_FROM_CXX17
#define GO_BOOST_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE
#endif  // #if (_MSC_VER < 1910)
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS
#define GO_BOOST_NO_CXX17_NESTED_NAMESPACE_DEFINITION
#define GO_BOOST_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION
#define GO_BOOST_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER
#define GO_BOOST_NO_CXX17_U8_CHARACTER_LITERALS
#endif  // #if (_MSC_VER < 1900)
#if (_MSC_VER < 1600)
#define GO_BOOST_NO_CXX17_REMOVING_TRIGRAPHS
#endif  // #if (_MSC_VER < 1600)

// C++17 library support
#if (_MSC_VER < 1915)
#define GO_BOOST_NO_CXX17_STD_IS_AGGREGATE
#endif  // #if (_MSC_VER < 1915)
#if (_MSC_VER < 1914)
#define GO_BOOST_NO_CXX17_ELEMENTARY_STRING_CONVERSIONS
#define GO_BOOST_NO_CXX17_FILE_SYSTEM_LIBRARY
#define GO_BOOST_NO_CXX17_MATHEMATICAL_SPECIAL_FUNCTIONS
#define GO_BOOST_NO_CXX17_STANDARDIZATION_OF_PARALLELISM_TS
#endif  // #if (_MSC_VER < 1914)
#if (_MSC_VER < 1913)
#define GO_BOOST_NO_CXX17_POLYMORPHIC_MEMORY_RESOURCES
#endif  // #if (_MSC_VER < 1913)
#if (_MSC_VER < 1912)
#define GO_BOOST_NO_CXX17_SPLICING_MAPS_AND_SETS
#define GO_BOOST_NO_CXX17_STD_NOT_FN
#define GO_BOOST_NO_CXX17_STD_SHARED_PTR_AND_STD_WEAK_PTR_WITH_ARRAY_SUPPORT
#endif  // #if (_MSC_VER < 1912)
#if (_MSC_VER < 1911)
#define GO_BOOST_NO_CXX17_HARDWARE_INTERFERENCE_SIZE
#define GO_BOOST_NO_CXX17_STD_BYTE
#define GO_BOOST_NO_CXX17_STD_GCD_AND_STD_LCM
#define GO_BOOST_NO_CXX17_STD_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#define GO_BOOST_NO_CXX17_STD_SCOPED_LOCK
#endif  // #if (_MSC_VER < 1911)
#if (_MSC_VER < 1910)
#define GO_BOOST_NO_CXX17_STD_ANY
#define GO_BOOST_NO_CXX17_STD_MAKE_FROM_TUPLE
#define GO_BOOST_NO_CXX17_STD_OPTIONAL
#define GO_BOOST_NO_CXX17_STD_STRING_VIEW
#define GO_BOOST_NO_CXX17_STD_VARIANT
#endif  // #if (_MSC_VER < 1910)
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE
#define GO_BOOST_NO_CXX17_LOGICAL_OPERATOR_TYPE_TRAITS
#define GO_BOOST_NO_CXX17_NOTHROW_SWAPPABLE_TRAITS
#define GO_BOOST_NO_CXX17_STD_BOOL_CONSTANT
#define GO_BOOST_NO_CXX17_STD_CLAMP
#define GO_BOOST_NO_CXX17_STD_SHARED_MUTEX_UNTIMED
#define GO_BOOST_NO_CXX17_STD_SIZE_STD_EMPTY_AND_STD_DATA
#define GO_BOOST_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS
#define GO_BOOST_NO_CXX17_STD_VOID_T
#define GO_BOOST_NO_CXX17_TYPE_TRAITS_VARIABLE_TEMPLATES
#endif  // #if (_MSC_VER < 1900)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX17_CXX17_SHOULD_REFER_TO_C11_INSTEAD_OF_C99
#endif  // #if defined(_MSC_VER)

// C++17 cross platform support

// C++20 support
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX20 1
#else
#ifndef GO_BOOST_NO_STD_AUTO_PTR
#define GO_BOOST_NO_STD_AUTO_PTR 1
#endif  // #ifndef GO_BOOST_NO_STD_AUTO_PTR
#endif  // #if (_MSC_VER < 1900)

// C++20 language support
#if (_MSC_VER < 1922)
#define GO_BOOST_NO_CXX20_ALLOW_LAMBDA_CAPTURE_ASSIGN_THIS 1
#define GO_BOOST_NO_CXX20_CHAR8_T 1
#define GO_BOOST_NO_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS 1
#define GO_BOOST_NO_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS 1
#define GO_BOOST_NO_CXX20_DEPRECATE_IMPLICIT_CAPTURE_OF_THIS_VIA_ASSIGN 1
#define GO_BOOST_NO_CXX20_EXPLICIT_BOOL 1
#define GO_BOOST_NO_CXX20_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE 1
#define GO_BOOST_NO_CXX20_TEMPLATE_PARAMETER_LIST_FOR_GENERIC_LAMBDAS 1
#define GO_BOOST_NO_CXX20_THREE_WAY_COMPARE_NOT_EQUAL_AND_EQUAL 1
#endif  // #if (_MSC_VER < 1922)
#if (_MSC_VER < 1921)
#define GO_BOOST_NO_CXX20_ADL_AND_FUNCTION_TEMPLATES_THAT_ARE_NOT_VISIBLE 1
#define GO_BOOST_NO_CXX20_DESIGNATED_INITIALIZERS 1
#define GO_BOOST_NO_CXX20_DR_ALLOW_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS 1
#define GO_BOOST_NO_CXX20_DR_RELAXING_THE_STRUCTURED_BINDINGS_CUSTOMIZATION_POINT_FINDING_RULES 1
#endif  // #if (_MSC_VER < 1921)
#if (_MSC_VER < 1920)
#define GO_BOOST_NO_CXX20_INTEGRATING_FEATURE_TEST_MACROS 1
#define GO_BOOST_NO_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS 1
#define GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR 1
#endif  // #if (_MSC_VER < 1920)
#if (_MSC_VER < 1914)
#define GO_BOOST_NO_CXX20_INITIALIZER_LIST_CONSTRUCTORS_IN_CLASS_TEMPLATE_ARGUMENT_DEDUCTION 1
#endif  // #if (_MSC_VER < 1914)
#if (_MSC_VER < 1910)
#define GO_BOOST_NO_CXX20_CHANGING_THE_ACTIVE_MEMBER_OF_A_UNION_INSIDE_CONSTEXPR 1
#endif  // #if (_MSC_VER < 1910)
#if (_MSC_VER < 1900)
#define GO_BOOST_NO_CXX20_CONST_REF_QUALIFIED_POINTERS_TO_MEMBERS 1
#endif  // #if (_MSC_VER < 1900)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX20___VA_OPT__ 1
#define GO_BOOST_NO_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS 1
#define GO_BOOST_NO_CXX20_ATTRIBUTE_NO_UNIQUE_ADDRESS 1
#define GO_BOOST_NO_CXX20_ATTRIBUTES_LIKELY_AND_UNLIKELY 1
#define GO_BOOST_NO_CXX20_CLASS_TYPES_IN_NON_TYPE_TEMPLATE_PARAMETERS 1
#define GO_BOOST_NO_CXX20_CONCEPTS 1
#define GO_BOOST_NO_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR 1
#define GO_BOOST_NO_CXX20_CONSTEXPR_DYNAMIC_CAST_AND_POLYMORPHIC_TYPEID 1
#define GO_BOOST_NO_CXX20_CONSTEXPR_TRY_CATCH_BLOCKS 1
#define GO_BOOST_NO_CXX20_CONSTEXPR_VIRTUAL_FUNCTION 1
#define GO_BOOST_NO_CXX20_CONSTINIT 1
#define GO_BOOST_NO_CXX20_COROUTINES 1
#define GO_BOOST_NO_CXX20_DEFAULT_MEMBER_INITIALIZERS_FOR_BIT_FIELDS 1
#define GO_BOOST_NO_CXX20_DEPRECATE_COMMA_OPERATOR_IN_SUBSCRIPTS 1
#define GO_BOOST_NO_CXX20_DEPRECATING_SOME_USES_OF_VOLATILE 1
#define GO_BOOST_NO_CXX20_DESTROYING_OPERATOR_DELETE 1
#define GO_BOOST_NO_CXX20_DR_ARRAY_SIZE_DEDUCTION_IN_NEW_EXPRESSIONS 1
#define GO_BOOST_NO_CXX20_DR_EXPLICITLY_DEFAULTED_FUNCTIONS_WITH_DIFFERENT_EXCEPTION_SPECIFICATIONS 1
#define GO_BOOST_NO_CXX20_DR_IMPLICIT_MOVE_FOR_MORE_LOCAL_OBJECTS_AND_RVALUE_REFERENCES 1
#define GO_BOOST_NO_CXX20_DR_NODISCARD_FOR_CONSTRUCTORS 1
#define GO_BOOST_NO_CXX20_DR_RELAXING_THE_RANGE_FOR_LOOP_CUSTOMIZATION_POINT_FINDING_RULES 1
#define GO_BOOST_NO_CXX20_IMMEDIATE_FUNCTIONS 1
#define GO_BOOST_NO_CXX20_INIT_STATEMENTS_FOR_RANGE_BASED_FOR 1
#define GO_BOOST_NO_CXX20_LAMBDA_CAPTURE_AND_STORAGE_CLASS_SPECIFIERS_OF_STRUCTURED_BINDINGS 1
#define GO_BOOST_NO_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS 1
#define GO_BOOST_NO_CXX20_LESS_EAGER_INSTANTIATION_OF_CONSTEXPR_FUNCTIONS 1
#define GO_BOOST_NO_CXX20_MAKE_TYPENAME_MORE_OPTIONAL 1
#define GO_BOOST_NO_CXX20_MODULES 1
#define GO_BOOST_NO_CXX20_MORE_CONSTEXPR_CONTAINERS 1
#define GO_BOOST_NO_CXX20_NESTED_INLINE_NAMESPACES 1
#define GO_BOOST_NO_CXX20_NODISCARD_WITH_MESSAGE 1
#define GO_BOOST_NO_CXX20_PARENTHESIZED_INITIALIZATION_OF_AGGREGATES 1
#define GO_BOOST_NO_CXX20_PERMIT_CONVERSIONS_TO_ARRAYS_OF_UNKNOWN_BOUND 1
#define GO_BOOST_NO_CXX20_SIGNED_INTEGERS_ARE_TWOS_COMPLEMENT 1
#define GO_BOOST_NO_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE 1
#define GO_BOOST_NO_CXX20_STD_IS_CONSTANT_EVALUATED 1
#define GO_BOOST_NO_CXX20_STRONGER_UNICODE_REQUIREMENTS 1
#define GO_BOOST_NO_CXX20_TRIVIAL_DEFAULT_INITIALIZATION_IN_CONSTEXPR_FUNCTIONS 1
#define GO_BOOST_NO_CXX20_UNEVALUATED_ASM_DECLARATION_IN_CONSTEXPR_FUNCTIONS 1
#define GO_BOOST_NO_CXX20_YET_ANOTHER_APPROACH_FOR_CONSTRAINED_DECLARATIONS 1
#endif  // #if defined(_MSC_VER)

// C++20 library support
#if (_MSC_VER < 1923)
#define GO_BOOST_NO_CXX20_USING_STD_MOVE_IN_NUMERIC_ALGORITHMS
#define GO_BOOST_NO_CXX20_STD_IS_NOTHROW_CONVERTIBLE
#define GO_BOOST_NO_CXX20_CONCEPTS_LIBRARY
#define GO_BOOST_NO_CXX20_FIXING_INPUT_STREAM_OPERATOR_BASIC_ISTREAM_REF_CHART_POINTER
#define GO_BOOST_NO_CXX20_HETEROGENEOUS_LOOKUP_FOR_UNORDERED_CONTAINERS
#endif  // #if (_MSC_VER < 1923)
#if (_MSC_VER < 1922)
#define GO_BOOST_NO_CXX20_STD_ENDIAN
#define GO_BOOST_NO_CXX20_FLOATING_POINT_ATOMIC
#define GO_BOOST_NO_CXX20_NODISCARD_IN_THE_STANDARD_LIBRARY
#define GO_BOOST_NO_CXX20_UTILITY_TO_CONVERT_A_POINTER_TO_A_RAW_POINTER
#define GO_BOOST_NO_CXX20_VERSION
#define GO_BOOST_NO_CXX20_LIBRARY_SUPPORT_FOR_CHAR8_T
#define GO_BOOST_NO_CXX20_STD_FUNCTIONS_MOVE_CONSTRUCTOR_SHOULD_BE_NOEXCEPT
#endif  // #if (_MSC_VER < 1922)
#if (_MSC_VER < 1921)
#define GO_BOOST_NO_CXX20_STRING_PREFIX_AND_SUFFIX_CHECKING
#define GO_BOOST_NO_CXX20_CONTAINS_MEMBER_FUNCTION_OF_ASSOCIATIVE_CONTAINERS
#define GO_BOOST_NO_CXX20_IMPROVING_THE_RETURN_VALUE_OF_ERASE_LIKE_ALGORITHMS
#define GO_BOOST_NO_CXX20_ADD_SHIFT_TO_ALGORITHM
#define GO_BOOST_NO_CXX20_STD_TYPE_IDENTITY
#define GO_BOOST_NO_CXX20_STD_UNWRAP_REF_DECAY_AND_STD_UNWRAP_REFERENCE
#endif  // #if (_MSC_VER < 1921)
#if (_MSC_VER < 1920)
#define GO_BOOST_NO_CXX20_STD_REMOVE_CVREF
#define GO_BOOST_NO_CXX20_DR_MAKE_CREATE_DIRECTORY_INTUITIVE
#endif  // #if (_MSC_VER < 1920)
#if (_MSC_VER < 1914)
#define GO_BOOST_NO_CXX20_CHRONO_ZERO_MIN_AND_MAX_SHOULD_BE_NOEXCEPT
#endif  // #if (_MSC_VER < 1914)
#if (_MSC_VER < 1911)
#define GO_BOOST_NO_CXX20_CONSTEXPRITERATOR_REQUIREMENTS
#define GO_BOOST_NO_CXX20_DR_STD_VARIANT_AND_STD_OPTIONAL_SHOULD_PROPAGATE_COPY_MOVE_TRIVIALITY
#endif  // #if (_MSC_VER < 1911)
#if (_MSC_VER < 1600)
#define GO_BOOST_NO_CXX20_COMPARING_UNORDERED_CONTAINERS
#endif  // #if (_MSC_VER < 1600)
#if defined(_MSC_VER)
#define GO_BOOST_NO_CXX20_EXTENDING_STD_MAKE_SHARED_TO_SUPPORT_ARRAYS
#define GO_BOOST_NO_CXX20_SYNCHRONIZED_BUFFERED_OSTREAM
#define GO_BOOST_NO_CXX20_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY
#define GO_BOOST_NO_CXX20_MORE_CONSTEXPR_FOR_COMPLEX
#define GO_BOOST_NO_CXX20_MAKE_STD_MEMORY_ORDER_A_SCOPED_ENUMERATION
#define GO_BOOST_NO_CXX20_LIBRARY_SUPPORT_FOR_OPERATOR_THREE_WAY_COMPARE
#define GO_BOOST_NO_CXX20_ATOMIC_STD_SHARED_PTR_AND_STD_WEAK_PTR
#define GO_BOOST_NO_CXX20_STD_SPAN
#define GO_BOOST_NO_CXX20_CALENDAR_AND_TIMEZONE
#define GO_BOOST_NO_CXX20_STD_BASIC_STRING_RESERVE_SHOULD_NOT_SHRINK
#define GO_BOOST_NO_CXX20_STD_ATOMIC_REF
#define GO_BOOST_NO_CXX20_DR_GUARANTEED_COPY_ELISION_FOR_PIECEWISE_CONSTRUCTION
#define GO_BOOST_NO_CXX20_STD_BIT_CAST
#define GO_BOOST_NO_CXX20_INTEGRAL_POWER_OF_2_OPERATIONS
#define GO_BOOST_NO_CXX20_STD_DESTROYING_DELETE
#define GO_BOOST_NO_CXX20_CONSTEXPR_FOR_STD_SWAP_AND_SWAP_RELATED_FUNCTIONS
#define GO_BOOST_NO_CXX20_CONSTEXPR_COMPARISON_OPERATORS_FOR_STD_ARRAY
#define GO_BOOST_NO_CXX20_STD_BIND_FRONT
#define GO_BOOST_NO_CXX20_STD_REFERENCE_WRAPPER_FOR_INCOMPLETE_TYPES
#define GO_BOOST_NO_CXX20_UTILITY_FUNCTIONS_TO_IMPLEMENT_USES_ALLOCATOR_CONSTRUCTION
#define GO_BOOST_NO_CXX20_A_SANE_STD_VARIANT_CONVERTING_CONSTRUCTOR
#define GO_BOOST_NO_CXX20_THE_ONE_RANGES_PROPOSAL
#define GO_BOOST_NO_CXX20_CONSTEXPR_IN_STD_POINTER_TRAITS
#define GO_BOOST_NO_CXX20_STD_ASSUME_ALIGNED
#define GO_BOOST_NO_CXX20_REMOVE_COMPARISON_OPERATORS_OF_STD_SPAN
#define GO_BOOST_NO_CXX20_MAKE_STATEFUL_ALLOCATOR_PROPAGATION_MORE_CONSISTENT_FOR_OPERATOR_PLUS_BASIC_STRING
#define GO_BOOST_NO_CXX20_CONSISTENT_CONTAINER_ERASURE
#define GO_BOOST_NO_CXX20_STD_LERP_AND_STD_MIDPOINT
#define GO_BOOST_NO_CXX20_USABILITY_ENHANCEMENTS_FOR_STD_SPAN
#define GO_BOOST_NO_CXX20_STD_SSIZE_AND_UNSIGNED_EXTENT_FOR_STD_SPAN
#define GO_BOOST_NO_CXX20_TRAITS_FOR_BOUNDED_AND_UNBOUNDED_ARRAYS
#define GO_BOOST_NO_CXX20_BIT_OPERATIONS
#define GO_BOOST_NO_CXX20_STD_SOURCE_LOCATION
#endif  // #if defined(_MSC_VER)

// C++20 cross platform support

// C99 support
#if defined(_MSC_VER)
#define GO_BOOST_NO_C99_PREPROCESSOR 1
#endif  // #if defined(_MSC_VER)

// ATL support
#if defined(_ATL_VER)
#define GO_BOOST_MSVC_ATL 1
#define GO_BOOST_MSVC_ATL_VER _MFX_VER
#endif  // if defined(_ATL_VER)

// MFC support
#if defined(_MFC_VER)
#define GO_BOOST_MSVC_MFC 1
#define GO_BOOST_MSVC_MFC_VER _MFX_VER
#endif  // if defined(_MFC_VER)

// Unicode support
#if defined(_UNICODE) || defined(UNICODE)
#define GO_BOOST_MSVC_UNICODE 1
#endif  // if defined(_UNICODE) || defined(UNICODE)

// Boost libraries support
#if (_MSC_VER < 1800)
#define GO_BOOST_NO_BOOST_PHOENIX 1
#endif  // #if (_MSC_VER < 1900)

// Treat some warnings as error
#pragma warning (error: 4355) // 'this' : used in base member initializer list

// Suppress warnings
#if defined (GO_BOOST_ENABLE_SUPPRESS_WARNINGS)

#define GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS \
__pragma(warning(push, 0))

#define GO_BOOST_END_SUPPRESS_ALL_WARNINGS \
__pragma(warning(pop))

#define GO_BOOST_MSVC_BEGIN_SUPPRESS_WARNING(_warning_) \
__pragma(warning(push)) \
__pragma(warning(disable: _warning_))

#define GO_BOOST_MSVC_SUPPRESS_WARNING(_warning_) \
__pragma(warning(disable: _warning_))

#define GO_BOOST_MSVC_END_SUPPRESS_WARNING \
__pragma(warning(pop))

#else

#define GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#define GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#define GO_BOOST_MSVC_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_MSVC_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_MSVC_END_SUPPRESS_WARNING

#endif  // #if defined (GO_BOOST_ENABLE_SUPPRESS_WARNINGS)

#define GO_BOOST_CLANG_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_CLANG_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_CLANG_END_SUPPRESS_WARNING

#define GO_BOOST_GCC_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_GCC_SUPPRESS_WARNING(_warning_)
#define GO_BOOST_GCC_END_SUPPRESS_WARNING

#endif  // #if defined(BOOST_MSVC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
