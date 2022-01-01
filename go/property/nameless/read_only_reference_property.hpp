#ifndef GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  read_only_reference_property.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/async/placebo_lockable.hpp>
#include <go/property/nameless/detail/arithmetic_comparison_operators.hpp>
#include <go/property/nameless/detail/read_only_property_base.hpp>
#include <go/property/policy/reference.hpp>
#include <go/string/u8string.hpp>

namespace go
{
namespace property
{
namespace nameless
{
namespace read_only
{

template<class T, class L = std::recursive_mutex> class reference_property
    : public detail::property_base<T, policy::reference<T, L>>
{
public:
    using value_type = T;
    using lockable_type = L;
    using this_type = reference_property<value_type, lockable_type>;
    using policy_type = typename policy::reference<value_type, lockable_type>;

public:
    virtual ~reference_property() GO_DEFAULT_DESTRUCTOR

    explicit reference_property(const value_type& v)
        : detail::property_base<value_type, policy_type>(policy_type(const_cast<value_type&>(v)))
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>

public:
    void bind(value_type& v)
    {
        detail::property_base<value_type, policy_type>::storage().bind(v);
    }

    GO_CONSTEXPR bool empty() const
    {
        return detail::property_base<value_type, policy_type>::storage().empty();
    }

    void reset()
    {
        detail::property_base<value_type, policy_type>::storage().reset();
    }

    explicit GO_CONSTEXPR operator bool() const
    {
        return !empty();
    }

    GO_CONSTEXPR bool operator!() const
    {
        return empty();
    }
};

GO_IMPLEMENT_DEFAULT_NAMELESS_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(reference_property)

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
