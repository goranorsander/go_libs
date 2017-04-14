#ifndef GO_UTILITY_SCOPE_GUARD_HPP_INCLUDED
#define GO_UTILITY_SCOPE_GUARD_HPP_INCLUDED

//
//  scope_guard.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <functional>
#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace utility
{

class scope_guard
    : public noncopyable_nonmovable
{
public:
    typedef std::function<void()> on_scope_exit_function_type;

public:
    virtual ~scope_guard()
    {
        if(_on_scope_exit != nullptr)
        {
            _on_scope_exit();
        }
    }

    explicit scope_guard(const on_scope_exit_function_type& on_scope_exit)
        : noncopyable_nonmovable()
        , _on_scope_exit(nullptr)
    {
        set_on_scope_exit_function(on_scope_exit);
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
