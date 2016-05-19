#ifndef GO_MVVM_COMMAND_HPP_INCLUDED
#define GO_MVVM_COMMAND_HPP_INCLUDED

//
//  command.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/command_parameters.hpp>
#include <go/property/read_only_property.hpp>
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_manager;

template<class S>
class basic_command
    : public std::enable_shared_from_this<basic_command<S>>
{
    friend class basic_command_manager<S>;

public:
    typedef S string_type;
    typedef basic_command<string_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef typename std::shared_ptr<command_parameters> command_parameters_type_ptr;
    typedef typename go::signals::signal<std::function<void(const ptr&)>> can_execute_changed_signal;
    typedef typename go::property::read_only::basic_property<string_type, string_type> command_name_type;

public:
    virtual ~basic_command() = 0;

private:
    basic_command(const basic_command&) = delete;

protected:
    basic_command(const string_type& cmd_name, const command_parameters::ptr& params);

public:
    command_name_type command_name;

public:
    virtual command_parameters::ptr parameters() const
    {
        return _parameters;
    }

    virtual void notify_can_execute_changed()
    {
        if(!can_execute_changed.empty())
        {
            can_execute_changed(std::enable_shared_from_this<this_type>::shared_from_this());
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
    : std::enable_shared_from_this<basic_command<std::string>>()
    , can_execute_changed()
    , command_name("command_name", std::bind(&this_type::get_command_name, this))
    , _command_name(cmd_name)
    , _parameters(params)
{
    can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command<std::wstring>::basic_command(const std::wstring& cmd_name, const command_parameters::ptr& params)
    : std::enable_shared_from_this<basic_command<std::wstring>>()
    , can_execute_changed()
    , command_name(L"command_name", std::bind(&this_type::get_command_name, this))
    , _command_name(cmd_name)
    , _parameters(params)
{
    can_execute_changed.disconnect_all_slots();
}

template<class S>
inline basic_command<S>::basic_command(const S& cmd_name, const command_parameters::ptr& params)
    : std::enable_shared_from_this<basic_command<S>>()
    , can_execute_changed()
    , command_name(S(), nullptr)
    , _command_name(cmd_name)
    , _parameters(params)
{
    throw std::exception();
}

class command
    : public basic_command<std::string>
{
public:
    typedef command this_type;

public:
    virtual ~command() = 0;

private:
    command(const command&) = delete;

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

private:
    wcommand(const wcommand&) = delete;

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
} // namespace go

#endif  // #ifndef GO_MVVM_COMMAND_HPP_INCLUDED
