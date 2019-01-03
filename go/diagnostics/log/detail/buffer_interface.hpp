#ifndef GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED

//
//  buffer_interface.hpp
//
//  Copyright 2018-2019 Göran Orsander
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

template <class L>
class buffer_interface
{
public:
    typedef L log_line_type;
    typedef buffer_interface<L> this_type;

public:
    virtual ~buffer_interface() = default;

    virtual void push(L&& logline) = 0;
    virtual bool try_pop(L& logline) = 0;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_INTERFACE_HPP_INCLUDED
