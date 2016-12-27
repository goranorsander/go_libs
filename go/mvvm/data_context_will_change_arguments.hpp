#ifndef GO_MVVM_DATA_CONTEXT_WILL_CHANGE_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_DATA_CONTEXT_WILL_CHANGE_ARGUMENTS_HPP_INCLUDED

//
//  data_context_will_change_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/signals/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

class data_context_will_change_arguments
    : public go::signals::slot_arguments
{
public:
    typedef data_context_will_change_arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~data_context_will_change_arguments() = default;

protected:
    data_context_will_change_arguments() = default;

public:
    static std::shared_ptr<data_context_will_change_arguments> create();
};

inline std::shared_ptr<data_context_will_change_arguments> data_context_will_change_arguments::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler()
            : this_type()
        {
        }
    };

    return std::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_DATA_CONTEXT_WILL_CHANGE_ARGUMENTS_HPP_INCLUDED
