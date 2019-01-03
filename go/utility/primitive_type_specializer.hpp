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

#include <cmath>

namespace go
{
namespace utility
{

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go::utility::primitive_type_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    _class_name_(_class_name_&& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(value_type&& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {}

#else

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go::utility::primitive_type_specializer<_primitive_type_>(_default_value_) {} \
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
    _class_name_ operator-() const { return _class_name_(-get()); } \
    _class_name_ operator+(const _class_name_& t) const { return _class_name_(get() + t.get()); } \
    _class_name_ operator-(const _class_name_& t) const { return _class_name_(get() - t.get()); } \
    _class_name_ operator*(const _class_name_& t) const { return _class_name_(get()*t.get()); } \
    _class_name_ operator/(const _class_name_& t) const { return _class_name_(get()/t.get()); }

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

#define GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
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

#endif  // #ifndef GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
