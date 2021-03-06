#ifndef GO_PROPERTY_NAMELESS_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED

//
//  write_only_property_base.hpp
//
//  Copyright 2015-2021 G�ran Orsander
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
namespace nameless
{
namespace write_only
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
    property_base(const property_base& v)
        : _s(v._s)
    {
    }

    explicit property_base(const storage_policy& s)
        : _s(s)
    {
    }

public:
    void operator()(const value_type& v)
    {
        set(v);
    }

private:
    this_type& operator=(const this_type& v) GO_NOEXCEPT_OR_NOTHROW; // = delete;

public:
    void set(const value_type& v)
    {
        _s.set(v);
    }

protected:
    storage_policy& storage()
    {
        return _s;
    }

    GO_CONSTEXPR const storage_policy& storage() const
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
} // namespace write_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_NAMELESS_DETAIL_WRITE_ONLY_PROPERTY_BASE_HPP_INCLUDED
