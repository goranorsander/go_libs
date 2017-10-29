#ifndef GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED
#define GO_UTILITY_PRIMITIVE_TYPE_SPECIALIZER_HPP_INCLUDED

//
//  primitive_type_specializer.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

namespace go
{
namespace utility
{

#define GO_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER( _class_name_, _primitive_type_, _default_value_ ) \
class _class_name_ \
    : public go::utility::primitive_type_specializer<_primitive_type_> \
{ \
public: \
    virtual ~_class_name_() GO_DEFAULT_DESTRUCTOR \
    _class_name_() : go::utility::primitive_type_specializer<_primitive_type_>(_default_value_) {} \
    _class_name_(const _class_name_& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    explicit _class_name_(const value_type& t) : go::utility::primitive_type_specializer<_primitive_type_>(t) {} \
    _class_name_& operator=(const _class_name_& t) { if(&t != this) { go::utility::primitive_type_specializer<_primitive_type_>::operator=(t); } return *this; } \
    _class_name_ operator+() const { return _class_name_(+get()); } \
    _class_name_ operator-() const { return _class_name_(-get()); } \
    _class_name_ operator+(const _class_name_& t) const { return _class_name_(get() + t.get()); } \
    _class_name_ operator-(const _class_name_& t) const { return _class_name_(get() - t.get()); } \
    _class_name_ operator*(const _class_name_& t) const { return _class_name_(get()*t.get()); } \
    _class_name_ operator/(const _class_name_& t) const { return _class_name_(get()/t.get()); } \
    bool operator==(const _class_name_& t) const { return get() == t.get(); } \
    bool operator!=(const _class_name_& t) const { return !operator==(t); } \
    bool operator<(const _class_name_& t) const { return get() < t.get(); } \
    bool operator<=(const _class_name_& t) const { return get() <= t.get(); } \
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
    operator const value_type&() const
    {
        return _t;
    }

    operator value_type&()
    {
        return _t;
    }

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
