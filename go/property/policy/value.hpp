#ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
#define GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED

//
//  value.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>

namespace go
{
namespace property
{
namespace policy
{

template<class T> class value
{
public:
    typedef T value_type;
    typedef value<value_type> this_type;

public:
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~value() = default;
#else
	virtual ~value() {}
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    value() = default;
#else
	value() {}
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    explicit value(const value& v)
        : _property_guard()
        , _v(v._v)
    {
    }

    explicit value(const value_type& v)
        : _property_guard()
        , _v(v)
    {
    }

    value_type get() const
    {
        const std::lock_guard<std::recursive_mutex> lock(_property_guard);
        return _v;
    }

    void set(const value_type& v)
    {
        const std::lock_guard<std::recursive_mutex> lock(_property_guard);
        _v = v;
    }

private:
    mutable std::recursive_mutex _property_guard;
    value_type _v;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
