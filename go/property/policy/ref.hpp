#ifndef GO_PROPERTY_POLICY_REF_HPP_INCLUDED
#define GO_PROPERTY_POLICY_REF_HPP_INCLUDED

//
//  ref.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <memory>
#include <mutex>

namespace go
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
        , _v(std::addressof(v))
    {
    }

    value_type get() const 
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        return *_v;
    }

    void set(const value_type& v) 
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        bind_ref(const_cast<value_type&>(v));
    }

    void bind_ref(value_type& v)
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        _v = std::addressof(v);
    }

    bool empty() const
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        return _v == NULL;
    }

    void clear()
    {
        std::lock_guard<std::recursive_mutex> lock(_property_guard);
        _v = NULL;
    }

private:
    mutable std::recursive_mutex _property_guard;
    value_type* _v;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_POLICY_REF_HPP_INCLUDED
