#ifndef GO_EXCEPTION_EXCEPTION_HPP_INCLUDED
#define GO_EXCEPTION_EXCEPTION_HPP_INCLUDED

//
//  exception.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <exception>
#include <string>

namespace go
{
namespace exception
{

class exception
    : public std::exception
{
public:
    GO_USING(this_type, exception);

public:
    virtual ~exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    exception() GO_NOEXCEPT_OR_NOTHROW;
    exception(const exception& other) GO_NOEXCEPT_OR_NOTHROW;
    explicit exception(const char* message) GO_NOEXCEPT_OR_NOTHROW;
    explicit exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW;

public:
    exception& operator=(const exception& other) GO_NOEXCEPT_OR_NOTHROW;

public:

    virtual const char* what() const GO_NOEXCEPT_OR_NOTHROW GO_OVERRIDE;

    virtual std::string message() const GO_NOEXCEPT_OR_NOTHROW;

private:
    std::string _message;
};

inline exception::exception() GO_NOEXCEPT_OR_NOTHROW
    : std::exception()
    , _message()
{
}

inline exception::exception(const exception& other) GO_NOEXCEPT_OR_NOTHROW
    : std::exception(other)
    , _message(other._message)
{
}

inline exception::exception(const char* message) GO_NOEXCEPT_OR_NOTHROW
    : std::exception()
    , _message(message)
{
}

inline exception::exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW
    : std::exception()
    , _message(message)
{
}

inline exception& exception::operator=(const exception& other) GO_NOEXCEPT_OR_NOTHROW
{
    if(this != &other)
    {
        std::exception::operator=(other);
        _message = other._message;
    }
    return *this;
}

inline const char* exception::what() const GO_NOEXCEPT_OR_NOTHROW
{
    return _message.c_str();
}

inline std::string exception::message() const GO_NOEXCEPT_OR_NOTHROW
{
    return _message;
}

} // namespace exception
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_EXCEPTION_EXCEPTION_HPP_INCLUDED
