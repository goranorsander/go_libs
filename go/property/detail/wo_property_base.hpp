#ifndef GO_PROPERTY_WO_PROPERTY_BASE_HPP_INCLUDED
#define GO_PROPERTY_WO_PROPERTY_BASE_HPP_INCLUDED

//
//  wo_property_base.hpp
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

template<class V, class P, class S> class wo_property_base
{
public:
    typedef V value_type;
    typedef P storage_policy;
    typedef S string_type;
    typedef wo_property_base<value_type, storage_policy, string_type> this_type;

    virtual ~wo_property_base() = 0
    {
    }

protected:
    explicit wo_property_base(const storage_policy& s, const string_type& n)
        : _s(s)
        , _n(n)
    {
    }

public:
    void operator()(const value_type& v) 
    {
        set(v);
    }

private:
    this_type& operator=(const this_type& v)
    {
        throw std::logic_error(std::string("template<class V, class P, class S> class wo_property_base : assignment operator should not be used"))
    }

public:
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

#endif  // #ifndef GO_PROPERTY_WO_PROPERTY_BASE_HPP_INCLUDED
