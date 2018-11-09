#ifndef GO_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
#define GO_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED

//
//  view_model_interface.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_view_model_change_interface.hpp>

namespace go
{
namespace mvvm
{

template<typename M = std::recursive_mutex>
class view_model_interface
    : public notify_view_model_change_interface<M>
{
public:
    typedef M mutex_type;
    typedef view_model_interface<M> this_type;

public:
    virtual ~view_model_interface() = 0;

protected:
    view_model_interface() GO_DEFAULT_CONSTRUCTOR

protected:
    virtual void on_view_model_will_change()
    {
        if(!notify_view_model_change_interface<M>::view_model_will_change.empty())
        {
            notify_view_model_change_interface<M>::view_model_will_change(view_model_will_change_arguments::create());
        }
    }

    virtual void on_view_model_changed()
    {
        if(!notify_view_model_change_interface<M>::view_model_changed.empty())
        {
            notify_view_model_change_interface<M>::view_model_changed(view_model_changed_arguments::create());
        }
    }
};

template<typename M>
inline view_model_interface<M>::~view_model_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
