#ifndef GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED

//
//  file_writer.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/log_line.hpp>
#include <go/string/string_cast.hpp>
#include <go/type_traits/noncopyable_nonmovable.hpp>

#include <fstream>
#include <string>

namespace go
{
namespace diagnostics
{
namespace log
{

template <class L, class O> class basic_file_writer;
using file_writer = basic_file_writer<log_line, std::ofstream>;
using wfile_writer = basic_file_writer<wlog_line, std::wofstream>;

template <class L, class O>
class basic_file_writer
    : go::type_traits::noncopyable_nonmovable
{
public:
    using log_line_type = L;
    using out_file_stream_type = O;
    using this_type = basic_file_writer<L, O>;

    using string_type = typename L::string_type;
    using out_stream_type = typename L::out_stream_type;
    using char_type = typename L::char_type;

public:
    virtual ~basic_file_writer() = default;

    basic_file_writer(const string_type& log_directory, const string_type& log_file_name, uint32_t log_file_roll_size_mb);

    void write(log_line_type& logline);

private:
    // cppcheck-suppress functionStatic
    void roll_file();

private:
    const uint32_t _log_file_roll_size_bytes;
    const string_type _name;
    uint32_t _file_number = 0;
    std::streamoff _bytes_written = 0;
    std::unique_ptr<out_file_stream_type> _os;
};

template <>
inline void basic_file_writer<log_line, std::ofstream>::roll_file()
{
    if (this->_os)
    {
        this->_os->flush();
        this->_os->close();
    }

    this->_bytes_written = 0;
    this->_os.reset(new std::ofstream());
    std::string log_file_name = this->_name;
    log_file_name.append(".");
    log_file_name.append(std::to_string(++(this->_file_number)));
    log_file_name.append(".txt");
    this->_os->open(log_file_name, std::ofstream::out | std::ofstream::trunc);
}

template <>
inline void basic_file_writer<wlog_line, std::wofstream>::roll_file()
{
    if (this->_os)
    {
        this->_os->flush();
        this->_os->close();
    }

    this->_bytes_written = 0;
    this->_os.reset(new std::wofstream());
    std::string log_file_name = go::string::string_cast<std::string>(this->_name);
    log_file_name.append(".");
    log_file_name.append(std::to_string(++(this->_file_number)));
    log_file_name.append(".txt");
    this->_os->open(log_file_name, std::wofstream::out | std::wofstream::trunc);
}

template <class L, class O>
inline void basic_file_writer<L, O>::roll_file()
{
}

template <>
inline basic_file_writer<log_line, std::ofstream>::basic_file_writer(const string_type& log_directory, const string_type& log_file_name, uint32_t log_file_roll_size_mb)
    : _log_file_roll_size_bytes(log_file_roll_size_mb * 1024 * 1024)
    , _name(log_directory + log_file_name)
    , _os()
{
    this->roll_file();
}

template <>
inline basic_file_writer<wlog_line, std::wofstream>::basic_file_writer(const string_type& log_directory, const string_type& log_file_name, uint32_t log_file_roll_size_mb)
    : _log_file_roll_size_bytes(log_file_roll_size_mb * 1024 * 1024)
    , _name(log_directory + log_file_name)
    , _os()
{
    this->roll_file();
}

template <>
inline void basic_file_writer<log_line, std::ofstream>::write(log_line_type& logline)
{
    auto pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (this->_bytes_written > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

template <>
inline void basic_file_writer<wlog_line, std::wofstream>::write(log_line_type& logline)
{
    auto pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (this->_bytes_written > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

template <class L, class O>
inline void basic_file_writer<L, O>::write(log_line_type& logline)
{
    auto pos = this->_os->tellp();
    logline.stringify(*(this->_os));
    this->_bytes_written += this->_os->tellp() - pos;
    if (this->_bytes_written > this->_log_file_roll_size_bytes)
    {
        this->roll_file();
    }
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
