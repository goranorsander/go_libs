#ifndef GO_PROPERTY_NAMELESS_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  reference_property.hpp
//
//  Copyright 2015-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/property/nameless/detail/arithmetic_comparison_operators.hpp>
#include <go/property/nameless/detail/property_base.hpp>
#include <go/property/policy/reference.hpp>
#include <go/utility/u8string.hpp>

namespace go
{
namespace property
{
namespace nameless
{

template<class T> class reference_property
    : public detail::property_base<T, policy::reference<T>>
{
public:
    typedef T value_type;
    typedef reference_property<value_type> this_type;
    typedef typename policy::reference<value_type> policy_type;

public:
    virtual ~reference_property() GO_DEFAULT_DESTRUCTOR

    reference_property()
        : detail::property_base<value_type, policy_type>(policy_type())
    {
    }

    explicit reference_property(const value_type& v)
        : detail::property_base<value_type, policy_type>(policy_type(v))
    {
    }

#include <go/property/detail/assignment_operator.hpp>

public:
    void bind(value_type& v)
    {
        detail::property_base<value_type, policy_type>::storage().bind(v);
    }

    bool empty() const
    {
        return detail::property_base<value_type, policy_type>::storage().empty();
    }

    void reset()
    {
        detail::property_base<value_type, policy_type>::storage().reset();
    }

    explicit operator bool() const
    {
        return !empty();
    }

    bool operator!() const
    {
        return empty();
    }
};

GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(reference_property, std::string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(reference_property, std::wstring)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(reference_property, utility::u8string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(reference_property, std::u16string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(reference_property, std::u32string)

} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_REFERENCE_PROPERTY_HPP_INCLUDED
