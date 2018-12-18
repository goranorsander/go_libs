#ifndef GO_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
#define GO_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED

//
//  primitive_type_implicit_specializer.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/utility/primitive_type_specializer.hpp>

namespace go
{
namespace utility
{

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go::utility::primitive_type_implicit_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    _class_name_(_class_name_&& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(value_type&& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {}

#else

#define GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    _class_name_() : go::utility::primitive_type_implicit_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_implicit_specializer<_primitive_type_>(t) {}

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#define GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    _class_name_& operator=(const _class_name_& t) { if(&t != this) { go::utility::primitive_type_implicit_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_& operator+=(const _class_name_& t) { get() += t.get(); return *this; } \
    _class_name_& operator-=(const _class_name_& t) { get() -= t.get(); return *this; } \
    _class_name_& operator*=(const _class_name_& t) { get() *= t.get(); return *this; } \
    _class_name_& operator/=(const _class_name_& t) { get() /= t.get(); return *this; } \
    template<typename P> _class_name_& operator=(const P& p) { get() = static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator+=(const P& p) { get() += static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator-=(const P& p) { get() -= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator*=(const P& p) { get() *= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator/=(const P& p) { get() /= static_cast<_primitive_type_>(p); return *this; }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) { get() %= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator&=(const P& p) { get() &= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator|=(const P& p) { get() |= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator^=(const P& p) { get() ^= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator<<=(const P& p) { get() <<= static_cast<_primitive_type_>(p); return *this; } \
    template<typename P> _class_name_& operator>>=(const P& p) { get() >>= static_cast<_primitive_type_>(p); return *this; }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_& operator%=(const P& p) { get() = std::fmod(get(), static_cast<_primitive_type_>(p)); return *this; }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator+(const P& p) const { return _class_name_(get() + static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator-(const P& p) const { return _class_name_(get() - static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator*(const P& p) const { return _class_name_(get()*static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator/(const P& p) const { return _class_name_(get()/static_cast<_primitive_type_>(p)); }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator%(const P& p) const { return _class_name_(get()%static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator&(const P& p) const { return _class_name_(get()&static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator|(const P& p) const { return _class_name_(get()|static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator^(const P& p) const { return _class_name_(get()^static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator<<(const P& p) const { return _class_name_(get()<<static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator>>(const P& p) const { return _class_name_(get()>>static_cast<_primitive_type_>(p)); }

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator%(const P& p) const { return _class_name_(std::fmod(get(), static_cast<_primitive_type_>(p))); }

#define GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> GO_CONSTEXPR bool operator==(const P& p) const { return get() == static_cast<_primitive_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator!=(const P& p) const { return !operator==(static_cast<_primitive_type_>(p)); } \
    template<typename P> GO_CONSTEXPR bool operator<(const P& p) const { return get() < static_cast<_primitive_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator<=(const P& p) const { return get() <= static_cast<_primitive_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator>(const P& p) const { return get() > static_cast<_primitive_type_>(p); } \
    template<typename P> GO_CONSTEXPR bool operator>=(const P& p) const { return get() >= static_cast<_primitive_type_>(p); }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    template<typename P> _class_name_ operator&&(const P& p) const { return _class_name_(get()&&static_cast<_primitive_type_>(p)); } \
    template<typename P> _class_name_ operator||(const P& p) const { return _class_name_(get()||static_cast<_primitive_type_>(p)); }

#define GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator+(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)+rhs.get()); } \
template<typename P> inline _class_name_ operator-(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)-rhs.get()); } \
template<typename P> inline _class_name_ operator*(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)*rhs.get()); } \
template<typename P> inline _class_name_ operator/(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)/rhs.get()); }

#define GO_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator%(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)%rhs.get()); } \
template<typename P> inline _class_name_ operator&(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)&rhs.get()); } \
template<typename P> inline _class_name_ operator|(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)|rhs.get()); } \
template<typename P> inline _class_name_ operator^(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)^rhs.get()); } \
template<typename P> inline _class_name_ operator<<(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)<<rhs.get()); } \
template<typename P> inline _class_name_ operator>>(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)>>rhs.get()); }

#define GO_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator%(const P& lhs, const _class_name_& rhs) { return _class_name_(std::fmod(static_cast<_primitive_type_>(lhs), rhs.get())); }

#define GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
template<typename P> inline _class_name_ operator==(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)==rhs.get()); } \
template<typename P> inline _class_name_ operator!=(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)!=rhs.get()); } \
template<typename P> inline _class_name_ operator<(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)<rhs.get()); } \
template<typename P> inline _class_name_ operator<=(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)<=rhs.get()); } \
template<typename P> inline _class_name_ operator>(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)>rhs.get()); } \
template<typename P> inline _class_name_ operator>=(const P& lhs, const _class_name_& rhs) { return _class_name_(static_cast<_primitive_type_>(lhs)>=rhs.get()); }

#define GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go::utility::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_SPECIALIZER_LOGICAL_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER_LOGICAL_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_IMPLEMENT_OUTSIDE_INTEGER_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ )

#define GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go::utility::primitive_type_implicit_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_CONSTRUCTORS( _class_name_, _primitive_type_, _default_value_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ASSIGNMENT_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_COMPARISON_OPERATORS( _class_name_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ ) \
    GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER_INCREMENT_DECREMENT_OPERATORS( _class_name_ ) \
}; \
GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS( _class_name_, _primitive_type_ ) \
GO_IMPLEMENT_OUTSIDE_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER_ARITHMETIC_OPERATORS(_class_name_, _primitive_type_) \
GO_IMPLEMENT_OUTSIDE_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_COMPARISON_OPERATORS( _class_name_, _primitive_type_ )

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

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    primitive_type_implicit_specializer(primitive_type_implicit_specializer&& t)
        : primitive_type_specializer<T>(t)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_implicit_specializer(const value_type& t)
        : primitive_type_specializer<T>(t)
    {
    }

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    explicit primitive_type_implicit_specializer(value_type&& t)
        : primitive_type_specializer<T>(t)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

    primitive_type_implicit_specializer& operator=(const primitive_type_implicit_specializer& t)
    {
        if (&t != this)
        {
            primitive_type_specializer<T>::operator=(t);
        }
        return *this;
    }

public:
    GO_CONSTEXPR operator const value_type&() const
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

#endif  // #ifndef GO_UTILITY_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_HPP_INCLUDED
