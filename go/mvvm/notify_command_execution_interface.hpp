#ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED

//
//  notify_command_execution_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
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
#include <go/utility/placebo_mutex.hpp>

namespace go
{
namespace mvvm
{

template<class S, typename M> class basic_notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::string, std::recursive_mutex> notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::wstring, std::recursive_mutex> notify_wcommand_execution_interface;

namespace single_threaded
{

typedef basic_notify_command_execution_interface<std::string, go::utility::placebo_mutex> notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::wstring, go::utility::placebo_mutex> notify_wcommand_execution_interface;

}

template<class S, typename M = std::recursive_mutex>
class basic_notify_command_execution_interface
    : public go::signals::slot
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_notify_command_execution_interface<S, M> this_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<string_type, mutex_type>>&)>, M> command_executed_signal;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<string_type, mutex_type>>&)>, M> command_not_executed_signal;

public:
    virtual ~basic_notify_command_execution_interface() = 0;

protected:
    basic_notify_command_execution_interface() GO_DEFAULT_CONSTRUCTOR

public:
    command_executed_signal command_executed;
    command_not_executed_signal command_not_executed;

protected:
    virtual void notify_command_executed(const std::shared_ptr<basic_command_interface<S, M>>& command) const;
    virtual void notify_command_not_executed(const std::shared_ptr<basic_command_interface<S, M>>& command) const;
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
inline basic_notify_command_execution_interface<std::string, go::utility::placebo_mutex>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::wstring, go::utility::placebo_mutex>::~basic_notify_command_execution_interface()
{
    this->command_executed.disconnect_all_slots();
    this->command_not_executed.disconnect_all_slots();
}

template<class S, typename M>
inline basic_notify_command_execution_interface<S, M>::~basic_notify_command_execution_interface()
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
inline void basic_notify_command_execution_interface<std::string, go::utility::placebo_mutex>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_mutex>>& command) const
{
    this->command_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, go::utility::placebo_mutex>::notify_command_executed(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_mutex>>& command) const
{
    this->command_executed(command);
}

template<class S, typename M>
inline void basic_notify_command_execution_interface<S, M>::notify_command_executed(const std::shared_ptr<basic_command_interface<S, M>>& command) const
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
inline void basic_notify_command_execution_interface<std::string, go::utility::placebo_mutex>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_mutex>>& command) const
{
    this->command_not_executed(command);
}

template<>
inline void basic_notify_command_execution_interface<std::wstring, go::utility::placebo_mutex>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_mutex>>& command) const
{
    this->command_not_executed(command);
}

template<class S, typename M>
inline void basic_notify_command_execution_interface<S, M>::notify_command_not_executed(const std::shared_ptr<basic_command_interface<S, M>>& command) const
{
    this->command_not_executed(command);
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
