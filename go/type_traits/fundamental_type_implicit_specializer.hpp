#ifndef GO_TYPE_TRAITS_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
#define GO_TYPE_TRAITS_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED

//
//  fundamental_type_implicit_specializer.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))

#include <cmath>
#include <type_traits>

#if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)
#include <compare>
#endif  // #if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

#include <go/type_traits/detail/fundamental_type_implicit_specializer_base.hpp>

#define GO_IMPLEMENT_IMPLICIT_FUNDAMENTAL_TYPE_SPECIALIZER( _class_name_, _fundamental_type_ ) \
struct _class_name_##_tag {}; \
using _class_name_ = go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_, _class_name_##_tag>;

#if defined(GO_COMP_MSVC_VC120)
#define GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE
#define GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE
#else
#define GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE std::forward<fundamental_type>
#define GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE std::forward<typename FundamentalTypeSpecializer::fundamental_type>
#endif  // #if !defined(GO_COMP_MSVC_VC120)

namespace go
{
namespace type_traits
{

template<typename FundamentalType, class TypeTraits>
class fundamental_type_implicit_specializer
    : detail::fundamental_type_implicit_specializer_base
{
public:
    using this_type = fundamental_type_implicit_specializer<FundamentalType, TypeTraits>;
    using fundamental_type = FundamentalType;
    using type_traits_type = TypeTraits;
    using this_reference = this_type&;
    using this_const_reference = const this_type&;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    using rvalue_reference = fundamental_type&&;
    using this_rvalue_reference = this_type&&;

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

public:
    ~fundamental_type_implicit_specializer() GO_NOEXCEPT GO_DEFAULT_DESTRUCTOR

    fundamental_type_implicit_specializer() GO_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_implicit_specializer_base()
        , _t(static_cast<fundamental_type>(0))
    {
    }

    fundamental_type_implicit_specializer(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_implicit_specializer_base()
        , _t(t._t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    fundamental_type_implicit_specializer(this_rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_implicit_specializer_base()
        , _t(std::move(t._t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_implicit_specializer(const fundamental_type& t) GO_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_implicit_specializer_base()
        , _t(t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_implicit_specializer(rvalue_reference t) GO_NOEXCEPT_OR_NOTHROW
        : detail::fundamental_type_implicit_specializer_base()
        , _t(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

public:
    // Cast operator

    GO_CONSTEXPR operator const fundamental_type&() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    operator fundamental_type&() GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    // Assignment operators

    this_reference operator=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
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

    template<typename P>
    this_reference operator=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = static_cast<fundamental_type>(p);
        return *this;
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    template<typename P>
    this_reference operator=(P&& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::move(static_cast<fundamental_type>(p));
        return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    template<typename P>
    this_reference operator+=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t += static_cast<fundamental_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator-=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t -= static_cast<fundamental_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator*=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t *= static_cast<fundamental_type>(p);
        return *this;
    }

    template<typename P>
    this_reference operator/=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t /= static_cast<fundamental_type>(p);
        return *this;
    }

    // Integer type assignment operators

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= t._t;
        return *this;
    }

    template <typename I = FundamentalType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= t._t;
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator%=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t %= static_cast<fundamental_type>(p);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator&=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t &= static_cast<fundamental_type>(p);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator|=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t |= static_cast<fundamental_type>(p);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator^=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t ^= static_cast<fundamental_type>(p);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator<<=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t <<= static_cast<fundamental_type>(p);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_reference>::type operator>>=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t >>= static_cast<fundamental_type>(p);
        return *this;
    }

    // Floating point type assignment operators

    template <typename F = FundamentalType>
    typename std::enable_if<std::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, t._t);
        return *this;
    }

    template <typename P>
    typename std::enable_if<std::is_floating_point<fundamental_type>::value && std::is_arithmetic<P>::value, this_reference>::type operator%=(const P& p) GO_NOEXCEPT_OR_NOTHROW
    {
        this->_t = std::fmod(_t, static_cast<fundamental_type>(p));
        return *this;
    }

    // Arithmetic operators

    GO_CONSTEXPR this_type operator+() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(+(this->_t));
    }

    GO_CONSTEXPR this_type operator+(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t + t._t));
    }

    GO_CONSTEXPR this_type operator-(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t - t._t));
    }

    GO_CONSTEXPR this_type operator*(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t * t._t));
    }

    GO_CONSTEXPR this_type operator/(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t / t._t));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator+(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t + static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator-(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t - static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator*(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t * static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, this_type>::type operator/(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t / static_cast<fundamental_type>(p)));
    }

    // Signed integer and floating point type arithmetic operators

    template <typename S = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_signed<S>::value, this_type>::type operator-() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(-(this->_t));
    }

    // Integer type arithmetic operators

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator~() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(~(this->_t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t % t._t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t & t._t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t | t._t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t ^ t._t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t << t._t));
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t >> t._t));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator%(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t % static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator&(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t & static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator|(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t | static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator^(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t ^ static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator<<(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t << static_cast<fundamental_type>(p)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, this_type>::type operator>>(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(this->_t >> static_cast<fundamental_type>(p)));
    }

    // Floating point type arithmetic operators

    template <typename F = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(std::fmod(this->_t, t._t)));
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_floating_point<fundamental_type>::value && std::is_arithmetic<P>::value, this_type>::type operator%(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE(std::fmod(this->_t, static_cast<fundamental_type>(p))));
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

#if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    constexpr auto operator<=>(this_const_reference t) const noexcept
    {
        return this->_t <=> t._t;
    }

#endif  // #if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator==(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t == static_cast<fundamental_type>(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator!=(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return !operator==(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator<(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t < static_cast<fundamental_type>(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator<=(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t <= static_cast<fundamental_type>(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator>(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t > static_cast<fundamental_type>(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_arithmetic<P>::value, bool>::type operator>=(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t >= static_cast<fundamental_type>(p);
    }

#if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value && std::is_integral<fundamental_type>::value, std::strong_ordering>::type operator<=>(const P& p) const noexcept
    {
        return this->_t <=> static_cast<fundamental_type>(p);
    }

    template <typename P>
    constexpr typename std::enable_if<std::is_arithmetic<P>::value && std::is_floating_point<fundamental_type>::value, std::partial_ordering>::type operator<=>(const P& p) const noexcept
    {
        return this->_t <=> static_cast<fundamental_type>(p);
    }

#endif  // #if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

    // Integer type logical operators

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator!() const GO_NOEXCEPT_OR_NOTHROW
    {
        return !(this->_t);
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && t._t;
    }

    template <typename I = FundamentalType>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<I>::value, bool>::type operator||(this_const_reference t) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || t._t;
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, bool>::type operator&&(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t && static_cast<fundamental_type>(p);
    }

    template <typename P>
    GO_CONSTEXPR typename std::enable_if<std::is_integral<fundamental_type>::value && std::is_integral<P>::value, bool>::type operator||(const P& p) const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t || static_cast<fundamental_type>(p);
    }

    // Increment/decrement operators

    this_reference operator++() GO_NOEXCEPT_OR_NOTHROW
    {
        ++(this->_t);
        return *this;
    }

    this_reference operator--() GO_NOEXCEPT_OR_NOTHROW
    {
        --(this->_t);
        return *this;
    }

    this_type operator++(int) GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE((this->_t)++));
    }

    this_type operator--(int) GO_NOEXCEPT_OR_NOTHROW
    {
        return this_type(GO_IFTS_USING_STD_FORWARD_FUNDAMENTAL_TYPE((this->_t)--));
    }

public:
    GO_CONSTEXPR const fundamental_type& get() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    fundamental_type& get() GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_t;
    }

    void set(const fundamental_type& t) GO_NOEXCEPT_OR_NOTHROW
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
    fundamental_type _t;
};

// Outside arithmetic operators

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, FundamentalTypeSpecializer>::type operator+(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) + rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, FundamentalTypeSpecializer>::type operator-(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) - rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, FundamentalTypeSpecializer>::type operator*(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) * rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, FundamentalTypeSpecializer>::type operator/(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) / rhs.get()));
}

// Outside integer arithmetic operators

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator%(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) % rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator&(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) & rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator|(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) | rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator^(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) ^ rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator<<(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) << rhs.get()));
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_integral<P>::value, FundamentalTypeSpecializer>::type operator>>(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) >> rhs.get()));
}

// Outside floating point arithmetic operators

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_floating_point<P>::value, FundamentalTypeSpecializer>::type operator%(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return FundamentalTypeSpecializer(GO_IFTS_USING_STD_FORWARD_TYPENAME_FUNDAMENTAL_TYPE(std::fmod(static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs), rhs.get())));
}

// Outside comparison operators

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator==(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) == rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator!=(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) != rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator<(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) < rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator<=(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) <= rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator>(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) > rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline GO_CONSTEXPR typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value, bool>::type operator>=(const P& lhs, const FundamentalTypeSpecializer& rhs) GO_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) >= rhs.get();
}

#if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

template<class FundamentalTypeSpecializer, typename P>
inline constexpr typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value && std::is_integral<typename FundamentalTypeSpecializer::fundamental_type>::value, std::strong_ordering>::type operator<=>(const P& lhs, const FundamentalTypeSpecializer& rhs) noexcept
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) <=> rhs.get();
}

template<class FundamentalTypeSpecializer, typename P>
inline constexpr typename std::enable_if<std::is_base_of<detail::fundamental_type_implicit_specializer_base, FundamentalTypeSpecializer>::value && std::is_arithmetic<P>::value && std::is_floating_point<typename FundamentalTypeSpecializer::fundamental_type>::value, std::partial_ordering>::type operator<=>(const P& lhs, const FundamentalTypeSpecializer& rhs) noexcept
{
    return static_cast<typename FundamentalTypeSpecializer::fundamental_type>(lhs) <=> rhs.get();
}

#endif  // #if !defined(GO_NO_CXX20_THREE_WAY_COMPARISON_OPERATOR)

}
}

#else

GO_MESSAGE("Required C++11 feature is not supported by this compiler. Using C++03 implementation")

#define GO_NO_CXX11_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER 1

#include <go/type_traits/fundamental_type_specializer.hpp>

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#define GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    _class_name_() GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(static_cast<_fundamental_type_>(0)) {} \
    _class_name_(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(t) {} \
    _class_name_(_class_name_&& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(std::move(t)) {} \
    explicit _class_name_(const value_type& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(t) {} \
    explicit _class_name_(value_type&& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(std::move(t)) {}

#else

#define GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    _class_name_() GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(static_cast<_fundamental_type_>(0)) {} \
    _class_name_(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(t) {} \
    explicit _class_name_(const value_type& t) GO_NOEXCEPT_OR_NOTHROW : go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>(t) {}

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#define GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    _class_name_& operator=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { if(&t != this) { go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) GO_NOEXCEPT_OR_NOTHROW { get() /= t.get(); return *this; } \
    template<typename P> _class_name_& operator=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() = static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator+=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() += static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator-=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() -= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator*=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() *= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator/=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() /= static_cast<_fundamental_type_>(p); return *this; }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() %= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator&=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() &= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator|=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() |= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator^=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() ^= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator<<=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() <<= static_cast<_fundamental_type_>(p); return *this; } \
    template<typename P> _class_name_& operator>>=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() >>= static_cast<_fundamental_type_>(p); return *this; }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) GO_NOEXCEPT_OR_NOTHROW { get() = std::fmod(get(), static_cast<_fundamental_type_>(p)); return *this; }

#define GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> GO_CONSTEXPR _class_name_ operator+(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get() + static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator-(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get() - static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator*(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()*static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator/(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()/static_cast<_fundamental_type_>(p)); }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> GO_CONSTEXPR _class_name_ operator%(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()%static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator&(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator|(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()|static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator^(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()^static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator<<(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()<<static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator>>(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()>>static_cast<_fundamental_type_>(p)); }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> GO_CONSTEXPR _class_name_ operator%(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(get(), static_cast<_fundamental_type_>(p))); }

#define GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> GO_CONSTEXPR bool operator==(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return get() == static_cast<_fundamental_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator!=(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return !operator==(static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR bool operator<(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return get() < static_cast<_fundamental_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator<=(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return get() <= static_cast<_fundamental_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator>(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return get() > static_cast<_fundamental_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator>=(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return get() >= static_cast<_fundamental_type_>(p); }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _fundamental_type_ ) \
    template<typename P> GO_CONSTEXPR _class_name_ operator&&(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()&&static_cast<_fundamental_type_>(p)); } \
    template<typename P> GO_CONSTEXPR _class_name_ operator||(const P& p) const GO_NOEXCEPT_OR_NOTHROW { return _class_name_(get()||static_cast<_fundamental_type_>(p)); }

#define GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
template<typename P> inline GO_CONSTEXPR _class_name_ operator+(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)+rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator-(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)-rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator*(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)*rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator/(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)/rhs.get()); }

#define GO_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
template<typename P> inline GO_CONSTEXPR _class_name_ operator%(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)%rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator&(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)&rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator|(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)|rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator^(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)^rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator<<(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)<<rhs.get()); } \
template<typename P> inline GO_CONSTEXPR _class_name_ operator>>(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(static_cast<_fundamental_type_>(lhs)>>rhs.get()); }

#define GO_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
template<typename P> inline GO_CONSTEXPR _class_name_ operator%(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return _class_name_(std::fmod(static_cast<_fundamental_type_>(lhs), rhs.get())); }

#if defined(GO_COMP_CLANG) || defined(GO_COMP_GCC) || defined(GO_COMP_GCC_MINGW)
#define GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
template<typename P> inline GO_CONSTEXPR bool operator==(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)==rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator!=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)!=rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator<(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)<rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator<=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)<=rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator>(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)>rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator>=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)>=rhs.get(); }
#else
#define GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
template<typename P> inline GO_CONSTEXPR bool operator==(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)==rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator!=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)!=rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator<(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)<rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator<=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)<=rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator>(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)>rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator>=(const P& lhs, const _class_name_& rhs) GO_NOEXCEPT_OR_NOTHROW { return static_cast<_fundamental_type_>(lhs)>=rhs.get(); } \
template<typename P> inline GO_CONSTEXPR bool operator==(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()==static_cast<_fundamental_type_>(rhs); } \
template<typename P> inline GO_CONSTEXPR bool operator!=(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()!=static_cast<_fundamental_type_>(rhs); } \
template<typename P> inline GO_CONSTEXPR bool operator<(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()<static_cast<_fundamental_type_>(rhs); } \
template<typename P> inline GO_CONSTEXPR bool operator<=(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()<=static_cast<_fundamental_type_>(rhs); } \
template<typename P> inline GO_CONSTEXPR bool operator>(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()>static_cast<_fundamental_type_>(rhs); } \
template<typename P> inline GO_CONSTEXPR bool operator>=(const _class_name_& lhs, const P& rhs) GO_NOEXCEPT_OR_NOTHROW { return lhs.get()>=static_cast<_fundamental_type_>(rhs); }
#endif  // #if defined(GO_COMP_CLANG) || defined(GO_COMP_GCC) || defined(GO_COMP_GCC_MINGW)

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
GO_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ )

#define GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
GO_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ )

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _fundamental_type_ ) \
class _class_name_ \
    : public go::type_traits::fundamental_type_implicit_specializer<_fundamental_type_> \
{ \
public: \
    virtual ~_class_name_() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ ) \
    GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _fundamental_type_ ) \
GO_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS(_class_name_, _fundamental_type_) \
GO_IMPLEMENT_OUTSIDE_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _fundamental_type_ )

namespace go
{
namespace type_traits
{

template<typename T>
class fundamental_type_implicit_specializer
    : public fundamental_type_specializer<T>
{
public:
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef fundamental_type_implicit_specializer<T> this_type;
    typedef fundamental_type_specializer<T> base_type;
    typedef T value_type;
#else
    using this_type = fundamental_type_implicit_specializer<T>;
    using base_type = fundamental_type_specializer<T>;
    using value_type = T;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)

    virtual ~fundamental_type_implicit_specializer() GO_NOEXCEPT = 0;

protected:
    fundamental_type_implicit_specializer(const fundamental_type_implicit_specializer& t) GO_NOEXCEPT_OR_NOTHROW
        : fundamental_type_specializer<T>(t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    fundamental_type_implicit_specializer(fundamental_type_implicit_specializer&& t) GO_NOEXCEPT_OR_NOTHROW
        : fundamental_type_specializer<T>(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_implicit_specializer(const value_type& t) GO_NOEXCEPT_OR_NOTHROW
        : fundamental_type_specializer<T>(t)
    {
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    explicit fundamental_type_implicit_specializer(value_type&& t) GO_NOEXCEPT_OR_NOTHROW
        : fundamental_type_specializer<T>(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    fundamental_type_implicit_specializer& operator=(const fundamental_type_implicit_specializer& t) GO_NOEXCEPT_OR_NOTHROW
    {
        if (&t != this)
        {
            fundamental_type_specializer<T>::operator=(t);
        }
        return *this;
    }

public:
    GO_CONSTEXPR operator const value_type&() const GO_NOEXCEPT_OR_NOTHROW
    {
        return fundamental_type_specializer<T>::get();
    }

    operator value_type&() GO_NOEXCEPT_OR_NOTHROW
    {
        return fundamental_type_specializer<T>::get();
    }
};

template<typename T>
inline fundamental_type_implicit_specializer<T>::~fundamental_type_implicit_specializer() GO_NOEXCEPT
{
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_TYPE_TRAITS_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
