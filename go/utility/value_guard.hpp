#ifndef GO_UTILITY_VALUE_GUARD_HPP_INCLUDED
#define GO_UTILITY_VALUE_GUARD_HPP_INCLUDED

//
//  value_guard.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/utility/scope_guard.hpp>

namespace go
{
namespace utility
{

template<class T> class value_guard
    : public scope_guard
{
public:
    typedef value_guard<T> this_type;
    typedef T value_type;

public:
    virtual ~value_guard() GO_DEFAULT_DESTRUCTOR

    value_guard(value_type& value, const value_type& new_value)
        : scope_guard(nullptr)
        , _old_value(new_value)
        , _value(value)
    {
        on_construction();
    }

    value_guard(value_type& value, value_type&& new_value)
        : scope_guard(nullptr)
        , _old_value(std::forward<value_type>(new_value))
        , _value(value)
    {
        on_construction();
    }

private:
    void on_construction()
    {
        std::swap(_old_value, _value);
        set_on_scope_exit_function(on_scope_exit_function_type(std::bind(&this_type::on_destroy, this)));
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
