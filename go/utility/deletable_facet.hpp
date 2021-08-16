#ifndef GO_UTILITY_DELETABLE_FACET_HPP_INCLUDED
#define GO_UTILITY_DELETABLE_FACET_HPP_INCLUDED

//
//  deletable_facet.hpp
//
//  Copyright 2017-2021 Göran Orsander
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

template<class Facet> struct deletable_facet
    : Facet
{
    GO_USING(facet_type, Facet);
    GO_USING(this_type, deletable_facet<facet_type>);

#if !defined(GO_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE)
    using Facet::Facet; // Inherit constructors
#endif  // #if !defined(GO_FACET_IS_NOT_A_MEMBER_OF_STD_CODECVT_ISSUE)

    ~deletable_facet() GO_DEFAULT_DESTRUCTOR
};

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_DELETABLE_FACET_HPP_INCLUDED
