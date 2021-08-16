#ifndef GO_MVVM_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_ARGUMENTS_HPP_INCLUDED

//
//  arguments.hpp
//
//  Copyright 2019-2021 Göran Orsander
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
#include <go/type_traits/noncopyable_nonmovable.hpp>

namespace go
{
namespace mvvm
{

class arguments
    : public go::type_traits::noncopyable_nonmovable
{
public:
    using this_type = arguments;
    using ptr = std::shared_ptr<this_type>;
    using wptr = std::weak_ptr<this_type>;

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
