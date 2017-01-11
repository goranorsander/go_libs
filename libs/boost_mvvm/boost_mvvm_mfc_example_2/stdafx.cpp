//
//  stdafx.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"

#include <go_boost/config.hpp>

#if (BOOST_COMP_MSVC) && (BOOST_MSVC <= 1700)
#error Boost.Phoenix is not supported by this compiler
#endif  // Boost.Phoenix is not supported by this compiler
