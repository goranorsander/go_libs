#ifndef GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
#define GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED

//
//  primitive_type_specializer.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))

#include <cmath>
#include <type_traits>

#if !defined(GO_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)
#include <compare>
#endif  // #if !defined(GO_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
struct _class_name_##_tag {}; \
using _class_name_ = go::utility::primitive_type_specializer<_primitive_type_, _class_name_##_tag>;

namespace go
{
namespace utility
{
namespace detail
{

class primitive_type_specializer_base
{
protected:
    ~primitive_type_specializer_base() GO_NOEXCEPT GO_DEFAULT_DESTRUCTOR
    primitive_type_specializer_base() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_CONSTRUCTOR
};

}

template<typename PrimitiveType, class TypeTraits>
class primitive_type_specializer
    : detail::primitive_type_specializer_base
{
public:
    using this_type = primitive_type_specializer<PrimitiveType, TypeTraits>;
    using primitive_type = PrimitiveType;
    using type_traits_type = TypeTraits;
    using this_reference = this_type&;
    using this_const_reference = const this_type&;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    using rvalue_reference = primitive_type&&;
    using this_rvalue_reference = this_type&&;

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

public:
    ~primitive_type_specializer() GO_NOEXCEPT = default;

    primitive_type_specializer() GO_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_specializer_base()
        , _t(static_cast<primitive_type>(0))
    {
    }

    primitive_type_specializer(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_specializer_base()
        , _t(t._t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    primitive_type_specializer(this_rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_specializer_base()
        , _t(std::move(t._t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_specializer(const primitive_type& t) GO_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_specializer_base()
        , _t(t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_specializer(rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_specializer_base()
        , _t(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

public:
    // Assignment operators

    this_reference operator=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        if(&t != this)
        {
            this->_t = t._t;
        }
        return *this;
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    this_reference operator=(this_rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
        {
            this->_t = std::move(t._t);
        }
        return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    this_reference operator+=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t += t._t;
        return *this;
    }

    this_reference operator-=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t -= t._t;
        return *this;
    }

    this_reference operator*=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t *= t._t;
        return *this;
    }

    this_reference operator/=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t /= t._t;
        return *this;
    }

    // Integer type assignment operators

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= t._t;
        return *this;
    }

    // Floating point type assignment operators

    template <typename F = PrimitiveType>
    typename std::enable_if<std::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, t._t);
        return *this;
    }

    // Arithmetic operators

    GO_CONSTEXPR this_type operator+() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(+(this->_t));
    }

    GO_CONSTEXPR this_type operator+(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t + t._t);
    }

    GO_CONSTEXPR this_type operator-(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t - t._t);
    }

    GO_CONSTEXPR this_type operator*(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t*t._t);
    }

    GO_CONSTEXPR this_type operator/(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t/t._t);
    }

    // Signed integer and floating point type arithmetic operators

    template <typename S = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_signed<S>::value, this_type>::type operator-() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    // Integer type arithmetic operators

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator~() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(~(this->_t));
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t%t._t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t&t._t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t|t._t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t^t._t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t<<t._t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t>>t._t);
    }

    // Floating point type arithmetic operators

    template <typename F = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(std::fmod(this->_t, t._t));
    }

    // Comparison operators

    GO_CONSTEXPR bool operator==(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t == t._t;
    }

    GO_CONSTEXPR bool operator!=(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return !operator==(t);
    }

    GO_CONSTEXPR bool operator<(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t < t._t;
    }

    GO_CONSTEXPR bool operator<=(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t <= t._t;
    }

    GO_CONSTEXPR bool operator>(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t > t._t;
    }

    GO_CONSTEXPR bool operator>=(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t >= t._t;
    }

#if !defined(GO_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    constexpr auto operator<=>(this_const_reference t) const noexcept
    {
        return this->_t <=> t._t;
    }

#endif  // #if !defined(GO_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    // Integer type logical operators

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator!() const GO_NOEXCEPT_OR_NOTHROW
    {
        return !(this->_t);
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && t._t;
    }

    template <typename I = PrimitiveType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator||(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || t._t;
    }

    // Increment/decrement operators

    this_type operator++() GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(++(this->_t));
    }

    this_type operator--() GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(--(this->_t));
    }

    this_type operator++(int) GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type((this->_t)++);
    }

    this_type operator--(int) GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type((this->_t)--);
    }

public:
    GO_CONSTEXPR const primitive_type& get() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    primitive_type& get() GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    void set(const primitive_type& t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = t;
    }

    void set(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = t._t;
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    void set(rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(t);
    }

    void set(this_rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(t._t);
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

private:
    primitive_type _t;
};

}
}

#else

GO_MESSAGE("Required C++11 feature is not supported by this compiler. Using C++03 implementation")

#define GO_NO_CXX11_PRIMITIVE_TYPE_SPECIALIZER 1

#include <cmath>

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    _class_name_() GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(static_cast<_primitive_type_>(0)) {} \
    _class_name_(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    _class_name_(_class_name_&& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(std::move(t)) {} \
    explicit _class_name_(const value_type& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(value_type&& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(std::move(t)) {}

#else

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    _class_name_() GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(static_cast<_primitive_type_>(0)) {} \
    _class_name_(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) GO_NOEXCEPT_OR_NOTHROW : go::utility::primitive_type_specializer<_primitive_type_>(t) {}

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { if(&t != this) { go::utility::primitive_type_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() /= t.get(); return *this; }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() %= t.get(); return *this; } \
    _class_name_& operator&=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() &= t.get(); return *this; } \
    _class_name_& operator|=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() |= t.get(); return *this; } \
    _class_name_& operator^=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() ^= t.get(); return *this; } \
    _class_name_& operator<<=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() <<= t.get(); return *this; } \
    _class_name_& operator>>=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() >>= t.get(); return *this; }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() = std::fmod(get(), t.get()); return *this; }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator+() const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(+get()); } \
    GO_CONSTEXPR _class_name_ operator+(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get() + t.get()); } \
    GO_CONSTEXPR _class_name_ operator-(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get() - t.get()); } \
    GO_CONSTEXPR _class_name_ operator*(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()*t.get()); } \
    GO_CONSTEXPR _class_name_ operator/(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()/t.get()); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator-() const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(-get()); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator~() const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(~get()); } \
    GO_CONSTEXPR _class_name_ operator%(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()%t.get()); } \
    GO_CONSTEXPR _class_name_ operator&(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&t.get()); } \
    GO_CONSTEXPR _class_name_ operator|(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()|t.get()); } \
    GO_CONSTEXPR _class_name_ operator^(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()^t.get()); } \
    GO_CONSTEXPR _class_name_ operator<<(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()<<t.get()); } \
    GO_CONSTEXPR _class_name_ operator>>(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()>>t.get()); }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator%(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(get(), t.get())); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR bool operator==(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return get() == t.get(); } \
    GO_CONSTEXPR bool operator!=(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return !operator==(t); } \
    GO_CONSTEXPR bool operator<(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return get() < t.get(); } \
    GO_CONSTEXPR bool operator<=(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return get() <= t.get(); } \
    GO_CONSTEXPR bool operator>(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return get() > t.get(); } \
    GO_CONSTEXPR bool operator>=(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return get() >= t.get(); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator!() const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(!get()); } \
    GO_CONSTEXPR _class_name_ operator&&(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&&t.get()); } \
    GO_CONSTEXPR _class_name_ operator||(const _class_name_& t) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()||t.get()); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR _class_name_ operator++() GO_NOEXCEPT_OR_NOTHROW { return _class_name_(++get()); } \
    GO_CONSTEXPR _class_name_ operator--() GO_NOEXCEPT_OR_NOTHROW { return _class_name_(--get()); } \
    GO_CONSTEXPR _class_name_ operator++(int) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()++); } \
    GO_CONSTEXPR _class_name_ operator--(int) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()--); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

namespace go
{
namespace utility
{

template<typename T>
class primitive_type_specializer
{
public:
    typedef primitive_type_specializer<T> this_type;
    typedef T value_type;

    virtual ~primitive_type_specializer() GO_NOEXCEPT = 0;

protected:
    primitive_type_specializer(const primitive_type_specializer& t) GO_NOEXCEPT_OR_NOTHROW
        : _t(t._t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    primitive_type_specializer(primitive_type_specializer&& t) GO_NOEXCEPT_OR_NOTHROW
        : _t(std::move(t._t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_specializer(const value_type& t) GO_NOEXCEPT_OR_NOTHROW
        : _t(t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_specializer(value_type&& t) GO_NOEXCEPT_OR_NOTHROW
        : _t(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    primitive_type_specializer& operator=(const primitive_type_specializer& t) GO_NOEXCEPT_OR_NOTHROW
    {
        if(&t != this)
        {
            _t = t._t;
        }
        return *this;
    }

public:
    GO_CONSTEXPR const value_type& get() const GO_NOEXCEPT_OR_NOTHROW
    {
        return _t;
    }

    value_type& get() GO_NOEXCEPT_OR_NOTHROW
    {
        return _t;
    }

    void set(const value_type& t) GO_NOEXCEPT_OR_NOTHROW
    {
        _t = t;
    }

    void set(const this_type& t) GO_NOEXCEPT_OR_NOTHROW
    {
        _t = t._t;
    }

private:
    value_type _t;
};

template<typename T>
inline primitive_type_specializer<T>::~primitive_type_specializer() GO_NOEXCEPT
{
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
