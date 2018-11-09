#ifndef GO_BOOST_PROPERTY_POLICY_VALUE_HPP_INCLUDED
#define GO_BOOST_PROPERTY_POLICY_VALUE_HPP_INCLUDED

//
//  value.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/thread/recursive_mutex.hpp>

namespace go_boost
{
namespace property
{
namespace policy
{

template<class V, typename M> class value
{
public:
    typedef V value_type;
    typedef M mutex_type;
    typedef value<value_type, mutex_type> this_type;

public:
    virtual ~value() GO_BOOST_DEFAULT_DESTRUCTOR

    value()
        : _property_guard()
        , _v()
    {
    }

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
        const typename mutex_type::scoped_lock lock(_property_guard);
        return _v;
    }

    void set(const value_type& v)
    {
        const typename mutex_type::scoped_lock lock(_property_guard);
        _v = v;
    }

private:
    mutable mutex_type _property_guard;
    value_type _v;
};

} // namespace policy
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_POLICY_VALUE_HPP_INCLUDED
