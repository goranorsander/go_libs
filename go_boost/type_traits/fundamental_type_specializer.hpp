#ifndef GO_BOOST_TYPE_TRAITS_FUNDAMENTAL_TYPE_SPECIALIZER_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_FUNDAMENTAL_TYPE_SPECIALIZER_HPP_INCLUDED

//
//  fundamental_type_specializer.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if !(defined(GO_BOOST_NO_CXX11) || defined(GO_BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))

#include <cmath>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits.hpp>

#if !defined(GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)
#include <compare>
#endif  // #if !defined(GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

#include <go_boost/type_traits/detail/fundamental_type_specializer_base.hpp>

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER( _class_name_, _fundamental_type_ ) \
struct _class_name_##_tag {}; \
typedef go_boost::type_traits::fundamental_type_specializer<_fundamental_type_, _class_name_##_tag> _class_name_;

#if defined(GO_BOOST_COMP_MSVC_VC120)
#define GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE
#else
#define GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE std::forward<fundamental_type>
#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

namespace go_boost
{
namespace type_traits
{

template<typename FundamentalType, class TypeTraits>
class fundamental_type_specializer
    : detail::fundamental_type_specializer_base
{
public:
    typedef fundamental_type_specializer<FundamentalType, TypeTraits> this_type;
    typedef FundamentalType fundamental_type;
    typedef TypeTraits type_traits_type;
    typedef this_type& this_reference;
    typedef const this_type& this_const_reference;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    typedef fundamental_type&& rvalue_reference;
    typedef this_type&& this_rvalue_reference;

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    ~fundamental_type_specializer() BOOST_NOEXCEPT GO_BOOST_DEFAULT_DESTRUCTOR

    fundamental_type_specializer() BOOST_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_specializer_base()
        , _t(static_cast<fundamental_type>(0))
    {
    }

    fundamental_type_specializer(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_specializer_base()
        , _t(t._t)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    fundamental_type_specializer(this_rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_specializer_base()
        , _t(std::move(t._t))
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_specializer(const fundamental_type& t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_specializer_base()
        , _t(t)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_specializer(rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_specializer_base()
        , _t(std::move(t))
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    // Assignment operators

    this_reference operator=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
        {
            this->_t = t._t;
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_reference operator=(this_rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
        {
            this->_t = std::move(t._t);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_reference operator+=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t += t._t;
        return *this;
    }

    this_reference operator-=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t -= t._t;
        return *this;
    }

    this_reference operator*=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t *= t._t;
        return *this;
    }

    this_reference operator/=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t /= t._t;
        return *this;
    }

    // Integer type assignment operators

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= t._t;
        return *this;
    }

    // Floating point type assignment operators

    template <typename F = FundamentalType>
    typename boost::enable_if_c<boost::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, t._t);
        return *this;
    }

    // Arithmetic operators

    GO_BOOST_CONSTEXPR this_type operator+() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(+(this->_t));
    }

    GO_BOOST_CONSTEXPR this_type operator+(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t + t._t));
    }

    GO_BOOST_CONSTEXPR this_type operator-(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t - t._t));
    }

    GO_BOOST_CONSTEXPR this_type operator*(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t * t._t));
    }

    GO_BOOST_CONSTEXPR this_type operator/(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t / t._t));
    }

    // Signed integer and floating point type arithmetic operators

    template <typename S = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_signed<S>::value, this_type>::type operator-() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    template <typename F = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_floating_point<F>::value, this_type>::type operator-() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    // Integer type arithmetic operators

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator~() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(~(this->_t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t % t._t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t & t._t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t | t._t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t ^ t._t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t << t._t));
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t >> t._t));
    }

    // Floating point type arithmetic operators

    template <typename F = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(std::fmod(this->_t, t._t)));
    }

    // Comparison operators

    GO_BOOST_CONSTEXPR bool operator==(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t == t._t;
    }

    GO_BOOST_CONSTEXPR bool operator!=(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return !operator==(t);
    }

    GO_BOOST_CONSTEXPR bool operator<(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t < t._t;
    }

    GO_BOOST_CONSTEXPR bool operator<=(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t <= t._t;
    }

    GO_BOOST_CONSTEXPR bool operator>(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t > t._t;
    }

    GO_BOOST_CONSTEXPR bool operator>=(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t >= t._t;
    }

#if !defined(GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    constexpr auto operator<=>(this_const_reference t) const noexcept
    {
        return this->_t <=> t._t;
    }

#endif  // #if !defined(GO_BOOST_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    // Integer type logical operators

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator!() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return !(this->_t);
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && t._t;
    }

    template <typename I = FundamentalType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator||(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || t._t;
    }

    // Increment/decrement operators

    this_type operator++() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(++(this->_t));
    }

    this_type operator--() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(--(this->_t));
    }

    this_type operator++(int) BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE((this->_t)++));
    }

    this_type operator--(int) BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_BOOST_FTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE((this->_t)--));
    }

public:
    GO_BOOST_CONSTEXPR const fundamental_type& get() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    fundamental_type& get() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    void set(const fundamental_type& t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = t;
    }

    void set(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = t._t;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void set(rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(t);
    }

    void set(this_rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(t._t);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

private:
    fundamental_type _t;
};

}
}

#else

GO_BOOST_MESSAGE("Required C++11 feature is not supported by this compiler. Using C++03 implementation")

#define GO_BOOST_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER 1

#include <cmath>

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    _class_name_() BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::fundamental_type_specializer<_fundamental_type_>(static_cast<_fundamental_type_>(0)) {} \
    _class_name_(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::fundamental_type_specializer<_fundamental_type_>(t) {} \
    explicit _class_name_(const value_type& t) BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::fundamental_type_specializer<_fundamental_type_>(t) {}

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    _class_name_& operator=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { if(&t != this) { go_boost::type_traits::fundamental_type_specializer<_fundamental_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() /= t.get(); return *this; }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() %= t.get(); return *this; } \
    _class_name_& operator&=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() &= t.get(); return *this; } \
    _class_name_& operator|=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() |= t.get(); return *this; } \
    _class_name_& operator^=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() ^= t.get(); return *this; } \
    _class_name_& operator<<=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() <<= t.get(); return *this; } \
    _class_name_& operator>>=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() >>= t.get(); return *this; }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() = std::fmod(get(), t.get()); return *this; }

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_CONSTEXPR _class_name_ operator+() const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(+get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator+(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get() + t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator-(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get() - t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator*(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()*t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator/(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()/t.get()); }

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_BOOST_CONSTEXPR _class_name_ operator-() const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(-get()); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_CONSTEXPR _class_name_ operator~() const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(~get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator%(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()%t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator&(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator|(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()|t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator^(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()^t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator<<(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()<<t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator>>(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()>>t.get()); }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_CONSTEXPR _class_name_ operator%(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(get(), t.get())); }

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_CONSTEXPR bool operator==(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return get() == t.get(); } \
    GO_BOOST_CONSTEXPR bool operator!=(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return !operator==(t); } \
    GO_BOOST_CONSTEXPR bool operator<(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return get() < t.get(); } \
    GO_BOOST_CONSTEXPR bool operator<=(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return get() <= t.get(); } \
    GO_BOOST_CONSTEXPR bool operator>(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return get() > t.get(); } \
    GO_BOOST_CONSTEXPR bool operator>=(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return get() >= t.get(); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_CONSTEXPR _class_name_ operator!() const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(!get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator&&(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&&t.get()); } \
    GO_BOOST_CONSTEXPR _class_name_ operator||(const _class_name_& t) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()||t.get()); }

#define GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
    _class_name_ operator++() BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(++get()); } \
    _class_name_ operator--() BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(--get()); } \
    _class_name_ operator++(int) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()++); } \
    _class_name_ operator--(int) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()--); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::fundamental_type_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW {} \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::fundamental_type_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW {} \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::fundamental_type_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW {} \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

namespace go_boost
{
namespace type_traits
{

template<typename T>
class fundamental_type_specializer
{
public:
    typedef fundamental_type_specializer<T> this_type;
    typedef T value_type;

    virtual ~fundamental_type_specializer() BOOST_NOEXCEPT = 0;

protected:
    fundamental_type_specializer(const fundamental_type_specializer& t) BOOST_NOEXCEPT_OR_NOTHROW
        : _t(t._t)
    {
    }

    explicit fundamental_type_specializer(const value_type& t) BOOST_NOEXCEPT_OR_NOTHROW
        : _t(t)
    {
    }

    fundamental_type_specializer& operator=(const fundamental_type_specializer& t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(&t != this)
        {
            _t = t._t;
        }
        return *this;
    }

public:
    GO_BOOST_CONSTEXPR const value_type& get() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _t;
    }

    value_type& get() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _t;
    }

    void set(const value_type& t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        _t = t;
    }

    void set(const this_type& t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        _t = t._t;
    }

private:
    value_type _t;
};

template<typename T>
inline fundamental_type_specializer<T>::~fundamental_type_specializer() BOOST_NOEXCEPT
{
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_FUNDAMENTAL_TYPE_SPECIALIZER_HPP_INCLUDED
