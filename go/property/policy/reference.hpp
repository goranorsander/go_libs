#ifndef GO_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED
#define GO_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED

//
//  reference.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>
#include <mutex>
#include <go/property/exception.hpp>

namespace go
{
namespace property
{
namespace policy
{

template<class T, class L> class reference
{
public:
    typedef T value_type;
    typedef L lockable_type;
    typedef reference<value_type, lockable_type> this_type;

public:
    virtual ~reference() GO_DEFAULT_DESTRUCTOR

    reference()
        : _property_guard()
        , _v(nullptr)
    {
    }

    explicit reference(const reference& v)
        : _property_guard()
        , _v(v._v)
    {
    }

    explicit reference(value_type& v)
        : _property_guard()
        , _v(std::addressof(v))
    {
    }

    reference& operator=(const reference& v) GO_NOEXCEPT_OR_NOTHROW
    {
        if (&v != this)
        {
            _v = v._v;
        }
        return *this;
    }

    reference& operator=(const value_type& v) GO_NOEXCEPT_OR_NOTHROW
    {
        set(v);
        return *this;
    }

    value_type get() const
    {
        if (_v == nullptr)
        {
            throw exception("Cannot get value to unbound reference property");
        }
        const std::lock_guard<lockable_type> lock(_property_guard);
        return *_v;
    }

    void set(const value_type& v)
    {
        if (_v == nullptr)
        {
            throw exception("Cannot set value to unbound reference property");
        }
        const std::lock_guard<lockable_type> lock(_property_guard);
        *_v = v;
    }

    void bind(value_type& v)
    {
        const std::lock_guard<lockable_type> lock(_property_guard);
        _v = std::addressof(v);
    }

    bool empty() const
    {
        const std::lock_guard<lockable_type> lock(_property_guard);
        return _v == nullptr;
    }

    void reset()
    {
        const std::lock_guard<lockable_type> lock(_property_guard);
        _v = nullptr;
    }

private:
    mutable lockable_type _property_guard;
    value_type* _v;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_POLICY_REFERENCE_HPP_INCLUDED
