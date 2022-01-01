#ifndef GO_BOOST_TYPE_TRAITS_IDENTITY_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IDENTITY_HPP_INCLUDED

//
//  identity.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace type_traits
{

template <typename T> struct identity
{
    GO_BOOST_USING(type, T);
};

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IDENTITY_HPP_INCLUDED
