#ifndef GO_PROPERTY_POLICY_PROXY_HPP_INCLUDED
#define GO_PROPERTY_POLICY_PROXY_HPP_INCLUDED

//
//  proxy.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <functional>
#include <mutex>
#include <stdexcept>

namespace go
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
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~proxy() = default;
#else
	virtual ~proxy() {}
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

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

    explicit proxy(const get_function_signature& get_function, const set_function_signature& set_function)
        : _property_guard()
        , _get(get_function)
        , _set(set_function)
    {
    }

    void getter(const get_function_signature& f)
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        _get = f;
    }

    void setter(const set_function_signature& f)
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        _set = f;
    }

    value_type get() const
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        return _get();
    }

    void set(const value_type& v)
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
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
    mutable std::recursive_mutex _property_guard;
    get_function_signature _get;
    set_function_signature _set;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_POLICY_PROXY_HPP_INCLUDED
