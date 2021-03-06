#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED

//
//  buffer_interface.hpp
//
//  Copyright 2018-2021 G�ran Orsander
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

template <class L>
class buffer_interface
{
public:
    typedef L log_line_type;
    typedef buffer_interface<L> this_type;

public:
    virtual ~buffer_interface() GO_BOOST_DEFAULT_DESTRUCTOR

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual void push(L&& logline) = 0;

#else

    virtual void push(const L& logline) = 0;

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual bool try_pop(L& logline) = 0;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED
