#ifndef GO_BOOST_UTILITY_STRING_DETAIL_SETUP_GLOBAL_LOCALE_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_SETUP_GLOBAL_LOCALE_HPP_INCLUDED

//
//  setup_global_locale.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/locale.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

inline void setup_global_locale()
{
    static bool global_locale_is_initialized = false;
    if (!global_locale_is_initialized)
    {
        boost::locale::generator generator;
        generator.locale_cache_enabled(true);
        const std::locale locale = generator.generate(boost::locale::util::get_system_locale());
        std::locale::global(locale);
        global_locale_is_initialized = true;
    }
}

}
}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_SETUP_GLOBAL_LOCALE_HPP_INCLUDED
