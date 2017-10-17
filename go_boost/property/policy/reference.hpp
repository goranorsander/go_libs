#ifndef GO_BOOST_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED
#define GO_BOOST_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED

//
//  reference.hpp
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

#include <boost/thread/recursive_mutex.hpp>
#include <boost/utility.hpp>
#include <go_boost/property/exception.hpp>

namespace go_boost
{
namespace property
{
namespace policy
{

template<class V> class reference
{
public:
    typedef V value_type;
    typedef reference<value_type> this_type;

public:
    virtual ~reference()
    {
    }

    reference()
        : _property_guard()
        , _v(NULL)
    {
    }

    explicit reference(const reference& v)
        : _property_guard()
        , _v(v._v)
    {
    }

    explicit reference(value_type& v)
        : _property_guard()
        , _v(boost::addressof(v))
    {
    }

    reference& operator=(const reference& v)
    {
        if (&v != this)
        {
            _v = v._v;
        }
        return *this;
    }

    reference& operator=(const value_type& v)
    {
        set(v);
        return *this;
    }

    value_type get() const
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        if (_v == NULL)
        {
            throw exception("Cannot get value to unbound reference property");
        }
        return *_v;
    }

    void set(const value_type& v)
    {
        if (_v == NULL)
        {
            throw exception("Cannot set value to unbound reference property");
        }
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        *_v = v;
    }

    void bind(value_type& v)
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        _v = boost::addressof(v);
    }

    bool empty() const
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        return _v == NULL;
    }

    void reset()
    {
        const boost::recursive_mutex::scoped_lock lock(_property_guard);
        _v = NULL;
    }

private:
    mutable boost::recursive_mutex _property_guard;
    value_type* _v;
};

} // namespace policy
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED
