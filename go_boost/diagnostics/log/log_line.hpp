#ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_LINE_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_LOG_LINE_HPP_INCLUDED

//
//  log_line.hpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/decode.hpp>
#include <go_boost/diagnostics/log/detail/types.hpp>
#include <go_boost/diagnostics/log/log_level.hpp>
#include <go_boost/diagnostics/log/thread_id.hpp>
#include <go_boost/diagnostics/log/timestamp.hpp>
#include <go_boost/utility/min_max.hpp>

#include <boost/core/enable_if.hpp>
#include <boost/core/is_same.hpp>
#include <boost/shared_array.hpp>

#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
#include <boost/typeof/std/utility.hpp>
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)

#if defined(_MSC_VER) && (_MSC_VER <= 1800)
GO_BOOST_MSVC_BEGIN_SUPPRESS_WARNING(4351)
#endif

#define GO_BOOST_DIAGNOSTICS_LOG_SUPPORTED_TYPES \
      std::string::value_type   /* 0  */ \
    , std::wstring::value_type  /* 1  */ \
    , boost::uint16_t           /* 2  */ \
    , boost::uint32_t           /* 3  */ \
    , boost::uint64_t           /* 4  */ \
    , boost::int16_t            /* 5  */ \
    , boost::int32_t            /* 6  */ \
    , boost::int64_t            /* 7  */ \
    , float                     /* 8  */ \
    , double                    /* 9  */ \
    , bool                      /* 10 */ \
    , std_string_literal_type   /* 11 */ \
    , std_wstring_literal_type  /* 12 */ \
    , std::string::value_type*  /* 13 */ \
    , std::wstring::value_type* /* 14 */

namespace go_boost
{
namespace diagnostics
{
namespace log
{

template<class S, class O> class basic_log_line;
typedef basic_log_line<std::string, std::ostream> log_line;
typedef basic_log_line<std::wstring, std::wostream> wlog_line;

template<class S, class O>
class basic_log_line
{
public:
    typedef S string_type;
    typedef O out_stream_type;
    typedef basic_log_line<S, O> this_type;
    typedef typename S::value_type char_type;

    typedef detail::string_literal_t<char_type> string_literal_type;
    typedef detail::string_literal_t<std::string::value_type> std_string_literal_type;
    typedef detail::string_literal_t<std::wstring::value_type> std_wstring_literal_type;

#if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    typedef boost::fusion::tuple<GO_BOOST_DIAGNOSTICS_LOG_SUPPORTED_TYPES> supported_types_type;
#else
    typedef std::tuple<GO_BOOST_DIAGNOSTICS_LOG_SUPPORTED_TYPES> supported_types_type;
#endif  // #if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

public:
    virtual ~basic_log_line() GO_BOOST_DEFAULT_DESTRUCTOR

    basic_log_line(const log_level level, const char_type* file, const char_type* function, const boost::uint32_t line)
        : _bytes_used(0)
        , _buffer_size(sizeof(_stack_buffer))
        , _heap_buffer()
        , _stack_buffer()
    {
        encode<boost::int64_t>(static_cast<boost::int64_t>(timestamp_now()));
        encode<boost::thread::id>(this_thread_id());
        encode<string_literal_type>(string_literal_type(file));
        encode<string_literal_type>(string_literal_type(function));
        encode<boost::uint32_t>(line);
        encode<log_level>(level);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120))

    basic_log_line(basic_log_line&&) GO_BOOST_DEFAULT_CONSTRUCTOR

#else

    basic_log_line(basic_log_line&& other)
        : _bytes_used(0)
        , _buffer_size(0)
        , _heap_buffer()
        , _stack_buffer()
    {
        *this = std::move(other);
    }

#endif  // #if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120))
#else

    basic_log_line(const basic_log_line& other)
        : _bytes_used(other._bytes_used)
        , _buffer_size(other._buffer_size)
        , _heap_buffer(other._heap_buffer)
        , _stack_buffer()
    {
        memcpy(_stack_buffer, other._stack_buffer, sizeof(_stack_buffer));
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120))

    basic_log_line& operator=(basic_log_line&&) noexcept = default;

#else

    basic_log_line& operator=(basic_log_line&& other) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &other)
        {
            _heap_buffer.reset();
            _heap_buffer = std::move(other._heap_buffer);

            _bytes_used = other._bytes_used;
            _buffer_size = other._buffer_size;
            std::copy(std::begin(other._stack_buffer), std::end(other._stack_buffer), std::begin(_stack_buffer));

            other._bytes_used = 0;
            other._buffer_size = 0;
        }
        return *this;
    }

#endif  // #if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120))
#else

    basic_log_line& operator=(const basic_log_line& other) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &other)
        {
            _bytes_used = other._bytes_used;
            _buffer_size = other._buffer_size;
            _heap_buffer = other._heap_buffer;
            memcpy(_stack_buffer, other._stack_buffer, sizeof(_stack_buffer));
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    void stringify(out_stream_type& os)
    {
        char_type* b = !_heap_buffer ? _stack_buffer : _heap_buffer.get();
        const char_type* const end = b + _bytes_used;

        const boost::int64_t timestamp = *reinterpret_cast<boost::int64_t*>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(boost::int64_t));

        const boost::thread::id threadid = *reinterpret_cast<boost::thread::id*>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(boost::thread::id));

        const string_literal_type file = *reinterpret_cast<string_literal_type*>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_type));

        const string_literal_type function = *reinterpret_cast<string_literal_type *>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_type));

        const boost::uint32_t line = *reinterpret_cast<boost::uint32_t*>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(boost::uint32_t));

        const log_level loglevel = *reinterpret_cast<log_level*>(b);
        b = reinterpret_cast<char_type*>(reinterpret_cast<std::size_t>(b) + sizeof(log_level));

        format_timestamp(os, static_cast<timestamp_type>(timestamp));

        stringify(os, loglevel, threadid, file, function, line);
        stringify(os, b, end);

        os << std::endl;
        os.flush();
    }

    basic_log_line& operator<<(const std::string::value_type arg)
    {
        encode<std::string::value_type>(arg, detail::types_tuple_index<std::string::value_type, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const std::wstring::value_type arg)
    {
        encode<std::wstring::value_type>(arg, detail::types_tuple_index<std::wstring::value_type, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::int16_t arg)
    {
        encode<boost::int16_t>(arg, detail::types_tuple_index<boost::int16_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::uint16_t arg)
    {
        encode<boost::uint16_t>(arg, detail::types_tuple_index<boost::uint16_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::int32_t arg)
    {
        encode<boost::int32_t>(arg, detail::types_tuple_index<boost::int32_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::uint32_t arg)
    {
        encode<boost::uint32_t>(arg, detail::types_tuple_index<boost::uint32_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::int64_t arg)
    {
        encode<boost::int64_t>(arg, detail::types_tuple_index<boost::int64_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const boost::uint64_t arg)
    {
        encode<boost::uint64_t>(arg, detail::types_tuple_index<boost::uint64_t, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const float arg)
    {
        encode<float>(arg, detail::types_tuple_index<float, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const double arg)
    {
        encode<double>(arg, detail::types_tuple_index<double, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const bool arg)
    {
        encode<bool>(arg, detail::types_tuple_index<bool, supported_types_type>::value);
        return *this;
    }

    basic_log_line& operator<<(const std::string& arg)
    {
        static const out_stream_type* const s = GO_BOOST_NULLPTR;
        encode_c_string(arg.c_str(), arg.length(), s);
        return *this;
    }

    basic_log_line& operator<<(const std::wstring& arg)
    {
        static const out_stream_type* const s = GO_BOOST_NULLPTR;
        encode_c_string(arg.c_str(), arg.length(), s);
        return *this;
    }

    template <std::size_t N>
    basic_log_line& operator<<(const std::string::value_type(&arg)[N])
    {
        encode(std_string_literal_type(arg));
        return *this;
    }

    template <typename Arg>
    typename boost::enable_if<boost::is_same<Arg, const std::string::value_type*>, basic_log_line&>::type operator<<(const Arg& arg)
    {
        encode(arg);
        return *this;
    }

    template <typename Arg>
    typename boost::enable_if<boost::is_same<Arg, std::string::value_type*>, basic_log_line&>::type operator<<(const Arg& arg)
    {
        encode(arg);
        return *this;
    }

    template <std::size_t N>
    basic_log_line& operator<<(const std::wstring::value_type(&arg)[N])
    {
        encode(std_wstring_literal_type(arg));
        return *this;
    }

    template <typename Arg>
    typename boost::enable_if<boost::is_same<Arg, const std::wstring::value_type*>, basic_log_line&>::type operator<<(const Arg& arg)
    {
        encode(arg);
        return *this;
    }

    template <typename Arg>
    typename boost::enable_if<boost::is_same<Arg, std::wstring::value_type*>, basic_log_line&>::type operator<<(const Arg& arg)
    {
        encode(arg);
        return *this;
    }

private:
    char_type* buffer()
    {
        return !_heap_buffer ? &_stack_buffer[_bytes_used] : &(_heap_buffer.get())[_bytes_used];
    }

    template <typename Arg>
    void encode(const Arg arg)
    {
        *reinterpret_cast<Arg*>(buffer()) = arg;
        _bytes_used += sizeof(Arg);
    }

    template <typename Arg>
    void encode(const Arg arg, const boost::uint8_t type_id)
    {
        resize_buffer_if_needed(sizeof(Arg) + sizeof(boost::uint8_t));
        encode<boost::uint8_t>(type_id);
        encode<Arg>(arg);
    }

    void encode(const string_literal_type arg)
    {
        encode<string_literal_type>(arg, detail::types_tuple_index<string_literal_type, supported_types_type>::value);
    }

    void encode(std::string::value_type* arg);
    void encode(const std::string::value_type* arg);

    void encode_c_string(const std::string::value_type* arg, const std::size_t length, const std::ostream* const /*stream_selector*/)
    {
        if (length == 0)
            return;
        const std::size_t string_size = length + 1;
        resize_buffer_if_needed(1 + string_size);
        std::string::value_type* b = buffer();
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
        typedef detail::types_tuple_index<std::string::value_type*, this_type::supported_types_type> this_types_tuple_index;
        BOOST_AUTO(type_id, this_types_tuple_index::value);
#else
        auto type_id = detail::types_tuple_index<std::string::value_type*, this_type::supported_types_type>::value;
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
        *reinterpret_cast<boost::uint8_t*>(b++) = static_cast<boost::uint8_t>(type_id);
        memcpy(b, arg, string_size);
        _bytes_used += 1 + string_size;
    }

    void encode_c_string(const std::string::value_type* arg, const std::size_t length, const std::wostream* const stream_selector)
    {
        if (length == 0)
            return;
        const std::wstring sws = go_boost::string::string_cast<std::wstring>(std::string(arg));
        encode_c_string(sws.c_str(), sws.size(), stream_selector);
    }

    void encode(std::wstring::value_type* arg);
    void encode(const std::wstring::value_type* arg);

    void encode_c_string(const std::wstring::value_type* arg, const std::size_t length, const std::ostream* const stream_selector)
    {
        if (length == 0)
            return;
        const std::string mbs = go_boost::string::string_cast<std::string>(std::wstring(arg));
        encode_c_string(mbs.c_str(), mbs.size(), stream_selector);
    }

    void encode_c_string(const std::wstring::value_type* arg, const std::size_t length, const std::wostream* const /*stream_selector*/)
    {
        if (length == 0)
            return;
        const std::size_t string_size = (length + 1) * 2;
        resize_buffer_if_needed(1 + string_size);
        std::wstring::value_type* b = buffer();
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
        typedef detail::types_tuple_index<std::wstring::value_type*, this_type::supported_types_type> this_types_tuple_index;
        BOOST_AUTO(type_id, this_types_tuple_index::value);
#else
        auto type_id = detail::types_tuple_index<std::wstring::value_type*, this_type::supported_types_type>::value;
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
        *reinterpret_cast<boost::uint8_t*>(b++) = static_cast<boost::uint8_t>(type_id);
        memcpy(b, arg, string_size);
        _bytes_used += 1 + string_size;
    }

    void resize_buffer_if_needed(const std::size_t additional_bytes)
    {
        const std::size_t required_size = _bytes_used + additional_bytes;

        if (required_size <= _buffer_size)
            return;

        if (!_heap_buffer)
        {
            _buffer_size = go_boost::utility::max_of(static_cast<std::size_t>(512), required_size);
            _heap_buffer.reset(new char_type[_buffer_size]);
            memcpy(_heap_buffer.get(), _stack_buffer, _bytes_used);
            return;
        }
        else
        {
            _buffer_size = go_boost::utility::max_of(static_cast<std::size_t>(2 * _buffer_size), required_size);
            boost::shared_array<char_type> new_heap_buffer(new char_type[_buffer_size]);
            memcpy(new_heap_buffer.get(), _heap_buffer.get(), _bytes_used);
            _heap_buffer.swap(new_heap_buffer);
        }
    }

    void stringify(out_stream_type& os, const log_level& loglevel, const boost::thread::id& threadid, const string_literal_type& file, const string_literal_type& function, const boost::uint32_t line) const;

    void stringify(out_stream_type& os, char_type* start, const char_type* const end)
    {
        if (start == end)
            return;

        const std::size_t type_id = static_cast<std::size_t>(*start);
        ++start;

#if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#define GO_BOOST_TUPLE_ELEMENT_TYPE boost::fusion::tuple_element
#else
#define GO_BOOST_TUPLE_ELEMENT_TYPE std::tuple_element
#endif  // #if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

        switch (type_id)
        {
        case 0:  // std::string::value_type
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<0, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 1:  // std::wstring::value_type
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<1, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 2:  // boost::uint16_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<2, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 3:  // boost::uint32_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<3, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 4:  // boost::uint64_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<4, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 5:  // boost::int16_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<5, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 6:  // boost::int32_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<6, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 7:  // boost::int64_t
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<7, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 8:  // float
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<8, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 9:  // double
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<9, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 10: // bool
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<10, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 11: // std_string_literal_type
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<11, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 12: // std_wstring_literal_type
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<12, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 13: // std::string::value_type*
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<13, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        case 14: // std::wstring::value_type*
            stringify(os, detail::decode(os, start, static_cast<GO_BOOST_TUPLE_ELEMENT_TYPE<14, supported_types_type>::type*>(GO_BOOST_NULLPTR)), end);
            return;
        }

#undef GO_BOOST_TUPLE_ELEMENT_TYPE

    }

private:
    typedef boost::shared_array<char_type> heap_buffer_type;

    std::size_t _bytes_used;
    std::size_t _buffer_size;
    heap_buffer_type _heap_buffer;
    char_type _stack_buffer[256 - 2 * sizeof(std::size_t) - sizeof(heap_buffer_type) - 8 /* Reserved */];
};

template<>
inline void basic_log_line<std::string, std::ostream>::encode(std::string::value_type* arg)
{
    static const std::ostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, strlen(arg), s);
}

template<>
inline void basic_log_line<std::wstring, std::wostream>::encode(std::string::value_type* arg)
{
    static const std::wostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, strlen(arg), s);
}

template<>
inline void basic_log_line<std::string, std::ostream>::encode(std::wstring::value_type* arg)
{
    static const std::ostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, wcslen(arg), s);
}

template<>
inline void basic_log_line<std::wstring, std::wostream>::encode(std::wstring::value_type* arg)
{
    static const std::wostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, wcslen(arg), s);
}

template<>
inline void basic_log_line<std::string, std::ostream>::encode(const std::string::value_type* arg)
{
    static const std::ostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, strlen(arg), s);
}

template<>
inline void basic_log_line<std::wstring, std::wostream>::encode(const std::string::value_type* arg)
{
    static const std::wostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, strlen(arg), s);
}

template<>
inline void basic_log_line<std::string, std::ostream>::encode(const std::wstring::value_type* arg)
{
    static const std::ostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, wcslen(arg), s);
}

template<>
inline void basic_log_line<std::wstring, std::wostream>::encode(const std::wstring::value_type* arg)
{
    static const std::wostream* const s = GO_BOOST_NULLPTR;
    if (arg != GO_BOOST_NULLPTR)
        encode_c_string(arg, wcslen(arg), s);
}

template<>
inline void basic_log_line<std::string, std::ostream>::stringify(std::ostream& os, const log_level& loglevel, const boost::thread::id& threadid, const detail::string_literal_t<std::string::value_type>& file, const detail::string_literal_t<std::string::value_type>& function, const boost::uint32_t line) const
{
    os << '[' << to_string(loglevel) << ']'
        << '[' << threadid << ']'
        << '[' << file._s << ':' << function._s << ':' << line << "] ";
}

template<>
inline void basic_log_line<std::wstring, std::wostream>::stringify(std::wostream& os, const log_level& loglevel, const boost::thread::id& threadid, const detail::string_literal_t<std::wstring::value_type>& file, const detail::string_literal_t<std::wstring::value_type>& function, const boost::uint32_t line) const
{
    os << L'[' << to_wstring(loglevel) << L']'
        << L'[' << threadid << L']'
        << L'[' << file._s << L':' << function._s << L':' << line << L"] ";
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#if defined(_MSC_VER) && (_MSC_VER <= 1800)
GO_BOOST_MSVC_END_SUPPRESS_WARNING
#endif

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_LINE_HPP_INCLUDED
