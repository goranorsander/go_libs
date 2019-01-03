#ifndef GO_PROPERTY_EXCEPTION_HPP_INCLUDED
#define GO_PROPERTY_EXCEPTION_HPP_INCLUDED

//
//  exception.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/exception.hpp>

namespace go
{
namespace property
{

class exception
    : public go::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    explicit exception(const char* message) GO_NOEXCEPT_OR_NOTHROW;
    explicit exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW;
};

inline exception::exception(const char* message) GO_NOEXCEPT_OR_NOTHROW
    : go::exception::exception(message)
{
}

inline exception::exception(const std::string& message) GO_NOEXCEPT_OR_NOTHROW
    : go::exception::exception(message)
{
}

}
}

#endif  // #ifndef GO_PROPERTY_EXCEPTION_HPP_INCLUDED
