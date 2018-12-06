#ifndef GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED

//
//  file_writer.hpp
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

#include <go/diagnostics/log/log_line.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>
#include <go/utility/string_cast.hpp>

#include <fstream>
#include <string>

namespace go
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
    : go::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef O out_file_stream_type;
    typedef basic_file_writer<L, O> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    virtual ~basic_file_writer() = default;

    basic_file_writer(const string_type& log_directory, const string_type& log_file_name, uint32_t log_file_roll_size_mb)
        : _log_file_roll_size_bytes(log_file_roll_size_mb * 1024 * 1024)
        , _name(log_directory + log_file_name)
        , _os()
    {
        roll_file();
    }

    void write(log_line_type& logline)
    {
        auto pos = _os->tellp();
        logline.stringify(*_os);
        _bytes_written += _os->tellp() - pos;
        if (_bytes_written > _log_file_roll_size_bytes)
        {
            roll_file();
        }
    }

private:
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
    if (_os)
    {
        _os->flush();
        _os->close();
    }

    _bytes_written = 0;
    _os.reset(new std::ofstream());
    std::string log_file_name = _name;
    log_file_name.append(".");
    log_file_name.append(std::to_string(++_file_number));
    log_file_name.append(".txt");
    _os->open(log_file_name, std::ofstream::out | std::ofstream::trunc);
}

template <>
inline void basic_file_writer<wlog_line, std::wofstream>::roll_file()
{
    if (_os)
    {
        _os->flush();
        _os->close();
    }

    _bytes_written = 0;
    _os.reset(new std::wofstream());
    std::string log_file_name = go::utility::string_cast<std::string>(_name);
    log_file_name.append(".");
    log_file_name.append(std::to_string(++_file_number));
    log_file_name.append(".txt");
    _os->open(log_file_name, std::wofstream::out | std::wofstream::trunc);
}

template <class L, class O>
inline void basic_file_writer<L, O>::roll_file()
{
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_FILE_WRITER_HPP_INCLUDED
