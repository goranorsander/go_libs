#ifndef GO_BOOST_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED

//
//  create_exception.hpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/exception.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{

class create_exception
    : public go_boost::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~create_exception() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR

    explicit create_exception(const char* message) BOOST_NOEXCEPT_OR_NOTHROW;
    explicit create_exception(const std::string& message) BOOST_NOEXCEPT_OR_NOTHROW;
};

inline create_exception::create_exception(const char* message) BOOST_NOEXCEPT_OR_NOTHROW
    : go_boost::exception::exception(message)
{
}

inline create_exception::create_exception(const std::string& message) BOOST_NOEXCEPT_OR_NOTHROW
    : go_boost::exception::exception(message)
{
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_CREATE_EXCEPTION_HPP_INCLUDED
