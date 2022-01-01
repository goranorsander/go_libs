#ifndef GO_UTILITY_SCOPE_GUARD_NEW_ARRAY_HPP_INCLUDED
#define GO_UTILITY_SCOPE_GUARD_NEW_ARRAY_HPP_INCLUDED

//
//  scope_guard_new_array.hpp
//
//  Copyright 2021-2022 Göran Orsander
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

template<class T> class scope_guard_new_array
    : public scope_guard
{
public:
    GO_USING(this_type, scope_guard_new_array);
    GO_USING(base_type, scope_guard);
    GO_USING(value_type, T);
    GO_USING(reference, T&);
    GO_USING(pointer, T*);
    GO_USING(size_type, size_t);

public:
    virtual ~scope_guard_new_array() GO_DEFAULT_DESTRUCTOR

    scope_guard_new_array(pointer px, const size_type size_)
        : scope_guard(GO_NULLPTR)
        , _size(size_)
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

    GO_CONSTEXPR value_type operator[](size_type i) const
    {
        return *(_px + (i * sizeof(value_type)));
    }

    reference operator[](size_type i)
    {
        return *(_px + (i * sizeof(value_type)));
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

    void reset()
    {
        on_destroy();
    }

    void reset(pointer px, const size_type size_)
    {
        on_destroy();
        _px = px;
        _size = size_;
    }

    GO_CONSTEXPR size_type size() const
    {
        return _size;
    }

private:
    void on_destroy()
    {
        if(_px != GO_NULLPTR)
        {
            delete [] _px;
            _px = GO_NULLPTR;
        }
    }

private:
    size_type _size;
    pointer _px;
};

}
}

#endif  // #ifndef GO_UTILITY_SCOPE_GUARD_NEW_ARRAY_HPP_INCLUDED
