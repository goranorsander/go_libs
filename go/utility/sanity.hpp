#ifndef GO_UTILITY_SANITY_HPP_INCLUDED
#define GO_UTILITY_SANITY_HPP_INCLUDED

//
//  sanity.hpp
//
//  Copyright 2016 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

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

#endif  // #ifndef GO_UTILITY_SANITY_HPP_INCLUDED
