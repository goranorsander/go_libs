#ifndef GO_BOOST_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
#define GO_BOOST_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED

//
//  write_only_property_base.hpp
//
//  Copyright 2015-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace property
{
namespace write_only
{
namespace detail
{

template<class V, class P, class S> class property_base
{
public:
    typedef V value_type;
    typedef P storage_policy;
    typedef S string_type;
    typedef property_base<value_type, storage_policy, string_type> this_type;

    virtual ~property_base() = 0;

protected:
    property_base(const storage_policy& s, const string_type& n)
        : _n(n)
        , _s(s)
    {
    }

public:
    void operator()(const value_type& v)
    {
        set(v);
    }

#include <go_boost/property/detail/assignment_operator.hpp>

public:
    void set(const value_type& v)
    {
        _s.set(v);
    }

    GO_BOOST_CONSTEXPR const string_type& name() const
    {
        return _n;
    }

protected:
    storage_policy& storage()
    {
        return _s;
    }

    GO_BOOST_CONSTEXPR const storage_policy& storage() const
    {
        return _s;
    }

private:
    const string_type _n;
    storage_policy _s;
};

template<class V, class P, class S>
inline property_base<V, P, S>::~property_base()
{
}

} // namespace detail
} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
