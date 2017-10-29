#ifndef GO_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED

//
//  property.hpp
//
//  Copyright 2015-2017 G�ran Orsander
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
#include <go/property/nameless/detail/property_base.hpp>
#include <go/property/policy/proxy.hpp>
#include <go/utility/u8string.hpp>

namespace go
{
namespace property
{
namespace nameless
{

template<class T> class property
    : public detail::property_base<T, policy::proxy<T>>
{
public:
    typedef T value_type;
    typedef property<value_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    property()
        : detail::property_base<value_type, policy_type>(policy_type())
    {
    }

    property(const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy_type>(policy_type(get_function, set_function))
    {
    }

#include <go/property/detail/assignment_operator.hpp>

public:
    void getter(const get_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().setter(f);
    }
};

GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(property, std::string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(property, std::wstring)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(property, utility::u8string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(property, std::u16string)
GO_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(property, std::u32string)

} // namespace nameless
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
