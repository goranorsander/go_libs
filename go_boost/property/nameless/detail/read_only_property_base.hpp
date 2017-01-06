#ifndef GO_BOOST_PROPERTY_NAMELESS_DETAIL_READ_ONLY_PROPERTY_BASE_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_DETAIL_READ_ONLY_PROPERTY_BASE_HPP_INCLUDED

//
//  read_only_property_base.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace go_boost
{
namespace property
{
namespace nameless
{
namespace read_only
{
namespace detail
{

template<class V, class P> class property_base
{
public:
    typedef V value_type;
    typedef P storage_policy;
    typedef property_base<value_type, storage_policy> this_type;

    virtual ~property_base() = 0;

protected:
    explicit property_base(const storage_policy& s)
        : _s(s)
    {
    }

public:
    operator value_type() const
    {
        return get();
    }

    value_type operator()() const
    {
        return get();
    }

    value_type operator*() const
    {
        return get();
    }

private:
    this_type& operator=(const this_type& v)
    {
        throw std::logic_error(std::string("template<class V, class P, class S> class property_base : assignment operator should not be used"));
    }

public:
    value_type get() const
    {
        return _s.get();
    }

protected:
    const storage_policy& storage() const
    {
        return _s;
    }

private:
    storage_policy _s;
};

template<class V, class P>
inline property_base<V, P>::~property_base()
{
}

} // namespace detail
} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_DETAIL_READ_ONLY_PROPERTY_BASE_HPP_INCLUDED