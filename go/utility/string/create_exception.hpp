#ifndef GO_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED
#define GO_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED

//
//  create_exception.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/exception.hpp>

namespace go
{
namespace utility
{
namespace string
{

class create_exception
    : public go::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~create_exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    explicit create_exception(const char* message) GO_NOEXCEPT_OR_NOTHROW;
    explicit create_exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW;
};

inline create_exception::create_exception(const char* message) GO_NOEXCEPT_OR_NOTHROW
    : go::exception::exception(message)
{
}

inline create_exception::create_exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW
    : go::exception::exception(message)
{
}

}
}
}

#endif  // #ifndef GO_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED
