---
layout: boost_lib_string
---

```c++
namespace go_boost::string
```

# class u32string

```c++
<go_boost/string/u32string.hpp>
```

The class **u32string** specializes **boost\::basic_string** and is intended for strings
encoded with [UTF-32](https://en.wikipedia.org/wiki/UTF-32).

It is declared as:

```c++
typedef boost::uint32_t char32_t;

class u32string
    : public boost::basic_string<char32_t, boost::char_traits<char32_t>, boost::allocator<char32_t>>
{
public:
    virtual ~u32string();
    u32string();
    explicit u32string(const allocator_type& alloc);
    u32string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());
    u32string(const u32string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());
    u32string(const u32string& other, size_type pos, const allocator_type& alloc = allocator_type());
    u32string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());
    u32string(const value_type* s, const allocator_type& alloc = allocator_type());
    template<class InputIt>
    u32string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    u32string(const u32string& other);
    u32string(const u32string& other, const allocator_type& alloc);
    u32string(u32string&& other) throw();
    u32string(u32string&& other, const allocator_type& alloc);
    u32string(boost::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());
    template<class T>
    u32string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());
    bool operator==(const u32string& other) const;
    bool operator!=(const u32string& other) const;
};
```

## Member types

Member type | Definition
-|-
this_type | u32string
base_type | boost\::basic_string\<char32_t, boost\::char_traits\<char32_t>, boost\::allocator\<char32_t>>
traits_type | boost\::char_traits\<char32_t>
allocator_type | boost\::allocator\<char32_t>
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

### Destructor

Specifiers |
-|
public virtual |

Destroys the **exception** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **u32string**()
*allocator constructor (2)* | public explicit | **u32string**(const allocator_type& alloc)
*character count constructor (3)* | public | **u32string**(size_type count, value_type ch, const allocator_type& alloc = allocator_type())
*substring constructor (4)* | public | **u32string**(const **u32string**& other, size_type pos, size_type count = this_type\::npos, const allocator_type& alloc = allocator_type())
*substring constructor (5)* | public | **u32string**(const **u32string**& other, size_type pos, const allocator_type& alloc = allocator_type())
*substring constructor (6)* | public | **u32string**(const value_type\* s, size_type count, const allocator_type& alloc = allocator_type())
*substring constructor (7)* | public | **u32string**(const value_type\* s, const allocator_type& alloc = allocator_type())
*range constructor (8)* | public | template\<class InputIt> **u32string**(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
*copy constructor (9)* | public | **u32string**(const **u32string**& other)
*copy constructor (10)* | public | **u32string**(const **u32string**& other, const allocator_type& alloc)
*move constructor (11)* | public | **u32string**(**u32string**&& other) throw()
*move constructor (12)* | public | **u32string**(**u32string**&& other, const allocator_type& alloc)
*initializer list constructor (13)* | public | **u32string**(boost\::initializer_list<value_type> init, const allocator_type& alloc = allocator_type())
*string view constructor (14)* | public | template\<class T> **u32string**(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type())

1. Constructs a **u32string** object.
2. Constructs empty **u32string** (zero size and unspecified capacity) using the supplied allocator.
3. Constructs the **u32string** with count copies of character ch. The behavior is undefined if count >= npos.
4. Constructs the **u32string** with a substring [pos, pos+count) of other. If count == npos, if count is not specified, or if the requested substring lasts past the end of the string, the resulting substring is [pos, size()).
5. Constructs the **u32string** with a substring [pos, pos+count) of other. If count == npos, if count is not specified, or if the requested substring lasts past the end of the string, the resulting substring is [pos, size()).
6. Constructs the **u32string** with the first count characters of character string pointed to by s. s can contain null characters. The length of the string is count. The behavior is undefined if s does not point at an array of at least count elements of **char32_t**, including the case when s is a null pointer.
7. Constructs the **u32string** with the contents initialized with a copy of the null-terminated character string pointed to by s. The length of the string is determined by the first null character. The behavior is undefined if s does not point at an array of at least Traits\::length(s)+1 elements of **char32_t**, including the case when s is a null pointer.
8. Constructs the **u32string** with the contents of the range [first, last). If InputIt is an integral type, equivalent to **u32string**(static_cast<size_type>(first), static_cast<value_type>(last), a).
9. Copy constructor. Constructs the **u32string** with the copy of the contents of other.
10. Copy constructor. Constructs the **u32string** with the copy of the contents of other.
11. Move constructor. Constructs the **u32string** with the contents of other using move semantics. other is left in valid, but unspecified state.
12. Move constructor. Constructs the **u32string** with the contents of other using move semantics. other is left in valid, but unspecified state.
13. Constructs the **u32string** with the contents of the initializer list init.
14. Implicitly converts t to a **u32string** view sv as if by boost\::basic_string_view<CharT, Traits> sv = t;, then initializes the string with the subrange [pos, pos + n) of sv as if by basic_string(sv.substr(pos, n), a). This overload only participates in overload resolution if boost\::is_convertible_v<const T&, boost\::basic_string_view<CharT, Traits>> is true.

### Equality operator

Specifiers | Signature
-|-
public | bool operator==(const u32string& other) const

Equal to operator. Returns true if this is equal to other, false otherwise.

### Inequality operator

Specifiers | Signature
-|-
public | bool operator!=(const u32string& other) const

Not equal to operator. Returns true if this is not equal to other, false otherwise.

## Inherited functions

See [boost\::basic_string](http://en.cppreference.com/w/cpp/string/basic_string) at
[cppreference.com](http://cppreference.com).
