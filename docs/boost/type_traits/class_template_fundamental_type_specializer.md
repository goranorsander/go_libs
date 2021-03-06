---
layout: boost_lib_type_traits
---

```c++
namespace go_boost::type_traits
```

# class template fundamental_type_specializer

```c++
<go_boost/type_traits/fundamental_type_specializer.hpp>
```

Class for explicit specializations of fundamental types.

The reason for implementing this class is mainly experience of large code bases with
long life. It is vital to express ideas directly in code and if possible also build in
sanity checks in the code. Fundamental types and implicit casting is an error prone
combination.

There are two implementations of this class. The first version do not require any C\++11
features and that is the only reason to keep it. The second version require C\++11 and
is used by compilers supporting the required C\++11 features. If the first version is
used then **GO_BOOST_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER** is defined.

# class template fundamental_type_specializer (C++11)

The **fundamental_type_specializer** is declared as:

```c++
template<typename FundamentalType, class TypeTraits> class fundamental_type_specializer
{
public:
    ~fundamental_type_specializer() noexcept = default;
    fundamental_type_specializer() noexcept;
    fundamental_type_specializer(this_const_reference t) noexcept;
    fundamental_type_specializer(this_rvalue_reference t) noexcept;
    explicit fundamental_type_specializer(const fundamental_type& t) noexcept;
    explicit fundamental_type_specializer(rvalue_reference t) noexcept;

public:
    // Assignment operators
    this_reference operator=(this_const_reference t) noexcept;
    this_reference operator=(this_rvalue_reference t) noexcept;
    this_reference operator+=(this_const_reference t) noexcept;
    this_reference operator-=(this_const_reference t) noexcept;
    this_reference operator*=(this_const_reference t) noexcept;
    this_reference operator/=(this_const_reference t) noexcept;

    // Integer type assignment operators
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t) noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t) noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t) noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t) noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t) noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t) noexcept;

    // Floating point type assignment operators
    template <typename F = FundamentalType>
    typename boost::enable_if_c<boost::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t) noexcept;

    // Arithmetic operators
    this_type operator+() const noexcept;
    this_type operator+(this_const_reference t) const noexcept;
    this_type operator-(this_const_reference t) const noexcept;
    this_type operator*(this_const_reference t) const noexcept;
    this_type operator/(this_const_reference t) const noexcept;

    // Signed integer and floating point type arithmetic operators
    template <typename S = FundamentalType>
    typename boost::enable_if_c<boost::is_signed<S>::value, this_type>::type operator-() const noexcept;

    // Integer type arithmetic operators
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator~() const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const noexcept;

    // Floating point type arithmetic operators
    template <typename F = FundamentalType>
    typename boost::enable_if_c<boost::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const noexcept;

    // Comparison operators
    constexpr bool operator==(this_const_reference t) const noexcept;
    constexpr bool operator!=(this_const_reference t) const noexcept;
    constexpr bool operator<(this_const_reference t) const noexcept;
    constexpr bool operator<=(this_const_reference t) const noexcept;
    constexpr bool operator>(this_const_reference t) const noexcept;
    constexpr bool operator>=(this_const_reference t) const noexcept;
    constexpr auto operator<=>(this_const_reference t) const noexcept;

    // Integer type logical operators
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator!() const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const noexcept;
    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator||(this_const_reference t) const noexcept;

    // Increment/decrement operators
    this_type operator++() noexcept;
    this_type operator--() noexcept;
    this_type operator++(int) noexcept;
    this_type operator--(int) noexcept;

public:
    constexpr const fundamental_type& get() const noexcept;
    fundamental_type& get() noexcept;
    void set(const fundamental_type& t) noexcept;
    void set(this_const_reference t) noexcept;
    void set(rvalue_reference t) noexcept;
    void set(this_rvalue_reference t) noexcept;
};
```

## Template parameters

Parameter | Description
-|-
FundamentalType | The fundamental value type
TypeTraits | A **struct** used as a dispatching tag to uniquely identify the specialized fundamental type

## Member types

Member type | Definition
-|-
this_type | fundamental_type_specializer<FundamentalType, TypeTraits>
fundamental_type | FundamentalType
type_traits_type | TypeTraits
this_reference | this_type&
this_const_reference | const this_type&
rvalue_reference | fundamental_type&&
this_rvalue_reference | this_type&&

## Member functions

### Destructor

Specifiers |
-|
public |

Destroys the **fundamental_type_specializer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public | **fundamental_type_specializer**() noexcept
*copy constructor (2)* | public explicit | **fundamental_type_specializer**(**this_const_reference** t) noexcept
*move constructor (3)* | public explicit | **fundamental_type_specializer**(**this_rvalue_reference** t) noexcept
*assign value, copy (4)* | public | **fundamental_type_specializer**(const **value_type**& t) noexcept
*assign value, move (5)* | public | **fundamental_type_specializer**(**value_type**&& t) noexcept

1. Constructor. Constructs a **fundamental_type_specializer**.
2. Copy constructor. Constructs a **fundamental_type_specializer** with the copy of the contents of t.
3. Move constructor. Constructs a **fundamental_type_specializer** with the contents of t using move semantics. t is left in valid, but unspecified state.
4. Assign value constructor. Constructs a **fundamental_type_specializer** and assign it the contents of t.
5. Assign value constructor. Constructs a **fundamental_type_specializer** and assign it the contents of t using move semantics. t is left in valid, but unspecified state.

### Assignment operators

Operator | Specifiers | Signature
-|-|-
*simple copy assignment (1)* | public | **this_reference** operator=(**this_const_reference** t) noexcept
*simple move assignment (2)* | public | **this_reference** operator=(**this_rvalue_reference** t) noexcept
*addition assignment (3)* | public | **this_reference** operator+=(**this_const_reference** t) noexcept
*subtraction assignment (4)* | public | **this_reference** operator-=(**this_const_reference** t) noexcept
*multiplication assignment (5)* | public | **this_reference** operator*=(**this_const_reference** t) noexcept
*division assignment (6)* | public | **this_reference** operator/=(**this_const_reference** t) noexcept
*modulo assignment (7)* | public | **this_reference** operator%=(**this_const_reference** t) noexcept
*bitwise AND assignment (8)* | public | **this_reference** operator&=(**this_const_reference** t) noexcept
*bitwise OR assignment (9)* | public | **this_reference** operator|=(**this_const_reference** t) noexcept
*bitwise XOR assignment (10)* | public | **this_reference** operator^=(**this_const_reference** t) noexcept
*bitwise left shift assignment (11)* | public | **this_reference** operator<<=(**this_const_reference** t) noexcept
*bitwise right shift assignment (12)* | public | **this_reference** operator>>=(**this_const_reference** t) noexcept

Assignment operators 1 to 6 apply to all fundamental types.

Assignment operator 7 apply to integer and floating point types.

Assignment operators 8 to 12 apply to all integer types.

### Arithmetic operators

Operator | Specifiers | Signature
-|-|-
*unary plus (1)* | public | **this_type** operator+() const noexcept
*addition (2)* | public | **this_type** operator+(**this_const_reference** t) const noexcept
*subtraction (3)* | public | **this_type** operator-(**this_const_reference** t) const noexcept
*multiplication (4)* | public | **this_type** operator*(**this_const_reference** t) const noexcept
*division (5)* | public | **this_type** operator/(**this_const_reference** t) const noexcept
*modulo (6)* | public | **this_type** operator%(**this_const_reference** t) const noexcept
*unary minus (7)* | public | **this_type** operator-() const noexcept
*bitwise NOT (8)* | public | **this_type** operator~() const noexcept
*bitwise AND (9)* | public | **this_type** operator&(**this_const_reference** t) const noexcept
*bitwise OR (10)* | public | **this_type** operator|(**this_const_reference** t) const noexcept
*bitwise XOR (11)* | public | **this_type** operator^(**this_const_reference** t) const noexcept
*bitwise left shift (12)* | public | **this_type** operator<<(**this_const_reference** t) const noexcept
*bitwise right shift (13)* | public | **this_type** operator>>(**this_const_reference** t) const noexcept

Arithmetic operators 1 to 6 apply to all arithmetic types.

Arithmetic operator 7 apply to signed integer and floating point types.

Arithmetic operators 8 to 13 apply to all integer types.

### Comparison operators

Operator | Specifiers | Signature
-|-|-
*equal to (1)* | public | constexpr bool operator==(**this_const_reference** t) const noexcept
*not equal to (2)* | public | constexpr bool operator!=(**this_const_reference** t) const noexcept
*less than (3)* | public | constexpr bool operator<(**this_const_reference** t) const noexcept
*less than or equal to (4)* | public | constexpr bool operator<=(**this_const_reference** t) const noexcept
*greater than (5)* | public | constexpr bool operator>(**this_const_reference** t) const noexcept
*greater than or equal to (6)* | public | constexpr bool operator>=(**this_const_reference** t) const noexcept
*three-way comparison (7)* | public | constexpr auto operator<=>(**this_const_reference** t) const noexcept

Comparison operators 1 to 7 apply to all fundamental types.

### Logical operators

Operator | Specifiers | Signature
-|-|-
*negation (1)* | public | bool operator!() const noexcept
*AND (2)* | public | bool operator&&(this_const_reference t) const noexcept
*inclusive OR (3)* | public | bool operator||(this_const_reference t) const noexcept

Logical operators 1 to 3 apply to all integer types.

### Increment/decrement operators

Operator | Specifiers | Signature
-|-|-
*pre-increment (1)* | public | **this_type** operator++() noexcept
*pre-decrement (2)* | public | **this_type** operator--() noexcept
*post-increment (3)* | public | **this_type** operator++(int) noexcept
*post-decrement (4)* | public | **this_type** operator--(int) noexcept

Increment/decrement operators 1 to 3 apply to all arithmetic types.

### get

Specifiers | Signature
-|-
public | **constexpr const fundamental_type**& **get**() const noexcept
public | **fundamental_type**& **get**() noexcept

Return the specialized fundamental type value.

### set

Specifiers | Signature
-|-
public | **void set**(const fundamental_type& t) noexcept
public | **void set**(this_const_reference t) noexcept
public | **void set**(fundamental_type&& t) noexcept
public | **void set**(this_rvalue_reference t) noexcept

Set the specialized fundamental type value.

## Macro

For convenience a macro is available to implement specialized fundamental type
classes. The macros will implement a dispatching tag **struct** and declare
the specialized fundamental type with a **using** statement.

### GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(class_name, fundamental_type)

The **GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER** macro implements a specialized
fundamental type class, e.g:

```c++
GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(my_integer_type, long)
```

Will implement a class declared as:

```c++
struct my_integer_type_tag {};
using my_integer_type = go_boost::type_traits::fundamental_type_specializer<long, my_integer_type_tag>;
```

## Example

This example is intended to show how specialized fundamental types can be used to
avoid errors by using explicit types that provide vital information about what
is expected.

```c++
#include <iostream>
#include <go_boost/type_traits.hpp>

namespace u = go_boost::type_traits;

GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(radian_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(degree_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(meter_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(square_meter_type, double)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace less_bad
{

typedef double meter;
typedef double radian;
typedef double square_meter;

square_meter circular_sector_area(const radian& central_angle, const meter& radius)
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
        // Bad, but correct
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Bad:" << std::endl << "  Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Less bad, but correct
        const less_bad::radian central_angle_rad = std::acos(-1.0)/3.0;
        const less_bad::meter radius = 1.0;
        const less_bad::square_meter area_4 = less_bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Less bad:" << std::endl << "  Area 4 = " << area_4 << std::endl;
        // Less bad, but wrong (parameter order)
        const less_bad::square_meter area_5 = less_bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 5 = " << area_5 << " (wrong)" << std::endl;
        // Less bad, but wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_6 = less_bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 6 = " << area_6 << " (wrong)" << std::endl;
    }
    {
        // Better, and correct
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_7 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Better:" << std::endl << "  Area 7 = " << area_7.get() << " square meter" << std::endl;
        // Also better and correct
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_8 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 8 = " << area_8.get() << " square meter" << std::endl;
    }
    return 0;
}
```

Output

```
Bad:
  Area 1 = 0.523599
  Area 2 = 0.548311 (wrong)
  Area 3 = 30 (wrong)
Less bad:
  Area 4 = 0.523599
  Area 5 = 0.548311 (wrong)
  Area 6 = 30 (wrong)
Better:
  Area 7 = 0.523599 square meter
  Area 8 = 0.523599 square meter
```

The function **bad::circular_sector_area(const double& central_angle, const double& radius)**
rely on anonymous quantities. The parameter **central_angle** is most error prone. There is
no information about what unit of measurement the function expects. The fact that it
expect radians can only be determined by inspecting the implementation and requires
knowledge of geometry to recognise the formula. The relationship between the parameter
**radius** and the returned result is probably less error prone but it still lack
clarity.

The functions in namespace **less_bad** provide information about expected units of
measurement by use of type definitions. The information is there for anyone who care
to read the function signature. However, the type definitions are not explicit. You
can get units of measurment or parameter order wrong.

The functions in namespace **better** provide information about expected units of
measurement by use of specialized types. The information is there for anyone who care
to read the function signature. The specialized types are explicit, e.g. you cannot pass
an anonymous **double** or **degree_type** value to the function that expect a
**radian_type** parameter (or worse, get the parameter order mixed up).

# class template fundamental_type_specializer (C++03)

The **fundamental_type_specializer** is declared as:

```c++
template<typename T> class fundamental_type_specializer
{
public:
    virtual ~fundamental_type_specializer() = 0;

protected:
    fundamental_type_specializer(const fundamental_type_specializer& t);
    fundamental_type_specializer(fundamental_type_specializer&& t);
    explicit fundamental_type_specializer(const value_type& t);
    explicit fundamental_type_specializer(value_type&& t);
    fundamental_type_specializer& operator=(const fundamental_type_specializer& t) noexcept;

public:
    const value_type& get() const;
    value_type& get();
    void set(const value_type& t);
    void set(const this_type& t);
};
```

## Template parameters

Parameter | Description
-|-
T | The fundamental value type

## Member types

Member type | Definition
-|-
value_type | T
this_type | fundamental_type_specializer<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **fundamental_type_specializer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*copy constructor (1)* | protected explicit | **fundamental_type_specializer**(const **fundamental_type_specializer**& t)
*move constructor (2)* | protected explicit | **fundamental_type_specializer**(**fundamental_type_specializer**&& t)
*assign value, copy (3)* | protected | **fundamental_type_specializer**(const **value_type**& t)
*assign value, move (4)* | protected | **fundamental_type_specializer**(**value_type**&& t)

1. Copy constructor. Constructs the **fundamental_type_specializer** with the copy of the contents of t.
2. Move constructor. Constructs the **fundamental_type_specializer** with the contents of t using move semantics. t is left in valid, but unspecified state.
3. Assign value constructor. Constructs the **fundamental_type_specializer** and assign it the contents of t.
4. Assign value constructor. Constructs the **fundamental_type_specializer** and assign it the contents of t using move semantics. t is left in valid, but unspecified state.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | protected | **fundamental_type_specializer**& operator=(const **fundamental_type_specializer**& t) noexcept

1. Copies an **fundamental_type_specializer** object.

### get

Specifiers | Signature
-|-
public | **const value_type**& **get**() const
public | **value_type**& **get**()

Return the specialized fundamental type value.

### set

Specifiers | Signature
-|-
public | **void set**(const value_type& t)
public | **void set**(const this_type& t)

Set the specialized fundamental type value.

## Macros

For convenience two macros are available to implement integer and floating point
classes. The macros will implement most standard operators available for the
specialized fundamental type with same funtionallity.

* [Assignment operators](http://en.cppreference.com/w/cpp/language/operator_assignment)
* [Arithmetic operators](http://en.cppreference.com/w/cpp/language/operator_arithmetic)
* [Comparison operators](http://en.cppreference.com/w/cpp/language/operator_comparison)
* [Logical operators](http://en.cppreference.com/w/cpp/language/operator_logical)
* [Increment/decrement operators](http://en.cppreference.com/w/cpp/language/operator_incdec)

### GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(class_name, fundamental_type)

The **GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER** macro implements a specialized integer
type class, e.g:

```c++
GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(my_integer_type, long)
```

Will implement a class declared as:

```c++
class my_integer_type
    : fundamental_type_specializer<long>
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
    my_integer_type& operator=(const my_integer_type& t) noexcept;
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

    // Comparison operators
    bool operator==(const my_integer_type& t) const;
    bool operator!=(const my_integer_type& t) const;
    bool operator<(const my_integer_type& t) const;
    bool operator<=(const my_integer_type& t) const;
    bool operator>(const my_integer_type& t) const;
    bool operator>=(const my_integer_type& t) const;

    // Logical operators
    my_integer_type operator!() const;
    my_integer_type operator&&(const my_integer_type& t) const;
    my_integer_type operator||(const my_integer_type& t) const;

    // Increment/decrement operators
    my_integer_type operator++();
    my_integer_type operator--();
    my_integer_type operator++(int);
    my_integer_type operator--(int);
};
```

### GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(class_name, fundamental_type)

The **GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER** macro implements a specialized
unsigned integer
type class, e.g:

```c++
GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(my_integer_type, unsigned long)
```

Will implement a class declared as:

```c++
class my_integer_type
    : fundamental_type_specializer<unsigned long>
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
    my_integer_type& operator=(const my_integer_type& t) noexcept;
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

    // Comparison operators
    bool operator==(const my_integer_type& t) const;
    bool operator!=(const my_integer_type& t) const;
    bool operator<(const my_integer_type& t) const;
    bool operator<=(const my_integer_type& t) const;
    bool operator>(const my_integer_type& t) const;
    bool operator>=(const my_integer_type& t) const;

    // Logical operators
    my_integer_type operator!() const;
    my_integer_type operator&&(const my_integer_type& t) const;
    my_integer_type operator||(const my_integer_type& t) const;

    // Increment/decrement operators
    my_integer_type operator++();
    my_integer_type operator--();
    my_integer_type operator++(int);
    my_integer_type operator--(int);
};
```

### GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(class_name, fundamental_type)

The **GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER** macro implements a specialized
floating point type class, e.g:

```c++
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(my_floating_point_type, double)
```

Will implement a class declared as:

```c++
class my_floating_point_type
    : fundamental_type_specializer<double>
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
    my_floating_point_type& operator=(const my_floating_point_type& t) noexcept;
    my_floating_point_type& operator+=(const my_floating_point_type& t);
    my_floating_point_type& operator-=(const my_floating_point_type& t);
    my_floating_point_type& operator*=(const my_floating_point_type& t);
    my_floating_point_type& operator/=(const my_floating_point_type& t);
    my_floating_point_type& operator%=(const my_floating_point_type& t);

    // Arithmetic operators
    my_floating_point_type operator+() const;
    my_floating_point_type operator-() const;
    my_floating_point_type operator+(const my_floating_point_type& t) const;
    my_floating_point_type operator-(const my_floating_point_type& t) const;
    my_floating_point_type operator*(const my_floating_point_type& t) const;
    my_floating_point_type operator/(const my_floating_point_type& t) const;
    my_floating_point_type operator%(const my_floating_point_type& t) const;

    // Comparison operators
    bool operator==(const my_floating_point_type& t) const;
    bool operator!=(const my_floating_point_type& t) const;
    bool operator<(const my_floating_point_type& t) const;
    bool operator<=(const my_floating_point_type& t) const;
    bool operator>(const my_floating_point_type& t) const;
    bool operator>=(const my_floating_point_type& t) const;

    // Increment/decrement operators
    my_floating_point_type operator++();
    my_floating_point_type operator--();
    my_floating_point_type operator++(int);
    my_floating_point_type operator--(int);
};
```

## Example

This example is intended to show how specialized fundamental types can be used to
avoid errors by using explicit types that provide vital information about what
is expected.

```c++
#include <iostream>
#include <go_boost/type_traits/fundamental_type_specializer.hpp>

namespace u = go_boost::type_traits;

GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(radian_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(degree_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(meter_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(square_meter_type, double, 0.0)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace less_bad
{

typedef double meter;
typedef double radian;
typedef double square_meter;

square_meter circular_sector_area(const radian& central_angle, const meter& radius)
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
        // Bad, but correct
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Bad:" << std::endl << "  Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Less bad, but correct
        const less_bad::radian central_angle_rad = std::acos(-1.0)/3.0;
        const less_bad::meter radius = 1.0;
        const less_bad::square_meter area_4 = less_bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Less bad:" << std::endl << "  Area 4 = " << area_4 << std::endl;
        // Less bad, but wrong (parameter order)
        const less_bad::square_meter area_5 = less_bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 5 = " << area_5 << " (wrong)" << std::endl;
        // Less bad, but wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_6 = less_bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 6 = " << area_6 << " (wrong)" << std::endl;
    }
    {
        // Better, and correct
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_7 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Better:" << std::endl << "  Area 7 = " << area_7.get() << " square meter" << std::endl;
        // Also better and correct
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_8 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 8 = " << area_8.get() << " square meter" << std::endl;
    }
    return 0;
}
```

Output

```
Bad:
  Area 1 = 0.523599
  Area 2 = 0.548311 (wrong)
  Area 3 = 30 (wrong)
Less bad:
  Area 4 = 0.523599
  Area 5 = 0.548311 (wrong)
  Area 6 = 30 (wrong)
Better:
  Area 7 = 0.523599 square meter
  Area 8 = 0.523599 square meter
```

The function **bad::circular_sector_area(const double& central_angle, const double& radius)**
rely on anonymous quantities. The parameter **central_angle** is most error prone. There is
no information about what unit of measurement the function expects. The fact that it
expect radians can only be determined by inspecting the implementation and requires
knowledge of geometry to recognise the formula. The relationship between the parameter
**radius** and the returned result is probably less error prone but it still lack
clarity.

The functions in namespace **less_bad** provide information about expected units of
measurement by use of type definitions. The information is there for anyone who care
to read the function signature. However, the type definitions are not explicit. You
can get units of measurment or parameter order wrong.

The functions in namespace **better** provide information about expected units of
measurement by use of specialized types. The information is there for anyone who care
to read the function signature. The specialized types are explicit, e.g. you cannot pass
an anonymous **double** or **degree_type** value to the function that expect a
**radian_type** parameter (or worse, get the parameter order mixed up).
