#ifndef GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_data_context_changed_interface.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/data_context_changed_arguments.hpp>
#include <go/mvvm/data_context_changing_arguments.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

class notify_data_context_changed_interface
    : public go::signals::slot
{
public:
    typedef notify_data_context_changed_interface this_type;
    typedef go::signals::signal<std::function<void(const std::shared_ptr<data_context_changed_arguments>&)>> data_context_changed_signal;
    typedef go::signals::signal<std::function<void(const std::shared_ptr<data_context_changing_arguments>&)>> data_context_changing_signal;

public:
    virtual ~notify_data_context_changed_interface() = 0;

protected:
    notify_data_context_changed_interface() = default;

public:
    data_context_changing_signal data_context_changing;
    data_context_changed_signal data_context_changed;
};

inline notify_data_context_changed_interface::~notify_data_context_changed_interface()
{
    data_context_changing.disconnect_all_slots();
    data_context_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED
