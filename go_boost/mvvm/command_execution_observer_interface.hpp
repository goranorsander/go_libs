#ifndef GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <string>

#include <go_boost/mvvm/command_interface.hpp>

namespace go_boost
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
    basic_command_execution_observer_interface();

public:
    virtual void on_command_executed(const boost::shared_ptr<basic_command_interface<S>>& /*c*/) = 0;
    virtual void on_command_not_executed(const boost::shared_ptr<basic_command_interface<S>>& /*c*/) = 0;
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

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
