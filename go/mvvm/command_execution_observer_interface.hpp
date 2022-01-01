#ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>
#include <string>

#include <go/async/placebo_lockable.hpp>
#include <go/mvvm/command_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_command_execution_observer_interface;
#if defined(GO_NO_CXX11_TYPE_ALIASES)
typedef basic_command_execution_observer_interface<std::string, std::recursive_mutex> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, std::recursive_mutex> wcommand_execution_wobserver_interface;
#else
using command_execution_observer_interface = basic_command_execution_observer_interface<std::string, std::recursive_mutex>;
using wcommand_execution_wobserver_interface = basic_command_execution_observer_interface<std::wstring, std::recursive_mutex>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

namespace single_threaded
{

#if defined(GO_NO_CXX11_TYPE_ALIASES)
typedef basic_command_execution_observer_interface<std::string, go::async::placebo_lockable> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, go::async::placebo_lockable> wcommand_execution_wobserver_interface;
#else
using command_execution_observer_interface = basic_command_execution_observer_interface<std::string, go::async::placebo_lockable>;
using wcommand_execution_wobserver_interface = basic_command_execution_observer_interface<std::wstring, go::async::placebo_lockable>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

}

template<class S, class L = std::recursive_mutex>
class basic_command_execution_observer_interface
{
public:
    GO_USING(string_type, S);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef basic_command_execution_observer_interface<S, L> this_type;
#else
    using this_type = basic_command_execution_observer_interface<S, L>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

public:
    virtual ~basic_command_execution_observer_interface() = 0;

protected:
    basic_command_execution_observer_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual void on_command_executed(const std::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
    virtual void on_command_not_executed(const std::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
};

template<class S, class L>
inline basic_command_execution_observer_interface<S, L>::~basic_command_execution_observer_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
