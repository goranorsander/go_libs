#ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED

//
//  guaranteed_logger.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/queue_buffer.hpp>
#include <go_boost/diagnostics/log/policy/logging_policy_interface.hpp>

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace policy
{

template <class W>
class guaranteed_logger
    : public logging_policy_interface<W>
{
public:
    typedef W file_writer_type;
    typedef guaranteed_logger<W> this_type;

    typedef typename W::log_line_type log_line_type;
    typedef typename W::out_file_stream_type out_file_stream_type;
    typedef typename W::string_type string_type;
    typedef typename W::out_stream_type out_stream_type;
    typedef typename W::char_type char_type;
    typedef typename logging_policy_interface<file_writer_type>::buffer_interface_pointer buffer_interface_pointer;

public:
    virtual ~guaranteed_logger() GO_BOOST_DEFAULT_DESTRUCTOR

    guaranteed_logger() GO_BOOST_DEFAULT_CONSTRUCTOR

private:
    virtual buffer_interface_pointer create_buffer() const GO_BOOST_OVERRIDE
    {
        return new go_boost::diagnostics::log::detail::queue_buffer<log_line_type>();
    }
};

} // namespace policy
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED
