#ifndef GO_BOOST_PROPERTY_POLICY_REF_HPP_INCLUDED
#define GO_BOOST_PROPERTY_POLICY_REF_HPP_INCLUDED

//
//  ref.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/thread/recursive_mutex.hpp>
#include <boost/utility.hpp>

namespace go_boost
{
namespace property
{
namespace policy
{

template<class T> class ref
{
public:
    typedef T value_type;
    typedef ref<value_type> this_type;

public:
    virtual ~ref()
    {
    }

    ref()
        : _property_guard()
        , _v(NULL)
    {
    }

    explicit ref(const ref& v)
        : _property_guard()
        , _v(v._v)
    {
    }

    explicit ref(value_type& v) 
        : _property_guard()
        , _v(boost::addressof(v))
    {
    }

    value_type get() const 
    {
        boost::recursive_mutex::scoped_lock lock(_property_guard);
        return *_v;
    }

    void set(const value_type& v) 
    {
        boost::recursive_mutex::scoped_lock lock(_property_guard);
        bind_ref(const_cast<value_type&>(v));
    }

    void bind_ref(value_type& v)
    {
        boost::recursive_mutex::scoped_lock lock(_property_guard);
        _v = boost::addressof(v);
    }

    bool empty() const
    {
        boost::recursive_mutex::scoped_lock lock(_property_guard);
        return _v == NULL;
    }

    void clear()
    {
        boost::recursive_mutex::scoped_lock lock(_property_guard);
        _v = NULL;
    }

private:
    mutable boost::recursive_mutex _property_guard;
    value_type* _v;
};

} // namespace policy
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_POLICY_REF_HPP_INCLUDED
