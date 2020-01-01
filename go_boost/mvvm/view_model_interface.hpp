#ifndef GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED

//
//  view_model_interface.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/notify_view_model_change_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class L = boost::recursive_mutex>
class view_model_interface
    : public notify_view_model_change_interface<L>
{
public:
    typedef L lockable_type;
    typedef view_model_interface<L> this_type;

public:
    virtual ~view_model_interface() = 0;

protected:
    view_model_interface()
        : notify_view_model_change_interface<L>()
    {
    }

protected:
    virtual void on_view_model_will_change()
    {
        if(!notify_view_model_change_interface<L>::view_model_will_change.empty())
        {
            notify_view_model_change_interface<L>::view_model_will_change(view_model_will_change_arguments::create());
        }
    }

    virtual void on_view_model_changed()
    {
        if(!notify_view_model_change_interface<L>::view_model_changed.empty())
        {
            notify_view_model_change_interface<L>::view_model_changed(view_model_changed_arguments::create());
        }
    }
};

template<class L>
inline view_model_interface<L>::~view_model_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_VIEW_MODEL_INTERFACE_HPP_INCLUDED
