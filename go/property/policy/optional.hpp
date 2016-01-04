#ifndef GO_PROPERTY_POLICY_OPTIONAL_HPP_INCLUDED
#define GO_PROPERTY_POLICY_OPTIONAL_HPP_INCLUDED

//
//  optional.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

//#include <boost/optional.hpp>
//#include <boost/serialization/access.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/optional.hpp>
#include <mutex>

//namespace go
//{
//namespace property
//{
//namespace policy
//{
//
//template<class T> class optional
//{
//public:
//    typedef T value_type;
//    typedef optional<value_type> this_type;
//
//public:
//    virtual ~optional()
//    {
//    }
//
//    optional()
//        : _property_guard()
//        , _v()
//    {
//    }
//
//    explicit optional(const optional& v)
//        : _property_guard()
//        , _v(v._v)
//    {
//    }
//
//    explicit optional(const value_type& v) 
//        : _property_guard()
//        , _v(v)
//    {
//    }
//
//    value_type get() const 
//    {
//        std::recursive_mutex::scoped_lock lock(_property_guard);
//        return *_v;
//    }
//
//    void set(const value_type& v) 
//    {
//        std::recursive_mutex::scoped_lock lock(_property_guard);
//        _v = v;
//    }
//
//    bool empty() const
//    {
//        std::recursive_mutex::scoped_lock lock(_property_guard);
//        return !_v;
//    }
//
//    void clear()
//    {
//        std::recursive_mutex::scoped_lock lock(_property_guard);
//        _v.reset();
//    }
//
//private:
//    friend class boost::serialization::access;
//
//    template<class archive>
//    void serialize(archive& a, unsigned int file_version)
//    {
//        std::recursive_mutex::scoped_lock lock(_property_guard);
//        a & boost::serialization::make_nvp("value", _v);
//    }
//
//    mutable std::recursive_mutex _property_guard;
//    boost::optional<value_type> _v;
//};
//
//} // namespace policy
//} // namespace property
//} // namespace go

#endif  // #ifndef GO_PROPERTY_POLICY_OPTIONAL_HPP_INCLUDED
