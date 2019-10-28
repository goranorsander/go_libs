#ifndef GO_BOOST_TYPE_TRAITS_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED

//
//  primitive_type_implicit_specializer.hpp
//
//  Copyright 2018-2019 Göran Orsander
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

#if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)
#include <compare>
#endif  // #if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

#include <go_boost/type_traits/detail/primitive_type_implicit_specializer_base.hpp>

#define GO_BOOST_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
struct _class_name_##_tag {}; \
typedef go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_, _class_name_##_tag> _class_name_;

namespace go_boost
{
namespace type_traits
{

template<typename PrimitiveType, class TypeTraits>
class primitive_type_implicit_specializer
    : detail::primitive_type_implicit_specializer_base
{
public:
    typedef primitive_type_implicit_specializer<PrimitiveType, TypeTraits> this_type;
    typedef PrimitiveType primitive_type;
    typedef TypeTraits type_traits_type;
    typedef this_type& this_reference;
    typedef const this_type& this_const_reference;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    typedef primitive_type&& rvalue_reference;
    typedef this_type&& this_rvalue_reference;

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    ~primitive_type_implicit_specializer() BOOST_NOEXCEPT GO_BOOST_DEFAULT_DESTRUCTOR

    primitive_type_implicit_specializer() BOOST_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_implicit_specializer_base()
        , _t(static_cast<primitive_type>(0))
    {
    }

    primitive_type_implicit_specializer(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_implicit_specializer_base()
        , _t(t._t)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    primitive_type_implicit_specializer(this_rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_implicit_specializer_base()
        , _t(std::move(t._t))
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_implicit_specializer(const primitive_type& t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_implicit_specializer_base()
        , _t(t)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit primitive_type_implicit_specializer(rvalue_reference t) BOOST_NOEXCEPT_OR_NOTHROW
        : detail::primitive_type_implicit_specializer_base()
        , _t(std::move(t))
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    // Cast operator

    GO_BOOST_CONSTEXPR operator const primitive_type&() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    operator primitive_type&() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

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

    template<typename P>
    this_reference operator=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = static_cast<primitive_type>(p);
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template<typename P>
    this_reference operator=(P&& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(static_cast<primitive_type>(p));
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template<typename P>
    this_reference operator+=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t += static_cast<primitive_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator-=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t -= static_cast<primitive_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator*=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t *= static_cast<primitive_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator/=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t /= static_cast<primitive_type>(p);
        return *this;
    }

    // Integer type assignment operators

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename boost::enable_if_c<boost::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= t._t;
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator%=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= static_cast<primitive_type>(p);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator&=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= static_cast<primitive_type>(p);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator|=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= static_cast<primitive_type>(p);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator^=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= static_cast<primitive_type>(p);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator<<=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= static_cast<primitive_type>(p);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_reference>::type operator>>=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= static_cast<primitive_type>(p);
        return *this;
    }

    // Floating point type assignment operators

    template <typename F = PrimitiveType>
    typename boost::enable_if_c<boost::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, t._t);
        return *this;
    }

    template <typename P>
    typename boost::enable_if_c<boost::is_floating_point<primitive_type>::value && boost::is_arithmetic<P>::value, this_reference>::type operator%=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, static_cast<primitive_type>(p));
        return *this;
    }

    // Arithmetic operators

    GO_BOOST_CONSTEXPR this_type operator+() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(+(this->_t));
    }

    GO_BOOST_CONSTEXPR this_type operator+(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t + t._t);
    }

    GO_BOOST_CONSTEXPR this_type operator-(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t - t._t);
    }

    GO_BOOST_CONSTEXPR this_type operator*(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t * t._t);
    }

    GO_BOOST_CONSTEXPR this_type operator/(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t / t._t);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, this_type>::type operator+(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t + static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, this_type>::type operator-(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t - static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, this_type>::type operator*(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t * static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, this_type>::type operator/(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t / static_cast<primitive_type>(p));
    }

    // Signed integer and floating point type arithmetic operators

    template <typename S = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_signed<S>::value, this_type>::type operator-() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    template <typename F = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_floating_point<F>::value, this_type>::type operator-() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    // Integer type arithmetic operators

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator~() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(~(this->_t));
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t % t._t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t & t._t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t | t._t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t ^ t._t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t << t._t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t >> t._t);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator%(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t % static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator&(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t & static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator|(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t | static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator^(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t ^ static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator<<(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t << static_cast<primitive_type>(p));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, this_type>::type operator>>(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(this->_t >> static_cast<primitive_type>(p));
    }

    // Floating point type arithmetic operators

    template <typename F = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(std::fmod(this->_t, t._t));
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_floating_point<primitive_type>::value && boost::is_arithmetic<P>::value, this_type>::type operator%(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type(std::fmod(this->_t, static_cast<primitive_type>(p)));
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

#if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    constexpr auto operator<=>(this_const_reference t) const noexcept
    {
        return this->_t <=> t._t;
    }

#endif  // #if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator==(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t == static_cast<primitive_type>(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator!=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return !operator==(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator<(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t < static_cast<primitive_type>(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator<=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t <= static_cast<primitive_type>(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator>(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t > static_cast<primitive_type>(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_arithmetic<P>::value, bool>::type operator>=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t >= static_cast<primitive_type>(p);
    }

#if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    template <typename P>
    constexpr typename boost::enable_if_c<boost::is_arithmetic<P>::value && boost::is_integral<primitive_type>::value, std::strong_ordering>::type operator<=>(const P& p) const noexcept
    {
        return this->_t <=> static_cast<primitive_type>(p);
    }

    template <typename P>
    constexpr typename boost::enable_if_c<boost::is_arithmetic<P>::value && boost::is_floating_point<primitive_type>::value, std::partial_ordering>::type operator<=>(const P& p) const noexcept
    {
        return this->_t <=> static_cast<primitive_type>(p);
    }

#endif  // #if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

    // Integer type logical operators

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator!() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return !(this->_t);
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && t._t;
    }

    template <typename I = PrimitiveType>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<I>::value, bool>::type operator||(this_const_reference t) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || t._t;
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, bool>::type operator&&(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && static_cast<primitive_type>(p);
    }

    template <typename P>
    GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_integral<primitive_type>::value && boost::is_integral<P>::value, bool>::type operator||(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || static_cast<primitive_type>(p);
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
        return this_type((this->_t)++);
    }

    this_type operator--(int) BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this_type((this->_t)--);
    }

public:
    GO_BOOST_CONSTEXPR const primitive_type& get() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    primitive_type& get() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    void set(const primitive_type& t) BOOST_NOEXCEPT_OR_NOTHROW
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
    primitive_type _t;
};

// Outside arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator+(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) + rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator-(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) - rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator*(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) * rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, PrimitiveTypeSpecializer>::type operator/(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) / rhs.get());
}

// Outside integer arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator%(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) % rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator&(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) & rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator|(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) | rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator^(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) ^ rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator<<(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) << rhs.get());
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_integral<P>::value, PrimitiveTypeSpecializer>::type operator>>(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) >> rhs.get());
}

// Outside floating point arithmetic operators

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_floating_point<P>::value, PrimitiveTypeSpecializer>::type operator%(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return PrimitiveTypeSpecializer(std::fmod(static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs), rhs.get()));
}

// Outside comparison operators

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator==(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) == rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator!=(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) != rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator<(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) < rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator<=(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) <= rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator>(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) > rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline GO_BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value, bool>::type operator>=(const P& lhs, const PrimitiveTypeSpecializer& rhs) BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) >= rhs.get();
}

#if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

template<class PrimitiveTypeSpecializer, typename P>
inline constexpr typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value && boost::is_integral<typename PrimitiveTypeSpecializer::primitive_type>::value, std::strong_ordering>::type operator<=>(const P& lhs, const PrimitiveTypeSpecializer& rhs) noexcept
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) <=> rhs.get();
}

template<class PrimitiveTypeSpecializer, typename P>
inline constexpr typename boost::enable_if_c<boost::is_base_of<detail::primitive_type_implicit_specializer_base, PrimitiveTypeSpecializer>::value && boost::is_arithmetic<P>::value && boost::is_floating_point<typename PrimitiveTypeSpecializer::primitive_type>::value, std::partial_ordering>::type operator<=>(const P& lhs, const PrimitiveTypeSpecializer& rhs) noexcept
{
    return static_cast<typename PrimitiveTypeSpecializer::primitive_type>(lhs) <=> rhs.get();
}

#endif  // #if !defined(GO_BOOST_NO_CXX2A_THREE_WAY_COMPARISON_OPERATOR)

}
}

# else

GO_BOOST_MESSAGE("Required C++11 feature is not supported by this compiler. Using C++03 implementation")

#define GO_BOOST_NO_CXX11_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER 1

#include <go_boost/type_traits/primitive_type_specializer.hpp>

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    _class_name_() BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_>(static_cast<_primitive_type_>(0)) {} \
    _class_name_(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) BOOST_NOEXCEPT_OR_NOTHROW : go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_>(t) {}

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { if(&t != this) { go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) BOOST_NOEXCEPT_OR_NOTHROW { get() /= t.get(); return *this; } \
    template<typename P> _class_name_& operator=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() = static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator+=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() += static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator-=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() -= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator*=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() *= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator/=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() /= static_cast<_primitive_type_>(p); return *this; }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() %= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator&=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() &= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator|=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() |= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator^=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() ^= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator<<=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() <<= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator>>=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() >>= static_cast<_primitive_type_>(p); return *this; }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) BOOST_NOEXCEPT_OR_NOTHROW { get() = std::fmod(get(), static_cast<_primitive_type_>(p)); return *this; }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator+(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get() + static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator-(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get() - static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator*(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()*static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator/(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()/static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator%(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()%static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator&(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator|(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()|static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator^(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()^static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator<<(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()<<static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator>>(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()>>static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator%(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(get(), static_cast<_primitive_type_>(p))); }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_BOOST_CONSTEXPR bool operator==(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return get() == static_cast<_primitive_type_>(p); } \
    template<typename P> GO_BOOST_CONSTEXPR bool operator!=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return !operator==(static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR bool operator<(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return get() < static_cast<_primitive_type_>(p); } \
    template<typename P> GO_BOOST_CONSTEXPR bool operator<=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return get() <= static_cast<_primitive_type_>(p); } \
    template<typename P> GO_BOOST_CONSTEXPR bool operator>(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return get() > static_cast<_primitive_type_>(p); } \
    template<typename P> GO_BOOST_CONSTEXPR bool operator>=(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return get() >= static_cast<_primitive_type_>(p); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator&&(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&&static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_BOOST_CONSTEXPR _class_name_ operator||(const P& p) const BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(get()||static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator+(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)+rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator-(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)-rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator*(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)*rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator/(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)/rhs.get()); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator%(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)%rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator&(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)&rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator|(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)|rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator^(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)^rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator<<(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)<<rhs.get()); } \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator>>(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_primitive_type_>(lhs)>>rhs.get()); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline GO_BOOST_CONSTEXPR _class_name_ operator%(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(static_cast<_primitive_type_>(lhs), rhs.get())); }

#if defined(GO_BOOST_COMP_CLANG) || defined(GO_BOOST_COMP_GCC) || defined(GO_BOOST_COMP_GCC_MINGW)
#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator==(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)==rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator!=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)!=rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)<rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)<=rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)>rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)>=rhs.get(); }
#else
#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator==(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)==rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator!=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)!=rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)<rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)<=rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)>rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>=(const P& lhs, const _class_name_& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return static_cast<_primitive_type_>(lhs)>=rhs.get(); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator==(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()==static_cast<_primitive_type_>(rhs); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator!=(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()!=static_cast<_primitive_type_>(rhs); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()<static_cast<_primitive_type_>(rhs); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator<=(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()<=static_cast<_primitive_type_>(rhs); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()>static_cast<_primitive_type_>(rhs); } \
template<typename P> inline GO_BOOST_CONSTEXPR bool operator>=(const _class_name_& lhs, const P& rhs) BOOST_NOEXCEPT_OR_NOTHROW { return lhs.get()>=static_cast<_primitive_type_>(rhs); }
#endif  // #if defined(GO_BOOST_COMP_CLANG) || defined(GO_BOOST_COMP_GCC) || defined(GO_BOOST_COMP_GCC_MINGW)

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_BOOST_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ )

#define GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_BOOST_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ )

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go_boost::type_traits::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_BOOST_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS(_class_name_, _primitive_type_) \
GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ )

namespace go_boost
{
namespace type_traits
{

template<typename T>
class primitive_type_implicit_specializer
    : public primitive_type_specializer<T>
{
public:
    typedef primitive_type_implicit_specializer<T> this_type;
    typedef primitive_type_specializer<T> base_type;
    typedef T value_type;

    virtual ~primitive_type_implicit_specializer() BOOST_NOEXCEPT = 0;

protected:
    primitive_type_implicit_specializer(const primitive_type_implicit_specializer& t) BOOST_NOEXCEPT_OR_NOTHROW
        : primitive_type_specializer<T>(t)
    {
    }

    explicit primitive_type_implicit_specializer(const value_type& t) BOOST_NOEXCEPT_OR_NOTHROW
        : primitive_type_specializer<T>(t)
    {
    }

    primitive_type_implicit_specializer& operator=(const primitive_type_implicit_specializer& t) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
        {
            primitive_type_specializer<T>::operator=(t);
        }
        return *this;
    }

public:
    GO_BOOST_CONSTEXPR operator const value_type&() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return primitive_type_specializer<T>::get();
    }

    operator value_type&() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return primitive_type_specializer<T>::get();
    }
};

template<typename T>
inline primitive_type_implicit_specializer<T>::~primitive_type_implicit_specializer() BOOST_NOEXCEPT
{
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
