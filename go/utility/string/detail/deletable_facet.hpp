#ifndef GO_UTILITY_STRING_DETAIL_DELETABLE_FACET_HPP_INCLUDED
#define GO_UTILITY_STRING_DETAIL_DELETABLE_FACET_HPP_INCLUDED

//
//  deletable_facet.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace utility
{
namespace string
{
namespace detail
{

template<class Facet> struct deletable_facet
    : Facet
{
    typedef Facet facet_type;
    typedef deletable_facet<facet_type> this_type;

#if !defined(GO_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE)
    using Facet::Facet; // inherit constructors
#endif  // #if !defined(GO_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE)

    ~deletable_facet() = default;
};

}
}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_DETAIL_DELETABLE_FACET_HPP_INCLUDED
