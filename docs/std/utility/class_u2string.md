---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class u2string

```c++
<go/utility/u2string.hpp>
```

The class **u2string** specializes **std\::basic_string** and is intended for strings
encoded with [UCS-2](https://en.wikipedia.org/wiki/Universal_Coded_Character_Set).

It is declared as:

```c++
typedef unsigned short char2_t;

class u2string
    : public std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>
{
public:
    virtual ~u2string() = default;
    u2string();
    explicit u2string(const allocator_type& alloc);
    u2string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());
    u2string(const u2string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());
    u2string(const u2string& other, size_type pos, const allocator_type& alloc = allocator_type());
    u2string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());
    u2string(const value_type* s, const allocator_type& alloc = allocator_type());
    template<class InputIt>
    u2string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    u2string(const u2string& other);
    u2string(const u2string& other, const allocator_type& alloc);
    u2string(u2string&& other) noexcept;
    u2string(u2string&& other, const allocator_type& alloc);
    u2string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());
    template<class T>
    u2string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());
    bool operator==(const u2string& other) const;
    bool operator!=(const u2string& other) const;
};
```

## Member types

Member type | Definition
-|-
this_type | u2string
base_type | std\::basic_string\<char2_t, std\::char_traits\<char2_t>, std\::allocator\<char2_t>>
traits_type | std\::char_traits\<char2_t>
allocator_type | std\::allocator\<char2_t>
value_type | base_type\::value_type
size_type | base_type\::size_type
difference_type | base_type\::difference_type
pointer | base_type\::pointer
const_pointer | base_type\::const_pointer
reference | base_type\::reference
const_reference | base_type\::const_reference
iterator | base_type\::iterator
const_iterator | base_type\::const_iterator
reverse_iterator | base_type\::reverse_iterator
const_reverse_iterator | base_type\::const_reverse_iterator

## Member functions

### (destructor)

*public virtual member function*

Destroys the **exception** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*default constructor (1)* | **u2string**()
*allocator constructor (2)* | explicit **u2string**(const allocator_type& alloc)
*character count constructor (3)* | **u2string**(size_type count, value_type ch, const allocator_type& alloc = allocator_type())
*substring constructor (4)* | **u2string**(const **u2string**& other, size_type pos, size_type count = this_type\::npos, const allocator_type& alloc = allocator_type())
*substring constructor (5)* | **u2string**(const **u2string**& other, size_type pos, const allocator_type& alloc = allocator_type())
*substring constructor (6)* | **u2string**(const value_type\* s, size_type count, const allocator_type& alloc = allocator_type())
*substring constructor (7)* | **u2string**(const value_type\* s, const allocator_type& alloc = allocator_type())
*range constructor (8)* | template\<class InputIt> **u2string**(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
*copy constructor (9)* | **u2string**(const **u2string**& other)
*copy constructor (10)* | **u2string**(const **u2string**& other, const allocator_type& alloc)
*move constructor (11)* | **u2string**(**u2string**&& other) noexcept
*move constructor (12)* | **u2string**(**u2string**&& other, const allocator_type& alloc)
*initializer list constructor (13)* | **u2string**(std\::initializer_list<value_type> init, const allocator_type& alloc = allocator_type())
*string view constructor (14)* | template\<class T> **u2string**(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type())

1. Constructs a **u2string** object.
2. Constructs empty **u2string** (zero size and unspecified capacity) using the supplied allocator.
3. Constructs the **u2string** with count copies of character ch. The behavior is undefined if count >= npos.
4. Constructs the **u2string** with a substring [pos, pos+count) of other. If count == npos, if count is not specified, or if the requested substring lasts past the end of the string, the resulting substring is [pos, size()).
5. Constructs the **u2string** with a substring [pos, pos+count) of other. If count == npos, if count is not specified, or if the requested substring lasts past the end of the string, the resulting substring is [pos, size()).
6. Constructs the **u2string** with the first count characters of character string pointed to by s. s can contain null characters. The length of the string is count. The behavior is undefined if s does not point at an array of at least count elements of **char2_t**, including the case when s is a null pointer.
7. Constructs the **u2string** with the contents initialized with a copy of the null-terminated character string pointed to by s. The length of the string is determined by the first null character. The behavior is undefined if s does not point at an array of at least Traits\::length(s)+1 elements of **char2_t**, including the case when s is a null pointer.
8. Constructs the **u2string** with the contents of the range [first, last). If InputIt is an integral type, equivalent to **u2string**(static_cast<size_type>(first), static_cast<value_type>(last), a).
9. Copy constructor. Constructs the **u2string** with the copy of the contents of other.
10. Copy constructor. Constructs the **u2string** with the copy of the contents of other.
11. Move constructor. Constructs the **u2string** with the contents of other using move semantics. other is left in valid, but unspecified state.
12. Move constructor. Constructs the **u2string** with the contents of other using move semantics. other is left in valid, but unspecified state.
13. Constructs the **u2string** with the contents of the initializer list init.
14. Implicitly converts t to a **u2string** view sv as if by std\::basic_string_view<CharT, Traits> sv = t;, then initializes the string with the subrange [pos, pos + n) of sv as if by basic_string(sv.substr(pos, n), a). This overload only participates in overload resolution if std\::is_convertible_v<const T&, std\::basic_string_view<CharT, Traits>> is true.

### operator==

*public member function*

Equal to operator. Returns true if this is equal to other, false otherwise.

### operator!=

*public member function*

Not equal to operator. Returns true if this is not equal to other, false otherwise.

## Inherited functions

See [std\::basic_string](http://en.cppreference.com/w/cpp/string/basic_string) at
[cppreference.com](http://cppreference.com).
