#ifndef GO_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED
#define GO_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED

//
//  string_cast_exception.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/exception.hpp>

namespace go
{
namespace utility
{

class string_cast_exception
    : public go::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~string_cast_exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    explicit string_cast_exception(const std::string& message);
};

inline string_cast_exception::string_cast_exception(const std::string& message)
    : go::exception::exception(message)
{
}

}
}

#endif  // #ifndef GO_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED
