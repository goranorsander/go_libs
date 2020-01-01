#ifndef GO_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED

//
//  string_literal.hpp
//
//  Copyright 2018-2020 Göran Orsander
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

    ~string_literal_t() GO_DEFAULT_DESTRUCTOR

    explicit string_literal_t(const char_type* s)
        : _s(s)
    {
    }

    const char_type* _s;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_STRING_LITERAL_HPP_INCLUDED
