#ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  command_parameters.hpp
//
//  Copyright 2015-2016 G�ran Orsander
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
#include <go/config.hpp>

namespace go
{
namespace mvvm
{

class command_parameters
{
public:
    typedef command_parameters this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~command_parameters()
    {
    }

protected:
    command_parameters()
    {
    }

private:
    command_parameters(const command_parameters&) = delete;

public:
    static ptr create()
    {
        return ptr(new this_type());
    }
};

} // namespace mvvm
} // namespace go

#endif // C++11/14 is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
