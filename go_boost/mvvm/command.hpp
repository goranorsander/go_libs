#ifndef GO_BOOST_MVVM_COMMAND_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_HPP_INCLUDED

//
//  command.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/weak_ptr.hpp>
#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/read_only_property.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_command_manager;

template<class S>
class basic_command
    : public boost::enable_shared_from_this<basic_command<S>>
    , private boost::noncopyable
{
    friend class basic_command_manager<S>;

public:
    typedef S string_type;
    typedef basic_command<string_type> this_type;
    typedef command_parameters command_parameters_type;
    typedef typename boost::shared_ptr<basic_command<string_type>> ptr;
    typedef typename boost::weak_ptr<basic_command<string_type>> wptr;
    typedef typename boost::shared_ptr<command_parameters_type> command_parameters_type_ptr;
    typedef typename boost::signals2::signal<void(const ptr&)> can_execute_changed_signal;

public:
    virtual ~basic_command() = 0;

protected:
    basic_command(const string_type& cmd_name, const command_parameters::ptr& params);

public:
    go_boost::property::read_only::basic_property<string_type, string_type> command_name;

public:
    virtual command_parameters::ptr parameters() const
    {
        return _parameters;
    }

    virtual void notify_can_execute_changed()
    {
        if(!can_execute_changed.empty())
        {
            can_execute_changed(basic_command<string_type>::shared_from_this());
        }
    }

    virtual string_type get_command_name() const
    {
        return _command_name;
    }

protected:
    virtual bool can_execute(const command_parameters_type_ptr& params) = 0;

    virtual void execute(const command_parameters_type_ptr& params) = 0;

public:
    can_execute_changed_signal can_execute_changed;

private:
    const string_type _command_name;
    command_parameters::ptr _parameters;
};

template<class S>
inline basic_command<S>::~basic_command()
{
}

template<>
inline basic_command<std::string>::basic_command(const std::string& cmd_name, const command_parameters::ptr& params)
    : boost::enable_shared_from_this<basic_command<std::string>>()
    , can_execute_changed()
    , command_name("command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(boost::bind(&basic_command::get_command_name, this));
    can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command<std::wstring>::basic_command(const std::wstring& cmd_name, const command_parameters::ptr& params)
    : boost::enable_shared_from_this<basic_command<std::wstring>>()
    , can_execute_changed()
    , command_name(L"command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(boost::bind(&basic_command::get_command_name, this));
    can_execute_changed.disconnect_all_slots();
}

class command
    : public basic_command<std::string>
{
public:
    typedef command this_type;

public:
    virtual ~command() = 0;

protected:
    command(const string_type& cmd_name, const command_parameters::ptr& params)
        : basic_command<string_type>(cmd_name, params)
    {
    }

};

inline command::~command()
{
}

class wcommand
    : public basic_command<std::wstring>
{
public:
    typedef wcommand this_type;

public:
    virtual ~wcommand() = 0;

protected:
    wcommand(const string_type& cmd_name, const command_parameters::ptr& params)
        : basic_command<string_type>(cmd_name, params)
    {
    }

};

inline wcommand::~wcommand()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_HPP_INCLUDED
