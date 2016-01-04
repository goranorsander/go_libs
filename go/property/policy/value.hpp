#ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
#define GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED

//
//  value.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

//#include <boost/serialization/access.hpp>
//#include <boost/serialization/nvp.hpp>
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
    virtual ~value()
    {
    }

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
        std::recursive_mutex::scoped_lock lock(_property_guard);
        return _v;
    }

    void set(const value_type& v) 
    {
        std::recursive_mutex::scoped_lock lock(_property_guard);
        _v = v;
    }

private:
    //friend class boost::serialization::access;

    //template<class archive>
    //void serialize(archive& a, unsigned int file_version)
    //{
    //    std::recursive_mutex::scoped_lock lock(_property_guard);
    //    a & boost::serialization::make_nvp("value", _v);
    //}

private:
    mutable std::recursive_mutex _property_guard;
    value_type _v;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
