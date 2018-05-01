#ifndef GO_BOOST_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
#define GO_BOOST_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED

//
//  primitive_type_specializer.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <cmath>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace utility
{

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go_boost::utility::primitive_type_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go_boost::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go_boost::utility::primitive_type_specializer<_primitive_type_>(t) {}

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) { if(&t != this) { go_boost::utility::primitive_type_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) { get() /= t.get(); return *this; }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) { get() %= t.get(); return *this; } \
    _class_name_& operator&=(const _class_name_& t) { get() &= t.get(); return *this; } \
    _class_name_& operator|=(const _class_name_& t) { get() |= t.get(); return *this; } \
    _class_name_& operator^=(const _class_name_& t) { get() ^= t.get(); return *this; } \
    _class_name_& operator<<=(const _class_name_& t) { get() <<= t.get(); return *this; } \
    _class_name_& operator>>=(const _class_name_& t) { get() >>= t.get(); return *this; }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    _class_name_& operator%=(const _class_name_& t) { get() = std::fmod(get(), t.get()); return *this; }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator+() const { return _class_name_(+get()); } \
    _class_name_ operator-() const { return _class_name_(-get()); } \
    _class_name_ operator+(const _class_name_& t) const { return _class_name_(get() + t.get()); } \
    _class_name_ operator-(const _class_name_& t) const { return _class_name_(get() - t.get()); } \
    _class_name_ operator*(const _class_name_& t) const { return _class_name_(get()*t.get()); } \
    _class_name_ operator/(const _class_name_& t) const { return _class_name_(get()/t.get()); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator~() const { return _class_name_(~get()); } \
    _class_name_ operator%(const _class_name_& t) const { return _class_name_(get()%t.get()); } \
    _class_name_ operator&(const _class_name_& t) const { return _class_name_(get()&t.get()); } \
    _class_name_ operator|(const _class_name_& t) const { return _class_name_(get()|t.get()); } \
    _class_name_ operator^(const _class_name_& t) const { return _class_name_(get()^t.get()); } \
    _class_name_ operator<<(const _class_name_& t) const { return _class_name_(get()<<t.get()); } \
    _class_name_ operator>>(const _class_name_& t) const { return _class_name_(get()>>t.get()); }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    _class_name_ operator%(const _class_name_& t) const { return _class_name_(std::fmod(get(), t.get())); }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    bool operator==(const _class_name_& t) const { return get() == t.get(); } \
    bool operator!=(const _class_name_& t) const { return !operator==(t); } \
    bool operator<(const _class_name_& t) const { return get() < t.get(); } \
    bool operator<=(const _class_name_& t) const { return get() <= t.get(); } \
    bool operator>(const _class_name_& t) const { return get() > t.get(); } \
    bool operator>=(const _class_name_& t) const { return get() >= t.get(); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    _class_name_ operator!() const { return _class_name_(!get()); } \
    _class_name_ operator&&(const _class_name_& t) const { return _class_name_(get()&&t.get()); } \
    _class_name_ operator||(const _class_name_& t) const { return _class_name_(get()||t.get()); }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
    _class_name_ operator++() { return _class_name_(++get()); } \
    _class_name_ operator--() { return _class_name_(--get()); } \
    _class_name_ operator++(int) { return _class_name_(get()++); } \
    _class_name_ operator--(int) { return _class_name_(get()--); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go_boost::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() {} \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
};

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go_boost::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() {} \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
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

    explicit primitive_type_specializer(const value_type& t)
        : _t(t)
    {
    }

    primitive_type_specializer& operator=(const primitive_type_specializer& t)
    {
        if(&t != this)
        {
            _t = t._t;
        }
        return *this;
    }

public:
    const value_type& get() const
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

#endif  // #ifndef GO_BOOST_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
