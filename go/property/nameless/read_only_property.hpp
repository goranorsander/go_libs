#ifndef GO_PROPERTY_NAMELESS_READ_ONLY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_READ_ONLY_PROPERTY_HPP_INCLUDED

//
//  read_only_property.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/property/nameless/detail/arithmetic_comparison_operators.hpp>
#include <go/property/nameless/detail/read_only_property_base.hpp>
#include <go/property/policy/proxy.hpp>
#include <go/utility/placebo_mutex.hpp>
#include <go/utility/u8string.hpp>

namespace go
{
namespace property
{
namespace nameless
{
namespace read_only
{

template<class T, typename M = std::recursive_mutex> class property
    : public detail::property_base<T, policy::proxy<T, M>>
{
public:
    typedef T value_type;
    typedef M mutex_type;
    typedef property<value_type, mutex_type> this_type;
    typedef typename policy::proxy<value_type, mutex_type> policy_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    property()
        : detail::property_base<value_type, policy_type>(policy_type())
    {
    }

    explicit property(const get_function_signature& get_function)
        : detail::property_base<value_type, policy_type>(policy_type(get_function, nullptr))
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>

public:
    void getter(const get_function_signature& f)
    {
        const_cast<policy_type&>(detail::property_base<value_type, policy_type>::storage()).getter(f);
    }
};

GO_IMPLEMENT_DEFAULT_NAMELESS_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(property)

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_READ_ONLY_PROPERTY_HPP_INCLUDED
