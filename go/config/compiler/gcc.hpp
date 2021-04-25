#ifndef GO_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
//
//  Copyright 2015-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/config/preprocessor.hpp>

#if defined(__GNUC__)

#define GO_COMP_GCC 1

#define GO_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#define GO_COMP_GCC_MINGW 1
#endif  // #if defined(__MINGW32__) || defined(__MINGW64__)

// Use #pragma in macros
#define GO_DO_PRAGMA(x) _Pragma (#x)
#define GO_DO_PRAGMA_EX(x) GO_DO_PRAGMA(x)

// Compiler message
#define GO_MESSAGE(_message_) GO_DO_PRAGMA_EX(GCC warning GO_TO_STRING(_message_))

// C++ keyword typename support
#define GO_TYPENAME typename
#define GO_CPP_TYPENAME_REQUIRED 1

// C++ issue workarounds
#define GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

#if defined(GO_COMP_GCC_MINGW) && (defined(_WIN32) || defined(WIN32))
// See https://stackoverflow.com/questions/14191566/c-mutex-in-namespace-std-does-not-name-a-type
#define GO_NO_GTHREADS_ISSUE 1
#endif  // #if defined(GO_COMP_GCC_MINGW)

// C++ restrictions
#define GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7 1

// C++11 support
#if (GO_GCC_VERSION < 30300)
#define GO_NO_CXX11 1
#endif  // #if (GO_GCC_VERSION < 30300)

// C++11 language support
#if (GO_GCC_VERSION < 40801)
#define GO_NO_CXX11_DECLTYPE 1
#define GO_NO_CXX11_REF_QUALIFIERS 1
#endif  // #if (GO_GCC_VERSION < 40801)
#if (GO_GCC_VERSION < 40800)
#define GO_NO_CXX11_ALIGNAS 1
#define GO_NO_CXX11_ATTRIBUTES 1
#define GO_NO_CXX11_INHERITING_CONSTRUCTORS 1
#define GO_NO_CXX11_THREAD_LOCAL_STORAGE 1
#endif  // #if (GO_GCC_VERSION < 40800)
#if (GO_GCC_VERSION < 40700)
#define GO_NO_CXX11_DELEGATING_CONSTRUCTORS 1
#define GO_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS 1
#define GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS 1
#define GO_NO_CXX11_OVERRIDE_AND_FINAL 1
#define GO_NO_CXX11_TEMPLATE_ALIASES 1
#define GO_NO_CXX11_USER_DEFINED_LITERALS 1
#endif  // #if (GO_GCC_VERSION < 40700)
#if (GO_GCC_VERSION < 40600)
#define GO_NO_CXX11_CONSTEXPRv
#define GO_NO_CXX11_FORWARD_ENUM_DECLARATIONS 1
#define GO_NO_CXX11_NOEXCEPT 1
#define GO_NO_CXX11_NULLPTR 1
#define GO_NO_CXX11_RANGE_FOR_LOOP 1
#define GO_NO_CXX11_RVALUE_REFERENCES 1
#define GO_NO_CXX11_UNRESTRICTED_UNIONS 1
#endif  // #if (GO_GCC_VERSION < 40600)
#if (GO_GCC_VERSION < 40500)
#define GO_NO_CXX11_ALIGNOF 1
#define GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS 1
#define GO_NO_CXX11_LAMBDA_EXPRESSIONS 1
#define GO_NO_CXX11_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS 1
#define GO_NO_CXX11_RAW_STRING_LITERALS 1
#endif  // #if (GO_GCC_VERSION < 40500)
#if (GO_GCC_VERSION < 40400)
#define GO_NO_CXX11_ATOMIC_OPERATIONS 1
#define GO_NO_CXX11_AUTO 1
#define GO_NO_CXX11_CHAR16_T_AND_CHAR32_T 1
#define GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS 1
#define GO_NO_CXX11_EXPRESSION_SFINAE 1
#define GO_NO_CXX11_INITIALIZER_LISTS 1
#define GO_NO_CXX11_INLINE_NAMESPACES 1
#define GO_NO_CXX11_STRONGLY_TYPED_ENUM 1
#define GO_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES 1
#define GO_NO_CXX11_UNICODE_STRING_LITERALS 1
#define GO_NO_CXX11_VARIADIC_TEMPLATES 1
#endif  // #if (GO_GCC_VERSION < 40400)
#if (GO_GCC_VERSION < 40300)
#define GO_NO_CXX11_C99_PREPROCESSOR 1
#define GO_NO_CXX11_COMPILER_SUPPORT_FOR_TYPE_TRAITS 1
#define GO_NO_CXX11_DYNAMIC_INITIALIZATION_AND_DESTRUCTION_WITH_CONCURRENCY_MAGIC_STATICS 1
#define GO_NO_CXX11_RIGHT_ANGLE_BRACKETS 1
#define GO_NO_CXX11_STATIC_ASSERT 1
#endif  // #if (GO_GCC_VERSION < 40300)
#if (GO_GCC_VERSION < 30300)
#define GO_NO_CXX11_EXTERN_TEMPLATE 1
#define GO_NO_CXX11_LONG_LONG 1
#endif  // #if (GO_GCC_VERSION < 30300)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION 1
#endif  // #if defined(GO_GCC_VERSION)

// C++11 library support
#if (GO_GCC_VERSION < 60000)
#define GO_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION_LIBRARY_SUPPORT_NO_OP 1
#endif  // #if (GO_GCC_VERSION < 60000)
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS 1
#endif  // #if (GO_GCC_VERSION < 50000)
#if (GO_GCC_VERSION < 40300)
#define GO_NO_CXX11_TYPE_TRAITS 1
#endif  // #if (GO_GCC_VERSION < 40300)

// C++11 cross platform support
#if (GO_GCC_VERSION < 40400)
#define GO_NO_CXX11_CHAR16_T 1
#define GO_NO_CXX11_CHAR32_T 1
#endif  // #if (GO_GCC_VERSION < 40400)
#if (GO_GCC_VERSION < 30300)
#define GO_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION 1
#endif  // #if (GO_GCC_VERSION < 30300)
#if !defined(GO_COMP_GCC_MINGW)
#define GO_NO_CXX11_LOCALTIME_S 1
#endif  // #if !defined(GO_COMP_GCC_MINGW)

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

#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
#define GO_USING(_alias_, _type_) typedef _type_ _alias_
#else
#define GO_USING(_alias_, _type_) using _alias_ = _type_
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)

// C++14 support
#if (GO_GCC_VERSION < 40900)
#define GO_NO_CXX14 1
#endif  // #if (GO_GCC_VERSION < 40900)

// C++14 language support
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX14_EXTENDED_CONSTEXPR
#define GO_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES_NSDMI
#define GO_NO_CXX14_SIZED_DEALLOCATION
#define GO_NO_CXX14_VARIABLE_TEMPLATES
#endif  // #if (GO_GCC_VERSION < 50000)
#if (GO_GCC_VERSION < 40900)
#define GO_NO_CXX14_BINARY_LITERALS
#define GO_NO_CXX14_DECLTYPE_AUTO_RETURN_TYPE_DEDUCTION_FOR_NORMAL_FUNCTIONS
#define GO_NO_CXX14_DEPRECATED_ATTRIBUTE
#define GO_NO_CXX14_GENERIC_POLYMORPHIC_LAMBDA_EXPRESSIONS
#define GO_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES_INIT_CAPTURE
#define GO_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR
#define GO_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS
#endif  // #if (GO_GCC_VERSION < 40900)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION_AVOIDING_FUSING_ALLOCATIONS
#endif  // #if defined(GO_GCC_VERSION)

// C++14 library support
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX14_CONSTEXPR_FOR_ARRAY
#define GO_NO_CXX14_CONSTEXPR_FOR_CHRONO
#define GO_NO_CXX14_CONSTEXPR_FOR_COMPLEX
#define GO_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE
#define GO_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH
#define GO_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST
#define GO_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP
#define GO_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT
#define GO_NO_CXX14_STD_EXCHANGE
#define GO_NO_CXX14_STD_GET_T
#define GO_NO_CXX14_STD_INTEGER_SEQUENCE
#define GO_NO_CXX14_STD_QUOTED
#define GO_NO_CXX14_STD_RESULT_OF_AND_SFINAE
#define GO_NO_CXX14_STD_SHARED_TIMED_MUTEX
#define GO_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING
#endif  // #if (GO_GCC_VERSION < 50000)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX14_NULL_FORWARD_ITERATORS
#endif  // #if defined(GO_GCC_VERSION)

// C++14 cross platform support
#if (GO_GCC_VERSION < 40900)
#define GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP 1
#endif  // #if (GO_GCC_VERSION < 40900)

#if defined(GO_NO_CXX14_EXTENDED_CONSTEXPR)
#define GO_EXTENDED_CONSTEXPR
#else
#define GO_EXTENDED_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR)

// C++17 support
#if (GO_GCC_VERSION < 30000)
#define GO_NO_CXX17 1
#else
#ifndef GO_NO_STD_AUTO_PTR
#define GO_NO_STD_AUTO_PTR 1
#endif  // #ifndef GO_NO_STD_AUTO_PTR
#endif  // #if (GO_GCC_VERSION < 30000)

// C++17 language support
#if (GO_GCC_VERSION < 70000)
#define GO_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES
#define GO_NO_CXX17_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
#define GO_NO_CXX17_CONSTEXPR_IF_STATEMENTS
#define GO_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS
#define GO_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS
#define GO_NO_CXX17_DR_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES
#define GO_NO_CXX17_DR_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS_DR1941_ET_AL
#define GO_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVER_ALIGNED_DATA
#define GO_NO_CXX17_FALLTHROUGH_ATTRIBUTE
#define GO_NO_CXX17_GUARANTEED_COPY_ELISION
#define GO_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH
#define GO_NO_CXX17_INLINE_VARIABLES
#define GO_NO_CXX17_LAMBDA_CAPTURE_OF_THIS_DEREFERENCED_BY_VALUE
#define GO_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM
#define GO_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE
#define GO_NO_CXX17_NODISCARD_ATTRIBUTE
#define GO_NO_CXX17_NON_TYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE
#define GO_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS
#define GO_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUS_PLUS_BOOL
#define GO_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD
#define GO_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS_FROM_CXX17
#define GO_NO_CXX17_REPLACEMENT_OF_CLASS_OBJECTS_CONTAINING_REFERENCE_MEMBERS
#define GO_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER
#define GO_NO_CXX17_STRUCTURED_BINDINGS
#define GO_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION
#endif  // #if (GO_GCC_VERSION < 70000)
#if (GO_GCC_VERSION < 60000)
#define GO_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NON_TYPE_TEMPLATE_ARGUMENTS
#define GO_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS
#define GO_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR
#define GO_NO_CXX17_FOLD_EXPRESSIONS
#define GO_NO_CXX17_NESTED_NAMESPACE_DEFINITION
#define GO_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE
#define GO_NO_CXX17_U8_CHARACTER_LITERALS
#define GO_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS
#endif  // #if (GO_GCC_VERSION < 60000)
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX17___HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS
#define GO_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION
#define GO_NO_CXX17_REMOVING_TRIGRAPHS
#define GO_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER
#endif  // #if (GO_GCC_VERSION < 50000)
#if (GO_GCC_VERSION < 30000)
#define GO_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS
#define GO_NO_CXX17_IGNORE_UNKNOWN_ATTRIBUTES
#endif  // #if (GO_GCC_VERSION < 30000)

// C++17 library support
#if (GO_GCC_VERSION < 90000)
#define GO_NO_CXX17_CXX17_SHOULD_REFER_TO_C11_INSTEAD_OF_C99
#define GO_NO_CXX17_POLYMORPHIC_MEMORY_RESOURCES
#define GO_NO_CXX17_STANDARDIZATION_OF_PARALLELISM_TS
#endif  // #if (GO_GCC_VERSION < 90000)
#if (GO_GCC_VERSION < 80000)
#define GO_NO_CXX17_ELEMENTARY_STRING_CONVERSIONS
#define GO_NO_CXX17_FILE_SYSTEM_LIBRARY
#endif  // #if (GO_GCC_VERSION < 80000)
#if (GO_GCC_VERSION < 70000)
#define GO_NO_CXX17_MATHEMATICAL_SPECIAL_FUNCTIONS
#define GO_NO_CXX17_NOTHROW_SWAPPABLE_TRAITS
#define GO_NO_CXX17_SPLICING_MAPS_AND_SETS
#define GO_NO_CXX17_STD_ANY
#define GO_NO_CXX17_STD_BYTE
#define GO_NO_CXX17_STD_CLAMP
#define GO_NO_CXX17_STD_GCD_AND_STD_LCM
#define GO_NO_CXX17_STD_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#define GO_NO_CXX17_STD_IS_AGGREGATE
#define GO_NO_CXX17_STD_MAKE_FROM_TUPLE
#define GO_NO_CXX17_STD_NOT_FN
#define GO_NO_CXX17_STD_OPTIONAL
#define GO_NO_CXX17_STD_SCOPED_LOCK
#define GO_NO_CXX17_STD_SHARED_PTR_AND_STD_WEAK_PTR_WITH_ARRAY_SUPPORT
#define GO_NO_CXX17_STD_STRING_VIEW
#define GO_NO_CXX17_STD_VARIANT
#define GO_NO_CXX17_TYPE_TRAITS_VARIABLE_TEMPLATES
#endif  // #if (GO_GCC_VERSION < 70000)
#if (GO_GCC_VERSION < 60000)
#define GO_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE
#define GO_NO_CXX17_LOGICAL_OPERATOR_TYPE_TRAITS
#define GO_NO_CXX17_STD_BOOL_CONSTANT
#define GO_NO_CXX17_STD_SHARED_MUTEX_UNTIMED
#define GO_NO_CXX17_STD_SIZE_STD_EMPTY_AND_STD_DATA
#define GO_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS
#define GO_NO_CXX17_STD_VOID_T
#endif  // #if (GO_GCC_VERSION < 60000)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX17_HARDWARE_INTERFERENCE_SIZE
#endif  // #if defined(GO_GCC_VERSION)

// C++17 cross platform support

// C++20 support
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX20 1
#else
#ifndef GO_NO_STD_AUTO_PTR
#define GO_NO_STD_AUTO_PTR 1
#endif  // #ifndef GO_NO_STD_AUTO_PTR
#endif  // #if (GO_GCC_VERSION < 50000)

// C++20 language support
#if (GO_GCC_VERSION < 100000)
#define GO_NO_CXX20_CONSTINIT 1
#define GO_NO_CXX20_DEPRECATE_COMMA_OPERATOR_IN_SUBSCRIPTS 1
#define GO_NO_CXX20_DEPRECATING_SOME_USES_OF_VOLATILE 1
#define GO_NO_CXX20_LAMBDA_CAPTURE_AND_STORAGE_CLASS_SPECIFIERS_OF_STRUCTURED_BINDINGS 1
#define GO_NO_CXX20_UNEVALUATED_ASM_DECLARATION_IN_CONSTEXPR_FUNCTIONS 1
#endif  // #if (GO_GCC_VERSION < 100000)
#if (GO_GCC_VERSION < 90000)
#define GO_NO_CXX20_ADL_AND_FUNCTION_TEMPLATES_THAT_ARE_NOT_VISIBLE 1
#define GO_NO_CXX20_ATTRIBUTE_NO_UNIQUE_ADDRESS 1
#define GO_NO_CXX20_ATTRIBUTES_LIKELY_AND_UNLIKELY 1
#define GO_NO_CXX20_CHANGING_THE_ACTIVE_MEMBER_OF_A_UNION_INSIDE_CONSTEXPR 1
#define GO_NO_CXX20_CHAR8_T 1
#define GO_NO_CXX20_CLASS_TYPES_IN_NON_TYPE_TEMPLATE_PARAMETERS 1
#define GO_NO_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR 1
#define GO_NO_CXX20_CONSTEXPR_TRY_CATCH_BLOCKS 1
#define GO_NO_CXX20_CONSTEXPR_VIRTUAL_FUNCTION 1
#define GO_NO_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS 1
#define GO_NO_CXX20_DEPRECATE_IMPLICIT_CAPTURE_OF_THIS_VIA_ASSIGN 1
#define GO_NO_CXX20_DESTROYING_OPERATOR_DELETE 1
#define GO_NO_CXX20_EXPLICIT_BOOL 1
#define GO_NO_CXX20_INIT_STATEMENTS_FOR_RANGE_BASED_FOR 1
#define GO_NO_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS 1
#define GO_NO_CXX20_LESS_EAGER_INSTANTIATION_OF_CONSTEXPR_FUNCTIONS 1
#define GO_NO_CXX20_MAKE_TYPENAME_MORE_OPTIONAL 1
#define GO_NO_CXX20_NESTED_INLINE_NAMESPACES 1
#define GO_NO_CXX20_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE 1
#define GO_NO_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS 1
#define GO_NO_CXX20_SIGNED_INTEGERS_ARE_TWOS_COMPLEMENT 1
#define GO_NO_CXX20_STD_IS_CONSTANT_EVALUATED 1
#endif  // #if (GO_GCC_VERSION < 90000)
#if (GO_GCC_VERSION < 80000)
#define GO_NO_CXX20_ALLOW_LAMBDA_CAPTURE_ASSIGN_THIS 1
#define GO_NO_CXX20_CONST_REF_QUALIFIED_POINTERS_TO_MEMBERS 1
#define GO_NO_CXX20_DEFAULT_MEMBER_INITIALIZERS_FOR_BIT_FIELDS 1
#define GO_NO_CXX20_DESIGNATED_INITIALIZERS 1
#define GO_NO_CXX20_DR_ALLOW_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS 1
#define GO_NO_CXX20_DR_RELAXING_THE_RANGE_FOR_LOOP_CUSTOMIZATION_POINT_FINDING_RULES 1
#define GO_NO_CXX20_DR_RELAXING_THE_STRUCTURED_BINDINGS_CUSTOMIZATION_POINT_FINDING_RULES 1
#define GO_NO_CXX20_INITIALIZER_LIST_CONSTRUCTORS_IN_CLASS_TEMPLATE_ARGUMENT_DEDUCTION 1
#define GO_NO_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE 1
#define GO_NO_CXX20_TEMPLATE_PARAMETER_LIST_FOR_GENERIC_LAMBDAS 1
#endif  // #if (GO_GCC_VERSION < 80000)
#if (GO_GCC_VERSION < 50000)
#define GO_NO_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS 1
#define GO_NO_CXX20_INTEGRATING_FEATURE_TEST_MACROS 1
#endif  // #if (GO_GCC_VERSION < 50000)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX20___VA_OPT__ 1
#define GO_NO_CXX20_CONCEPTS 1
#define GO_NO_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS 1
#define GO_NO_CXX20_CONSTEXPR_DYNAMIC_CAST_AND_POLYMORPHIC_TYPEID 1
#define GO_NO_CXX20_COROUTINES 1
#define GO_NO_CXX20_DR_ARRAY_SIZE_DEDUCTION_IN_NEW_EXPRESSIONS 1
#define GO_NO_CXX20_DR_EXPLICITLY_DEFAULTED_FUNCTIONS_WITH_DIFFERENT_EXCEPTION_SPECIFICATIONS 1
#define GO_NO_CXX20_DR_IMPLICIT_MOVE_FOR_MORE_LOCAL_OBJECTS_AND_RVALUE_REFERENCES 1
#define GO_NO_CXX20_DR_NODISCARD_FOR_CONSTRUCTORS 1
#define GO_NO_CXX20_IMMEDIATE_FUNCTIONS 1
#define GO_NO_CXX20_MODULES 1
#define GO_NO_CXX20_MORE_CONSTEXPR_CONTAINERS 1
#define GO_NO_CXX20_NODISCARD_WITH_MESSAGE 1
#define GO_NO_CXX20_PARENTHESIZED_INITIALIZATION_OF_AGGREGATES 1
#define GO_NO_CXX20_PERMIT_CONVERSIONS_TO_ARRAYS_OF_UNKNOWN_BOUND 1
#define GO_NO_CXX20_STRONGER_UNICODE_REQUIREMENTS 1
#define GO_NO_CXX20_THREE_WAY_COMPARE_NOT_EQUAL_AND_EQUAL 1
#define GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR 1
#define GO_NO_CXX20_TRIVIAL_DEFAULT_INITIALIZATION_IN_CONSTEXPR_FUNCTIONS 1
#define GO_NO_CXX20_YET_ANOTHER_APPROACH_FOR_CONSTRAINED_DECLARATIONS 1
#endif  // #if defined(GO_GCC_VERSION)

// C++20 library support
#if (GO_GCC_VERSION < 100000)
#define GO_NO_CXX20_A_SANE_STD_VARIANT_CONVERTING_CONSTRUCTOR 1
#define GO_NO_CXX20_CONSTEXPR_COMPARISON_OPERATORS_FOR_STD_ARRAY 1
#define GO_NO_CXX20_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY 1
#define GO_NO_CXX20_CONSTEXPR_FOR_STD_SWAP_AND_SWAP_RELATED_FUNCTIONS 1
#define GO_NO_CXX20_FLOATING_POINT_ATOMIC 1
#define GO_NO_CXX20_MAKE_STATEFUL_ALLOCATOR_PROPAGATION_MORE_CONSISTENT_FOR_OPERATOR_PLUS_BASIC_STRING 1
#define GO_NO_CXX20_REMOVE_COMPARISON_OPERATORS_OF_STD_SPAN 1
#define GO_NO_CXX20_STD_ATOMIC_REF 1
#define GO_NO_CXX20_STD_SPAN 1
#define GO_NO_CXX20_STD_SSIZE_AND_UNSIGNED_EXTENT_FOR_STD_SPAN 1
#define GO_NO_CXX20_USABILITY_ENHANCEMENTS_FOR_STD_SPAN 1
#endif  // #if (GO_GCC_VERSION < 100000)
#if (GO_GCC_VERSION < 90000)
#define GO_NO_CXX20_BIT_OPERATIONS 1
#define GO_NO_CXX20_CHRONO_ZERO_MIN_AND_MAX_SHOULD_BE_NOEXCEPT 1
#define GO_NO_CXX20_CONSISTENT_CONTAINER_ERASURE 1
#define GO_NO_CXX20_CONSTEXPR_IN_STD_POINTER_TRAITS 1
#define GO_NO_CXX20_CONSTEXPRITERATOR_REQUIREMENTS 1
#define GO_NO_CXX20_CONTAINS_MEMBER_FUNCTION_OF_ASSOCIATIVE_CONTAINERS 1
#define GO_NO_CXX20_DR_GUARANTEED_COPY_ELISION_FOR_PIECEWISE_CONSTRUCTION 1
#define GO_NO_CXX20_IMPROVING_THE_RETURN_VALUE_OF_ERASE_LIKE_ALGORITHMS 1
#define GO_NO_CXX20_INTEGRAL_POWER_OF_2_OPERATIONS 1
#define GO_NO_CXX20_LIBRARY_SUPPORT_FOR_CHAR8_T 1
#define GO_NO_CXX20_MAKE_STD_MEMORY_ORDER_A_SCOPED_ENUMERATION 1
#define GO_NO_CXX20_MORE_CONSTEXPR_FOR_COMPLEX 1
#define GO_NO_CXX20_NODISCARD_IN_THE_STANDARD_LIBRARY 1
#define GO_NO_CXX20_STD_ASSUME_ALIGNED 1
#define GO_NO_CXX20_STD_BIND_FRONT 1
#define GO_NO_CXX20_STD_DESTROYING_DELETE 1
#define GO_NO_CXX20_STD_IS_NOTHROW_CONVERTIBLE 1
#define GO_NO_CXX20_STD_LERP_AND_STD_MIDPOINT 1
#define GO_NO_CXX20_STD_REFERENCE_WRAPPER_FOR_INCOMPLETE_TYPES 1
#define GO_NO_CXX20_STD_REMOVE_CVREF 1
#define GO_NO_CXX20_STD_TYPE_IDENTITY 1
#define GO_NO_CXX20_STD_UNWRAP_REF_DECAY_AND_STD_UNWRAP_REFERENCE 1
#define GO_NO_CXX20_STRING_PREFIX_AND_SUFFIX_CHECKING 1
#define GO_NO_CXX20_TRAITS_FOR_BOUNDED_AND_UNBOUNDED_ARRAYS 1
#define GO_NO_CXX20_USING_STD_MOVE_IN_NUMERIC_ALGORITHMS 1
#define GO_NO_CXX20_UTILITY_FUNCTIONS_TO_IMPLEMENT_USES_ALLOCATOR_CONSTRUCTION 1
#define GO_NO_CXX20_VERSION 1
#endif  // #if (GO_GCC_VERSION < 90000)
#if (GO_GCC_VERSION < 80300)
#define GO_NO_CXX20_DR_MAKE_CREATE_DIRECTORY_INTUITIVE 1
#define GO_NO_CXX20_DR_STD_VARIANT_AND_STD_OPTIONAL_SHOULD_PROPAGATE_COPY_MOVE_TRIVIALITY 1
#endif  // #if (GO_GCC_VERSION < 80300)
#if (GO_GCC_VERSION < 80000)
#define GO_NO_CXX20_STD_ENDIAN 1
#define GO_NO_CXX20_UTILITY_TO_CONVERT_A_POINTER_TO_A_RAW_POINTER 1
#endif  // #if (GO_GCC_VERSION < 80000)
#if (GO_GCC_VERSION < 70200)
#define GO_NO_CXX20_STD_FUNCTIONS_MOVE_CONSTRUCTOR_SHOULD_BE_NOEXCEPT 1
#endif  // #if (GO_GCC_VERSION < 70200)
#if defined(GO_GCC_VERSION)
#define GO_NO_CXX20_ADD_SHIFT_TO_ALGORITHM 1
#define GO_NO_CXX20_ATOMIC_STD_SHARED_PTR_AND_STD_WEAK_PTR 1
#define GO_NO_CXX20_CALENDAR_AND_TIMEZONE 1
#define GO_NO_CXX20_COMPARING_UNORDERED_CONTAINERS 1
#define GO_NO_CXX20_CONCEPTS_LIBRARY 1
#define GO_NO_CXX20_EXTENDING_STD_MAKE_SHARED_TO_SUPPORT_ARRAYS 1
#define GO_NO_CXX20_FIXING_INPUT_STREAM_OPERATOR_BASIC_ISTREAM_REF_CHART_POINTER 1
#define GO_NO_CXX20_HETEROGENEOUS_LOOKUP_FOR_UNORDERED_CONTAINERS 1
#define GO_NO_CXX20_LIBRARY_SUPPORT_FOR_OPERATOR_THREE_WAY_COMPARE 1
#define GO_NO_CXX20_STD_BASIC_STRING_RESERVE_SHOULD_NOT_SHRINK 1
#define GO_NO_CXX20_STD_BIT_CAST 1
#define GO_NO_CXX20_STD_SOURCE_LOCATION 1
#define GO_NO_CXX20_SYNCHRONIZED_BUFFERED_OSTREAM 1
#define GO_NO_CXX20_THE_ONE_RANGES_PROPOSAL 1
#endif  // #if defined(GO_GCC_VERSION)

// C++20 cross platform support

// C99 support
#if (GO_GCC_VERSION < 40300)
#define GO_NO_C99_PREPROCESSOR 1
#endif  // #if (GO_GCC_VERSION < 40300)

// Treat some warnings as error
//#pragma GCC diagnostic error "-Wfoo"

// Suppress warnings
#if defined (GO_ENABLE_SUPPRESS_WARNINGS)

#define GO_BEGIN_SUPPRESS_ALL_WARNINGS \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wall\"") \
_Pragma("GCC diagnostic ignored \"-Wextra\"")

#define GO_END_SUPPRESS_ALL_WARNINGS \
_Pragma("GCC diagnostic pop")

#define GO_GCC_BEGIN_SUPPRESS_WARNING(_warning_) \
_Pragma("GCC diagnostic push") \
GO_DO_PRAGMA_EX(GCC diagnostic ignored GO_TO_STRING(GO_CAT(-W, _warning_)))

#define GO_GCC_SUPPRESS_WARNING(_warning_) \
GO_DO_PRAGMA_EX(GCC diagnostic ignored GO_TO_STRING(GO_CAT(-W, _warning_)))

#define GO_GCC_END_SUPPRESS_WARNING \
_Pragma("GCC diagnostic pop")

#else

#define GO_BEGIN_SUPPRESS_ALL_WARNINGS
#define GO_END_SUPPRESS_ALL_WARNINGS

#define GO_GCC_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_GCC_SUPPRESS_WARNING(_warning_)
#define GO_GCC_END_SUPPRESS_WARNING

#endif  // #if defined (GO_ENABLE_SUPPRESS_WARNINGS)

#define GO_CLANG_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_CLANG_SUPPRESS_WARNING(_warning_)
#define GO_CLANG_END_SUPPRESS_WARNING

#define GO_MSVC_BEGIN_SUPPRESS_WARNING(_warning_)
#define GO_MSVC_SUPPRESS_WARNING(_warning_)
#define GO_MSVC_END_SUPPRESS_WARNING

#endif  // defined(__GNUC__)

#endif  // #ifndef GO_CONFIG_COMPILER_GCC_HPP_INCLUDED
