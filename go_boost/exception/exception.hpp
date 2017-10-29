#ifndef GO_BOOST_EXCEPTION_EXCEPTION_HPP_INCLUDED
#define GO_BOOST_EXCEPTION_EXCEPTION_HPP_INCLUDED

//
//  exception.hpp
//
//  Copyright 2016-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <exception>
#include <string>

namespace go_boost
{
namespace exception
{

class exception
    : public std::exception
{
public:
    typedef exception this_type;

public:
    virtual ~exception() GO_BOOST_DEFAULT_DESTRUCTOR

    exception(const exception& other);
    explicit exception(const char* message);
    explicit exception(const std::string& message);

public:
    exception& operator=(const exception& other);

public:
    virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW;

    virtual std::string message() const;

private:
    std::string _message;
};

inline exception::exception(const exception& other)
    : std::exception(other)
    , _message(other._message)
{
}

inline exception::exception(const char* message)
    : std::exception()
    , _message(message)
{
}

inline exception::exception(const std::string& message)
    : std::exception()
    , _message(message)
{
}

inline exception& exception::operator=(const exception& other)
{
    if(this != &other)
    {
        std::exception::operator=(other);
        _message = other._message;
    }
    return *this;
}

inline const char* exception::what() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return _message.c_str();
}

inline std::string exception::message() const
{
    return _message;
}

} // namespace exception
} // namespace go_boost

#endif  // #ifndef GO_BOOST_EXCEPTION_EXCEPTION_HPP_INCLUDED
