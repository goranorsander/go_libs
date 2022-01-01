#ifndef GO_BOOST_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED

//
//  file_writer.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/log_line.hpp>
#include <go_boost/string/string_cast.hpp>
#include <go_boost/type_traits/noncopyable_nonmovable.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <fstream>
#include <string>

namespace go_boost
{
namespace diagnostics
{
namespace log
{

template <class L, class O> class basic_file_writer;
typedef basic_file_writer<log_line, std::ofstream> file_writer;
typedef basic_file_writer<wlog_line, std::wofstream> wfile_writer;

template <class L, class O>
class basic_file_writer
    : go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef O out_file_stream_type;
    typedef basic_file_writer<L, O> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    virtual ~basic_file_writer() GO_BOOST_DEFAULT_DESTRUCTOR

    basic_file_writer(const string_type& log_directory, const string_type& log_file_name, boost::uint32_t log_file_roll_size_mb);

    void write(log_line_type& logline);

private:
    void roll_file();

private:
    const boost::uint32_t _log_file_roll_size_bytes;
    const string_type _name;
    boost::uint32_t _file_number;
    std::streamoff _bytes_written;
    boost::scoped_ptr<out_file_stream_type> _os;
};

template <>
inline void basic_file_writer<log_line, std::ofstream>::roll_file()
{
    if (this->_os.get() != GO_BOOST_NULLPTR)
    {
        this->_os->flush();
        this->_os->close();
    }

    this->_bytes_written = 0;
    this->_os.reset(new std::ofstream());
    std::string log_file_name = this->_name;
    log_file_name.append(".");
    log_file_name.append(boost::lexical_cast<std::string>(++(this->_file_number)));
    log_file_name.append(".txt");
    this->_os->open(log_file_name.c_str(), std::ofstream::out | std::ofstream::trunc);
}

template <>
inline void basic_file_writer<wlog_line, std::wofstream>::roll_file()
{
    if (this->_os.get() != GO_BOOST_NULLPTR)
    {
        this->_os->flush();
        this->_os->close();
    }

    this->_bytes_written = 0;
    this->_os.reset(new std::wofstream());
    std::string log_file_name = go_boost::string::string_cast<std::string>(this->_name);
    log_file_name.append(".");
    log_file_name.append(boost::lexical_cast<std::string>(++(this->_file_number)));
    log_file_name.append(".txt");
    this->_os->open(log_file_name.c_str(), std::wofstream::out | std::wofstream::trunc);
}

template <class L, class O>
inline void basic_file_writer<L, O>::roll_file()
{
}

template <>
inline basic_file_writer<log_line, std::ofstream>::basic_file_writer(const string_type& log_directory, const string_type& log_file_name, boost::uint32_t log_file_roll_size_mb)
    : _log_file_roll_size_bytes(log_file_roll_size_mb * 1024 * 1024)
    , _name(log_directory + log_file_name)
    , _file_number(0)
    , _bytes_written(0)
    , _os()
{
    this->roll_file();
}

template <>
inline basic_file_writer<wlog_line, std::wofstream>::basic_file_writer(const string_type& log_directory, const string_type& log_file_name, boost::uint32_t log_file_roll_size_mb)
    : _log_file_roll_size_bytes(log_file_roll_size_mb * 1024 * 1024)
    , _name(log_directory + log_file_name)
    , _file_number(0)
    , _bytes_written(0)
    , _os()
{
    this->roll_file();
}

template <>
inline void basic_file_writer<log_line, std::ofstream>::write(log_line_type& logline)
{
    GO_BOOST_TYPENAME out_file_stream_type::pos_type pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (static_cast<boost::uint32_t>(this->_bytes_written) > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

template <>
inline void basic_file_writer<wlog_line, std::wofstream>::write(log_line_type& logline)
{
    GO_BOOST_TYPENAME out_file_stream_type::pos_type pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (static_cast<boost::uint32_t>(this->_bytes_written) > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

template <class L, class O>
inline void basic_file_writer<L, O>::write(log_line_type& logline)
{
    typename out_file_stream_type::pos_type pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (this->_bytes_written > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
