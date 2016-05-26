#ifndef GO_MVVM_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if (GO_COMP_MSVC) && (_MSC_VER <= 1800)
#pragma message("C++11/14 is not supported by this compiler")
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
    object()
        : std::enable_shared_from_this<object>()
    {
    }
};

inline object::~object()
{
}

} // namespace mvvm
} // namespace go

#endif // C++11/14 is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBJECT_HPP_INCLUDED
