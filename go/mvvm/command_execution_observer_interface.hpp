#ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>

#include <go/mvvm/command_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::string> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring> wcommand_execution_wobserver_interface;

template<class S>
class basic_command_execution_observer_interface
{
public:
    typedef S string_type;
    typedef basic_command_execution_observer_interface<S> this_type;

public:
    virtual ~basic_command_execution_observer_interface() = 0;

protected:

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    basic_command_execution_observer_interface();

#else

    basic_command_execution_observer_interface() = default;

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

public:
    virtual void on_command_executed(const std::shared_ptr<basic_command_interface<S>>& /*c*/) = 0;
    virtual void on_command_not_executed(const std::shared_ptr<basic_command_interface<S>>& /*c*/) = 0;
};

template<>
inline basic_command_execution_observer_interface<std::string>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring>::~basic_command_execution_observer_interface()
{
}

template<class S>
inline basic_command_execution_observer_interface<S>::~basic_command_execution_observer_interface()
{
}

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

template<>
inline basic_command_execution_observer_interface<std::string>::basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring>::basic_command_execution_observer_interface()
{
}

template<class S>
inline basic_command_execution_observer_interface<S>::basic_command_execution_observer_interface()
{
}

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED