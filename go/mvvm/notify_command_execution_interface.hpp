#ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED

//
//  notify_command_execution_interface.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/async/placebo_lockable.hpp>
#include <go/mvvm/command_interface.hpp>
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_notify_command_execution_interface;
using notify_command_execution_interface = basic_notify_command_execution_interface<std::string, std::recursive_mutex>;
using notify_wcommand_execution_interface = basic_notify_command_execution_interface<std::wstring, std::recursive_mutex>;

namespace single_threaded
{

using notify_command_execution_interface = basic_notify_command_execution_interface<std::string, go::async::placebo_lockable>;
using notify_wcommand_execution_interface = basic_notify_command_execution_interface<std::wstring, go::async::placebo_lockable>;

}

template<class S, class L = std::recursive_mutex>
class basic_notify_command_execution_interface
{
public:
    using string_type = S;
    using lockable_type = L;
    using this_type = basic_notify_command_execution_interface<S, L>;
    using command_executed_signal = typename go::signals::signal<void(const std::shared_ptr<basic_command_interface<string_type, lockable_type>>&)>;
    using command_not_executed_signal = typename go::signals::signal<void(const std::shared_ptr<basic_command_interface<string_type, lockable_type>>&)>;

public:
    virtual ~basic_notify_command_execution_interface() = 0;

protected:
    basic_notify_command_execution_interface() GO_DEFAULT_CONSTRUCTOR

public:
    command_executed_signal command_executed;
    command_not_executed_signal command_not_executed;

protected:
    virtual void notify_command_executed(const std::shared_ptr<basic_command_interface<S, L>>& command) const;
    virtual void notify_command_not_executed(const std::shared_ptr<basic_command_interface<S, L>>& command) const;
};

template<>
inline basic_notify_command_execution_interface<std::string, std::recursive_mutex>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::wstring, std::recursive_mutex>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::string, go::async::placebo_lockable>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::wstring, go::async::placebo_lockable>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<class S, class L>
inline basic_notify_command_execution_interface<S, L>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<>
inline void basic_notify_command_execution_interface<std::string, std::recursive_mutex>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>& command) const
{
    this->command_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, std::recursive_mutex>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>& command) const
{
    this->command_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::string, go::async::placebo_lockable>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::string, go::async::placebo_lockable>>& command) const
{
    this->command_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, go::async::placebo_lockable>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::wstring, go::async::placebo_lockable>>& command) const
{
    this->command_executed(command);
}

template<class S, class L>
inline void basic_notify_command_execution_interface<S, L>::notify_command_executed(const std::shared_ptr<basic_command_interface<S, L>>& command) const
{
    this->command_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::string, std::recursive_mutex>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>& command) const
{
    this->command_not_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, std::recursive_mutex>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>& command) const
{
    this->command_not_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::string, go::async::placebo_lockable>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::string, go::async::placebo_lockable>>& command) const
{
    this->command_not_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, go::async::placebo_lockable>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::wstring, go::async::placebo_lockable>>& command) const
{
    this->command_not_executed(command);
}

template<class S, class L>
inline void basic_notify_command_execution_interface<S, L>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<S, L>>& command) const
{
    this->command_not_executed(command);
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
