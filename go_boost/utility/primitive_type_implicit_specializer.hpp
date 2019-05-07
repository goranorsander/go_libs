#ifndef GO_BOOST_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
#define GO_BOOST_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED

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

#include <go_boost/utility/primitive_type_specializer.hpp>

namespace go_boost
{
namespace utility
{

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go_boost::utility::primitive_type_implicit_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go_boost::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go_boost::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {}

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) { if(&t != this) { go_boost::utility::primitive_type_implicit_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) { get() /= t.get(); return *this; } \
    template<typename P> _class_name_& operator=(const P& p) { get() = static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator+=(const P& p) { get() += static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator-=(const P& p) { get() -= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator*=(const P& p) { get() *= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator/=(const P& p) { get() /= static_cast<_primitive_type_>(p); return *this; }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) { get() %= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator&=(const P& p) { get() &= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator|=(const P& p) { get() |= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator^=(const P& p) { get() ^= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator<<=(const P& p) { get() <<= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator>>=(const P& p) { get() >>= static_cast<_primitive_type_>(p); return *this; }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) { get() = std::fmod(get(), static_cast<_primitive_type_>(p)); return *this; }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator+(const P& p) const { return _class_name_(get() + static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator-(const P& p) const { return _class_name_(get() - static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator*(const P& p) const { return _class_name_(get()*static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator/(const P& p) const { return _class_name_(get()/static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator%(const P& p) const { return _class_name_(get()%static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator&(const P& p) const { return _class_name_(get()&static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator|(const P& p) const { return _class_name_(get()|static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator^(const P& p) const { return _class_name_(get()^static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator<<(const P& p) const { return _class_name_(get()<<static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator>>(const P& p) const { return _class_name_(get()>>static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator%(const P& p) const { return _class_name_(std::fmod(get(), static_cast<_primitive_type_>(p))); }

#define GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> bool operator==(const P& p) const { return get() == static_cast<_primitive_type_>(p); } \
    template<typename P> bool operator!=(const P& p) const { return !operator==(static_cast<_primitive_type_>(p)); } \
    template<typename P> bool operator<(const P& p) const { return get() < static_cast<_primitive_type_>(p); } \
    template<typename P> bool operator<=(const P& p) const { return get() <= static_cast<_primitive_type_>(p); } \
    template<typename P> bool operator>(const P& p) const { return get() > static_cast<_primitive_type_>(p); } \
    template<typename P> bool operator>=(const P& p) const { return get() >= static_cast<_primitive_type_>(p); }

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator&&(const P& p) const { return _class_name_(get()&&static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator||(const P& p) const { return _class_name_(get()||static_cast<_primitive_type_>(p)); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator+(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)+rhs.get()); } \
template<typename P> inline _class_name_ operator-(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)-rhs.get()); } \
template<typename P> inline _class_name_ operator*(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)*rhs.get()); } \
template<typename P> inline _class_name_ operator/(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)/rhs.get()); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator%(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)%rhs.get()); } \
template<typename P> inline _class_name_ operator&(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)&rhs.get()); } \
template<typename P> inline _class_name_ operator|(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)|rhs.get()); } \
template<typename P> inline _class_name_ operator^(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)^rhs.get()); } \
template<typename P> inline _class_name_ operator<<(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)<<rhs.get()); } \
template<typename P> inline _class_name_ operator>>(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)>>rhs.get()); }

#define GO_BOOST_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator%(const P& lhs, const _class_name_& rhs) { return _class_name_(std::fmod(static_cast<_primitive_type_>(lhs), rhs.get())); }

#if defined(GO_BOOST_COMP_GCC_MINGW)
#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline bool operator==(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)==rhs.get(); } \
template<typename P> inline bool operator!=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)!=rhs.get(); } \
template<typename P> inline bool operator<(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)<rhs.get(); } \
template<typename P> inline bool operator<=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)<=rhs.get(); } \
template<typename P> inline bool operator>(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)>rhs.get(); } \
template<typename P> inline bool operator>=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)>=rhs.get(); }
#else
#define GO_BOOST_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline bool operator==(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)==rhs.get(); } \
template<typename P> inline bool operator!=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)!=rhs.get(); } \
template<typename P> inline bool operator<(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)<rhs.get(); } \
template<typename P> inline bool operator<=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)<=rhs.get(); } \
template<typename P> inline bool operator>(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)>rhs.get(); } \
template<typename P> inline bool operator>=(const P& lhs, const _class_name_& rhs) { return static_cast<_primitive_type_>(lhs)>=rhs.get(); } \
template<typename P> inline bool operator==(const _class_name_& lhs, const P& rhs) { return lhs.get()==static_cast<_primitive_type_>(rhs); } \
template<typename P> inline bool operator!=(const _class_name_& lhs, const P& rhs) { return lhs.get()!=static_cast<_primitive_type_>(rhs); } \
template<typename P> inline bool operator<(const _class_name_& lhs, const P& rhs) { return lhs.get()<static_cast<_primitive_type_>(rhs); } \
template<typename P> inline bool operator<=(const _class_name_& lhs, const P& rhs) { return lhs.get()<=static_cast<_primitive_type_>(rhs); } \
template<typename P> inline bool operator>(const _class_name_& lhs, const P& rhs) { return lhs.get()>static_cast<_primitive_type_>(rhs); } \
template<typename P> inline bool operator>=(const _class_name_& lhs, const P& rhs) { return lhs.get()>=static_cast<_primitive_type_>(rhs); }
#endif  // #if defined(GO_BOOST_COMP_GCC_MINGW)

#define GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go_boost::utility::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
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

#define GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go_boost::utility::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
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

#define GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go_boost::utility::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_BOOST_DEFAULT_DESTRUCTOR \
    GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
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

template<typename T>
class primitive_type_implicit_specializer
    : public primitive_type_specializer<T>
{
public:
    typedef primitive_type_implicit_specializer<T> this_type;
    typedef primitive_type_specializer<T> base_type;
    typedef T value_type;

    virtual ~primitive_type_implicit_specializer() = 0;

protected:
    primitive_type_implicit_specializer(const primitive_type_implicit_specializer& t)
        : primitive_type_specializer<T>(t)
    {
    }

    explicit primitive_type_implicit_specializer(const value_type& t)
        : primitive_type_specializer<T>(t)
    {
    }

    primitive_type_implicit_specializer& operator=(const primitive_type_implicit_specializer& t)
    {
        if (&t != this)
        {
            primitive_type_specializer<T>::operator=(t);
        }
        return *this;
    }

public:
    operator const value_type&() const
    {
        return primitive_type_specializer<T>::get();
    }

    operator value_type&()
    {
        return primitive_type_specializer<T>::get();
    }
};

template<typename T>
inline primitive_type_implicit_specializer<T>::~primitive_type_implicit_specializer()
{
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
