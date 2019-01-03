#ifndef GO_MVVM_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>

namespace go
{
namespace mvvm
{

class object
    : public std::enable_shared_from_this<object>
{
public:
    typedef object this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~object() = 0;

protected:
    object() GO_DEFAULT_CONSTRUCTOR
};

inline object::~object()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBJECT_HPP_INCLUDED
