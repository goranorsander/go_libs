---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# abstract class template primitive_type_specializer

```c++
<go/utility/primitive_type_specializer.hpp>
```

Base class for explicit specializations of objects in the **GO Std C++ Libraries**.

The reason for implementing this class is mainly experience of large code bases with
long life. It is vital to express ideas directly in code and if possible also build in
sanity checks in the code. Primitive types and implicit casting is an error prone
combination.

It is declared as:

```c++
template<typename T> class primitive_type_specializer
{
public:
    virtual ~primitive_type_specializer() = 0;

protected:
    primitive_type_specializer(const primitive_type_specializer& t);
    primitive_type_specializer(primitive_type_specializer&& t);
    explicit primitive_type_specializer(const value_type& t);
    explicit primitive_type_specializer(value_type&& t);
    primitive_type_specializer& operator=(const primitive_type_specializer& t);

public:
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
this_type | primitive_type_specializer<value_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **primitive_type_specializer** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*protected member function*

Constructor | Signature
-|-
*copy constructor (1)* | **primitive_type_specializer**(const **primitive_type_specializer**& t)
*move constructor (2)* | **primitive_type_specializer**(**primitive_type_specializer**&& t)
*assign value, copy (3)* | **primitive_type_specializer**(const **value_type**& t)
*assign value, move (4)* | **primitive_type_specializer**(**value_type**&& t)

1. Copy constructor. Constructs the **primitive_type_specializer** with the copy of the contents of t.
2. Move constructor. Constructs the **primitive_type_specializer** with the contents of t using move semantics. t is left in valid, but unspecified state.
3. Assign value constructor. Constructs the **primitive_type_specializer** and assign it the contents of t.
4. Assign value constructor. Constructs the **primitive_type_specializer** and assign it the contents of t using move semantics. t is left in valid, but unspecified state.

### operator=

*protected member function*

Operator | Signature
-|-
*assign copy (1)* | **primitive_type_specializer**& operator=(const **primitive_type_specializer**& t)

1. Copies an **primitive_type_specializer** object.

### constexpr const value_type& get() const

*public member function*

Return the specialized primitive type value.

### value_type& get()

*public member function*

Return the specialized primitive type value.

### void set(const value_type& t)

*public member function*

Set the specialized primitive type value.

### void set(const this_type& t)

*public member function*

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

### GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(class_name, primitive_type, default_value)

The **GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER** macro implements a specialized integer
type class, e.g:

```c++
GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(my_integer_type, long, 0)
```

Will implement a class declared as:

```c++
class my_integer_type
    : primitive_type_specializer<long>
{
public:
    // Destructor and constructors
    virtual ~my_integer_type();
    my_integer_type();
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
    constexpr bool operator==(const my_integer_type& t) const;
    constexpr bool operator!=(const my_integer_type& t) const;
    constexpr bool operator<(const my_integer_type& t) const;
    constexpr bool operator<=(const my_integer_type& t) const;
    constexpr bool operator>(const my_integer_type& t) const;
    constexpr bool operator>=(const my_integer_type& t) const;

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

### GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(class_name, primitive_type, default_value)

The **GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER** macro implements a specialized
floating point type class, e.g:

```c++
GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(my_floating_point_type, double, 0.0)
```

Will implement a class declared as:

```c++
class my_floating_point_type
    : primitive_type_specializer<double>
{
public:
    // Destructor and constructors
    virtual ~my_floating_point_type();
    my_floating_point_type();
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

    // Arithmetic operators
    my_floating_point_type operator+() const;
    my_floating_point_type operator-() const;
    my_floating_point_type operator+(const my_floating_point_type& t) const;
    my_floating_point_type operator-(const my_floating_point_type& t) const;
    my_floating_point_type operator*(const my_floating_point_type& t) const;
    my_floating_point_type operator/(const my_floating_point_type& t) const;
    my_floating_point_type operator%(const my_floating_point_type& t) const;

    // Comparison operators
    constexpr bool operator==(const my_floating_point_type& t) const;
    constexpr bool operator!=(const my_floating_point_type& t) const;
    constexpr bool operator<(const my_floating_point_type& t) const;
    constexpr bool operator<=(const my_floating_point_type& t) const;
    constexpr bool operator>(const my_floating_point_type& t) const;
    constexpr bool operator>=(const my_floating_point_type& t) const;

    // Increment/decrement operators
    my_floating_point_type operator++();
    my_floating_point_type operator--();
    my_floating_point_type operator++(int);
    my_floating_point_type operator--(int);
};
```

## Example

This example is intended to show how specialized primitive types can be used to
avoid errors by using explicit types that provide vital information about what
is expected.

```c++
#include <iostream>
#include <go/utility/primitive_type_specializer.hpp>

namespace u = go::utility;

GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(radian_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(degree_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(meter_type, double, 0.0)
GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(square_meter_type, double, 0.0)

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