#ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED

//
//  notify_command_execution_interface.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/mvvm/command_interface.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::string> notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::wstring> notify_wcommand_execution_interface;

template<class S>
class basic_notify_command_execution_interface
    : public go::signals::slot
{
public:
    typedef S string_type;
    typedef basic_notify_command_execution_interface<S> this_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<string_type>>&)>> command_executed_signal;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<string_type>>&)>> command_not_executed_signal;

public:
    virtual ~basic_notify_command_execution_interface() = 0;

protected:
    basic_notify_command_execution_interface() = default;

public:
    command_executed_signal command_executed;
    command_not_executed_signal command_not_executed;
};

template<>
inline basic_notify_command_execution_interface<std::string>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::wstring>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

template<class S>
inline basic_notify_command_execution_interface<S>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
