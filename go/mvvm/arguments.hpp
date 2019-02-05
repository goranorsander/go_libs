#ifndef GO_MVVM_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_ARGUMENTS_HPP_INCLUDED

//
//  arguments.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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

class arguments
    : public go::utility::noncopyable_nonmovable
{
public:
    typedef arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~arguments() = 0;

protected:
    arguments() GO_DEFAULT_CONSTRUCTOR
};

inline arguments::~arguments()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_ARGUMENTS_HPP_INCLUDED
