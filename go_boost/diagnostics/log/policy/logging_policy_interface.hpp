#ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_LOGGING_POLICY_INTERFACE_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_POLICY_LOGGING_POLICY_INTERFACE_HPP_INCLUDED

//
//  logging_policy_interface.hpp
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

#include <go_boost/diagnostics/log/detail/buffer_interface.hpp>

#include <memory>

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class W> class basic_logger;

}
namespace policy
{

template <class W>
class logging_policy_interface
{
public:
    typedef W file_writer_type;
    typedef logging_policy_interface<W> this_type;

    typedef typename W::log_line_type log_line_type;
    typedef typename W::out_file_stream_type out_file_stream_type;
    typedef typename W::string_type string_type;
    typedef typename W::out_stream_type out_stream_type;
    typedef typename W::char_type char_type;
    typedef typename go_boost::diagnostics::log::detail::buffer_interface<log_line_type>* buffer_interface_pointer;

public:
    virtual ~logging_policy_interface() = 0;

protected:
    logging_policy_interface() GO_BOOST_DEFAULT_DESTRUCTOR

    virtual buffer_interface_pointer create_buffer() const = 0;

    friend class go_boost::diagnostics::log::detail::basic_logger<W>;
};

template <class W>
inline logging_policy_interface<W>::~logging_policy_interface()
{
}

} // namespace policy
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_POLICY_LOGGING_POLICY_INTERFACE_HPP_INCLUDED
