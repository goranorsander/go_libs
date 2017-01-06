#ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  command_parameters.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>
#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace mvvm
{

class command_parameters
    : public go::utility::noncopyable_nonmovable
{
public:
    typedef command_parameters this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~command_parameters() GO_DEFAULT_DESTRUCTOR

protected:
    command_parameters() = default;

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() : this_type() {}
        };

        return std::make_shared<make_shared_enabler>();
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
