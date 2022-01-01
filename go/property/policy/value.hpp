#ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
#define GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED

//
//  value.hpp
//
//  Copyright 2015-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>

namespace go
{
namespace property
{
namespace policy
{

template<class T, class L> class value
{
public:
    GO_USING(value_type, T);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value<value_type, lockable_type> this_type;
#else
    using this_type = value<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

public:
    virtual ~value() GO_DEFAULT_DESTRUCTOR

    value() GO_DEFAULT_CONSTRUCTOR

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

    // cppcheck-suppress operatorEqVarError
    value& operator=(const value& v) GO_NOEXCEPT_OR_NOTHROW
    {
        if (&v != this)
        {
            _v = v._v;
        }
        return *this;
    }

    value_type get() const
    {
        const std::lock_guard<lockable_type> lock(_property_guard);
        return _v;
    }

    void set(const value_type& v)
    {
        const std::lock_guard<lockable_type> lock(_property_guard);
        _v = v;
    }

private:
    mutable lockable_type _property_guard;
    value_type _v;
};

} // namespace policy
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_POLICY_VALUE_HPP_INCLUDED
