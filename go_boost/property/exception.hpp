#ifndef GO_BOOST_PROPERTY_EXCEPTION_HPP_INCLUDED
#define GO_BOOST_PROPERTY_EXCEPTION_HPP_INCLUDED

//
//  exception.hpp
//
//  Copyright 2017 Göran Orsander
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
namespace property
{

class exception
    : public go_boost::exception::exception
{
public:
    typedef exception this_type;

public:
    virtual ~exception() BOOST_NOEXCEPT_OR_NOTHROW;

    explicit exception(const std::string& message);
};

inline exception::~exception() BOOST_NOEXCEPT_OR_NOTHROW
{
}

inline exception::exception(const std::string& message)
    : go_boost::exception::exception(message)
{
}

}
}

#endif  // #ifndef GO_BOOST_PROPERTY_EXCEPTION_HPP_INCLUDED
