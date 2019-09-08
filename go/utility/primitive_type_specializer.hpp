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

namespace go
{
namespace utility
{

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
struct _class_name_##_tag {}; \
using _class_name_ = go::utility::primitive_type_specializer<_primitive_type_, _class_name_##_tag>;

template<typename PrimitiveType, class Tag>
class primitive_type_specializer
{
public:
    using this_type = primitive_type_specializer<PrimitiveType, Tag>;
    using primitive_type = PrimitiveType;
    using tag_type = Tag;
    using this_reference = this_type&;
    using this_const_reference = const this_type&;

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    using rvalue_reference = primitive_type&&;
    using this_rvalue_reference = this_type&&;

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

public:
    ~primitive_type_specializer() = default;

    primitive_type_specializer()
        : _t(static_cast<primitive_type>(0))
    {
    }

    primitive_type_specializer(this_const_reference t)
        : _t(t._t)
    {
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    primitive_type_specializer(this_rvalue_reference t)
        : _t(std::move(t._t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_specializer(const primitive_type& t)
        : _t(t)
    {
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_specializer(rvalue_reference t)
        : _t(std::move(t))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

public:
    // Assignment operators

    this_reference operator=(this_const_reference t)
    {
        if(&t != this)
        {
            this->_t = t._t;
        }
        return *this;
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    this_reference operator=(this_rvalue_reference t)
    {
        if (&t != this)
        {
            this->_t = std::move(t._t);
        }
        return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    this_reference operator+=(this_const_reference t)
    {
        this->_t += t._t;
        return *this;
    }

    this_reference operator-=(this_const_reference t)
    {
        this->_t -= t._t;
        return *this;
    }

    this_reference operator*=(this_const_reference t)
    {
        this->_t *= t._t;
        return *this;
    }

    this_reference operator/=(this_const_reference t)
    {
        this->_t /= t._t;
        return *this;
    }

    // Integer type assignment operators

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator%=(this_const_reference t)
    {
        this->_t %= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator&=(this_const_reference t)
    {
        this->_t &= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator|=(this_const_reference t)
    {
        this->_t |= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator^=(this_const_reference t)
    {
        this->_t ^= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator<<=(this_const_reference t)
    {
        this->_t <<= t._t;
        return *this;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_reference>::type operator>>=(this_const_reference t)
    {
        this->_t >>= t._t;
        return *this;
    }

    // Floating point type assignment operators

    template <typename F = PrimitiveType>
    typename std::enable_if<std::is_floating_point<F>::value, this_reference>::type operator%=(this_const_reference t)
    {
        this->_t = std::fmod(_t, t._t);
        return *this;
    }

    // Arithmetic operators

    this_type operator+() const
    {
        return this_type(+(this->_t));
    }

    this_type operator+(this_const_reference t) const
    {
        return this_type(this->_t + t._t);
    }

    this_type operator-(this_const_reference t) const
    {
        return this_type(this->_t - t._t);
    }

    this_type operator*(this_const_reference t) const
    {
        return this_type(this->_t*t._t);
    }

    this_type operator/(this_const_reference t) const
    {
        return this_type(this->_t/t._t);
    }

    // Signed integer and floating point type arithmetic operators

    template <typename S = PrimitiveType>
    typename std::enable_if<std::is_signed<S>::value, this_type>::type operator-() const
    {
        return this_type(-(this->_t));
    }

    // Integer type arithmetic operators

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator~() const
    {
        return this_type(~(this->_t));
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator%(this_const_reference t) const
    {
        return this_type(this->_t%t._t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator&(this_const_reference t) const
    {
        return this_type(this->_t&t._t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator|(this_const_reference t) const
    {
        return this_type(this->_t|t._t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator^(this_const_reference t) const
    {
        return this_type(this->_t^t._t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator<<(this_const_reference t) const
    {
        return this_type(this->_t<<t._t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, this_type>::type operator>>(this_const_reference t) const
    {
        return this_type(this->_t>>t._t);
    }

    // Floating point type arithmetic operators

    template <typename F = PrimitiveType>
    typename std::enable_if<std::is_floating_point<F>::value, this_type>::type operator%(this_const_reference t) const
    {
        return this_type(std::fmod(this->_t, t._t));
    }

    // Comparison operators

    GO_CONSTEXPR bool operator==(this_const_reference t) const
    {
        return this->_t == t._t;
    }

    GO_CONSTEXPR bool operator!=(this_const_reference t) const
    {
        return !operator==(t);
    }

    GO_CONSTEXPR bool operator<(this_const_reference t) const
    {
        return this->_t < t._t;
    }

    GO_CONSTEXPR bool operator<=(this_const_reference t) const
    {
        return this->_t <= t._t;
    }

    GO_CONSTEXPR bool operator>(this_const_reference t) const
    {
        return this->_t > t._t;
    }

    GO_CONSTEXPR bool operator>=(this_const_reference t) const
    {
        return this->_t >= t._t;
    }

    // Integer type logical operators

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator!() const
    {
        return !(this->_t);
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator&&(this_const_reference t) const
    {
        return this->_t && t._t;
    }

    template <typename I = PrimitiveType>
    typename std::enable_if<std::is_integral<I>::value, bool>::type operator||(this_const_reference t) const
    {
        return this->_t || t._t;
    }

    // Increment/decrement operators

    this_type operator++()
    {
        return this_type(++(this->_t));
    }

    this_type operator--()
    {
        return this_type(--(this->_t));
    }

    this_type operator++(int)
    {
        return this_type((this->_t)++);
    }

    this_type operator--(int)
    {
        return this_type((this->_t)--);
    }

public:
    GO_CONSTEXPR const primitive_type& get() const
    {
        return this->_t;
    }

    primitive_type& get()
    {
        return this->_t;
    }

    void set(const primitive_type& t)
    {
        this->_t = t;
    }

    void set(this_const_reference t)
    {
        this->_t = t._t;
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    void set(rvalue_reference t)
    {
        this->_t = std::move(t);
    }

    void set(this_rvalue_reference t)
    {
        this->_t = std::move(t._t);
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

private:
    primitive_type _t;
};

}
}

#else

GO_MESSAGE("Required C++11 feature is not supported by this compiler. Using C++03 implementation")

#define GO_NO_CXX11_PRIMITIVE_TYPE_SPECIALIZER 1

#include <cmath>

namespace go
{
namespace utility
{

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    _class_name_() : go::utility::primitive_type_specializer<_primitive_type_>(static_cast<_primitive_type_>(0)) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    _class_name_(_class_name_&& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(value_type&& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {}

#else

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    _class_name_() : go::utility::primitive_type_specializer<_primitive_type_>(static_cast<_primitive_type_>(0)) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {}

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) { if(&t != this) { go::utility::primitive_type_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) { get() /= t.get(); return *this; }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) { get() %= t.get(); return *this; } \
    _class_name_& operator&=(const _class_name_& t) { get() &= t.get(); return *this; } \
    _class_name_& operator|=(const _class_name_& t) { get() |= t.get(); return *this; } \
    _class_name_& operator^=(const _class_name_& t) { get() ^= t.get(); return *this; } \
    _class_name_& operator<<=(const _class_name_& t) { get() <<= t.get(); return *this; } \
    _class_name_& operator>>=(const _class_name_& t) { get() >>= t.get(); return *this; }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) { get() = std::fmod(get(), t.get()); return *this; }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator+() const { return _class_name_(+get()); } \
    _class_name_ operator+(const _class_name_& t) const { return _class_name_(get() + t.get()); } \
    _class_name_ operator-(const _class_name_& t) const { return _class_name_(get() - t.get()); } \
    _class_name_ operator*(const _class_name_& t) const { return _class_name_(get()*t.get()); } \
    _class_name_ operator/(const _class_name_& t) const { return _class_name_(get()/t.get()); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    _class_name_ operator-() const { return _class_name_(-get()); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator~() const { return _class_name_(~get()); } \
    _class_name_ operator%(const _class_name_& t) const { return _class_name_(get()%t.get()); } \
    _class_name_ operator&(const _class_name_& t) const { return _class_name_(get()&t.get()); } \
    _class_name_ operator|(const _class_name_& t) const { return _class_name_(get()|t.get()); } \
    _class_name_ operator^(const _class_name_& t) const { return _class_name_(get()^t.get()); } \
    _class_name_ operator<<(const _class_name_& t) const { return _class_name_(get()<<t.get()); } \
    _class_name_ operator>>(const _class_name_& t) const { return _class_name_(get()>>t.get()); }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator%(const _class_name_& t) const { return _class_name_(std::fmod(get(), t.get())); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_CONSTEXPR bool operator==(const _class_name_& t) const { return get() == t.get(); } \
    GO_CONSTEXPR bool operator!=(const _class_name_& t) const { return !operator==(t); } \
    GO_CONSTEXPR bool operator<(const _class_name_& t) const { return get() < t.get(); } \
    GO_CONSTEXPR bool operator<=(const _class_name_& t) const { return get() <= t.get(); } \
    GO_CONSTEXPR bool operator>(const _class_name_& t) const { return get() > t.get(); } \
    GO_CONSTEXPR bool operator>=(const _class_name_& t) const { return get() >= t.get(); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    _class_name_ operator!() const { return _class_name_(!get()); } \
    _class_name_ operator&&(const _class_name_& t) const { return _class_name_(get()&&t.get()); } \
    _class_name_ operator||(const _class_name_& t) const { return _class_name_(get()||t.get()); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
    _class_name_ operator++() { return _class_name_(++get()); } \
    _class_name_ operator--() { return _class_name_(--get()); } \
    _class_name_ operator++(int) { return _class_name_(get()++); } \
    _class_name_ operator--(int) { return _class_name_(get()--); }

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER( _class_name_, _primitive_type_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
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
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
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
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_UNARY_MINUS_OPERATOR_ARITHMETIC_OPERATOR( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

template<typename T>
class primitive_type_specializer
{
public:
    typedef primitive_type_specializer<T> this_type;
    typedef T value_type;

    virtual ~primitive_type_specializer() = 0;

protected:
    primitive_type_specializer(const primitive_type_specializer& t)
        : _t(t._t)
    {
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    primitive_type_specializer(primitive_type_specializer&& t)
        : _t(t._t)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_specializer(const value_type& t)
        : _t(t)
    {
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_specializer(value_type&& t)
        : _t(t)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    primitive_type_specializer& operator=(const primitive_type_specializer& t)
    {
        if(&t != this)
        {
            _t = t._t;
        }
        return *this;
    }

public:
    GO_CONSTEXPR const value_type& get() const
    {
        return _t;
    }

    value_type& get()
    {
        return _t;
    }

    void set(const value_type& t)
    {
        _t = t;
    }

    void set(const this_type& t)
    {
        _t = t._t;
    }

private:
    value_type _t;
};

template<typename T>
inline primitive_type_specializer<T>::~primitive_type_specializer()
{
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
