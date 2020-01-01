#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED

//
//  string_literal.hpp
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

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <typename C>
struct string_literal_t
{
    typedef C char_type;
    typedef string_literal_t<C> this_type;

    ~string_literal_t() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit string_literal_t(const char_type* s)
        : _s(s)
    {
    }

    const char_type* _s;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED
