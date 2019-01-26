#ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
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

#include <mutex>
#include <string>

#include <go/mvvm/command_interface.hpp>
#include <go/utility/placebo_lockable.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::string, go::utility::recursive_spin_lock> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, go::utility::recursive_spin_lock> wcommand_execution_wobserver_interface;

namespace single_threaded
{

typedef basic_command_execution_observer_interface<std::string, go::utility::placebo_lockable> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, go::utility::placebo_lockable> wcommand_execution_wobserver_interface;

}

template<class S, class L = go::utility::recursive_spin_lock>
class basic_command_execution_observer_interface
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_command_execution_observer_interface<S, L> this_type;

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
