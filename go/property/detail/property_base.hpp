#ifndef GO_PROPERTY_BASE_HPP_INCLUDED
#define GO_PROPERTY_BASE_HPP_INCLUDED

//
//  property_base.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

namespace go
{
namespace property
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

    virtual ~property_base() = 0
    {
    }

protected:
    explicit property_base(const storage_policy& s, const string_type& n)
        : _s(s)
        , _n(n)
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

    void operator()(const value_type& v) 
    {
        set(v);
    }

#include <go/property/detail/assignment_operator.hpp>

    value_type get() const
    {
        return _s.get();
    }

    void set(const value_type& v) 
    {
        _s.set(v);
    }

    string_type const& name() const
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

} // namespace detail
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_BASE_HPP_INCLUDED
