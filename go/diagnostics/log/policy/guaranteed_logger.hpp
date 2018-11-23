#ifndef GO_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED

//
//  guaranteed_logger.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/detail/queue_buffer.hpp>
#include <go/diagnostics/log/policy/logging_policy_interface.hpp>

namespace go
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
    virtual ~guaranteed_logger() = default;

    guaranteed_logger() = default;

private:
    virtual buffer_interface_pointer create_buffer() const override
    {
        return new go::diagnostics::log::detail::queue_buffer<log_line_type>();
    }
};

} // namespace policy
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED
