#ifndef GO_BOOST_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED

//
//  notify_command_execution_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <string>
#include <boost/signals2.hpp>
#include <go_boost/mvvm/command_interface.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, typename M> class basic_notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::string, boost::recursive_mutex> notify_command_execution_interface;
typedef basic_notify_command_execution_interface<std::wstring, boost::recursive_mutex> notify_wcommand_execution_interface;

template<class S, typename M = boost::recursive_mutex>
class basic_notify_command_execution_interface
    : public go_boost::signals::slot
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_notify_command_execution_interface<S, M> this_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_command_interface<S, M>>&)> command_executed_signal;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_command_interface<S, M>>&)> command_not_executed_signal;

public:
    virtual ~basic_notify_command_execution_interface() = 0;

protected:
    basic_notify_command_execution_interface();

public:
    command_executed_signal command_executed;
    command_not_executed_signal command_not_executed;
};

template<>
inline basic_notify_command_execution_interface<std::string, boost::recursive_mutex>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::wstring, boost::recursive_mutex>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

template<class S, typename M>
inline basic_notify_command_execution_interface<S, M>::~basic_notify_command_execution_interface()
{
    command_executed.disconnect_all_slots();
    command_not_executed.disconnect_all_slots();
}

template<>
inline basic_notify_command_execution_interface<std::string, boost::recursive_mutex>::basic_notify_command_execution_interface()
    : go_boost::signals::slot()
    , command_executed()
    , command_not_executed()
{
}

template<>
inline basic_notify_command_execution_interface<std::wstring, boost::recursive_mutex>::basic_notify_command_execution_interface()
    : go_boost::signals::slot()
    , command_executed()
    , command_not_executed()
{
}

template<class S, typename M>
inline basic_notify_command_execution_interface<S, M>::basic_notify_command_execution_interface()
    : go_boost::signals::slot()
    , command_executed()
    , command_not_executed()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_COMMAND_EXECUTION_INTERFACE_HPP_INCLUDED
