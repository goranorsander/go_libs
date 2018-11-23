#ifndef GO_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED

//
//  non_guaranteed_logger.hpp
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

#include <go/diagnostics/log/detail/ring_buffer.hpp>
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
class non_guaranteed_logger
    : public logging_policy_interface<W>
{
public:
    typedef W file_writer_type;
    typedef non_guaranteed_logger<W> this_type;

    typedef typename W::log_line_type log_line_type;
    typedef typename W::out_file_stream_type out_file_stream_type;
    typedef typename W::string_type string_type;
    typedef typename W::out_stream_type out_stream_type;
    typedef typename W::char_type char_type;
    typedef typename logging_policy_interface<file_writer_type>::buffer_interface_pointer buffer_interface_pointer;

public:
    virtual ~non_guaranteed_logger() = default;

    non_guaranteed_logger(const uint32_t ring_buffer_size_mb)
        : logging_policy_interface<L>
        , _ring_buffer_size_mb(ring_buffer_size_mb)
    {
    }

private:
    virtual buffer_interface_pointer create_buffer() const override
    {
        return dynamic_cast<buffer_interface_pointer>(new go::diagnostics::log::detail::ring_buffer<log_line_type>(static_cast<std::size_t>(std::max(1u, _ring_buffer_size_mb) * 1024 * 4)));
    }

private:
    const uint32_t _ring_buffer_size_mb;
};

} // namespace policy
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED
