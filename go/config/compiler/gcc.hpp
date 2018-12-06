#ifndef GO_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
//
//  Copyright 2015-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if defined(__GNUC__)

#define GO_COMP_GCC 1

#define GO_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#define GO_COMP_GCC_MINGW 1
#endif  // #if defined(__MINGW32__) || defined(__MINGW64__)

// Compiler message
#define GO_MESSAGE(_message_) \
__warning _message_

// C/C++ support according to http://en.cppreference.com/w/cpp/compiler_support
#if (GO_GCC_VERSION < 40500)
#define GO_NO_CXX_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS 1
#endif  // #if (GO_GCC_VERSION < 40500)

// C++ keyword typename support
#define GO_TYPENAME typename
#define GO_TYPENAME_REQUIRED 1

// C++ issue workarounds
#define GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

// C++ restrictions
#define GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7 1

// C++11 support
#if (GO_GCC_VERSION)
#define GO_NO_CXX11_DYNAMIC_POINTER_SAFETY 1
#endif  // #if (GO_GCC_VERSION)
#if (GO_GCC_VERSION < 50100)
#define GO_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS 1
#endif  // #if (GO_GCC_VERSION < 50100)
#if (GO_GCC_VERSION < 40801)
#define GO_NO_CXX11_REF_QUALIFIERS 1
#endif  // #if (GO_GCC_VERSION < 40801)
#if (GO_GCC_VERSION < 40800)
#define GO_NO_CXX11_ALIGNAS 1
#define GO_NO_CXX11_INHERITING_CONSTRUCTORS 1
#define GO_NO_CXX11_THREAD_LOCAL_STORAGE 1
#define GO_NO_CXX11_ATTRIBUTES 1
#endif  // #if (GO_GCC_VERSION < 40800)
#if (GO_GCC_VERSION < 40700)
#define GO_NO_CXX11_DELEGATING_CONSTRUCTORS 1
#define GO_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS 1
#define GO_NO_CXX11_USER_DEFINED_LITERALS 1
#define GO_NO_CXX11_TEMPLATE_ALIASES 1
#define GO_NO_CXX11_OVERRIDE_AND_FINAL 1
#define GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS 1
#endif  // #if (GO_GCC_VERSION < 40700)
#if (GO_GCC_VERSION < 40600)
#define GO_NO_CXX11_CONSTEXPR 1
#define GO_NO_CXX11_FORWARD_ENUM_DECLARATIONS 1
#define GO_NO_CXX11_NULLPTR 1
#define GO_NO_CXX11_UNRESTRICTED_UNIONS 1
#define GO_NO_CXX11_RANGE_FOR_LOOP 1
#define GO_NO_CXX11_NOEXCEPT 1
#endif  // #if (GO_GCC_VERSION < 40600)
#if (GO_GCC_VERSION < 40500)
#define GO_NO_CXX11_ALIGNOF 1
#define GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS 1
#define GO_NO_CXX11_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX11_RAW_STRING_LITERALS 1
#endif  // #if (GO_GCC_VERSION < 40500)
#if (GO_GCC_VERSION < 40400)
#define GO_NO_CXX11_ATOMIC_OPERATIONS 1
#define GO_NO_CXX11_AUTO 1
#define GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS 1
#define GO_NO_CXX11_INITIALIZER_LISTS 1
#define GO_NO_CXX11_INLINE_NAMESPACES 1
#define GO_NO_CXX11_NEW_CHARACTER_TYPES 1
#define GO_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES 1
#define GO_NO_CXX11_UNICODE_STRING_LITERALS 1
#define GO_NO_CXX11_STRONGLY_TYPED_ENUM 1
#define GO_NO_CXX11_VARIADIC_TEMPLATES 1
#endif  // #if (GO_GCC_VERSION < 40400)
#if (GO_GCC_VERSION < 40300)
#define GO_NO_CXX11_DECLTYPE 1
#define GO_NO_CXX11_RIGHT_ANGLE_BRACKETS 1
#define GO_NO_CXX11_R_VALUE_REFERENCES 1
#define GO_NO_CXX11_STATIC_ASSERT 1
#define GO_NO_CXX11_TYPE_TRAITS 1
#define GO_NO_CXX11_MAGIC_STATICS 1
#endif  // #if (GO_GCC_VERSION < 40300)
#if (GO_GCC_VERSION < 30300)
#define GO_NO_CXX11_EXTERN_TEMPLATE 1
#define GO_NO_CXX11_LONG_LONG 1
#define GO_NO_CXX11 1
#endif  // #if (GO_GCC_VERSION < 30300)

#if defined(GO_NO_CXX11_CONSTEXPR)
#define GO_CONSTEXPR
#else
#define GO_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR)

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
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

#if defined(GO_NO_CXX11_NULLPTR)
#define GONULLPTR NULL
#else
#define GO_NULLPTR nullptr
#endif  // #if defined(GO_NO_CXX11_NULLPTR)

#if defined(GO_NO_CXX11_OVERRIDE_AND_FINAL)
#define GO_FINAL
#define GO_OVERRIDE
#else
#define GO_FINAL final
#define GO_OVERRIDE override
#endif  // #if defined(GO_NO_CXX11_OVERRIDE_AND_FINAL)

// C++14 support
#if (GO_GCC_VERSION)
#define GO_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION 1
#define GO_NO_CXX14_NULL_FORWARD_ITERATORS 1
#endif  // #if (GO_GCC_VERSION)
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX14_VARIABLE_TEMPLATES 1
#define GO_NO_CXX14_EXTENDED_CONSTEXPR 1
#define GO_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES 1
#define GO_NO_CXX14_SIZED_DEALLOCATION 1
#define GO_NO_CXX14_STD_RESULT_OF_AND_SFINAE 1
#define GO_NO_CXX14_CONSTEXPR_FOR_COMPLEX 1
#define GO_NO_CXX14_CONSTEXPR_FOR_CHRONO 1
#define GO_NO_CXX14_CONSTEXPR_FOR_ARRAY 1
#define GO_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE 1
#define GO_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT 1
#define GO_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING 1
#define GO_NO_CXX14_STD_QUOTED 1
#define GO_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP 1
#define GO_NO_CXX14_STD_INTEGER_SEQUENCE 1
#define GO_NO_CXX14_STD_SHARED_TIMED_MUTEX 1
#define GO_NO_CXX14_STD_EXCHANGE 1
#define GO_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST 1
#define GO_NO_CXX14_STD_GET_T 1
#define GO_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH 1
#endif  // #if (GO_GCC_VERSION < 50000)
#if (GO_GCC_VERSION < 40900)
#define GO_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS 1
#define GO_NO_CXX14_BINARY_LITERALS 1
#define GO_NO_CXX14_DECLTYPE_AUTO 1
#define GO_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES 1
#define GO_NO_CXX14_GENERIC_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX14_DEPRECATED_ATTRIBUTE 1
#define GO_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR 1
#define GO_NO_CXX14 1
#endif  // #if (GO_GCC_VERSION < 40900)

// C++17 support
#if (GO_GCC_VERSION < 70000)
#define GO_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD 1
#define GO_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUSPLUS_BOOL 1
#define GO_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS 1
#define GO_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM 1
#define GO_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES 1
#define GO_NO_CXX17_LAMBDA_CAPTURE_OF_INDIRECTED_THIS 1
#define GO_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION 1
#define GO_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVERALIGNED_DATA 1
#define GO_NO_CXX17_TEMPLATE_ARGUMENT_DEDUCTION_FOR_CLASS_TEMPLATES 1
#define GO_NO_CXX17_NONTYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE 1
#define GO_NO_CXX17_GUARANTEED_COPY_ELISION 1
#define GO_NO_CXX17_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS 1
#define GO_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS 1
#define GO_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER 1
#define GO_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX17_FALLTHROUGH_ATTRIBUTE 1
#define GO_NO_CXX17_NODISCARD_ATTRIBUTE 1
#define GO_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS 1
#define GO_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE 1
#define GO_NO_CXX17_STRUCTURED_BINDINGS 1
#define GO_NO_CXX17_CONSTEXPR_IF_STATEMENTS 1
#define GO_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH 1
#define GO_NO_CXX17_INLINE_VARIABLES 1
#define GO_NO_CXX17_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES 1
#define GO_NO_CXX17_SPLICING_MAPS_AND_SETS 1
#endif // #if (GO_GCC_VERSION < 70000)
#if (GO_GCC_VERSION < 60000)
#define GO_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE 1
#define GO_NO_CXX17_NESTED_NAMESPACE_DEFINITION 1
#define GO_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS 1
#define GO_NO_CXX17_U8_CHARACTER_LITERALS 1
#define GO_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NONTYPE_TEMPLATE_ARGUMENTS 1
#define GO_NO_CXX17_FOLD_EXPRESSIONS 1
#define GO_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS 1
#define GO_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR 1
#define GO_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS 1
#define GO_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE 1
#define GO_NO_CXX17_STD_SHARED_MUTEX_UNTIMED 1
#endif  // #if (GO_GCC_VERSION < 60000)
#if (GO_GCC_VERSION < 50100)
#define GO_NO_CXX17_REMOVING_TRIGRAPHS 1
#endif  // #if (GO_GCC_VERSION < 50100)
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION 1
#define GO_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER 1
#define GO_NO_CXX17_HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS 1
#endif  // #if (GO_GCC_VERSION < 50000)
#if (GO_GCC_VERSION < 30000)
#define GO_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS 1
#define GO_NO_CXX17 1
#endif  // #if (GO_GCC_VERSION < 30000)

// C99 support
#if (GO_GCC_VERSION < 40300)
#define GO_NO_C99_PREPROCESSOR 1
#endif  // #if (GO_GCC_VERSION < 40300)

#endif  // defined(__GNUC__)

#endif  // #ifndef GO_CONFIG_COMPILER_GCC_HPP_INCLUDED
