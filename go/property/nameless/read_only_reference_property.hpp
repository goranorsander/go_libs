#ifndef GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  read_only_reference_property.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/property/nameless/detail/arithmetic_comparison_operators.hpp>
#include <go/property/nameless/detail/read_only_property_base.hpp>
#include <go/property/policy/reference.hpp>

namespace go
{
namespace property
{
namespace nameless
{
namespace read_only
{

template<class T> class reference_property
    : public detail::property_base<T, policy::reference<T>>
{
public:
    typedef T value_type;
    typedef reference_property<value_type> this_type;
    typedef typename policy::reference<value_type> policy_type;

public:
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~reference_property() GO_DEFAULT_DESTRUCTOR
#else
    virtual ~reference_property() GO_DEFAULT_DESTRUCTOR
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    explicit reference_property(const value_type& v)
        : detail::property_base<value_type, policy_type>(policy_type(const_cast<value_type&>(v)))
    {
    }

    bool empty() const
    {
        return detail::property_base<value_type, policy_type>::storage().empty();
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

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED