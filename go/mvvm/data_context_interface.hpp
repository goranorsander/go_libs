#ifndef GO_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED
#define GO_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED

//
//  data_context_interface.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_data_context_change_interface.hpp>
#include <go/property/nameless/property.hpp>

namespace go
{
namespace mvvm
{

template<class T, class L = std::recursive_mutex>
class data_context_interface
    : public notify_data_context_change_interface<L>
{
public:
    typedef T data_type;
    typedef L lockable_type;
    typedef data_context_interface<T, L> this_type;
    typedef go::property::nameless::property<data_type> data_context_type;

public:
    virtual ~data_context_interface() = 0;

protected:
    data_context_interface()
        : notify_data_context_change_interface<lockable_type>()
        , data_context()
        , _data_context()
    {
        bind_data_context_properties();
    }

    explicit data_context_interface(const data_type& t)
        : notify_data_context_change_interface<lockable_type>()
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
        data_context.getter([this]() -> data_type { return _data_context; });
        data_context.setter([this](const data_type& v) { if(v != _data_context) { on_data_context_will_change(); _data_context = v; on_data_context_changed(); } });
    }

    virtual void on_data_context_will_change()
    {
        if(!notify_data_context_change_interface<lockable_type>::data_context_will_change.empty())
        {
            notify_data_context_change_interface<lockable_type>::data_context_will_change(data_context_will_change_arguments::create());
        }
    }

    virtual void on_data_context_changed()
    {
        if(!notify_data_context_change_interface<lockable_type>::data_context_changed.empty())
        {
            notify_data_context_change_interface<lockable_type>::data_context_changed(data_context_changed_arguments::create());
        }
    }

private:
    data_type _data_context;
};

template<class T, class L>
inline data_context_interface<T, L>::~data_context_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_DATA_CONTEXT_INTERFACE_HPP_INCLUDED
