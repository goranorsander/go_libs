#ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED

//
//  non_guaranteed_logger.hpp
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

#include <go_boost/diagnostics/log/detail/ring_buffer.hpp>
#include <go_boost/diagnostics/log/policy/logging_policy_interface.hpp>
#include <go_boost/utility/min_max.hpp>
#include <boost/noncopyable.hpp>

namespace go_boost
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
    , boost::noncopyable
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
    virtual ~non_guaranteed_logger() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit non_guaranteed_logger(const std::size_t ring_buffer_size_mb)
        : logging_policy_interface<W>()
        , boost::noncopyable()
        , _ring_buffer_size_mb(ring_buffer_size_mb)
    {
    }

private:
    virtual buffer_interface_pointer create_buffer() const GO_BOOST_OVERRIDE
    {
        return dynamic_cast<buffer_interface_pointer>(new go_boost::diagnostics::log::detail::ring_buffer<log_line_type>(static_cast<std::size_t>(go_boost::utility::max_of(static_cast<std::size_t>(GO_BOOST_UL(1)), _ring_buffer_size_mb) * static_cast<std::size_t>(GO_BOOST_UL(1024) * GO_BOOST_UL(4)))));
    }

private:
    const std::size_t _ring_buffer_size_mb;
};

} // namespace policy
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_NON_GUARANTEED_LOGGER_HPP_INCLUDED
