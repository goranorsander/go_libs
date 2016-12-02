#ifndef GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED

//
//  view_model_interface.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/notify_view_model_changed_interface.hpp>

namespace go_boost
{
namespace mvvm
{

class view_model_interface
    : public notify_view_model_changed_interface
{
public:
    typedef view_model_interface this_type;

public:
    virtual ~view_model_interface() = 0;

protected:
    view_model_interface()
        : notify_view_model_changed_interface()
    {
    }

protected:
    virtual void on_view_model_changed()
    {
        if(!notify_view_model_changed_interface::view_model_changed.empty())
        {
            notify_view_model_changed_interface::view_model_changed(view_model_changed_arguments::create());
        }
    }
};

template<class T>
inline view_model_interface<T>::~view_model_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
