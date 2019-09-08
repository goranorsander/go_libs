---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class template primitive_type_implicit_specializer

```c++
<go/utility/primitive_type_implicit_specializer.hpp>
```

Class for implicit specializations of primitive types.

The reason for implementing this class is mainly experience of large code bases with
long life. It is vital to express ideas directly in code and if possible also build in
sanity checks in the code. Primitive types and implicit casting is an error prone
combination. This class have implicit casting to the wrapped primitive type.

There are two implementations of this class. The first version do not require any C\++11
features and that is the only reason to keep it. The second version require C\++11 and
is used by compilers supporting the required C\++11 features. If the first version is
used then **GO_NO_CXX11_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER** is defined.

# class template primitive_type_implicit_specializer (C++11)

The **primitive_type_implicit_specializer** is declared as:

```c++
namespace detail
{

class primitive_type_implicit_specializer_base
{
protected:
    ~primitive_type_implicit_specializer_base() = default;
    primitive_type_implicit_specializer_base() = default;
    primitive_type_implicit_specializer_base(const primitive_type_implicit_specializer_base&) = default;
    primitive_type_implicit_specializer_base(primitive_type_implicit_specializer_base&&) = default;
    primitive_type_implicit_specializer_base& operator=(const primitive_type_implicit_specializer_base&) = default;
    primitive_type_implicit_specializer_base& operator=(primitive_type_implicit_specializer_base&&) = default;
};

}

template<typename PrimitiveType, class Tag> class primitive_type_implicit_specializer
    : detail::primitive_type_implicit_specializer_base
{
public:
    ~primitive_type_implicit_specializer() = default;
    primitive_type_implicit_specializer();
    primitive_type_implicit_specializer(this_const_reference t);
    primitive_type_implicit_specializer(this_rvalue_reference t);
    explicit primitive_type_implicit_specializer(const primitive_type& t);
    explicit primitive_type_implicit_specializer(rvalue_reference t);

public:
    // Cast operator
    constexpr operator const primitive_type&() const;
    operator primitive_type&();

    // Assignment operators
    this_reference operator=(this_const_reference t);
    this_reference operator=(this_rvalue_reference t);
    this_reference operator+=(this_const_reference t);
    this_reference operator-=(this_const_reference t);
    this_reference operator*=(this_const_reference t);
    this_reference operator/=(this_const_reference t);

    template<typename P> this_reference operator=(const P& p);
    template<typename P> this_reference operator=(P&& p);
    template<typename P> this_reference operator+=(const P& p);
    template<typename P> this_reference operator-=(const P& p);
    template<typename P> this_reference operator*=(const P& p);
    template<typename P> this_reference operator/=(const P& p);

    // Integer type assignment operators
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t);
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t);
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t);
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t);
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t);
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t);

    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator%=(const P& p);
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator&=(const P& p);
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator|=(const P& p);
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator^=(const P& p);
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator<<=(const P& p);
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_reference>::type operator>>=(const P& p);

    // Floating point type assignment operators
    template <typename F = PrimitiveType>
    typename std::enable_if<std::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t);

    template <typename P>
    typename std::enable_if<std::is_floating_point<primitive_type>::value && std::is_arithmetic<P>::value, this_reference>::type operator%=(const P& p);

    // Arithmetic operators
    this_type operator+() const;
    this_type operator+(this_const_reference t) const;
    this_type operator-(this_const_reference t) const;
    this_type operator*(this_const_reference t) const;
    this_type operator/(this_const_reference t) const;

    template <typename P>
    typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator+(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator-(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator*(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator/(const P& p) const;

    // Signed integer and floating point type arithmetic operators
    template <typename S = PrimitiveType>
    typename std::enable_if<std::is_signed<S>::value, this_type>::type operator-() const;

    // Integer type arithmetic operators
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator~() const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const;

    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator%(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator&(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator|(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator^(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator<<(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, this_type>::type operator>>(const P& p) const;

    // Floating point type arithmetic operators
    template <typename F = PrimitiveType>
    typename std::enable_if<std::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const;

    template <typename P>
    typename std::enable_if<std::is_floating_point<primitive_type>::value && std::is_arithmetic<P>::value, this_type>::type operator%(const P& p) const;

    // Comparison operators
    constexpr bool operator==(this_const_reference t) const;
    constexpr bool operator!=(this_const_reference t) const;
    constexpr bool operator<(this_const_reference t) const;
    constexpr bool operator<=(this_const_reference t) const;
    constexpr bool operator>(this_const_reference t) const;
    constexpr bool operator>=(this_const_reference t) const;

    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator==(const P& p) const;
    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator!=(const P& p) const;
    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator<(const P& p) const;
    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator<=(const P& p) const;
    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator>(const P& p) const;
    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator>=(const P& p) const;

    // Integer type logical operators
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator!() const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const;
    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator||(this_const_reference t) const;

    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, bool>::type operator&&(const P& p) const;
    template <typename P>
    typename std::enable_if<std::is_integral<primitive_type>::value && std::is_integral<P>::value, bool>::type operator||(const P& p) const;

    // Increment/decrement operators
    this_type operator++();
    this_type operator--();
    this_type operator++(int);
    this_type operator--(int);

public:
    constexpr const primitive_type& get() const;
    primitive_type& get();
    void set(const primitive_type& t);
    void set(this_const_reference t);
    void set(rvalue_reference t);
    void set(this_rvalue_reference t);
};

// Outside arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator+(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator-(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator*(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator/(const P& lhs, const PrimitiveTypeSpecializer& rhs);

// Outside integer arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator%(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator&(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator|(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator^(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator<<(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator>>(const P& lhs, const PrimitiveTypeSpecializer& rhs);

// Outside floating point arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_floating_point<P>::value, PrimitiveTypeSpecializer>::type operator%(const P& lhs, const PrimitiveTypeSpecializer& rhs);

// Outside comparison operators

template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator==(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator!=(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator<(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator<=(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator>(const P& lhs, const PrimitiveTypeSpecializer& rhs);
template<class PrimitiveTypeSpecializer, typename P>
inline typename std::enable_if<std::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator>=(const P& lhs, const PrimitiveTypeSpecializer& rhs);
```

## Template parameters

Parameter | Description
-|-
PrimitiveType | The primitive value type
Tag | A **struct** used as a dispatching tag to uniquely identify the specialized primitive type

## Member types

Member type | Definition
-|-
this_type | primitive_type_implicit_specializer<PrimitiveType, Tag>
primitive_type | PrimitiveType
tag_type | Tag
this_reference | this_type&
this_const_reference | const this_type&
rvalue_reference | primitive_type&&
this_rvalue_reference | this_type&&

## Member functions

### Destructor

Specifiers |
-|
public |

Destroys the **primitive_type_implicit_specializer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public | **primitive_type_implicit_specializer**()
*copy constructor (2)* | public explicit | **primitive_type_implicit_specializer**(**this_const_reference** t)
*move constructor (3)* | public explicit | **primitive_type_implicit_specializer**(**this_rvalue_reference** t)
*assign value, copy (4)* | public | **primitive_type_implicit_specializer**(const **value_type**& t)
*assign value, move (5)* | public | **primitive_type_implicit_specializer**(**value_type**&& t)

1. Constructor. Constructs a **primitive_type_implicit_specializer**.
2. Copy constructor. Constructs a **primitive_type_implicit_specializer** with the copy of the contents of t.
3. Move constructor. Constructs a **primitive_type_implicit_specializer** with the contents of t using move semantics. t is left in valid, but unspecified state.
4. Assign value constructor. Constructs a **primitive_type_implicit_specializer** and assign it the contents of t.
5. Assign value constructor. Constructs a **primitive_type_implicit_specializer** and assign it the contents of t using move semantics. t is left in valid, but unspecified state.

### Cast operators

Operator | Specifiers | Signature
-|-|-
*cast to primitive type (1)* | public | constexpr operator const **primitive_type**&() const;
*cast to primitive type (2)* | public | operator **primitive_type**&();

### Assignment operators

Operator | Specifiers | Signature
-|-|-
*simple copy assignment (1)* | public | **this_reference** operator=(**this_const_reference** t)
*simple copy assignment (1)* | public | template<typename P> **this_reference** operator=(const P& p)
*simple move assignment (2)* | public | **this_reference** operator=(**this_rvalue_reference** t)
*simple move assignment (2)* | public | template<typename P> **this_reference** operator=(P&& p)
*addition assignment (3)* | public | **this_reference** operator+=(**this_const_reference** t)
*addition assignment (3)* | public | template<typename P> **this_reference** operator+=(const P& p)
*subtraction assignment (4)* | public | **this_reference** operator-=(**this_const_reference** t)
*subtraction assignment (4)* | public | template<typename P> **this_reference** operator-=(const P& p)
*multiplication assignment (5)* | public | **this_reference** operator*=(**this_const_reference** t)
*multiplication assignment (5)* | public | template<typename P> **this_reference** operator*=(const P& p)
*division assignment (6)* | public | **this_reference** operator/=(**this_const_reference** t)
*division assignment (6)* | public | template<typename P> **this_reference** operator/=(const P& p)
*modulo assignment (7)* | public | **this_reference** operator%=(**this_const_reference** t)
*modulo assignment (7)* | public | template<typename P> **this_reference** operator%=(const P& p)
*bitwise AND assignment (8)* | public | **this_reference** operator&=(**this_const_reference** t)
*bitwise AND assignment (8)* | public | template<typename P> **this_reference** operator&=(const P& p)
*bitwise OR assignment (9)* | public | **this_reference** operator|=(**this_const_reference** t)
*bitwise OR assignment (9)* | public | template<typename P> **this_reference** operator|=(const P& p)
*bitwise XOR assignment (10)* | public | **this_reference** operator^=(**this_const_reference** t)
*bitwise XOR assignment (10)* | public | template<typename P> **this_reference** operator^=(const P& p)
*bitwise left shift assignment (11)* | public | **this_reference** operator<<=(**this_const_reference** t)
*bitwise left shift assignment (11)* | public | template<typename P> **this_reference** operator<<=(const P& p)
*bitwise right shift assignment (12)* | public | **this_reference** operator>>=(**this_const_reference** t)
*bitwise right shift assignment (12)* | public | template<typename P> **this_reference** operator>>=(const P& p)

Assignment operators 1 to 6 apply to all primitive types.

Assignment operator 7 apply to integer and floating point types.

Assignment operators 8 to 12 apply to all integer types.

### Arithmetic operators

Operator | Specifiers | Signature
-|-|-
*unary plus (1)* | public | **this_type** operator+() const
*addition (2)* | public | **this_type** operator+(**this_const_reference** t) const
*addition (2)* | public | template<typename P> **this_type** operator+(const P& p) const
*subtraction (3)* | public | **this_type** operator-(**this_const_reference** t) const
*subtraction (3)* | public | template<typename P> **this_type** operator-(const P& p) const
*multiplication (4)* | public | **this_type** operator*(**this_const_reference** t) const
*multiplication (4)* | public | template<typename P> **this_type** operator*(const P& p) const
*division (5)* | public | **this_type** operator/(**this_const_reference** t) const
*division (5)* | public | template<typename P> **this_type** operator/(const P& p) const
*modulo (6)* | public | **this_type** operator%(**this_const_reference** t) const
*modulo (6)* | public | template<typename P> **this_type** operator%(const P& p) const
*unary minus (7)* | public | **this_type** operator-() const
*bitwise NOT (8)* | public | **this_type** operator~() const
*bitwise NOT (8)* | public | template<typename P> **this_type** operator~() const
*bitwise AND (9)* | public | **this_type** operator&(**this_const_reference** t) const
*bitwise AND (9)* | public | template<typename P> **this_type** operator&(const P& p) const
*bitwise OR (10)* | public | **this_type** operator|(**this_const_reference** t) const
*bitwise OR (10)* | public | template<typename P> **this_type** operator|(const P& p) const
*bitwise XOR (11)* | public | **this_type** operator^(**this_const_reference** t) const
*bitwise XOR (11)* | public | template<typename P> **this_type** operator^(const P& p) const
*bitwise left shift (12)* | public | **this_type** operator<<(**this_const_reference** t) const
*bitwise left shift (12)* | public | template<typename P> **this_type** operator<<(const P& p) const
*bitwise right shift (13)* | public | **this_type** operator>>(**this_const_reference** t) const
*bitwise right shift (13)* | public | template<typename P> **this_type** operator>>(const P& p) const

Arithmetic operators 1 to 6 apply to all arithmetic types.

Arithmetic operator 7 apply to signed integer and floating point types.

Arithmetic operators 8 to 13 apply to all integer types.

### Comparison operators

Operator | Specifiers | Signature
-|-
*equal to (1)* | public | constexpr bool operator==(**this_const_reference** t) const
*equal to (1)* | public | template <typename P> constexpr bool operator==(const P& p) const
*not equal to (2)* | public | constexpr bool operator!=(**this_const_reference** t) const
*not equal to (2)* | public | template <typename P> constexpr bool operator!=(const P& p) const
*less than (3)* | public | constexpr bool operator<(**this_const_reference** t) const
*less than (3)* | public | template <typename P> constexpr bool operator<(const P& p) const
*less than or equal to (4)* | public | constexpr bool operator<=(**this_const_reference** t) const
*less than or equal to (4)* | public | template <typename P> constexpr bool operator<=(const P& p) const
*greater than (5)* | public | constexpr bool operator>(**this_const_reference** t) const
*greater than (5)* | public | template <typename P> constexpr bool operator>(const P& p) const
*greater than or equal to (6)* | public | constexpr bool operator>=(**this_const_reference** t) const
*greater than or equal to (6)* | public | template <typename P> constexpr bool operator>=(const P& p) const

Comparison operators 1 to 6 apply to all primitive types.

### Logical operators

Operator | Specifiers | Signature
-|-|-
*negation (1)* | public | bool operator!() const
*AND (2)* | public | bool operator&&(this_const_reference t) const
*AND (2)* | public | template <typename P> bool operator&&(const P& p) const
*inclusive OR (3)* | public | bool operator||(this_const_reference t) const
*inclusive OR (3)* | public | template <typename P> bool operator||(const P& p) const

Logical operators 1 to 3 apply to all integer types.

### Increment/decrement operators

Operator | Specifiers | Signature
-|-|-
*pre-increment (1)* | public | **this_type** operator++()
*pre-decrement (2)* | public | **this_type** operator--()
*post-increment (3)* | public | **this_type** operator++(int)
*post-decrement (4)* | public | **this_type** operator--(int)

Increment/decrement operators 1 to 3 apply to all arithmetic types.

### get

Specifiers | Signature
-|-
public | **constexpr const primitive_type**& **get**() const
public | **primitive_type**& **get**()

Return the specialized primitive type value.

### set

Specifiers | Signature
-|-
public | **void set**(const primitive_type& t)
public | **void set**(this_const_reference t)
public | **void set**(primitive_type&& t)
public | **void set**(this_rvalue_reference t)

Set the specialized primitive type value.

## Outside functions

### Outside arithmetic operators

Operator | Signature
-|-
*addition (1)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator+(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*subtraction (2)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator-(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*multiplication (3)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator*(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*division (4)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator/(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*modulo (5)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator%(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*bitwise AND (6)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator&(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*bitwise OR (7)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator|(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*bitwise XOR (8)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator^(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*bitwise left shift (9)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator<<(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*bitwise right shift (10)* | template<class PrimitiveTypeSpecializer, typename P> PrimitiveTypeSpecializer operator>>(const P& lhs, const PrimitiveTypeSpecializer& rhs)

Arithmetic operators 1 to 4 apply to all arithmetic types.

Arithmetic operator 5 apply to signed integer and floating point types.

Arithmetic operators 6 to 10 apply to all integer types.

### Outside comparison operators

Operator | Signature
-|-
*equal to (1)* | template<class PrimitiveTypeSpecializer, typename P> bool operator==(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*not equal to (2)* | template<class PrimitiveTypeSpecializer, typename P> bool operator!=(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*less than (3)* | template<class PrimitiveTypeSpecializer, typename P> bool operator<(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*less than or equal to (4)* | template<class PrimitiveTypeSpecializer, typename P> bool operator<=(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*greater than (5)* | template<class PrimitiveTypeSpecializer, typename P> bool operator>(const P& lhs, const PrimitiveTypeSpecializer& rhs)
*greater than or equal to (6)* | template<class PrimitiveTypeSpecializer, typename P> bool operator>=(const P& lhs, const PrimitiveTypeSpecializer& rhs)

Comparison operators 1 to 6 apply to all primitive types.

## Macro

For convenience a macro is available to implement specialized primitive type
classes. The macros will implement a dispatching tag **struct** and declare
the specialized primitive type with a **using** statement.

### GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(class_name, primitive_type)

The **GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER** macro implements a specialized
primitive type class, e.g:

```c++
GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(my_integer_type, long)
```

Will implement a class declared as:

```c++
struct my_integer_type_tag {};
using my_integer_type = go::utility::primitive_type_implicit_specializer<long, my_integer_type_tag>;
```

## Example

This example is intended to show how specialized primitive types can be used to
avoid errors by using explicit types that provide vital information about what
is expected.

```c++
#include <iostream>
#include <go/utility/primitive_type_implicit_specializer.hpp>

namespace u = go::utility;

GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(radian_type, double)
GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(degree_type, double)
GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(meter_type, double)
GO_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(square_meter_type, double)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace better
{

square_meter_type circular_sector_area(const radian_type& central_angle, const meter_type& radius)
{
    return square_meter_type(((radius*radius)*central_angle.get())/2.0);
}

square_meter_type circular_sector_area(const degree_type& central_angle, const meter_type& radius)
{
    static const double pi = std::acos(-1.0);
    return square_meter_type(((radius*radius)*central_angle.get())*pi/360.0);
}

}

int main()
{
    {
        // Bad, but right
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Better, and right
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_4 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 4 = " << area_4 << " square meter" << std::endl;
        // Also better and right
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_5 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 5 = " << area_5 << " square meter" << std::endl;
    }
    return 0;
}
```

Output

```
Area 1 = 0.523599
Area 2 = 0.548311 (wrong)
Area 3 = 30 (wrong)
Area 4 = 0.523599 square meter
Area 5 = 0.523599 square meter
```

The function **bad::circular_sector_area(const double& central_angle, const double& radius)**
rely on anonymous quantities. The parameter **central_angle** is most error prone. There is
no information about what unit of measurement the function expects. The fact that it
expect radians can only be determined by inspecting the implementation and requires
knowledge of geometry to recognise the formula. The relationship between the parameter
**radius** and the returned result is probably less error prone but it still lack
clarity.

The functions in namespace **better** provide information about expected units of
measurement by use of specialized types. The information is there for anyone who care
to read the function signature. The specialized types are explicit, e.g. you cannot pass
an anonymous **double** or **degree_type** value to the function that expect a
**radian_type** parameter (or worse, get the parameter order mixed up).

# class template primitive_type_implicit_specializer (C++03)

The **primitive_type_implicit_specializer** is declared as:

```c++
template<typename T> class primitive_type_implicit_specializer
    : public primitive_type_specializer<T>
{
public:
    virtual ~primitive_type_implicit_specializer() = 0;

protected:
    primitive_type_implicit_specializer(const primitive_type_implicit_specializer& t);
    primitive_type_implicit_specializer(primitive_type_implicit_specializer&& t);
    explicit primitive_type_implicit_specializer(const value_type& t);
    explicit primitive_type_implicit_specializer(value_type&& t);
    primitive_type_implicit_specializer& operator=(const primitive_type_implicit_specializer& t);

public:
    constexpr operator const value_type&() const;
    operator value_type&();
    constexpr const value_type& get() const;
    value_type& get();
    void set(const value_type& t);
    void set(const this_type& t);
};
```

## Template parameters

Parameter | Description
-|-
T | The primitive value type

## Member types

Member type | Definition
-|-
value_type | T
this_type | primitive_type_implicit_specializer<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **primitive_type_implicit_specializer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*copy constructor (1)* | protected explicit | **primitive_type_implicit_specializer**(const **primitive_type_implicit_specializer**& t)
*move constructor (2)* | protected explicit | **primitive_type_implicit_specializer**(**primitive_type_implicit_specializer**&& t)
*assign value, copy (3)* | protected | **primitive_type_implicit_specializer**(const **value_type**& t)
*assign value, move (4)* | protected | **primitive_type_implicit_specializer**(**value_type**&& t)

1. Copy constructor. Constructs the **primitive_type_implicit_specializer** with the copy of the contents of t.
2. Move constructor. Constructs the **primitive_type_implicit_specializer** with the contents of t using move semantics. t is left in valid, but unspecified state.
3. Assign value constructor. Constructs the **primitive_type_implicit_specializer** and assign it the contents of t.
4. Assign value constructor. Constructs the **primitive_type_implicit_specializer** and assign it the contents of t using move semantics. t is left in valid, but unspecified state.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | protected | **primitive_type_implicit_specializer**& operator=(const **primitive_type_implicit_specializer**& t)

1. Copies an **primitive_type_implicit_specializer** object.

### Cast operator

Specifiers | Signature
-|-
public constexpr | operator const value_type&() const
public | operator value_type&()

Return the specialized primitive type value.

## Inherited functions

### get

Specifiers | Signature
-|-
public | **constexpr const value_type**& **get**() const
public | **value_type**& **get**()

Return the specialized primitive type value.

### set

Specifiers | Signature
-|-
public | **void set**(const value_type& t)
public | **void set**(const this_type& t)

Set the specialized primitive type value.

## Macros

For convenience two macros are available to implement integer and floating point
classes. The macros will implement most standard operators available for the
specialized primitive type with same funtionallity.

* [Assignment operators](http://en.cppreference.com/w/cpp/language/operator_assignment)
* [Arithmetic operators](http://en.cppreference.com/w/cpp/language/operator_arithmetic)
* [Comparison operators](http://en.cppreference.com/w/cpp/language/operator_comparison)
* [Logical operators](http://en.cppreference.com/w/cpp/language/operator_logical)
* [Increment/decrement operators](http://en.cppreference.com/w/cpp/language/operator_incdec)

### GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER(class_name, primitive_type)

The **GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER** macro implements a specialized integer
type class, e.g:

```c++
GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER(my_integer_type, long)
```

Will implement a class declared as:

```c++
class my_integer_type
    : primitive_type_implicit_specializer<long>
{
public:
    // Destructor and constructors
    virtual ~my_integer_type();
    my_integer_type(static_cast<long>(0));
    my_integer_type(const my_integer_type& t);
    my_integer_type(my_integer_type&& t);
    explicit my_integer_type(const value_type& t);
    explicit my_integer_type(value_type&& t);

    // Assignment operators
    my_integer_type& operator=(const my_integer_type& t);
    my_integer_type& operator+=(const my_integer_type& t);
    my_integer_type& operator-=(const my_integer_type& t);
    my_integer_type& operator*=(const my_integer_type& t);
    my_integer_type& operator/=(const my_integer_type& t);
    my_integer_type& operator%=(const my_integer_type& t);
    my_integer_type& operator&=(const my_integer_type& t);
    my_integer_type& operator|=(const my_integer_type& t);
    my_integer_type& operator^=(const my_integer_type& t);
    my_integer_type& operator<<=(const my_integer_type& t);
    my_integer_type& operator>>=(const my_integer_type& t);
    template<typename P> my_integer_type& operator=(const P& p);
    template<typename P> my_integer_type& operator+=(const P& p);
    template<typename P> my_integer_type& operator-=(const P& p);
    template<typename P> my_integer_type& operator*=(const P& p);
    template<typename P> my_integer_type& operator/=(const P& p);
    template<typename P> my_integer_type& operator%=(const P& p);
    template<typename P> my_integer_type& operator&=(const P& p);
    template<typename P> my_integer_type& operator|=(const P& p);
    template<typename P> my_integer_type& operator^=(const P& p);
    template<typename P> my_integer_type& operator<<=(const P& p);
    template<typename P> my_integer_type& operator>>=(const P& p);

    // Arithmetic operators
    my_integer_type operator+() const;
    my_integer_type operator-() const;
    my_integer_type operator+(const my_integer_type& t) const;
    my_integer_type operator-(const my_integer_type& t) const;
    my_integer_type operator*(const my_integer_type& t) const;
    my_integer_type operator/(const my_integer_type& t) const;
    my_integer_type operator~() const;
    my_integer_type operator%(const my_integer_type& t) const;
    my_integer_type operator&(const my_integer_type& t) const;
    my_integer_type operator|(const my_integer_type& t) const;
    my_integer_type operator^(const my_integer_type& t) const;
    my_integer_type operator<<(const my_integer_type& t) const;
    my_integer_type operator>>(const my_integer_type& t) const;
    template<typename P> my_integer_type operator+(const P& p) const;
    template<typename P> my_integer_type operator-(const P& p) const;
    template<typename P> my_integer_type operator*(const P& p) const;
    template<typename P> my_integer_type operator/(const P& p) const;
    template<typename P> my_integer_type operator%(const P& p) const;
    template<typename P> my_integer_type operator&(const P& p) const;
    template<typename P> my_integer_type operator|(const P& p) const;
    template<typename P> my_integer_type operator^(const P& p) const;
    template<typename P> my_integer_type operator<<(const P& p) const;
    template<typename P> my_integer_type operator>>(const P& p) const;

    // Comparison operators
    constexpr bool operator==(const my_integer_type& t) const;
    constexpr bool operator!=(const my_integer_type& t) const;
    constexpr bool operator<(const my_integer_type& t) const;
    constexpr bool operator<=(const my_integer_type& t) const;
    constexpr bool operator>(const my_integer_type& t) const;
    constexpr bool operator>=(const my_integer_type& t) const;
    template<typename P> constexpr bool operator==(const P& p) const;
    template<typename P> constexpr bool operator!=(const P& p) const;
    template<typename P> constexpr bool operator<(const P& p) const;
    template<typename P> constexpr bool operator<=(const P& p) const;
    template<typename P> constexpr bool operator>(const P& p) const;
    template<typename P> constexpr bool operator>=(const P& p) const;

    // Logical operators
    my_integer_type operator!() const;
    my_integer_type operator&&(const my_integer_type& t) const;
    my_integer_type operator||(const my_integer_type& t) const;
    template<typename P> my_integer_type operator&&(const P& p) const;
    template<typename P> my_integer_type operator||(const P& p) const;

    // Increment/decrement operators
    my_integer_type operator++();
    my_integer_type operator--();
    my_integer_type operator++(int);
    my_integer_type operator--(int);
};

// Outside arithmetic operators
template<typename P> inline my_integer_type operator+(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator-(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator*(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator/(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator%(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator&(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator|(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator^(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<<(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>>(const P& lhs, const my_integer_type& rhs);

// Outside comparison operators
template<typename P> inline my_integer_type operator==(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator!=(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<=(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>=(const P& lhs, const my_integer_type& rhs);
```

### GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER(class_name, primitive_type)

The **GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER** macro implements a specialized integer
type class, e.g:

```c++
GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER(my_integer_type, unsigned long)
```

Will implement a class declared as:

```c++
class my_integer_type
    : primitive_type_implicit_specializer<unsigned long>
{
public:
    // Destructor and constructors
    virtual ~my_integer_type();
    my_integer_type(static_cast<unsigned long>(0));
    my_integer_type(const my_integer_type& t);
    my_integer_type(my_integer_type&& t);
    explicit my_integer_type(const value_type& t);
    explicit my_integer_type(value_type&& t);

    // Assignment operators
    my_integer_type& operator=(const my_integer_type& t);
    my_integer_type& operator+=(const my_integer_type& t);
    my_integer_type& operator-=(const my_integer_type& t);
    my_integer_type& operator*=(const my_integer_type& t);
    my_integer_type& operator/=(const my_integer_type& t);
    my_integer_type& operator%=(const my_integer_type& t);
    my_integer_type& operator&=(const my_integer_type& t);
    my_integer_type& operator|=(const my_integer_type& t);
    my_integer_type& operator^=(const my_integer_type& t);
    my_integer_type& operator<<=(const my_integer_type& t);
    my_integer_type& operator>>=(const my_integer_type& t);
    template<typename P> my_integer_type& operator=(const P& p);
    template<typename P> my_integer_type& operator+=(const P& p);
    template<typename P> my_integer_type& operator-=(const P& p);
    template<typename P> my_integer_type& operator*=(const P& p);
    template<typename P> my_integer_type& operator/=(const P& p);
    template<typename P> my_integer_type& operator%=(const P& p);
    template<typename P> my_integer_type& operator&=(const P& p);
    template<typename P> my_integer_type& operator|=(const P& p);
    template<typename P> my_integer_type& operator^=(const P& p);
    template<typename P> my_integer_type& operator<<=(const P& p);
    template<typename P> my_integer_type& operator>>=(const P& p);

    // Arithmetic operators
    my_integer_type operator+() const;
    my_integer_type operator+(const my_integer_type& t) const;
    my_integer_type operator-(const my_integer_type& t) const;
    my_integer_type operator*(const my_integer_type& t) const;
    my_integer_type operator/(const my_integer_type& t) const;
    my_integer_type operator~() const;
    my_integer_type operator%(const my_integer_type& t) const;
    my_integer_type operator&(const my_integer_type& t) const;
    my_integer_type operator|(const my_integer_type& t) const;
    my_integer_type operator^(const my_integer_type& t) const;
    my_integer_type operator<<(const my_integer_type& t) const;
    my_integer_type operator>>(const my_integer_type& t) const;
    template<typename P> my_integer_type operator+(const P& p) const;
    template<typename P> my_integer_type operator-(const P& p) const;
    template<typename P> my_integer_type operator*(const P& p) const;
    template<typename P> my_integer_type operator/(const P& p) const;
    template<typename P> my_integer_type operator%(const P& p) const;
    template<typename P> my_integer_type operator&(const P& p) const;
    template<typename P> my_integer_type operator|(const P& p) const;
    template<typename P> my_integer_type operator^(const P& p) const;
    template<typename P> my_integer_type operator<<(const P& p) const;
    template<typename P> my_integer_type operator>>(const P& p) const;

    // Comparison operators
    bool operator==(const my_integer_type& t) const;
    bool operator!=(const my_integer_type& t) const;
    bool operator<(const my_integer_type& t) const;
    bool operator<=(const my_integer_type& t) const;
    bool operator>(const my_integer_type& t) const;
    bool operator>=(const my_integer_type& t) const;
    template<typename P> bool operator==(const P& p) const;
    template<typename P> bool operator!=(const P& p) const;
    template<typename P> bool operator<(const P& p) const;
    template<typename P> bool operator<=(const P& p) const;
    template<typename P> bool operator>(const P& p) const;
    template<typename P> bool operator>=(const P& p) const;

    // Logical operators
    my_integer_type operator!() const;
    my_integer_type operator&&(const my_integer_type& t) const;
    my_integer_type operator||(const my_integer_type& t) const;
    template<typename P> my_integer_type operator&&(const P& p) const;
    template<typename P> my_integer_type operator||(const P& p) const;

    // Increment/decrement operators
    my_integer_type operator++();
    my_integer_type operator--();
    my_integer_type operator++(int);
    my_integer_type operator--(int);
};

// Outside arithmetic operators
template<typename P> inline my_integer_type operator+(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator-(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator*(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator/(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator%(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator&(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator|(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator^(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<<(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>>(const P& lhs, const my_integer_type& rhs);

// Outside comparison operators
template<typename P> inline my_integer_type operator==(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator!=(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator<=(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>(const P& lhs, const my_integer_type& rhs);
template<typename P> inline my_integer_type operator>=(const P& lhs, const my_integer_type& rhs);
```

### GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(class_name, primitive_type)

The **GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER** macro implements a specialized
floating point type class, e.g:

```c++
GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(my_floating_point_type, double)
```

Will implement a class declared as:

```c++
class my_floating_point_type
    : primitive_type_implicit_specializer<double>
{
public:
    // Destructor and constructors
    virtual ~my_floating_point_type();
    my_floating_point_type(static_cast<double>(0));
    my_floating_point_type(const my_floating_point_type& t);
    my_floating_point_type(my_floating_point_type&& t);
    explicit my_floating_point_type(const value_type& t);
    explicit my_floating_point_type(value_type&& t);

    // Assignment operators
    my_floating_point_type& operator=(const my_floating_point_type& t);
    my_floating_point_type& operator+=(const my_floating_point_type& t);
    my_floating_point_type& operator-=(const my_floating_point_type& t);
    my_floating_point_type& operator*=(const my_floating_point_type& t);
    my_floating_point_type& operator/=(const my_floating_point_type& t);
    my_floating_point_type& operator%=(const my_floating_point_type& t);
    template<typename P> my_floating_point_type& operator=(const P& p);
    template<typename P> my_floating_point_type& operator+=(const P& p);
    template<typename P> my_floating_point_type& operator-=(const P& p);
    template<typename P> my_floating_point_type& operator*=(const P& p);
    template<typename P> my_floating_point_type& operator/=(const P& p);
    template<typename P> my_floating_point_type& operator%=(const P& p);

    // Arithmetic operators
    my_floating_point_type operator+() const;
    my_floating_point_type operator-() const;
    my_floating_point_type operator+(const my_floating_point_type& t) const;
    my_floating_point_type operator-(const my_floating_point_type& t) const;
    my_floating_point_type operator*(const my_floating_point_type& t) const;
    my_floating_point_type operator/(const my_floating_point_type& t) const;
    my_floating_point_type operator%(const my_floating_point_type& t) const;
    template<typename P> my_floating_point_type operator+(const P& p) const;
    template<typename P> my_floating_point_type operator-(const P& p) const;
    template<typename P> my_floating_point_type operator*(const P& p) const;
    template<typename P> my_floating_point_type operator/(const P& p) const;
    template<typename P> my_floating_point_type operator%(const P& p) const;

    // Comparison operators
    constexpr bool operator==(const my_floating_point_type& t) const;
    constexpr bool operator!=(const my_floating_point_type& t) const;
    constexpr bool operator<(const my_floating_point_type& t) const;
    constexpr bool operator<=(const my_floating_point_type& t) const;
    constexpr bool operator>(const my_floating_point_type& t) const;
    constexpr bool operator>=(const my_floating_point_type& t) const;
    template<typename P> constexpr bool operator==(const P& p) const;
    template<typename P> constexpr bool operator!=(const P& p) const;
    template<typename P> constexpr bool operator<(const P& p) const;
    template<typename P> constexpr bool operator<=(const P& p) const;
    template<typename P> constexpr bool operator>(const P& p) const;
    template<typename P> constexpr bool operator>=(const P& p) const;

    // Increment/decrement operators
    my_floating_point_type operator++();
    my_floating_point_type operator--();
    my_floating_point_type operator++(int);
    my_floating_point_type operator--(int);
};

// Outside arithmetic operators
template<typename P> inline my_floating_point_type operator+(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator-(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator*(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator/(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator%(const P& lhs, const my_floating_point_type& rhs);

// Outside comparison operators
template<typename P> inline my_floating_point_type operator==(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator!=(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator<(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator<=(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator>(const P& lhs, const my_floating_point_type& rhs);
template<typename P> inline my_floating_point_type operator>=(const P& lhs, const my_floating_point_type& rhs);
```

## Example

This example is intended to show how specialized primitive types can be used to
avoid errors by using explicit types that provide vital information about what
is expected.

```c++
#include <iostream>
#include <go/utility/primitive_type_implicit_specializer.hpp>

namespace u = go::utility;

GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(radian_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(degree_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(meter_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(square_meter_type, double, 0.0)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace better
{

square_meter_type circular_sector_area(const radian_type& central_angle, const meter_type& radius)
{
    return square_meter_type(((radius*radius).get()*central_angle.get())/2.0);
}

square_meter_type circular_sector_area(const degree_type& central_angle, const meter_type& radius)
{
    static const double pi = std::acos(-1.0);
    return square_meter_type(((radius*radius).get()*central_angle.get())*pi/360.0);
}

}

int main()
{
    {
        // Bad, but right
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Better, and right
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_4 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 4 = " << area_4.get() << " square meter" << std::endl;
        // Also better and right
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_5 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 5 = " << area_5.get() << " square meter" << std::endl;
    }
    return 0;
}
```

Output

```
Area 1 = 0.523599
Area 2 = 0.548311 (wrong)
Area 3 = 30 (wrong)
Area 4 = 0.523599 square meter
Area 5 = 0.523599 square meter
```

The function **bad::circular_sector_area(const double& central_angle, const double& radius)**
rely on anonymous quantities. The parameter **central_angle** is most error prone. There is
no information about what unit of measurement the function expects. The fact that it
expect radians can only be determined by inspecting the implementation and requires
knowledge of geometry to recognise the formula. The relationship between the parameter
**radius** and the returned result is probably less error prone but it still lack
clarity.

The functions in namespace **better** provide information about expected units of
measurement by use of specialized types. The information is there for anyone who care
to read the function signature. The specialized types are explicit, e.g. you cannot pass
an anonymous **double** or **degree_type** value to the function that expect a
**radian_type** parameter (or worse, get the parameter order mixed up).
