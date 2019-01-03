#ifndef GO_PROPERTY_NAMELESS_WRITE_ONLY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_WRITE_ONLY_PROPERTY_HPP_INCLUDED

//
//  write_only_property.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/property/nameless/detail/write_only_property_base.hpp>
#include <go/property/policy/proxy.hpp>

namespace go
{
namespace property
{
namespace nameless
{
namespace write_only
{

template<class T, class L = std::recursive_mutex> class property
    : public detail::property_base<T, policy::proxy<T, L>>
{
public:
    typedef T value_type;
    typedef L lockable_type;
    typedef property<value_type, lockable_type> this_type;
    typedef typename policy::proxy<value_type, lockable_type> policy_type;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    property()
        : detail::property_base<value_type, policy_type>(policy_type())
    {
    }

    explicit property(const set_function_signature& set_function)
        : detail::property_base<value_type, policy_type>(policy_type(nullptr, set_function))
    {
    }

#include <go/property/detail/assignment_operator.hpp>

public:
    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().setter(f);
    }
};

} // namespace write_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_WRITE_ONLY_PROPERTY_HPP_INCLUDED
