#ifndef GO_BOOST_PROPERTY_POLICY_PROXY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_POLICY_PROXY_HPP_INCLUDED

//
//  proxy.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/function.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <stdexcept>

namespace go_boost
{
namespace property
{
namespace policy
{

template<class T> class proxy
{
public:
    typedef T value_type;
    typedef proxy<value_type> this_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~proxy()
    {
    }

    proxy()
        : _property_guard()
        , _get(&proxy<value_type>::default_get)
        , _set(&proxy<value_type>::default_set)
    {
    }

    explicit proxy(const proxy& v)
        : _property_guard()
        , _get(v._get)
        , _set(v._set)
    {
    }

    proxy(const get_function_signature& get_function, const set_function_signature& set_function)
        : _property_guard()
        , _get(get_function)
        , _set(set_function)
    {
    }

    void getter(const get_function_signature& f)
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        _get = f;
    }

    void setter(const set_function_signature& f)
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        _set = f;
    }

    value_type get() const
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        return _get();
    }

    void set(const value_type& v)
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        _set(v);
    }

private:
    static value_type default_get()
    {
        throw std::runtime_error("proxy getter not bound");
    }

    static void default_set(const value_type &)
    {
        throw std::runtime_error("proxy setter not bound");
    }

private:
    mutable boost::recursive_mutex _property_guard;
    get_function_signature _get;
    set_function_signature _set;
};

} // namespace policy
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_POLICY_PROXY_HPP_INCLUDED
