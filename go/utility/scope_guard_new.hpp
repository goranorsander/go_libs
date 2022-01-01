#ifndef GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
#define GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED

//
//  scope_guard_new.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/utility/scope_guard.hpp>

namespace go
{
namespace utility
{

template<class T> class scope_guard_new
    : public scope_guard
{
public:
    GO_USING(this_type, scope_guard_new);
    GO_USING(base_type, scope_guard);
    GO_USING(value_type, T);
    GO_USING(reference, T&);
    GO_USING(pointer, T*);

public:
    virtual ~scope_guard_new() GO_DEFAULT_DESTRUCTOR

    explicit scope_guard_new(pointer px)
        : scope_guard(GO_NULLPTR)
        , _px(px)
    {
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        set_on_scope_exit_function(on_scope_exit_function_type(std::tr1::bind(&this_type::on_destroy, this)));
#else
        set_on_scope_exit_function(on_scope_exit_function_type(std::bind(&this_type::on_destroy, this)));
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    }

public:
    GO_CONSTEXPR pointer operator->() const
    {
        return _px;
    }

    GO_CONSTEXPR reference operator*() const
    {
        return *_px;
    }

#if !defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

    explicit GO_CONSTEXPR operator bool() const
    {
        return _px != GO_NULLPTR;
    }

#else

    GO_CONSTEXPR operator bool() const
    {
        return _px != GO_NULLPTR;
    }

#endif  // #if !defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

public:
    pointer detach()
    {
        pointer px = _px;
        _px = GO_NULLPTR;
        return px;
    }

    GO_CONSTEXPR pointer get() const
    {
        return _px;
    }

private:
    void on_destroy()
    {
        if(_px != GO_NULLPTR)
        {
            delete _px;
            _px = GO_NULLPTR;
        }
    }

private:
    pointer _px;
};

}
}

#endif  // #ifndef GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
