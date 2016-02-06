#ifndef GO_MVVM_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
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
    typedef std::shared_ptr<object> ptr;
    typedef std::weak_ptr<object> wptr;

public:
    virtual ~object() = 0
    {
    }

protected:
    object()
        : std::enable_shared_from_this<object>()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBJECT_HPP_INCLUDED
