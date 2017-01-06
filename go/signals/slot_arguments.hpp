#ifndef GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
#define GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED

//
//  slot_arguments.hpp
//
//  Copyright 2015-2017 G�ran Orsander
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
namespace signals
{

class slot_arguments
    : public go::utility::noncopyable_nonmovable
{
public:
    typedef slot_arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~slot_arguments() = 0;

protected:
    slot_arguments() = default;
};

inline slot_arguments::~slot_arguments()
{
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
