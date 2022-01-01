#ifndef GO_UTILITY_SCOPE_GUARD_HPP_INCLUDED
#define GO_UTILITY_SCOPE_GUARD_HPP_INCLUDED

//
//  scope_guard.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/type_traits/noncopyable_nonmovable.hpp>

#include <functional>

namespace go
{
namespace utility
{

class scope_guard
    : go::type_traits::noncopyable_nonmovable
{
public:
    GO_USING(this_type, scope_guard);
    GO_USING(base_type, go::type_traits::noncopyable_nonmovable);

#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    typedef std::tr1::function<void()> on_scope_exit_function_type;
#else
    GO_USING(on_scope_exit_function_type, std::function<void()>);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)

public:
    virtual ~scope_guard()
    {
        if(_on_scope_exit != GO_NULLPTR)
        {
            _on_scope_exit();
        }
    }

    explicit scope_guard(const on_scope_exit_function_type& on_scope_exit)
        : go::type_traits::noncopyable_nonmovable()
        , _on_scope_exit(GO_NULLPTR)
    {
        set_on_scope_exit_function(on_scope_exit);
    }

protected:
    scope_guard()
        : go::type_traits::noncopyable_nonmovable()
        , _on_scope_exit(GO_NULLPTR)
    {
    }

protected:
    void set_on_scope_exit_function(const on_scope_exit_function_type& on_scope_exit)
    {
        _on_scope_exit = on_scope_exit;
    }

private:
    on_scope_exit_function_type _on_scope_exit;
};

}
}

#endif  // #ifndef GO_UTILITY_SCOPE_GUARD_HPP_INCLUDED
