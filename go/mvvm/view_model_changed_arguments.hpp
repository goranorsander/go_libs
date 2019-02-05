#ifndef GO_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  view_model_changed_arguments.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/arguments.hpp>

namespace go
{
namespace mvvm
{

class view_model_changed_arguments
    : public arguments
{
public:
    typedef view_model_changed_arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~view_model_changed_arguments() GO_DEFAULT_DESTRUCTOR

protected:
    view_model_changed_arguments() GO_DEFAULT_CONSTRUCTOR

public:
    static std::shared_ptr<view_model_changed_arguments> create();
};

inline std::shared_ptr<view_model_changed_arguments> view_model_changed_arguments::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED
