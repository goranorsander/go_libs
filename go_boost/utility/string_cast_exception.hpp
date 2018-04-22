#ifndef GO_BOOST_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED

//
//  string_cast_exception.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/exception.hpp>

namespace go_boost
{
namespace utility
{

class string_cast_exception
    : public go_boost::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~string_cast_exception() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR

    explicit string_cast_exception(const char* message) BOOST_NOEXCEPT_OR_NOTHROW;
    explicit string_cast_exception(const std::string& message) BOOST_NOEXCEPT_OR_NOTHROW;
};

inline string_cast_exception::string_cast_exception(const char* message) BOOST_NOEXCEPT_OR_NOTHROW
    : go_boost::exception::exception(message)
{
}

inline string_cast_exception::string_cast_exception(const std::string& message) BOOST_NOEXCEPT_OR_NOTHROW
    : go_boost::exception::exception(message)
{
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_CAST_EXCEPTION_HPP_INCLUDED
