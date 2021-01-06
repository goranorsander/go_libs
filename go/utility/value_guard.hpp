#ifndef GO_UTILITY_VALUE_GUARD_HPP_INCLUDED
#define GO_UTILITY_VALUE_GUARD_HPP_INCLUDED

//
//  value_guard.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/type_traits/noncopyable_nonmovable.hpp>

namespace go
{
namespace utility
{

template<class T> class value_guard
    : go::type_traits::noncopyable_nonmovable
{
public:
    typedef value_guard<T> this_type;
    typedef go::type_traits::noncopyable_nonmovable base_type;
    typedef T value_type;

public:
    virtual ~value_guard()
    {
        on_destroy();
    }

    value_guard(value_type& value, const value_type& new_value)
        : go::type_traits::noncopyable_nonmovable()
        , _old_value(new_value)
        , _value(value)
    {
        on_construction();
    }

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    value_guard(value_type& value, value_type&& new_value)
        : go::type_traits::noncopyable_nonmovable()
        , _old_value(std::forward<value_type>(new_value))
        , _value(value)
    {
        on_construction();
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

private:
    void on_construction()
    {
        std::swap(_old_value, _value);
    }

    void on_destroy()
    {
        std::swap(_old_value, _value);
    }

private:
    value_type _old_value;
    value_type& _value;
};

}
}

#endif  // #ifndef GO_UTILITY_VALUE_GUARD_HPP_INCLUDED
