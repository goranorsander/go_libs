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
GO_BOOST_MSVC_ATL | Using ATL
GO_BOOST_MSVC_ATL_VER | ATL version
GO_BOOST_MSVC_MFC | Using MFC
GO_BOOST_MSVC_MFC_VER | MFC version
GO_BOOST_MSVC_UNICODE | Using unicode

## Compiler C99 support

Macro | Description
-|-
GO_BOOST_NO_C99_PREPROCESSOR | The compiler does not support C99 preprocessor

## Compiler C++ support

Macro | Description
-|-
GO_BOOST_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7 | 1
GO_BOOST_CPP_TYPENAME_REQUIRED | 1

## Compiler C++11 support

Macro | The compiler does not support
-|-
GO_BOOST_NO_CXX11 | [C++11](https://en.wikipedia.org/wiki/C%2B%2B11)
GO_BOOST_NO_CXX11_ALIGNAS | [alignas](https://en.cppreference.com/w/cpp/language/alignas)
GO_BOOST_NO_CXX11_ALIGNOF | [alignof](https://en.cppreference.com/w/cpp/language/alignof)
GO_BOOST_NO_CXX11_ATOMIC_OPERATIONS | [Atomic operations](https://en.cppreference.com/w/cpp/atomic)
GO_BOOST_NO_CXX11_ATTRIBUTES | Attributes
GO_BOOST_NO_CXX11_AUTO | [auto](https://en.cppreference.com/w/cpp/language/auto)
GO_BOOST_NO_CXX11_CHAR16_T | char16_t
GO_BOOST_NO_CXX11_CHAR32_T | char32_t
GO_BOOST_NO_CXX11_CODECVT | Header \<codecvt\>
GO_BOOST_NO_CXX11_CONCURRENCY_SUPPORT | Concurrency support
GO_BOOST_NO_CXX11_CONDITION_VARIABLE | [constexpr](https://en.cppreference.com/w/cpp/header/condition_variable)
GO_BOOST_NO_CXX11_CONSTEXPR | [constexpr](https://en.cppreference.com/w/cpp/language/constexpr)
GO_BOOST_NO_CXX11_DECLTYPE | [decltype](https://en.cppreference.com/w/cpp/language/decltype)
GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS | Defaulted and deleted functions
GO_BOOST_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR | Defaulted copy assign operator
GO_BOOST_NO_CXX11_DEFAULTED_COPY_CONSTRUCTOR | Defaulted copy assign constructor
GO_BOOST_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR | Defaulted move assign operator
GO_BOOST_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR | Defaulted move assign constructor
GO_BOOST_NO_CXX11_DELEGATING_CONSTRUCTORS | [Delegating constructors](https://en.cppreference.com/w/cpp/language/initializer_list#Delegating_constructor)
GO_BOOST_NO_CXX11_DYNAMIC_POINTER_SAFETY | [dynamic pointer safety (GC interface)](https://en.cppreference.com/w/cpp/memory#Garbage_collector_support)
GO_BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS | Explicit conversion operators
GO_BOOST_NO_CXX11_EXTENDED_FRIEND_DECLARATIONS | Extended friend declarations
GO_BOOST_NO_CXX11_EXTERN_TEMPLATE | extern template
GO_BOOST_NO_CXX11_FIXED_WIDTH_INTEGER_TYPES | Fixed width integer types
GO_BOOST_NO_CXX11_FORWARD_ENUM_DECLARATIONS | Forward enum declarations
GO_BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS | Function template default arguments
GO_BOOST_NO_CXX11_INHERITING_CONSTRUCTORS | Inheriting constructors
GO_BOOST_NO_CXX11_INITIALIZER_LISTS | Initializer lists
GO_BOOST_NO_CXX11_INLINE_NAMESPACES | Inline namespaces
GO_BOOST_NO_CXX11_LAMBDA_EXPRESSIONS | [Lambda expressions](https://en.cppreference.com/w/cpp/language/lambda)
GO_BOOST_NO_CXX11_LOCAL_AND_UNNAMED_TYPES_AS_TEMPLATE_PARAMETERS | Local and unnamed types as template parameters
GO_BOOST_NO_CXX11_LONG_LONG | long long
GO_BOOST_NO_CXX11_MAGIC_STATICS | [Dynamic initialization and destruction with concurrency (magic statics)](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables)
GO_BOOST_NO_CXX11_MONEY_TIME_AND_HEXFLOAT_IO_MANIPULATORS | [Money, Time, and hexfloat I/O manipulators](https://en.cppreference.com/w/cpp/io/manip)
GO_BOOST_NO_CXX11_MUTEX | Header \<mutex\>
GO_BOOST_NO_CXX11_NEW_CHARACTER_TYPES | New character types
GO_BOOST_NO_CXX11_NOEXCEPT | [noexcept](https://en.cppreference.com/w/cpp/language/noexcept_spec)
GO_BOOST_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS | Non-static data member initializers
GO_BOOST_NO_CXX11_NULLPTR | [nullptr](https://en.cppreference.com/w/cpp/language/nullptr)
GO_BOOST_NO_CXX11_OVERRIDE_AND_FINAL | [override](https://en.cppreference.com/w/cpp/language/override) and [final](https://en.cppreference.com/w/cpp/language/final)
GO_BOOST_NO_CXX11_R_VALUE_REFERENCES | Rvalue references
GO_BOOST_NO_CXX11_RANGE_FOR_LOOP | Range-for loop
GO_BOOST_NO_CXX11_RAW_STRING_LITERALS | Raw string literals
GO_BOOST_NO_CXX11_REF_QUALIFIERS | ref-qualifiers
GO_BOOST_NO_CXX11_RIGHT_ANGLE_BRACKETS | Right angle brackets
GO_BOOST_NO_CXX11_SNPRINTF | snprintf
GO_BOOST_NO_CXX11_STATIC_ASSERT | [static_assert](https://en.cppreference.com/w/cpp/language/static_assert)
GO_BOOST_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION | A static const data member of integral or enumeration type can be initialized right inside the class definition
GO_BOOST_NO_CXX11_STRONGLY_TYPED_ENUM | [Strongly-typed enum](https://en.cppreference.com/w/cpp/language/enum#Scoped_enumerations)
GO_BOOST_NO_CXX11_TEMPLATE_ALIASES | [Template aliases](https://en.cppreference.com/w/cpp/language/type_alias)
GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE | Thread-local storage
GO_BOOST_NO_CXX11_TRAILING_FUNCTION_RETURN_TYPES | Trailing function return types
GO_BOOST_NO_CXX11_TYPE_ALIASES | [Type aliases](https://en.cppreference.com/w/cpp/language/type_alias)
GO_BOOST_NO_CXX11_TYPE_TRAITS | Type traits
GO_BOOST_NO_CXX11_UNICODE_STRING_LITERALS | Unicode string literals
GO_BOOST_NO_CXX11_UNRESTRICTED_UNIONS | Unrestricted unions
GO_BOOST_NO_CXX11_USER_DEFINED_LITERALS | User-defined literals
GO_BOOST_NO_CXX11_VARIADIC_TEMPLATES | Variadic templates

## Compiler C++14 support

Macro | The compiler does not support
-|-
GO_BOOST_NO_CXX14 | [C++14](https://en.wikipedia.org/wiki/C%2B%2B14)
GO_BOOST_NO_CXX14_BINARY_LITERALS | Binary literals
GO_BOOST_NO_CXX14_CLARIFYING_MEMORY_ALLOCATION | Clarifying memory allocation (avoiding/fusing allocations)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_ARRAY | constexpr for [<array>](https://en.cppreference.com/w/cpp/header/array)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_CHRONO | constexpr for [<chrono>](https://en.cppreference.com/w/cpp/header/chrono)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_COMPLEX | constexpr for [<complex>](https://en.cppreference.com/w/cpp/header/complex)
GO_BOOST_NO_CXX14_CONSTEXPR_FOR_INITIALIZER_LIST_UTILITY_AND_TUPLE | constexpr for [<initializer_list>](https://en.cppreference.com/w/cpp/header/initializer_list), [<utility>](https://en.cppreference.com/w/cpp/header/utility) and [<tuple>](https://en.cppreference.com/w/cpp/header/tuple)
GO_BOOST_NO_CXX14_DECLTYPE_AUTO | decltype(auto), return type deduction for normal functions
GO_BOOST_NO_CXX14_DEPRECATED_ATTRIBUTE | [[[deprecated]] attribute](https://en.cppreference.com/w/cpp/language/attributes/deprecated)
GO_BOOST_NO_CXX14_DUAL_RANGE_STD_EQUAL_STD_IS_PERMUTATION_STD_MISMATCH | Dual-Range [std::equal](https://en.cppreference.com/w/cpp/algorithm/equal), [std::is_permutation](https://en.cppreference.com/w/cpp/algorithm/is_permutation), [std::mismatch](https://en.cppreference.com/w/cpp/algorithm/mismatch)
GO_BOOST_NO_CXX14_EXTENDED_CONSTEXPR | Extended constexpr
GO_BOOST_NO_CXX14_FIXING_CONSTEXPR_MEMBER_FUNCTIONS_WITHOUT_CONST | fixing constexpr member functions without const
GO_BOOST_NO_CXX14_GENERIC_POLYMORPHIC_LAMBDA_EXPRESSIONS | Generic (polymorphic) lambda expressions
GO_BOOST_NO_CXX14_HETEROGENEOUS_ASSOCIATIVE_LOOKUP | Heterogeneous associative lookup
GO_BOOST_NO_CXX14_IMPROVED_STD_INTEGRAL_CONSTANT | [Improved std::integral_constant](https://en.cppreference.com/w/cpp/types/integral_constant)
GO_BOOST_NO_CXX14_INITIALIZED_GENERALIZED_LAMBDA_CAPTURES | Initialized/Generalized lambda captures (init-capture)
GO_BOOST_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS | Default arguments are allowed in the parameter lists of lambda-expressions
GO_BOOST_NO_CXX14_MEMBER_INITIALIZERS_AND_AGGREGATES | Member initializers and aggregates (NSDMI)
GO_BOOST_NO_CXX14_NULL_FORWARD_ITERATORS | [Null forward iterators](https://en.cppreference.com/w/cpp/named_req/ForwardIterator#Singular_iterators)
GO_BOOST_NO_CXX14_SINGLE_QUOTE_AS_DIGIT_SEPARATOR | Single quote as digit separator
GO_BOOST_NO_CXX14_SIZED_DEALLOCATION | Sized deallocation
GO_BOOST_NO_CXX14_STD_EXCHANGE | [std::exchange](https://en.cppreference.com/w/cpp/utility/exchange)
GO_BOOST_NO_CXX14_STD_GET_T | [std::get<T>()](https://en.cppreference.com/w/cpp/utility/pair/get)
GO_BOOST_NO_CXX14_STD_INTEGER_SEQUENCE | [std::integer_sequence](https://en.cppreference.com/w/cpp/utility/integer_sequence)
GO_BOOST_NO_CXX14_STD_QUOTED | [std::quoted](https://en.cppreference.com/w/cpp/io/manip/quoted)
GO_BOOST_NO_CXX14_STD_RESULT_OF_AND_SFINAE | [std::result_of](https://en.cppreference.com/w/cpp/types/result_of) and SFINAE
GO_BOOST_NO_CXX14_STD_SHARED_TIMED_MUTEX | [std::shared_timed_mutex](https://en.cppreference.com/w/cpp/thread/shared_timed_mutex)
GO_BOOST_NO_CXX14_TWEAKED_WORDING_FOR_CONTEXTUAL_CONVERSIONS | Tweaked wording for contextual conversions
GO_BOOST_NO_CXX14_USER_DEFINED_LITERALS_FOR_CHRONO_AND_STRING | User-defined literals for [<chrono>](https://en.cppreference.com/w/cpp/header/chrono) and  [<string>](https://en.cppreference.com/w/cpp/header/string)
GO_BOOST_NO_CXX14_VARIABLE_TEMPLATES | Variable templates

## Compiler C++17 support

Macro | The compiler does not support
-|-
GO_BOOST_NO_CXX17 | [C++17](https://en.wikipedia.org/wiki/C%2B%2B17)
GO_BOOST_NO_CXX17_AGGREGATE_INITIALIZATION_OF_CLASSES_WITH_BASE_CLASSES | Aggregate initialization of classes with base classes
GO_BOOST_NO_CXX17_ALLOW_CONSTANT_EVALUATION_FOR_ALL_NONTYPE_TEMPLATE_ARGUMENTS | Allow constant evaluation for all non-type template arguments
GO_BOOST_NO_CXX17_ATTRIBUTES_FOR_NAMESPACES_AND_ENUMERATORS | Attributes for namespaces and enumerators
GO_BOOST_NO_CXX17_CONSTEXPR_IF_STATEMENTS | [constexpr if statements](https://en.cppreference.com/w/cpp/language/if)
GO_BOOST_NO_CXX17_CONSTEXPR_LAMBDA_EXPRESSIONS | constexpr lambda expressions
GO_BOOST_NO_CXX17_DIFFERING_BEGIN_AND_END_TYPES_IN_RANGE_BASED_FOR | Differing begin and end types in range-based for
GO_BOOST_NO_CXX17_DIRECT_LIST_INITIALIZATION_OF_ENUMERATIONS | Direct-list-initialization of enumerations
GO_BOOST_NO_CXX17_DYNAMIC_MEMORY_ALLOCATION_FOR_OVERALIGNED_DATA | Dynamic memory allocation for over-aligned data
GO_BOOST_NO_CXX17_ELEMENTARY_STRING_CONVERSIONS | Elementary string conversions
GO_BOOST_NO_CXX17_FALLTHROUGH_ATTRIBUTE | [[[fallthrough]] attribute](https://en.cppreference.com/w/cpp/language/attributes/fallthrough)
GO_BOOST_NO_CXX17_FOLD_EXPRESSIONS | [Fold Expressions](https://en.cppreference.com/w/cpp/language/fold)
GO_BOOST_NO_CXX17_GUARANTEED_COPY_ELISION | Guaranteed copy elision
GO_BOOST_NO_CXX17_HARDWARE_INTERFERENCE_SIZE | [Hardware interference size](https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size)
GO_BOOST_NO_CXX17_HAS_INCLUDE_IN_PREPROCESSOR_CONDITIONALS | [__has_include](https://en.cppreference.com/w/cpp/preprocessor/include) in preprocessor conditionals
GO_BOOST_NO_CXX17_HEXADECIMAL_FLOATING_POINT_LITERALS | Hexadecimal floating-point literals
GO_BOOST_NO_CXX17_IGNORE_UNKNOWN_ATTRIBUTES | Ignore unknown attributes
GO_BOOST_NO_CXX17_IMPROVING_STD_PAIR_AND_STD_TUPLE | Improving [std::pair](https://en.cppreference.com/w/cpp/utility/pair) and [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple)
GO_BOOST_NO_CXX17_INIT_STATEMENTS_FOR_IF_AND_SWITCH | init-statements for if and switch
GO_BOOST_NO_CXX17_INLINE_VARIABLES | Inline variables
GO_BOOST_NO_CXX17_LAMBDA_CAPTURE_OF_INDIRECTED_THIS | Lambda capture of *this
GO_BOOST_NO_CXX17_MAKE_EXCEPTION_SPECIFICATIONS_PART_OF_THE_TYPE_SYSTEM | Make exception specifications part of the type system
GO_BOOST_NO_CXX17_MATCHING_OF_TEMPLATE_TEMPLATE_ARGUMENTS_EXCLUDES_COMPATIBLE_TEMPLATES | DR: Matching of template template-arguments excludes compatible templates
GO_BOOST_NO_CXX17_MATHEMATICAL_SPECIAL_FUNCTIONS | Mathematical special functions
GO_BOOST_NO_CXX17_MAYBE_UNUSED_ATTRIBUTE | [[[maybe_unused]] attribute](https://en.cppreference.com/w/cpp/language/attributes/maybe_unused)
GO_BOOST_NO_CXX17_NESTED_NAMESPACE_DEFINITION | Nested namespace definition
GO_BOOST_NO_CXX17_NEW_AUTO_RULES_FOR_DIRECT_LIST_INITIALIZATION | New auto rules for direct-list-initialization
GO_BOOST_NO_CXX17_NEW_SPECIFICATION_FOR_INHERITING_CONSTRUCTORS | New specification for inheriting constructors (DR1941 et al)
GO_BOOST_NO_CXX17_NODISCARD_ATTRIBUTE | [[[nodiscard]] attribute](https://en.cppreference.com/w/cpp/language/attributes/nodiscard)
GO_BOOST_NO_CXX17_NONTYPE_TEMPLATE_PARAMETERS_WITH_AUTO_TYPE | Non-type template parameters with auto type
GO_BOOST_NO_CXX17_PACK_EXPANSIONS_IN_USING_DECLARATIONS | Pack expansions in using-declarations
GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_OPERATOR_PLUSPLUS_BOOL | Remove deprecated operator++(bool)
GO_BOOST_NO_CXX17_REMOVE_DEPRECATED_USE_OF_THE_REGISTER_KEYWORD | Remove deprecated use of the register keyword
GO_BOOST_NO_CXX17_REMOVING_DEPRECATED_EXCEPTION_SPECIFICATIONS | Removing deprecated exception specifications from C++17
GO_BOOST_NO_CXX17_REMOVING_TRIGRAPHS | Removing trigraphs
GO_BOOST_NO_CXX17_REPLACEMENT_OF_CLASS_OBJECTS_CONTAINING_REFERENCE_MEMBERS | Replacement of class objects containing reference members
GO_BOOST_NO_CXX17_SPLICING_MAPS_AND_SETS | Splicing maps and sets
GO_BOOST_NO_CXX17_STANDARDIZATION_OF_PARALLELISM_TS | Standardization of Parallelism TS
GO_BOOST_NO_CXX17_STATIC_ASSERT_WITH_NO_MESSAGE | static_assert with no message
GO_BOOST_NO_CXX17_STD_ANY | [std::any](https://en.cppreference.com/w/cpp/utility/any)
GO_BOOST_NO_CXX17_STD_BYTE | [std::byte](https://en.cppreference.com/w/cpp/types/byte)
GO_BOOST_NO_CXX17_STD_FILESYSTEM | [std::filesystem](https://en.cppreference.com/w/cpp/filesystem)
GO_BOOST_NO_CXX17_STD_OPTIONAL | [std::optional](https://en.cppreference.com/w/cpp/utility/optional)
GO_BOOST_NO_CXX17_STD_SHARED_MUTEX_UNTIMED | [std::shared_mutex (untimed)](https://en.cppreference.com/w/cpp/thread/shared_mutex)
GO_BOOST_NO_CXX17_STD_STRING_VIEW | [std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view)
GO_BOOST_NO_CXX17_STD_UNCAUGHT_EXCEPTIONS | [std::uncaught_exceptions()](https://en.cppreference.com/w/cpp/error/uncaught_exception)
GO_BOOST_NO_CXX17_STD_VARIANT | [std::variant](https://en.cppreference.com/w/cpp/utility/variant)
GO_BOOST_NO_CXX17_STRICTER_EXPRESSION_EVALUATION_ORDER | Stricter expression evaluation order
GO_BOOST_NO_CXX17_STRUCTURED_BINDINGS | Structured bindings
GO_BOOST_NO_CXX17_TEMPLATE_ARGUMENT_DEDUCTION_FOR_CLASS_TEMPLATES | Template argument deduction for class templates
GO_BOOST_NO_CXX17_TYPENAME_IN_A_TEMPLATE_TEMPLATE_PARAMETER | typename in a template template parameter
GO_BOOST_NO_CXX17_U8_CHARACTER_LITERALS | u8 character literals
GO_BOOST_NO_CXX17_UNARY_FOLD_EXPRESSIONS_AND_EMPTY_PARAMETER_PACKS | Unary fold expressions and empty parameter packs
GO_BOOST_NO_CXX17_USING_ATTRIBUTE_NAMESPACES_WITHOUT_REPETITION | Using attribute namespaces without repetition

## Compiler C++2a support

Macro | The compiler does not support
-|-
GO_BOOST_NO_CXX2A | [C++2a](https://en.wikipedia.org/wiki/C%2B%2B20)
GO_BOOST_NO_CXX2A_ACCESS_CHECKING_ON_SPECIALIZATIONS | Access checking on specializations
GO_BOOST_NO_CXX2A_ADL_AND_FUNCTION_TEMPLATES_THAT_ARE_NOT_VISIBLE | ADL and function templates that are not visible
GO_BOOST_NO_CXX2A_ALLOW_LAMBDA_CAPTURE_ASSIGN_THIS | Allow lambda-capture [=, this]
GO_BOOST_NO_CXX2A_ATTRIBUTE_NO_UNIQUE_ADDRESS | [attribute [[no_unique_address]]](https://en.cppreference.com/w/cpp/language/attributes/no_unique_address)
GO_BOOST_NO_CXX2A_ATTRIBUTES_LIKELY_AND_UNLIKELY | attributes [[[likely]]](https://en.cppreference.com/w/cpp/language/attributes/likely) and [[[unlikely]]](https://en.cppreference.com/w/cpp/language/attributes/likely)
GO_BOOST_NO_CXX2A_CALENDAR_AND_TIMEZONE | [Calendar](https://en.cppreference.com/w/cpp/chrono#Calendar) and [timezone](https://en.cppreference.com/w/cpp/chrono#Time_zone)
GO_BOOST_NO_CXX2A_CLASS_TYPES_IN_NON_TYPE_TEMPLATE_PARAMETERS | Class types in non-type template parameters
GO_BOOST_NO_CXX2A_CONCEPTS | [Concepts](https://en.cppreference.com/w/cpp/language/constraints)
GO_BOOST_NO_CXX2A_CONCEPTS_LIBRARY | [Concepts library](https://en.cppreference.com/w/cpp/concepts)
GO_BOOST_NO_CXX2A_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR | const mismatch with defaulted copy constructor
GO_BOOST_NO_CXX2A_CONST_REF_QUALIFIED_POINTERS_TO_MEMBERS | const&-qualified pointers to members
GO_BOOST_NO_CXX2A_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY | constexpr for [<algorithm>](https://en.cppreference.com/w/cpp/header/algorithm) and [<utility>](https://en.cppreference.com/w/cpp/header/utility)
GO_BOOST_NO_CXX2A_CONSTEXPR_VIRTUAL_FUNCTION | constexpr virtual function
GO_BOOST_NO_CXX2A_CONTRACTS | [Contracts](https://en.cppreference.com/w/cpp/language/attributes/contract)
GO_BOOST_NO_CXX2A_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS | Default constructible and assignable stateless lambdas
GO_BOOST_NO_CXX2A_DEFAULT_MEMBER_INITIALIZERS_FOR_BIT_FIELDS | Default member initializers for bit-fields
GO_BOOST_NO_CXX2A_DESIGNATED_INITIALIZERS | [Designated initializers](https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers)
GO_BOOST_NO_CXX2A_EFFICIENT_SIZED_DELETE_FOR_VARIABLE_SIZED_CLASSES | Efficient sized delete for variable sized classes
GO_BOOST_NO_CXX2A_EXPLICIT_BOOL | explicit(bool)
GO_BOOST_NO_CXX2A_EXTENDING_STD_MAKE_SHARED_TO_SUPPORT_ARRAYS | Extending [std::make_shared](https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared) to support arrays
GO_BOOST_NO_CXX2A_FLOATING_POINT_ATOMIC | Floating point atomic
GO_BOOST_NO_CXX2A_INIT_STATEMENTS_FOR_RANGE_BASED_FOR | init-statements for range-based for
GO_BOOST_NO_CXX2A_INITIALIZER_LIST_CONSTRUCTORS_IN_CLASS_TEMPLATE_ARGUMENT_DEDUCTION | Initializer list constructors in class template argument deduction
GO_BOOST_NO_CXX2A_INTEGRATING_OUR_FEATURE_TEST_MACROS | Integrating our feature-test macros
GO_BOOST_NO_CXX2A_LAMBDAS_IN_UNEVALUATED_CONTEXTS | Lambdas in unevaluated contexts
GO_BOOST_NO_CXX2A_LESS_EAGER_INSTANTIATION_OF_CONSTEXPR_FUNCTIONS | Less eager instantiation of constexpr functions
GO_BOOST_NO_CXX2A_MORE_CONSTEXPR_FOR_COMPLEX | More constexpr for [<complex>](https://en.cppreference.com/w/cpp/header/complex)
GO_BOOST_NO_CXX2A_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE | Pack expansion in lambda init-capture
GO_BOOST_NO_CXX2A_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS | Prohibit aggregates with user-declared constructors
GO_BOOST_NO_CXX2A_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE | Simplifying implicit lambda capture
GO_BOOST_NO_CXX2A_STD_ATOMIC_REF | [std::atomic_ref](https://en.cppreference.com/w/cpp/atomic/atomic_ref)
GO_BOOST_NO_CXX2A_STD_BIT_CAST | [std::bit_cast](https://en.cppreference.com/w/cpp/numeric/bit_cast)
GO_BOOST_NO_CXX2A_STD_ENDIAN | [std::endian](https://en.cppreference.com/w/cpp/types/endian)
GO_BOOST_NO_CXX2A_STD_REMOVE_CVREF | [std::remove_cvref](https://en.cppreference.com/w/cpp/types/remove_cvref)
GO_BOOST_NO_CXX2A_STD_SPAN | [std::span](https://en.cppreference.com/w/cpp/container/span)
GO_BOOST_NO_CXX2A_STRING_PREFIX_AND_SUFFIX_CHECKING | String prefix and suffix checking
GO_BOOST_NO_CXX2A_SYNCHRONIZED_BUFFERED_OSTREAM | [Synchronized buffered ostream](https://en.cppreference.com/w/cpp/io/basic_syncbuf)
GO_BOOST_NO_CXX2A_TEMPLATE_PARAMETER_LIST_FOR_GENERIC_LAMBDAS | template-parameter-list for generic lambdas
GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR | [Three-way comparison operator](https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison)
GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR_SUPPORT_COMPARE | Three-way comparison operator support [<compare>](https://en.cppreference.com/w/cpp/header/compare)
GO_BOOST_NO_CXX2A_TYPENAME_OPTIONAL | typename optional
GO_BOOST_NO_CXX2A_UTILITY_TO_CONVERT_A_POINTER_TO_A_RAW_POINTER | Utility to convert a pointer to a raw pointer
GO_BOOST_NO_CXX2A_VA_OPT | \_\_VA_OPT\_\_
GO_BOOST_NO_CXX2A_VERSION | [<version>](https://en.cppreference.com/w/cpp/header/version)

## C++ cross platform support

Macro | Description
-|-
GO_BOOST_CONSTEXPR | constexpr
GO_BOOST_DEFAULT_CONSTRUCTOR | = default;
GO_BOOST_DEFAULT_DESTRUCTOR | = default;
GO_BOOST_FINAL | final
GO_BOOST_NOEXCEPT | noexcept
GO_BOOST_NOEXCEPT_EXPR(_expression_) | noexcept((_expression_))
GO_BOOST_NOEXCEPT_IF(_predicate_) | noexcept((_predicate_))
GO_BOOST_NOEXCEPT_OR_NOTHROW | noexcept
GO_BOOST_NULLPTR | nullptr
GO_BOOST_OVERRIDE | override
GO_BOOST_TYPENAME | typename

## Compiler Boost support

Macro | Description
-|-
GO_BOOST_NO_BOOST_PHOENIX | The compiler does not support [Boost.Phoenix](https://www.boost.org/doc/libs/1_71_0/libs/phoenix/doc/html/index.html)

## Utility macros

Macro | Description
-|-
GO_BOOST_MESSAGE(_message_) | Compiler message

## Issue workarounds

Macro | Description
-|-
GO_BOOST_CANNOT_CREATE_U2STRING_ISSUE | template<class to_string, typename from_char_t> go_boost\::utility\::string\::to_string create(const from_char_t* sz) does not work with to_string = go_boost\::utility\::u2string
GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE | Compiler only accept ASCII characters in quoted strings
