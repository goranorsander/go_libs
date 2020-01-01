#ifndef GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  command_execution_observer_interface.hpp
//
//  Copyright 2015-2020 Göran Orsander
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

#include <go_boost/mvvm/command_interface.hpp>
#include <go_boost/utility/placebo_lockable.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::string, boost::recursive_mutex> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, boost::recursive_mutex> wcommand_execution_wobserver_interface;

namespace single_threaded
{

typedef basic_command_execution_observer_interface<std::string, go_boost::utility::placebo_lockable> command_execution_observer_interface;
typedef basic_command_execution_observer_interface<std::wstring, go_boost::utility::placebo_lockable> wcommand_execution_wobserver_interface;

}

template<class S, class L = boost::recursive_mutex>
class basic_command_execution_observer_interface
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_command_execution_observer_interface<S, L> this_type;

public:
    virtual ~basic_command_execution_observer_interface() = 0;

protected:
    basic_command_execution_observer_interface();

public:
    virtual void on_command_executed(const boost::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
    virtual void on_command_not_executed(const boost::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
};

template<>
inline basic_command_execution_observer_interface<std::string, boost::recursive_mutex>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring, boost::recursive_mutex>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::string, go_boost::utility::placebo_lockable>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring, go_boost::utility::placebo_lockable>::~basic_command_execution_observer_interface()
{
}

template<class S, class L>
inline basic_command_execution_observer_interface<S, L>::~basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::string, boost::recursive_mutex>::basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring, boost::recursive_mutex>::basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::string, go_boost::utility::placebo_lockable>::basic_command_execution_observer_interface()
{
}

template<>
inline basic_command_execution_observer_interface<std::wstring, go_boost::utility::placebo_lockable>::basic_command_execution_observer_interface()
{
}

template<class S, class L>
inline basic_command_execution_observer_interface<S, L>::basic_command_execution_observer_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_EXECUTION_OBSERVER_INTERFACE_HPP_INCLUDED
