#ifndef GO_BOOST_UTILITY_SANITY_HPP_INCLUDED
#define GO_BOOST_UTILITY_SANITY_HPP_INCLUDED

//
//  sanity.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(BOOST_COMP_MSVC)

// __LOC__ : Line Of Code (see https://support.microsoft.com/en-us/kb/155196)
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "(" __STR1__(__LINE__) ")"

#define GO_BOOST_BEGIN_DISABLE_WARNING(_warning_) \
__pragma(warning(push)) \
__pragma(warning(disable: _warning_)) \
__pragma(message("DISABLED WARNING " __STR1__(_warning_) " at " __LOC__))

#define GO_BOOST_DISABLE_WARNING(_warning_) \
__pragma(warning(disable: _warning_)) \
__pragma(message("DISABLED WARNING " __STR1__(_warning_) " at " __LOC__))

#define GO_BOOST_DISABLE_END_WARNING \
__pragma(warning(pop)) \
__pragma(message("RE-ENABLED WARNINGS at " __LOC__))

#else

#define GO_BOOST_BEGIN_DISABLE_WARNING(_warning_)
#define GO_BOOST_DISABLE_WARNING(_warning_)
#define GO_BOOST_DISABLE_END_WARNING

#endif  // #if defined(BOOST_COMP_MSVC)

#endif  // #ifndef GO_BOOST_UTILITY_SANITY_HPP_INCLUDED
