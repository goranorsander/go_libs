#ifndef GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED

//
//  notify_data_context_change_interface.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_MUTEX) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/data_context_changed_arguments.hpp>
#include <go/mvvm/data_context_will_change_arguments.hpp>
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class L = std::recursive_mutex>
class notify_data_context_change_interface
{
public:
    GO_USING(lockable_type, L);
    GO_USING(this_type, notify_data_context_change_interface<L>);
    GO_USING(data_context_changed_signal, go::signals::signal<void(const std::shared_ptr<data_context_changed_arguments>&)>);
    GO_USING(data_context_will_change_signal, go::signals::signal<void(const std::shared_ptr<data_context_will_change_arguments>&)>);

public:
    virtual ~notify_data_context_change_interface() = 0;

protected:
    notify_data_context_change_interface() GO_DEFAULT_CONSTRUCTOR

public:
    data_context_will_change_signal data_context_will_change;
    data_context_changed_signal data_context_changed;
};

template<class L>
inline notify_data_context_change_interface<L>::~notify_data_context_change_interface()
{
    data_context_will_change.disconnect_all_slots();
    data_context_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED
