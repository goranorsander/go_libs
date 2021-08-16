#ifndef GO_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  write_only_value_property.hpp
//
//  Copyright 2015-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/property/nameless/detail/write_only_property_base.hpp>
#include <go/property/policy/value.hpp>

namespace go
{
namespace property
{
namespace nameless
{
namespace write_only
{

template<class T, class L = std::recursive_mutex> class value_property
    : public detail::property_base<T, policy::value<T, L>>
{
public:
    GO_USING(value_type, T);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_property<value_type, lockable_type> this_type;
    typedef typename policy::value<value_type, lockable_type> policy_type;
#else
    using this_type = value_property<value_type, lockable_type>;
    using policy_type = typename policy::value<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

public:
    virtual ~value_property() GO_DEFAULT_DESTRUCTOR

    value_property()
        : detail::property_base<value_type, policy_type>(policy_type())
    {
    }

    explicit value_property(const value_type& v)
        : detail::property_base<value_type, policy_type>(policy_type(v))
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
