#ifndef GO_MVVM_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

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

#endif  // #ifndef GO_MVVM_OBJECT_HPP_INCLUDED
