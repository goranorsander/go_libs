#ifndef GO_UTILITY_SANITY_HPP_INCLUDED
#define GO_UTILITY_SANITY_HPP_INCLUDED

//
//  sanity.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#if defined(WIN32) || defined(WINDOWS)

// __LOC__ : Line Of Code (see https://support.microsoft.com/en-us/kb/155196)
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)")"

#define BEGIN_DISABLE_WARNING(_warning_) \
__pragma(warning(push)) \
__pragma(warning(disable: _warning_)) \
__pragma(message("DISABLED WARNING " __STR1__(_warning_) " at " __LOC__))

#define DISABLE_WARNING(_warning_) \
__pragma(warning(disable: _warning_)) \
__pragma(message("DISABLED WARNING " __STR1__(_warning_) " at " __LOC__))

#define DISABLE_END_WARNING \
__pragma(warning(pop)) \
__pragma(message("RE-ENABLED WARNINGS at " __LOC__))

#else

#define BEGIN_DISABLE_WARNING(_warning_)
#define DISABLE_WARNING(_warning_)
#define DISABLE_END_WARNING

#endif

#endif  // #ifndef GO_UTILITY_SANITY_HPP_INCLUDED
