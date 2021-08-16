#ifndef GO_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_POLICY_GUARANTEED_LOGGER_HPP_INCLUDED

//
//  guaranteed_logger.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/detail/queue_buffer.hpp>
#include <go/diagnostics/log/policy/logging_policy_interface.hpp>
#include <go/type_traits/noncopyable.hpp>

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
    , go::type_traits::noncopyable
{
public:
    using file_writer_type = W;
    using this_type = guaranteed_logger<W>;

    using log_line_type = typename W::log_line_type;
    using out_file_stream_type = typename W::out_file_stream_type;
    using string_type = typename W::string_type;
    using out_stream_type = typename W::out_stream_type;
    using char_type = typename W::char_type;
    using buffer_interface_pointer = typename logging_policy_interface<file_writer_type>::buffer_interface_pointer;

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
