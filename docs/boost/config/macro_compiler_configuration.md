---
layout: boost_lib_config
---

```c++
namespace go_boost::config
```

# Compiler configuration

```c++
<go_boost/config.hpp>
```

## Compiler information

### clang

Macros that are defined if compiler is **clang**.

Macro | Description
-|-
GO_BOOST_CLANG_VERSION | clang version number on the format **major** * 10000 + **minor** * 100 + **patch level**
GO_BOOST_COMP_CLANG | Compiler is [clang](https://clang.llvm.org/)

### gcc

Macros that are defined if compiler is **gcc**.

Macro | Description
-|-
GO_BOOST_COMP_GCC | Compiler is [gcc](https://gcc.gnu.org/)
GO_BOOST_COMP_GCC_MINGW | Compiler is [gcc](https://gcc.gnu.org/) for [MinGW](http://www.mingw.org/)
GO_BOOST_GCC_VERSION | gcc version number on the format **major** * 10000 + **minor** * 100 + **patch level**

### MSVC

Macros that are defined if compiler is **msvc** (Microsoft Visual C++).

Macro | Description
-|-
GO_BOOST_COMP_MSVC | Compiler is [Microsoft Visual C++](https://docs.microsoft.com/en-us/cpp/)
GO_BOOST_MSVC_VER | Visual Studio version, [_MSC_VER](https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros)
GO_BOOST_MSVC_FULL_VER | Visual Studio version, [_MSC_FULL_VER](https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros) if **_MSC_FULL_VER** > 100000000, otherwise **_MSC_FULL_VER** * 10
GO_BOOST_COMP_MSVC_VC10 | Compiler is Microsoft Visual C++ 1.0
GO_BOOST_COMP_MSVC_VC20 | Compiler is Microsoft Visual C++ 2.0
GO_BOOST_COMP_MSVC_VC40 | Compiler is Microsoft Visual C++ 4.0 / Developer Studio 4.0
GO_BOOST_COMP_MSVC_VC42 | Compiler is Microsoft Visual C++ 4.2 / Developer Studio 4.2
GO_BOOST_COMP_MSVC_VC50 | Compiler is Microsoft Visual C++ 5.0 / Visual Studio 97
GO_BOOST_COMP_MSVC_VC60 | Compiler is Microsoft Visual C++ 6.0 / Visual Studio 6.0
GO_BOOST_COMP_MSVC_VC70 | Compiler is Microsoft Visual C++ 7.0 / Visual Studio .NET 2002
GO_BOOST_COMP_MSVC_VC71 | Compiler is Microsoft Visual C++ 7.1 / Visual Studio .NET 2003
GO_BOOST_COMP_MSVC_VC80 | Compiler is Microsoft Visual C++ 8.0 / Visual Studio 2005
GO_BOOST_COMP_MSVC_VC90 | Compiler is Microsoft Visual C++ 9.0 / Visual Studio 2008
GO_BOOST_COMP_MSVC_VC100 | Compiler is Microsoft Visual C++ 10.0 / Visual Studio 2010
GO_BOOST_COMP_MSVC_VC110 | Compiler is Microsoft Visual C++ 11.0 / Visual Studio 2012
GO_BOOST_COMP_MSVC_VC120 | Compiler is Microsoft Visual C++ 12.0 / Visual Studio 2013
GO_BOOST_COMP_MSVC_VC140 | Compiler is Microsoft Visual C++ 14.0 / Visual Studio 2015
GO_BOOST_COMP_MSVC_VC141 | Compiler is Microsoft Visual C++ 14.1 / Visual Studio 2017
GO_BOOST_COMP_MSVC_VC142 | Compiler is Microsoft Visual C++ 14.2 / Visual Studio 2019
GO_BOOST_COMP_MSVC_VC143 | Compiler is Microsoft Visual C++ 14.3 / Visual Studio 2022
GO_BOOST_IDE_MS_DS40 | Development environment is Developer Studio 4.0
GO_BOOST_IDE_MS_DS42 | Development environment is Developer Studio 4.2
GO_BOOST_IDE_MS_VS97 | Development environment is Visual Studio 97
GO_BOOST_IDE_MS_VS60 | Development environment is Visual Studio 6.0
GO_BOOST_IDE_MS_VS2002 | Development environment is Visual Studio .NET 2002
GO_BOOST_IDE_MS_VS2003 | Development environment is Visual Studio .NET 2003
GO_BOOST_IDE_MS_VS2005 | Development environment is Visual Studio 2005
GO_BOOST_IDE_MS_VS2008 | Development environment is Visual Studio 2008
GO_BOOST_IDE_MS_VS2010 | Development environment is Visual Studio 2010
GO_BOOST_IDE_MS_VS2012 | Development environment is Visual Studio 2012
GO_BOOST_IDE_MS_VS2013 | Development environment is Visual Studio 2013
GO_BOOST_IDE_MS_VS2015 | Development environment is Visual Studio 2015
GO_BOOST_IDE_MS_VS2015_U1 | Visual Studio 2015 update 1
GO_BOOST_IDE_MS_VS2015_U2 | Visual Studio 2015 update 2
GO_BOOST_IDE_MS_VS2015_U3 | Visual Studio 2015 update 3
GO_BOOST_IDE_MS_VS2017 | Development environment is Visual Studio 2017
GO_BOOST_IDE_MS_VS2017_15_0 | Visual Studio 2017 version 15.0
GO_BOOST_IDE_MS_VS2017_15_3 | Visual Studio 2017 version 15.3
GO_BOOST_IDE_MS_VS2017_15_5 | Visual Studio 2017 version 15.5
GO_BOOST_IDE_MS_VS2017_15_6 | Visual Studio 2017 version 15.6
GO_BOOST_IDE_MS_VS2017_15_7 | Visual Studio 2017 version 15.7
GO_BOOST_IDE_MS_VS2017_15_8 | Visual Studio 2017 version 15.8
GO_BOOST_IDE_MS_VS2017_15_9 | Visual Studio 2017 version 15.9
GO_BOOST_IDE_MS_VS2019 | Development environment is Visual Studio 2019
GO_BOOST_IDE_MS_VS2019_16_0 | Visual Studio 2019 version 16.0
GO_BOOST_IDE_MS_VS2019_16_1 | Visual Studio 2019 version 16.1
GO_BOOST_IDE_MS_VS2019_16_2 | Visual Studio 2019 version 16.2
GO_BOOST_IDE_MS_VS2019_16_3 | Visual Studio 2019 version 16.3
GO_BOOST_IDE_MS_VS2019_16_4 | Visual Studio 2019 version 16.4
GO_BOOST_IDE_MS_VS2019_16_5 | Visual Studio 2019 version 16.5
GO_BOOST_IDE_MS_VS2019_16_6 | Visual Studio 2019 version 16.6
GO_BOOST_IDE_MS_VS2019_16_7 | Visual Studio 2019 version 16.7
GO_BOOST_IDE_MS_VS2019_16_8 | Visual Studio 2019 version 16.8
GO_BOOST_IDE_MS_VS2019_16_10 | Visual Studio 2019 version 16.10
GO_BOOST_IDE_MS_VS2022 | Development environment is Visual Studio 2022
GO_BOOST_IDE_MS_VS2022_17_0 | Visual Studio 2022 version 17.0
GO_BOOST_MSVC_ATL | Using ATL
GO_BOOST_MSVC_ATL_VER | ATL version
GO_BOOST_MSVC_MFC | Using MFC
GO_BOOST_MSVC_MFC_VER | MFC version
GO_BOOST_MSVC_UNICODE | Using unicode

## Compiler C99 support

Macro | Description
-|-
GO_BOOST_NO_C99_PREPROCESSOR | The compiler does not support C99 preprocessor

## Compiler C++11 support

Macro | Description
-|-
GO_BOOST_NO_CXX11 | The compiler does not support C++11

### Compiler C++11 language support

Macro | Unsupported language feature | Paper(s)
-|-
GO_BOOST_NO_CXX11_ALIGNAS | alignas | [N2341](https://wg21.link/N2341)
GO_BOOST_NO_CXX11_ALIGNOF | alignof | [N2341](https://wg21.link/N2341)
GO_BOOST_NO_CXX11_ATOMIC_OPERATIONS | Atomic operations | [N2427](https://wg21.link/N2427)
GO_BOOST_NO_CXX11_ATTRIBUTES | Attributes | [N2761](https://wg21.link/N2761)
GO_BOOST_NO_CXX11_AUTO | auto | [N1984](https://wg21.link/N1984)
GO_BOOST_NO_CXX11_C99_PREPROCESSOR | C99 preprocessor | [N1653](https://wg21.link/N1653)
GO_BOOST_NO_CXX11_CHAR16_T_AND_CHAR32_T | char16_t and char32_t | [N2249](https://wg21.link/N2249)
GO_BOOST_NO_CXX11_COMPILER_SUPPORT_FOR_TYPE_TRAITS | Compiler support for type traits | [N1836](https://wg21.link/N1836)
GO_BOOST_NO_CXX11_CONSTEXPR | constexpr | [N2235](https://wg21.link/N2235)
GO_BOOST_NO_CXX11_DECLTYPE | decltype | [N2343](https://wg21.link/N2343), [N3276](https://wg21.link/N3276)
GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS | Defaulted and deleted functions | [N2346](https://wg21.link/N2346)
GO_BOOST_NO_CXX11_DELEGATING_CONSTRUCTORS | Delegating constructors | [N1986](https://wg21.link/N1986)
GO_BOOST_NO_CXX11_DYNAMIC_INITIALIZATION_AND_DESTRUCTION_WITH_CONCURRENCY_MAGIC_STATICS | Dynamic initialization and destruction with concurrency (magic statics) | [N2660](https://wg21.link/N2660)
GO_BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS | Explicit conversion operators | [N2437](https://wg21.link/N2437)
GO_BOOST_NO_CXX11_EXPRESSION_SFINAE | Expression SFINAE | [N2634](https://wg21.link/N2634)
GO_BOOST_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS | Extended friend declarations | [N1791](https://wg21.link/N1791)
GO_BOOST_NO_CXX11_EXTERN_TEMPLATE | extern template | [N1987](https://wg21.link/N1987)
GO_BOOST_NO_CXX11_FORWARD_ENUM_DECLARATIONS | Forward enum declarations | [N2764](https://wg21.link/N2764)
GO_BOOST_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION | Garbage Collection and Reachability-Based Leak Detection | [N2670](https://wg21.link/N2670)
GO_BOOST_NO_CXX11_INHERITING_CONSTRUCTORS | Inheriting constructors | [N2540](https://wg21.link/N2540)
GO_BOOST_NO_CXX11_INITIALIZER_LISTS | Initializer lists | [N2672](https://wg21.link/N2672)
GO_BOOST_NO_CXX11_INLINE_NAMESPACES | Inline namespaces | [N2535](https://wg21.link/N2535)
GO_BOOST_NO_CXX11_LAMBDA_EXPRESSIONS | Lambda expressions | [N2550](https://wg21.link/N2550), [N2658](https://wg21.link/N2658), [N2927](https://wg21.link/N2927)
GO_BOOST_NO_CXX11_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS | Local and unnamed types as template parameters | [N2657](https://wg21.link/N2657)
GO_BOOST_NO_CXX11_LONG_LONG | long long | [N1811](https://wg21.link/N1811)
GO_BOOST_NO_CXX11_NOEXCEPT | noexcept | [N3050](https://wg21.link/N3050)
GO_BOOST_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS | Non-static data member initializers | [N2756](https://wg21.link/N2756)
GO_BOOST_NO_CXX11_NULLPTR | nullptr | [N2431](https://wg21.link/N2431)
GO_BOOST_NO_CXX11_OVERRIDE_AND_FINAL | override and final | [N2928](https://wg21.link/N2928), [N3206](https://wg21.link/N3206), [N3272](https://wg21.link/N3272)
GO_BOOST_NO_CXX11_RANGE_FOR_LOOP | Range-for loop | [N2930](https://wg21.link/N2930)
GO_BOOST_NO_CXX11_RAW_STRING_LITERALS | Raw string literals | [N2442](https://wg21.link/N2442)
GO_BOOST_NO_CXX11_REF_QUALIFIERS | ref-qualifiers | [N2439](https://wg21.link/N2439)
GO_BOOST_NO_CXX11_RIGHT_ANGLE_BRACKETS | Right angle brackets | [N1757](https://wg21.link/N1757)
GO_BOOST_NO_CXX11_RVALUE_REFERENCES | Rvalue references | [N2118](https://wg21.link/N2118), [N2844](https://wg21.link/N2844), [CWG1138](https://wg21.link/CWG1138), [N3053](https://wg21.link/N3053)
GO_BOOST_NO_CXX11_STATIC_ASSERT | static_assert | [N1720](https://wg21.link/N1720)
GO_BOOST_NO_CXX11_STRONGLY_TYPED_ENUM | Strongly-typed enum | [N2347](https://wg21.link/N2347)
GO_BOOST_NO_CXX11_TEMPLATE_ALIASES | Template aliases | [N2258](https://wg21.link/N2258)
GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE | Thread-local storage | [N2659](https://wg21.link/N2659)
GO_BOOST_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES | Trailing function return types | [N2541](https://wg21.link/N2541)
GO_BOOST_NO_CXX11_UNICODE_STRING_LITERALS | Unicode string literals | [N2442](https://wg21.link/N2442)
GO_BOOST_NO_CXX11_UNRESTRICTED_UNIONS | Unrestricted unions | [N2544](https://wg21.link/N2544)
GO_BOOST_NO_CXX11_USER_DEFINED_LITERALS | User-defined literals | [N2765](https://wg21.link/N2765)
GO_BOOST_NO_CXX11_VARIADIC_TEMPLATES | Variadic templates | [N2242](https://wg21.link/N2242), [N2555](https://wg21.link/N2555)

### Compiler C++11 standard library support

Macro | Unsupported library feature | Paper(s)
-|-
GO_BOOST_NO_CXX11_GARBAGE_COLLECTION_AND_REACHABILITY_BASED_LEAK_DETECTION_LIBRARY_SUPPORT_NO_OP | Garbage Collection and Reachability-Based Leak Detection (library support) | [N2670](https://wg21.link/N2670)
GO_BOOST_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS | Money, Time, and hexfloat I/O manipulators | [N2071](https://wg21.link/N2071), [N2072](https://wg21.link/N2072)
GO_BOOST_NO_CXX11_TYPE_TRAITS | Type traits | [N1836](https://wg21.link/N1836)

### Compiler C++11 cross platform support

Macro | Description
-|-
GO_BOOST_NO_CXX11_CHAR16_T | 1
GO_BOOST_NO_CXX11_CHAR32_T | 1
GO_BOOST_NO_CXX11_CODECVT | 1
GO_BOOST_NO_CXX11_CONCURRENCY_SUPPORT | 1
GO_BOOST_NO_CXX11_CONDITION_VARIABLE | 1
GO_BOOST_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR | 1
GO_BOOST_NO_CXX11_DEFAULTED_COPY_CONSTRUCTOR | 1
GO_BOOST_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR | 1
GO_BOOST_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR | 1
GO_BOOST_NO_CXX11_FIXED_WIDTH_INTEGER_TYPES | 1
GO_BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS | 1
GO_BOOST_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST | 1
GO_BOOST_NO_CXX11_LOCALTIME_S | 1
GO_BOOST_NO_CXX11_SNPRINTF | 1
GO_BOOST_NO_CXX11_STATIC_CONST_DATA_MEMBER_INITIALIZER | 1
GO_BOOST_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION | 1
GO_BOOST_NO_CXX11_TYPE_ALIASES | 1

## Compiler C++14 support

Macro | Description
-|-
GO_BOOST_NO_CXX14 | The compiler does not support C++14

### Compiler C++14 language support

Macro | Unsupported language feature | Paper(s)
-|-
GO_BOOST_NO_CXX14_BINARY_LITERALS | Binary literals | [N3472](https://wg21.link/N3472)
GO_BOOST_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION_AVOIDING_FUSING_ALLOCATIONS | Clarifying memory allocation (avoiding/fusing allocations) | [N3664](https://wg21.link/N3664)
GO_BOOST_NO_CXX14_DECLTYPE_AUTO_RETURN_TYPE_DEDUCTION_FOR_NORMAL_FUNCTIONS | decltype(auto), Return type deduction for normal functions | [N3638](https://wg21.link/N3638)
GO_BOOST_NO_CXX14_DEPRECATED_ATTRIBUTE | [[deprecated]] attribute | [N3760](https://wg21.link/N3760)
GO_BOOST_NO_CXX14_EXTENDED_CONSTEXPR | Extended constexpr | [N3652](https://wg21.link/N3652)
GO_BOOST_NO_CXX14_GENERIC_POLYMORPHIC_LAMBDA_EXPRESSIONS | Generic (polymorphic) lambda expressions | [N3649](https://wg21.link/N3649)
GO_BOOST_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES_INIT_CAPTURE | Initialized/Generalized lambda captures (init-capture) | [N3648](https://wg21.link/N3648)
GO_BOOST_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES_NSDMI | Member initializers and aggregates (NSDMI) | [N3653](https://wg21.link/N3653)
GO_BOOST_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR | Single quote as digit separator | [N3781](https://wg21.link/N3781)
GO_BOOST_NO_CXX14_SIZED_DEALLOCATION | Sized deallocation | [N3778](https://wg21.link/N3778)
GO_BOOST_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS | Tweaked wording for contextual conversions | [N3323](https://wg21.link/N3323)
GO_BOOST_NO_CXX14_VARIABLE_TEMPLATES | Variable templates | [N3651](https://wg21.link/N3651)

### Compiler C++14 standard library support

Macro | Unsupported library feature | Paper(s)
-|-
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_ARRAY | constexpr for <array> | [N3470](https://wg21.link/N3470)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_CHRONO | constexpr for <chrono> | [N3469](https://wg21.link/N3469)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_COMPLEX | constexpr for <complex> | [N3302](https://wg21.link/N3302)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE | constexpr for <initializer_list>, <utility> and <tuple> | [N3471](https://wg21.link/N3471)
GO_BOOST_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH | Dual-Range std::equal, std::is_permutation, std::mismatch | [N3671](https://wg21.link/N3671)
GO_BOOST_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST | fixing constexpr member functions without const | [N3669](https://wg21.link/N3669)
GO_BOOST_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP | Heterogeneous associative lookup | [N3657](https://wg21.link/N3657)
GO_BOOST_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT | Improved std::integral_constant | [N3545](https://wg21.link/N3545)
GO_BOOST_NO_CXX14_NULL_FORWARD_ITERATORS | Null forward iterators | [N3644](https://wg21.link/N3644)
GO_BOOST_NO_CXX14_STD_EXCHANGE | std::exchange | [N3668](https://wg21.link/N3668)
GO_BOOST_NO_CXX14_STD_GET_T | std::get<T>() | [N3670](https://wg21.link/N3670)
GO_BOOST_NO_CXX14_STD_INTEGER_SEQUENCE | std::integer_sequence | [N3658](https://wg21.link/N3658)
GO_BOOST_NO_CXX14_STD_QUOTED | std::quoted | [N3654](https://wg21.link/N3654)
GO_BOOST_NO_CXX14_STD_RESULT_OF_AND_SFINAE | std::result_of and SFINAE | [N3462](https://wg21.link/N3462)
GO_BOOST_NO_CXX14_STD_SHARED_TIMED_MUTEX | std::shared_timed_mutex | [N3659](https://wg21.link/N3659)
GO_BOOST_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING | User-defined literals for <chrono> and <string> | [N3642](https://wg21.link/N3642)

### Compiler C++14 cross platform support

Macro | Description
-|-
GO_BOOST_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP | 1
GO_BOOST_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS | 1

## Compiler C++17 support

Macro | Description
-|-
GO_BOOST_NO_CXX17 | The compiler does not support C++17

### Compiler C++17 language support

Macro | Unsupported language feature | Paper(s)
-|-
GO_BOOST_NO_CXX17___HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS | __has_include in preprocessor conditionals | [P0061R1](https://wg21.link/P0061R1)
GO_BOOST_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES | Aggregate initialization of classes with base classes | [P0017R1](https://wg21.link/P0017R1)
GO_BOOST_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NON_TYPE_TEMPLATE_ARGUMENTS | Allow constant evaluation for all non-type template arguments | [N4268](https://wg21.link/N4268)
GO_BOOST_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS | Attributes for namespaces and enumerators | [N4266](https://wg21.link/N4266)
GO_BOOST_NO_CXX17_CLASS_TEMPLATE_ARGUMENT_DEDUCTION | Class template argument deduction | [P0091R3](https://wg21.link/P0091R3)
GO_BOOST_NO_CXX17_CONSTEXPR_IF_STATEMENTS | constexpr if statements | [P0292R2](https://wg21.link/P0292R2)
GO_BOOST_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS | constexpr lambda expressions | [P0170R1](https://wg21.link/P0170R1)
GO_BOOST_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR | Differing begin and end types in range-based for | [P0184R0](https://wg21.link/P0184R0)
GO_BOOST_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS | Direct-list-initialization of enumerations | [P0138R2](https://wg21.link/P0138R2)
GO_BOOST_NO_CXX17_DR_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES | DR: Matching of template template-arguments excludes compatible templates | [P0522R0](https://wg21.link/P0522R0)
GO_BOOST_NO_CXX17_DR_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS_DR1941_ET_AL | DR: New specification for inheriting constructors (DR1941 et al) | [P0136R1](https://wg21.link/P0136R1)
GO_BOOST_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVER_ALIGNED_DATA | Dynamic memory allocation for over-aligned data | [P0035R4](https://wg21.link/P0035R4)
GO_BOOST_NO_CXX17_FALLTHROUGH_ATTRIBUTE | [[fallthrough]] attribute | [P0188R1](https://wg21.link/P0188R1)
GO_BOOST_NO_CXX17_FOLD_EXPRESSIONS | Fold Expressions | [N4295](https://wg21.link/N4295)
GO_BOOST_NO_CXX17_GUARANTEED_COPY_ELISION | Guaranteed copy elision | [P0135R1](https://wg21.link/P0135R1)
GO_BOOST_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS | Hexadecimal floating-point literals | [P0245R1](https://wg21.link/P0245R1)
GO_BOOST_NO_CXX17_IGNORE_UNKNOWN_ATTRIBUTES | Ignore unknown attributes | [P0283R2](https://wg21.link/P0283R2)
GO_BOOST_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH | init-statements for if and switch | [P0305R1](https://wg21.link/P0305R1)
GO_BOOST_NO_CXX17_INLINE_VARIABLES | Inline variables | [P0386R2](https://wg21.link/P0386R2)
GO_BOOST_NO_CXX17_LAMBDA_CAPTURE_OF_THIS_DEREFERENCED_BY_VALUE | Lambda capture of *this | [P0018R3](https://wg21.link/P0018R3)
GO_BOOST_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM | Make exception specifications part of the type system | [P0012R1](https://wg21.link/P0012R1)
GO_BOOST_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE | [[maybe_unused]] attribute | [P0212R1](https://wg21.link/P0212R1)
GO_BOOST_NO_CXX17_NESTED_NAMESPACE_DEFINITION | Nested namespace definition | [N4230](https://wg21.link/N4230)
GO_BOOST_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION | New auto rules for direct-list-initialization | [N3922](https://wg21.link/N3922)
GO_BOOST_NO_CXX17_NODISCARD_ATTRIBUTE | [[nodiscard]] attribute | [P0189R1](https://wg21.link/P0189R1)
GO_BOOST_NO_CXX17_NON_TYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE | Non-type template parameters with auto type | [P0127R2](https://wg21.link/P0127R2)
GO_BOOST_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS | Pack expansions in using-declarations | [P0195R2](https://wg21.link/P0195R2)
GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUS_PLUS_BOOL | Remove Deprecated operator++(bool) | [P0002R1](https://wg21.link/P0002R1)
GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD | Remove Deprecated Use of the register Keyword | [P0001R1](https://wg21.link/P0001R1)
GO_BOOST_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS_FROM_CXX17 | Removing Deprecated Exception Specifications from C++17 | [P0003R5](https://wg21.link/P0003R5)
GO_BOOST_NO_CXX17_REMOVING_TRIGRAPHS | Removing trigraphs | [N4086](https://wg21.link/N4086)
GO_BOOST_NO_CXX17_REPLACEMENT_OF_CLASS_OBJECTS_CONTAINING_REFERENCE_MEMBERS | Replacement of class objects containing reference members | [P0137R1](https://wg21.link/P0137R1)
GO_BOOST_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE | static_assert with no message | [N3928](https://wg21.link/N3928)
GO_BOOST_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER | Stricter expression evaluation order | [P0145R3](https://wg21.link/P0145R3)
GO_BOOST_NO_CXX17_STRUCTURED_BINDINGS | Structured Bindings | [P0217R3](https://wg21.link/P0217R3)
GO_BOOST_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER | typename in a template template parameter | [N4051](https://wg21.link/N4051)
GO_BOOST_NO_CXX17_U8_CHARACTER_LITERALS | u8 character literals | [N4267](https://wg21.link/N4267)
GO_BOOST_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS | Unary fold expressions and empty parameter packs | [P0036R0](https://wg21.link/P0036R0)
GO_BOOST_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION | Using attribute namespaces without repetition | [P0028R4](https://wg21.link/P0028R4)

### Compiler C++17 standard library support

Macro | Unsupported library feature | Paper(s)
-|-
GO_BOOST_NO_CXX17_CXX17_SHOULD_REFER_TO_C11_INSTEAD_OF_C99 | C++17 should refer to C11 instead of C99 | [P0063R3](https://wg21.link/P0063R3)
GO_BOOST_NO_CXX17_ELEMENTARY_STRING_CONVERSIONS | Elementary string conversions | [P0067R5](https://wg21.link/P0067R5)
GO_BOOST_NO_CXX17_FILE_SYSTEM_LIBRARY | File system library | [P0218R1](https://wg21.link/P0218R1)
GO_BOOST_NO_CXX17_HARDWARE_INTERFERENCE_SIZE | Hardware interference size | [P0154R1](https://wg21.link/P0154R1)
GO_BOOST_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE | Improving std::pair and std::tuple | [N4387](https://wg21.link/N4387)
GO_BOOST_NO_CXX17_LOGICAL_OPERATOR_TYPE_TRAITS | Logical operator type traits | [P0013R1](https://wg21.link/P0013R1)
GO_BOOST_NO_CXX17_MATHEMATICAL_SPECIAL_FUNCTIONS | Mathematical special functions | [P0226R1](https://wg21.link/P0226R1)
GO_BOOST_NO_CXX17_NOTHROW_SWAPPABLE_TRAITS | (nothrow-)swappable traits | [P0185R1](https://wg21.link/P0185R1)
GO_BOOST_NO_CXX17_POLYMORPHIC_MEMORY_RESOURCES | Polymorphic memory resources | [P0220R1](https://wg21.link/P0220R1)
GO_BOOST_NO_CXX17_SPLICING_MAPS_AND_SETS | Splicing Maps and Sets | [P0083R3](https://wg21.link/P0083R3)
GO_BOOST_NO_CXX17_STANDARDIZATION_OF_PARALLELISM_TS | Standardization of Parallelism TS | [P0024R2](https://wg21.link/P0024R2)
GO_BOOST_NO_CXX17_STD_ANY | std::any | [P0220R1](https://wg21.link/P0220R1)
GO_BOOST_NO_CXX17_STD_BOOL_CONSTANT | std::bool_constant | [N4389](https://wg21.link/N4389)
GO_BOOST_NO_CXX17_STD_BYTE | std::byte | [P0298R3](https://wg21.link/P0298R3)
GO_BOOST_NO_CXX17_STD_CLAMP | std::clamp() | [P0025R0](https://wg21.link/P0025R0)
GO_BOOST_NO_CXX17_STD_GCD_AND_STD_LCM | std::gcd() and std::lcm() | [P0295R0](https://wg21.link/P0295R0)
GO_BOOST_NO_CXX17_STD_HAS_UNIQUE_OBJECT_REPRESENTATIONS | std::has_unique_object_representations | [P0258R2](https://wg21.link/P0258R2)
GO_BOOST_NO_CXX17_STD_IS_AGGREGATE | std::is_aggregate | [LWG2911](https://wg21.link/LWG2911)
GO_BOOST_NO_CXX17_STD_MAKE_FROM_TUPLE | std::make_from_tuple() | [P0209R2](https://wg21.link/P0209R2)
GO_BOOST_NO_CXX17_STD_NOT_FN | std::not_fn | [P0005R4](https://wg21.link/P0005R4), [P0358R1](https://wg21.link/P0358R1)
GO_BOOST_NO_CXX17_STD_OPTIONAL | std::optional | [P0220R1](https://wg21.link/P0220R1)
GO_BOOST_NO_CXX17_STD_SCOPED_LOCK | std::scoped_lock | [P0156R2](https://wg21.link/P0156R2)
GO_BOOST_NO_CXX17_STD_SHARED_MUTEX_UNTIMED | std::shared_mutex (untimed) | [N4508](https://wg21.link/N4508)
GO_BOOST_NO_CXX17_STD_SHARED_PTR_AND_STD_WEAK_PTR_WITH_ARRAY_SUPPORT | std::shared_ptr and std::weak_ptr with array support | [P0414R2](https://wg21.link/P0414R2)
GO_BOOST_NO_CXX17_STD_SIZE_STD_EMPTY_AND_STD_DATA | std::size(), std::empty() and std::data() | [N4280](https://wg21.link/N4280)
GO_BOOST_NO_CXX17_STD_STRING_VIEW | std::string_view | [N3921](https://wg21.link/N3921), [P0220R1](https://wg21.link/P0220R1)
GO_BOOST_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS | std::uncaught_exceptions() | [N4259](https://wg21.link/N4259)
GO_BOOST_NO_CXX17_STD_VARIANT | std::variant | [P0088R3](https://wg21.link/P0088R3)
GO_BOOST_NO_CXX17_STD_VOID_T | std::void_t | [N3911](https://wg21.link/N3911)
GO_BOOST_NO_CXX17_TYPE_TRAITS_VARIABLE_TEMPLATES | Type traits variable templates | [P0006R0](https://wg21.link/P0006R0)

### Compiler C++17 cross platform support

Macro | Description
-|-

## Compiler C++20 support

Macro | Description
-|-
GO_BOOST_NO_CXX20 | The compiler does not support C++20

### Compiler C++20 language support

Macro | Unsupported language feature | Paper(s)
-|-
GO_BOOST_NO_CXX20___VA_OPT__ | \_\_VA\_OPT\_\_ | [P0306R4](https://wg21.link/P0306R4), [P1042R1](https://wg21.link/P1042R1)
GO_BOOST_NO_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS | Access checking on specializations | [P0692R1](https://wg21.link/P0692R1)
GO_BOOST_NO_CXX20_ADL_AND_FUNCTION_TEMPLATES_THAT_ARE_NOT_VISIBLE | ADL and function templates that are not visible | [P0846R0](https://wg21.link/P0846R0)
GO_BOOST_NO_CXX20_ALLOW_LAMBDA_CAPTURE_ASSIGN_THIS | Allow lambda-capture [=, this] | [P0409R2](https://wg21.link/P0409R2)
GO_BOOST_NO_CXX20_ATTRIBUTE_NO_UNIQUE_ADDRESS | Attribute [[no_unique_address]] | [P0840R2](https://wg21.link/P0840R2)
GO_BOOST_NO_CXX20_ATTRIBUTES_LIKELY_AND_UNLIKELY | Attributes [[likely]] and [[unlikely]] | [P0479R5](https://wg21.link/P0479R5)
GO_BOOST_NO_CXX20_CHANGING_THE_ACTIVE_MEMBER_OF_A_UNION_INSIDE_CONSTEXPR | Changing the active member of a union inside constexpr | [P1330R0](https://wg21.link/P1330R0)
GO_BOOST_NO_CXX20_CHAR8_T | char8_t | [P0482R6](https://wg21.link/P0482R6)
GO_BOOST_NO_CXX20_CLASS_TYPES_IN_NON_TYPE_TEMPLATE_PARAMETERS | Class types in non-type template parameters | [P0732R2](https://wg21.link/P0732R2)
GO_BOOST_NO_CXX20_CONCEPTS | Concepts | [P0734R0](https://wg21.link/P0734R0)
GO_BOOST_NO_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS | Consistency improvements for comparisons | [P1120R0](https://wg21.link/P1120R0)
GO_BOOST_NO_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR | const mismatch with defaulted copy constructor | [P0641R2](https://wg21.link/P0641R2)
GO_BOOST_NO_CXX20_CONST_REF_QUALIFIED_POINTERS_TO_MEMBERS | const&-qualified pointers to members | [P0704R1](https://wg21.link/P0704R1)
GO_BOOST_NO_CXX20_CONSTEXPR_DYNAMIC_CAST_AND_POLYMORPHIC_TYPEID | constexpr dynamic_cast and polymorphic typeid | [P1327R1](https://wg21.link/P1327R1)
GO_BOOST_NO_CXX20_CONSTEXPR_TRY_CATCH_BLOCKS | constexpr try-catch blocks | [P1002R1](https://wg21.link/P1002R1)
GO_BOOST_NO_CXX20_CONSTEXPR_VIRTUAL_FUNCTION | constexpr virtual function | [P1064R0](https://wg21.link/P1064R0)
GO_BOOST_NO_CXX20_CONSTINIT | constinit | [P1143R2](https://wg21.link/P1143R2)
GO_BOOST_NO_CXX20_COROUTINES | Coroutines | [P0912R5](https://wg21.link/P0912R5)
GO_BOOST_NO_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS | Default constructible and assignable stateless lambdas | [P0624R2](https://wg21.link/P0624R2)
GO_BOOST_NO_CXX20_DEFAULT_MEMBER_INITIALIZERS_FOR_BIT_FIELDS | Default member initializers for bit-fields | [P0683R1](https://wg21.link/P0683R1)
GO_BOOST_NO_CXX20_DEPRECATE_COMMA_OPERATOR_IN_SUBSCRIPTS | Deprecate comma operator in subscripts | [P1161R3](https://wg21.link/P1161R3)
GO_BOOST_NO_CXX20_DEPRECATE_IMPLICIT_CAPTURE_OF_THIS_VIA_ASSIGN | Deprecate implicit capture of this via [=] | [P0806R2](https://wg21.link/P0806R2)
GO_BOOST_NO_CXX20_DEPRECATING_SOME_USES_OF_VOLATILE | Deprecating some uses of volatile | [P1152R4](https://wg21.link/P1152R4)
GO_BOOST_NO_CXX20_DESIGNATED_INITIALIZERS | Designated initializers | [P0329R4](https://wg21.link/P0329R4)
GO_BOOST_NO_CXX20_DESTROYING_OPERATOR_DELETE | Destroying operator delete | [P0722R3](https://wg21.link/P0722R3)
GO_BOOST_NO_CXX20_DR_ALLOW_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS | DR: Allow structured bindings to accessible members | [P0969R0](https://wg21.link/P0969R0)
GO_BOOST_NO_CXX20_DR_ARRAY_SIZE_DEDUCTION_IN_NEW_EXPRESSIONS | DR: Array size deduction in new-expressions | [P1009R2](https://wg21.link/P1009R2)
GO_BOOST_NO_CXX20_DR_EXPLICITLY_DEFAULTED_FUNCTIONS_WITH_DIFFERENT_EXCEPTION_SPECIFICATIONS | DR: Explicitly defaulted functions with different exception specifications | [P1286R2](https://wg21.link/P1286R2)
GO_BOOST_NO_CXX20_DR_IMPLICIT_MOVE_FOR_MORE_LOCAL_OBJECTS_AND_RVALUE_REFERENCES | DR: Implicit move for more local objects and rvalue references | [P1825R0](https://wg21.link/P1825R0)
GO_BOOST_NO_CXX20_DR_NODISCARD_FOR_CONSTRUCTORS | DR: [[nodiscard]] for constructors | [P1771R1](https://wg21.link/P1771R1)
GO_BOOST_NO_CXX20_DR_RELAXING_THE_RANGE_FOR_LOOP_CUSTOMIZATION_POINT_FINDING_RULES | DR: Relaxing the range-for loop customization point finding rules | [P0962R1](https://wg21.link/P0962R1)
GO_BOOST_NO_CXX20_DR_RELAXING_THE_STRUCTURED_BINDINGS_CUSTOMIZATION_POINT_FINDING_RULES | DR: Relaxing the structured bindings customization point finding rules | [P0961R1](https://wg21.link/P0961R1)
GO_BOOST_NO_CXX20_EXPLICIT_BOOL | explicit(bool) | [P0892R2](https://wg21.link/P0892R2)
GO_BOOST_NO_CXX20_IMMEDIATE_FUNCTIONS | Immediate functions | [P1073R3](https://wg21.link/P1073R3)
GO_BOOST_NO_CXX20_INIT_STATEMENTS_FOR_RANGE_BASED_FOR | init-statements for range-based for | [P0614R1](https://wg21.link/P0614R1)
GO_BOOST_NO_CXX20_INITIALIZER_LIST_CONSTRUCTORS_IN_CLASS_TEMPLATE_ARGUMENT_DEDUCTION | Initializer list constructors in class template argument deduction | [P0702R1](https://wg21.link/P0702R1)
GO_BOOST_NO_CXX20_INTEGRATING_FEATURE_TEST_MACROS | Integrating feature-test macros | [P0941R2](https://wg21.link/P0941R2)
GO_BOOST_NO_CXX20_LAMBDA_CAPTURE_AND_STORAGE_CLASS_SPECIFIERS_OF_STRUCTURED_BINDINGS | Lambda capture and storage class specifiers of structured bindings | [P1091R3](https://wg21.link/P1091R3), [P1381R1](https://wg21.link/P1381R1)
GO_BOOST_NO_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS | Lambdas in unevaluated contexts | [P0315R4](https://wg21.link/P0315R4)
GO_BOOST_NO_CXX20_LESS_EAGER_INSTANTIATION_OF_CONSTEXPR_FUNCTIONS | Less eager instantiation of constexpr functions | [P0859R0](https://wg21.link/P0859R0)
GO_BOOST_NO_CXX20_MAKE_TYPENAME_MORE_OPTIONAL | Make typename more optional | [P0634R3](https://wg21.link/P0634R3)
GO_BOOST_NO_CXX20_MODULES | Modules | [P1103R3](https://wg21.link/P1103R3)
GO_BOOST_NO_CXX20_MORE_CONSTEXPR_CONTAINERS | More constexpr containers | [P0784R7](https://wg21.link/P0784R7)
GO_BOOST_NO_CXX20_NESTED_INLINE_NAMESPACES | Nested inline namespaces | [P1094R2](https://wg21.link/P1094R2)
GO_BOOST_NO_CXX20_NODISCARD_WITH_MESSAGE | [[nodiscard]] with message | [P1301R4](https://wg21.link/P1301R4)
GO_BOOST_NO_CXX20_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE | Pack expansion in lambda init-capture | [P0780R2](https://wg21.link/P0780R2)
GO_BOOST_NO_CXX20_PARENTHESIZED_INITIALIZATION_OF_AGGREGATES | Parenthesized initialization of aggregates | [P0960R3](https://wg21.link/P0960R3)
GO_BOOST_NO_CXX20_PERMIT_CONVERSIONS_TO_ARRAYS_OF_UNKNOWN_BOUND | Permit conversions to arrays of unknown bound | [P0388R4](https://wg21.link/P0388R4)
GO_BOOST_NO_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS | Prohibit aggregates with user-declared constructors | [P1008R1](https://wg21.link/P1008R1)
GO_BOOST_NO_CXX20_SIGNED_INTEGERS_ARE_TWOS_COMPLEMENT | Signed integers are two's complement | [P1236R1](https://wg21.link/P1236R1)
GO_BOOST_NO_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE | Simplifying implicit lambda capture | [P0588R1](https://wg21.link/P0588R1)
GO_BOOST_NO_CXX20_STD_IS_CONSTANT_EVALUATED | std::is_constant_evaluated() | [P0595R2](https://wg21.link/P0595R2)
GO_BOOST_NO_CXX20_STRONGER_UNICODE_REQUIREMENTS | Stronger Unicode requirements | [P1041R4](https://wg21.link/P1041R4), [P1139R2](https://wg21.link/P1139R2)
GO_BOOST_NO_CXX20_TEMPLATE_PARAMETER_LIST_FOR_GENERIC_LAMBDAS | template-parameter-list for generic lambdas | [P0428R2](https://wg21.link/P0428R2)
GO_BOOST_NO_CXX20_THREE_WAY_COMPARE_NOT_EQUAL_AND_EQUAL | <=> != == | [P1185R2](https://wg21.link/P1185R2)
GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR | Three-way comparison operator | [P0515R3](https://wg21.link/P0515R3)
GO_BOOST_NO_CXX20_TRIVIAL_DEFAULT_INITIALIZATION_IN_CONSTEXPR_FUNCTIONS | Trivial default initialization in constexpr functions | [P1331R2](https://wg21.link/P1331R2)
GO_BOOST_NO_CXX20_UNEVALUATED_ASM_DECLARATION_IN_CONSTEXPR_FUNCTIONS | Unevaluated asm-declaration in constexpr functions | [P1668R1](https://wg21.link/P1668R1)
GO_BOOST_NO_CXX20_YET_ANOTHER_APPROACH_FOR_CONSTRAINED_DECLARATIONS | Yet another approach for constrained declarations | [P1141R2](https://wg21.link/P1141R2)

### Compiler C++20 standard library support

Macro | Unsupported library feature | Paper(s)
-|-
GO_BOOST_NO_CXX20_A_SANE_STD_VARIANT_CONVERTING_CONSTRUCTOR | A sane std::variant converting constructor | [P0608R3](https://wg21.link/P0608R3)
GO_BOOST_NO_CXX20_ADD_SHIFT_TO_ALGORITHM | Add shift to <algorithm> | [P0769R2](https://wg21.link/P0769R2)
GO_BOOST_NO_CXX20_ATOMIC_STD_SHARED_PTR_AND_STD_WEAK_PTR | Atomic std::shared_ptr and std::weak_ptr | [P0718R2](https://wg21.link/P0718R2)
GO_BOOST_NO_CXX20_BIT_OPERATIONS | Bit operations | [P0553R4](https://wg21.link/P0553R4)
GO_BOOST_NO_CXX20_CALENDAR_AND_TIMEZONE | Calendar and timezone | [P0355R7](https://wg21.link/P0355R7)
GO_BOOST_NO_CXX20_CHRONO_ZERO_MIN_AND_MAX_SHOULD_BE_NOEXCEPT | <chrono> zero(), min(), and max() should be noexcept | [P0972R0](https://wg21.link/P0972R0)
GO_BOOST_NO_CXX20_COMPARING_UNORDERED_CONTAINERS | Comparing unordered containers | [P0809R0](https://wg21.link/P0809R0)
GO_BOOST_NO_CXX20_CONCEPTS_LIBRARY | Concepts library | [P0898R3](https://wg21.link/P0898R3)
GO_BOOST_NO_CXX20_CONSISTENT_CONTAINER_ERASURE | Consistent container erasure | [P1209R0](https://wg21.link/P1209R0)
GO_BOOST_NO_CXX20_CONSTEXPR_COMPARISON_OPERATORS_FOR_STD_ARRAY | constexpr comparison operators for std::array | [P1023R0](https://wg21.link/P1023R0)
GO_BOOST_NO_CXX20_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY | constexpr for <algorithm> and <utility> | [P0202R3](https://wg21.link/P0202R3)
GO_BOOST_NO_CXX20_CONSTEXPR_FOR_STD_SWAP_AND_SWAP_RELATED_FUNCTIONS | Constexpr for std::swap() and swap related functions | [P0879R0](https://wg21.link/P0879R0)
GO_BOOST_NO_CXX20_CONSTEXPR_IN_STD_POINTER_TRAITS | constexpr in std::pointer_traits | [P1006R1](https://wg21.link/P1006R1)
GO_BOOST_NO_CXX20_CONSTEXPRITERATOR_REQUIREMENTS | ConstexprIterator requirements | [P0858R0](https://wg21.link/P0858R0)
GO_BOOST_NO_CXX20_CONTAINS_MEMBER_FUNCTION_OF_ASSOCIATIVE_CONTAINERS | contains() member function of associative containers | [P0458R2](https://wg21.link/P0458R2)
GO_BOOST_NO_CXX20_DR_GUARANTEED_COPY_ELISION_FOR_PIECEWISE_CONSTRUCTION | DR: Guaranteed copy elision for piecewise construction | [P0475R1](https://wg21.link/P0475R1)
GO_BOOST_NO_CXX20_DR_MAKE_CREATE_DIRECTORY_INTUITIVE | DR: Make create_directory() Intuitive | [P1164R1](https://wg21.link/P1164R1)
GO_BOOST_NO_CXX20_DR_STD_VARIANT_AND_STD_OPTIONAL_SHOULD_PROPAGATE_COPY_MOVE_TRIVIALITY | DR: std::variant and std::optional should propagate copy/move triviality | [P0602R4](https://wg21.link/P0602R4)
GO_BOOST_NO_CXX20_EXTENDING_STD_MAKE_SHARED_TO_SUPPORT_ARRAYS | Extending std::make_shared() to support arrays | [P0674R1](https://wg21.link/P0674R1)
GO_BOOST_NO_CXX20_FIXING_INPUT_STREAM_OPERATOR_BASIC_ISTREAM_REF_CHART_POINTER | Fixing operator>>(basic_istream&, CharT*) | [P0487R1](https://wg21.link/P0487R1)
GO_BOOST_NO_CXX20_FLOATING_POINT_ATOMIC | Floating point atomic | [P0020R6](https://wg21.link/P0020R6)
GO_BOOST_NO_CXX20_HETEROGENEOUS_LOOKUP_FOR_UNORDERED_CONTAINERS | Heterogeneous lookup for unordered containers | [P0919R3](https://wg21.link/P0919R3)
GO_BOOST_NO_CXX20_IMPROVING_THE_RETURN_VALUE_OF_ERASE_LIKE_ALGORITHMS | Improving the return value of erase-like algorithms | [P0646R1](https://wg21.link/P0646R1)
GO_BOOST_NO_CXX20_INTEGRAL_POWER_OF_2_OPERATIONS | Integral power-of-2 operations | [P0556R3](https://wg21.link/P0556R3)
GO_BOOST_NO_CXX20_LIBRARY_SUPPORT_FOR_CHAR8_T | Library support for char8_t | [P0482R6](https://wg21.link/P0482R6)
GO_BOOST_NO_CXX20_LIBRARY_SUPPORT_FOR_OPERATOR_THREE_WAY_COMPARE | Library support for operator<=> <compare> | [P0515R3](https://wg21.link/P0515R3)
GO_BOOST_NO_CXX20_MAKE_STATEFUL_ALLOCATOR_PROPAGATION_MORE_CONSISTENT_FOR_OPERATOR_PLUS_BASIC_STRING | Make stateful allocator propagation more consistent for operator+(basic_string) | [P1165R1](https://wg21.link/P1165R1)
GO_BOOST_NO_CXX20_MAKE_STD_MEMORY_ORDER_A_SCOPED_ENUMERATION | Make std::memory_order a scoped enumeration | [P0439R0](https://wg21.link/P0439R0)
GO_BOOST_NO_CXX20_MORE_CONSTEXPR_FOR_COMPLEX | More constexpr for <complex> | [P0415R1](https://wg21.link/P0415R1)
GO_BOOST_NO_CXX20_NODISCARD_IN_THE_STANDARD_LIBRARY | [[nodiscard]] in the standard library | [P0600R1](https://wg21.link/P0600R1)
GO_BOOST_NO_CXX20_REMOVE_COMPARISON_OPERATORS_OF_STD_SPAN | Remove comparison operators of std::span | [P1085R2](https://wg21.link/P1085R2)
GO_BOOST_NO_CXX20_STD_ASSUME_ALIGNED | std::assume_aligned() | [P1007R3](https://wg21.link/P1007R3)
GO_BOOST_NO_CXX20_STD_ATOMIC_REF | std::atomic_ref | [P0019R8](https://wg21.link/P0019R8)
GO_BOOST_NO_CXX20_STD_BASIC_STRING_RESERVE_SHOULD_NOT_SHRINK | std::basic_string::reserve() should not shrink | [P0966R1](https://wg21.link/P0966R1)
GO_BOOST_NO_CXX20_STD_BIND_FRONT | std::bind_front() | [P0356R5](https://wg21.link/P0356R5)
GO_BOOST_NO_CXX20_STD_BIT_CAST | std::bit_cast() | [P0476R2](https://wg21.link/P0476R2)
GO_BOOST_NO_CXX20_STD_DESTROYING_DELETE | std::destroying_delete | [P0722R3](https://wg21.link/P0722R3)
GO_BOOST_NO_CXX20_STD_ENDIAN | std::endian | [P0463R1](https://wg21.link/P0463R1)
GO_BOOST_NO_CXX20_STD_FUNCTIONS_MOVE_CONSTRUCTOR_SHOULD_BE_NOEXCEPT | std::function's move constructor should be noexcept | [P0771R1](https://wg21.link/P0771R1)
GO_BOOST_NO_CXX20_STD_IS_NOTHROW_CONVERTIBLE | std::is_nothrow_convertible | [P0758R1](https://wg21.link/P0758R1)
GO_BOOST_NO_CXX20_STD_LERP_AND_STD_MIDPOINT | std::lerp() and std::midpoint() | [P0811R3](https://wg21.link/P0811R3)
GO_BOOST_NO_CXX20_STD_REFERENCE_WRAPPER_FOR_INCOMPLETE_TYPES | std::reference_wrapper for incomplete types | [P0357R3](https://wg21.link/P0357R3)
GO_BOOST_NO_CXX20_STD_REMOVE_CVREF | std::remove_cvref | [P0550R2](https://wg21.link/P0550R2)
GO_BOOST_NO_CXX20_STD_SOURCE_LOCATION | std::source_location | [P1208R5](https://wg21.link/P1208R5)
GO_BOOST_NO_CXX20_STD_SPAN | std::span | [P0122R7](https://wg21.link/P0122R7)
GO_BOOST_NO_CXX20_STD_SSIZE_AND_UNSIGNED_EXTENT_FOR_STD_SPAN | std::ssize() and unsigned extent for std::span | [P1227R2](https://wg21.link/P1227R2)
GO_BOOST_NO_CXX20_STD_TYPE_IDENTITY | std::type_identity | [P0887R1](https://wg21.link/P0887R1)
GO_BOOST_NO_CXX20_STD_UNWRAP_REF_DECAY_AND_STD_UNWRAP_REFERENCE | std::unwrap_ref_decay and std::unwrap_reference | [P0318R1](https://wg21.link/P0318R1)
GO_BOOST_NO_CXX20_STRING_PREFIX_AND_SUFFIX_CHECKING | String prefix and suffix checking | [P0457R2](https://wg21.link/P0457R2)
GO_BOOST_NO_CXX20_SYNCHRONIZED_BUFFERED_OSTREAM | Synchronized buffered ostream | [P0053R7](https://wg21.link/P0053R7)
GO_BOOST_NO_CXX20_THE_ONE_RANGES_PROPOSAL | The One Ranges Proposal | [P0896R4](https://wg21.link/P0896R4)
GO_BOOST_NO_CXX20_TRAITS_FOR_BOUNDED_AND_UNBOUNDED_ARRAYS | Traits for (un)bounded arrays | [P1357R0](https://wg21.link/P1357R0)
GO_BOOST_NO_CXX20_USABILITY_ENHANCEMENTS_FOR_STD_SPAN | Usability enhancements for std::span | [P1024R3](https://wg21.link/P1024R3)
GO_BOOST_NO_CXX20_USING_STD_MOVE_IN_NUMERIC_ALGORITHMS | Using std::move in numeric algorithms | [P616R0](https://wg21.link/P616R0)
GO_BOOST_NO_CXX20_UTILITY_FUNCTIONS_TO_IMPLEMENT_USES_ALLOCATOR_CONSTRUCTION | Utility functions to implement uses-allocator construction | [P0591R4](https://wg21.link/P0591R4)
GO_BOOST_NO_CXX20_UTILITY_TO_CONVERT_A_POINTER_TO_A_RAW_POINTER | Utility to convert a pointer to a raw pointer | [P0653R2](https://wg21.link/P0653R2)
GO_BOOST_NO_CXX20_VERSION | <version> | [P0754R2](https://wg21.link/P0754R2)

### Compiler C++20 cross platform support

Macro | Description
-|-

## C++ cross platform support

Macro | Description
-|-
GO_BOOST_CONSTEXPR | constexpr
GO_BOOST_DEFAULT_CONSTRUCTOR | = default;
GO_BOOST_DEFAULT_DESTRUCTOR | = default;
GO_BOOST_EXTENDED_CONSTEXPR | constexpr
GO_BOOST_FINAL | final
GO_BOOST_NOEXCEPT | noexcept
GO_BOOST_NOEXCEPT_EXPR(\_expression\_) | noexcept((\_expression\_))
GO_BOOST_NOEXCEPT_IF(\_predicate\_) | noexcept((\_predicate\_))
GO_BOOST_NOEXCEPT_OR_NOTHROW | noexcept
GO_BOOST_NULLPTR | nullptr
GO_BOOST_OVERRIDE | override
GO_BOOST_TYPENAME | typename
GO_BOOST_USING(\_alias\_, \_type\_) | using \_alias\_ = \_type\_

## Utility macros

Macro | Description
-|-
GO_BOOST_MESSAGE(\_message\_) | Compiler message

## Issue workarounds

Macro | Description
-|-
GO_BOOST_CANNOT_CREATE_U2STRING_ISSUE | template<class to_string, typename from_char_t> go_boost\::utility\::string\::to_string create(const from_char_t* sz) does not work with to_string = go_boost\::utility\::u2string
GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
