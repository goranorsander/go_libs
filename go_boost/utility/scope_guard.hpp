#ifndef GO_BOOST_UTILITY_SCOPE_GUARD_HPP_INCLUDED
#define GO_BOOST_UTILITY_SCOPE_GUARD_HPP_INCLUDED

//
//  scope_guard.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace go_boost
{
namespace utility
{

class scope_guard
    : public boost::noncopyable
{
public:
    typedef boost::function<void()> on_scope_exit_function_type;

public:
    virtual ~scope_guard()
    {
        if(_on_scope_exit != NULL)
        {
            _on_scope_exit();
        }
    }

    explicit scope_guard(const on_scope_exit_function_type& on_scope_exit)
        : boost::noncopyable()
        , _on_scope_exit(NULL)
    {
        set_on_scope_exit_function(on_scope_exit);
    }

protected:
    void set_on_scope_exit_function(const on_scope_exit_function_type& on_scope_exit) BOOST_NOEXCEPT
    {
        _on_scope_exit = on_scope_exit;
    }

private:
    on_scope_exit_function_type _on_scope_exit;
};

}
}

#endif  // #ifndef GO_BOOST_UTILITY_SCOPE_GUARD_HPP_INCLUDED
