#ifndef GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
#define GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED

//
//  scope_guard_new.hpp
//
//  Copyright 2016-2018 Göran Orsander
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
    virtual ~scope_guard_new() GO_DEFAULT_DESTRUCTOR

    explicit scope_guard_new(pointer px)
        : scope_guard(nullptr)
        , _px(px)
    {
        set_on_scope_exit_function(on_scope_exit_function_type(std::bind(&this_type::on_destroy, this)));
    }

public:
    pointer operator->() const
    {
        return _px;
    }

    reference operator*() const
    {
        return *_px;
    }

    explicit operator bool() const
    {
        return _px != nullptr;
    }

public:
    pointer detach()
    {
        pointer px = _px;
        _px = nullptr;
        return px;
    }

    pointer get() const
    {
        return _px;
    }

private:
    void on_destroy()
    {
        if(_px != nullptr)
        {
            delete _px;
            _px = nullptr;
        }
    }

private:
    pointer _px;
};

}
}

#endif  // #ifndef GO_UTILITY_SCOPE_GUARD_NEW_HPP_INCLUDED
