#ifndef GO_BOOST_TYPE_TRAITS_DETAIL_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_BASE_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_DETAIL_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_BASE_HPP_INCLUDED

//
//  fundamental_type_implicit_specializer_base.hpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if !(defined(GO_BOOST_NO_CXX11) || defined(GO_BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))

namespace go_boost
{
namespace type_traits
{
namespace detail
{

class fundamental_type_implicit_specializer_base
{
protected:
    ~fundamental_type_implicit_specializer_base() BOOST_NOEXCEPT GO_BOOST_DEFAULT_DESTRUCTOR
    fundamental_type_implicit_specializer_base() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_CONSTRUCTOR
};

}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_DETAIL_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_BASE_HPP_INCLUDED
