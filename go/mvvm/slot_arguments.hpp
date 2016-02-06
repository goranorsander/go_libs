#ifndef GO_MVVM_SLOT_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_SLOT_ARGUMENTS_HPP_INCLUDED

//
//  slot_arguments.hpp
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

class slot_arguments
{
public:
    typedef std::shared_ptr<slot_arguments> ptr;
    typedef std::weak_ptr<slot_arguments> wptr;

public:
    virtual ~slot_arguments() = 0
    {
    }

protected:
    slot_arguments()
    {
    }

private:
    slot_arguments(const slot_arguments&) = delete;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_SLOT_ARGUMENTS_HPP_INCLUDED
