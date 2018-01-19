#ifndef GO_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
#define GO_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED

//
//  write_only_property_base.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
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
    property_base(const property_base& v)
        : _n(v._n)
        , _s(v._s)
    {
    }

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

#include <go/property/detail/assignment_operator.hpp>

public:
    void set(const value_type& v)
    {
        _s.set(v);
    }

    const string_type& name() const
    {
        return _n;
    }

protected:
    storage_policy& storage()
    {
        return _s;
    }

    const storage_policy& storage() const
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
} // namespace go

#endif  // #ifndef GO_PROPERTY_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
