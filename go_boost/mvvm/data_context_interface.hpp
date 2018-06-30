#ifndef GO_BOOST_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED

//
//  data_context_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/notify_data_context_change_interface.hpp>
#include <go_boost/property/nameless/property.hpp>

namespace go_boost
{
namespace mvvm
{

template<class T> class data_context_interface
    : public notify_data_context_change_interface
{
public:
    typedef T data_type;
    typedef data_context_interface<data_type> this_type;
    typedef go_boost::property::nameless::property<data_type> data_context_type;

public:
    virtual ~data_context_interface() = 0;

protected:
    data_context_interface()
        : notify_data_context_change_interface()
        , data_context()
        , _data_context()
    {
        bind_data_context_properties();
    }

    explicit data_context_interface(const data_type& t)
        : notify_data_context_change_interface()
        , data_context()
        , _data_context(t)
    {
        bind_data_context_properties();
    }

public:
    data_context_type data_context;

protected:
    virtual void bind_data_context_properties()
    {
        data_context.getter(boost::bind(&this_type::get_data_context, this));
        data_context.setter(boost::bind(&this_type::set_data_context, this, _1));
    }

    virtual void on_data_context_will_change()
    {
        if(!notify_data_context_change_interface::data_context_will_change.empty())
        {
            notify_data_context_change_interface::data_context_will_change(data_context_will_change_arguments::create());
        }
    }

    virtual void on_data_context_changed()
    {
        if(!notify_data_context_change_interface::data_context_changed.empty())
        {
            notify_data_context_change_interface::data_context_changed(data_context_changed_arguments::create());
        }
    }

private:
    data_type get_data_context() const
    {
        return _data_context;
    }

    void set_data_context(const data_type& v)
    {
        if(v != _data_context)
        {
            on_data_context_will_change();
            _data_context = v;
            on_data_context_changed();
        }
    }

private:
    data_type _data_context;
};

template<class T>
inline data_context_interface<T>::~data_context_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED
