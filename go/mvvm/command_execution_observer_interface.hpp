#ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
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

#include <mutex>
#include <string>

#include <go/mvvm/command_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, typename M> class basic_command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::string, std::recursive_mutex> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, std::recursive_mutex> wcommand_execution_wobserver_interface;

template<class S, typename M = std::recursive_mutex>
class basic_command_execution_observer_interface
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_command_execution_observer_interface<S, M> this_type;

public:
    virtual ~basic_command_execution_observer_interface() = 0;

protected:
    basic_command_execution_observer_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual void on_command_executed(const std::shared_ptr<basic_command_interface<S, M>>& /*c*/) = 0;
    virtual void on_command_not_executed(const std::shared_ptr<basic_command_interface<S, M>>& /*c*/) = 0;
};

template<>
inline basic_command_execution_observer_interface<std::string>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring>::~basic_command_execution_observer_interface()
{
}

template<class S, typename M>
inline basic_command_execution_observer_interface<S, M>::~basic_command_execution_observer_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
