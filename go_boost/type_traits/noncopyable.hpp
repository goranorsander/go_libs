#ifndef GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED

//
//  noncopyable_nonmovable.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/noncopyable.hpp>

namespace go_boost
{
namespace type_traits
{

typedef noncopyable boost::noncopyable;

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
