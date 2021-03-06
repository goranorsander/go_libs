#ifndef GO_BOOST_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
#define GO_BOOST_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED

//
//  scope_guard_new.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/bind/bind.hpp>
#include <boost/utility/explicit_operator_bool.hpp>
#include <go_boost/utility/scope_guard.hpp>

namespace go_boost
{
namespace utility
{

template<class T> class scope_guard_new
    : public scope_guard
{
public:
    typedef scope_guard_new<T> this_type;
    typedef scope_guard base_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;

public:
    virtual ~scope_guard_new() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit scope_guard_new(pointer px)
        : scope_guard(NULL)
        , _px(px)
    {
        set_on_scope_exit_function(on_scope_exit_function_type(boost::bind(&this_type::on_destroy, this)));
    }

public:
    GO_BOOST_CONSTEXPR pointer operator->() const BOOST_NOEXCEPT
    {
        return _px;
    }

    GO_BOOST_CONSTEXPR reference operator*() const BOOST_NOEXCEPT
    {
        return *_px;
    }

    GO_BOOST_CONSTEXPR bool operator!() const BOOST_NOEXCEPT
    {
        return _px == NULL;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL()

public:
    pointer detach() BOOST_NOEXCEPT
    {
        pointer px = _px;
        _px = NULL;
        return px;
    }

    GO_BOOST_CONSTEXPR pointer get() const BOOST_NOEXCEPT
    {
        return _px;
    }

private:
    void on_destroy()
    {
        if(_px != NULL)
        {
            delete _px;
            _px = NULL;
        }
    }

private:
    pointer _px;
};

}
}

#endif  // #ifndef GO_BOOST_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
