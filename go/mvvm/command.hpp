#ifndef GO_MVVM_COMMAND_HPP_INCLUDED
#define GO_MVVM_COMMAND_HPP_INCLUDED

//
//  command.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/command_parameters.hpp>
#include <go/property/read_only_property.hpp>
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_manager;

template<class S> class basic_command;
typedef basic_command<std::string> command;
typedef basic_command<std::wstring> wcommand;

template<class S>
class basic_command
    : public std::enable_shared_from_this<basic_command<S>>
{
    friend class basic_command_manager<S>;

public:
    typedef S string_type;
    typedef basic_command<S> this_type;
    typedef typename std::shared_ptr<basic_command<S>> ptr;
    typedef typename std::weak_ptr<basic_command<S>> wptr;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command<S>>&)>> can_execute_changed_signal;
    typedef typename go::property::read_only::basic_property<S, S> command_name_type;

public:
    virtual ~basic_command() = 0;

private:
    basic_command(const basic_command<S>&) = delete;
    basic_command(basic_command<S>&&) = delete;

    basic_command<S>& operator=(const basic_command<S>&) = delete;
    basic_command<S>& operator=(basic_command<S>&&) = delete;

protected:
    basic_command(const S& cmd_name, const std::shared_ptr<command_parameters>& params);

public:
    command_name_type command_name;

public:
    virtual std::shared_ptr<command_parameters> parameters() const;

    virtual void notify_can_execute_changed();

    virtual S get_command_name() const;

protected:
    virtual bool can_execute(const std::shared_ptr<command_parameters>& params) = 0;

    virtual void execute(const std::shared_ptr<command_parameters>& params) = 0;

public:
    can_execute_changed_signal can_execute_changed;

private:
    const S _command_name;
    std::shared_ptr<command_parameters> _parameters;
};

template<>
inline basic_command<std::string>::~basic_command()
{
    can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command<std::wstring>::~basic_command()
{
    can_execute_changed.disconnect_all_slots();
}

template<class S>
inline basic_command<S>::~basic_command()
{
    can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command<std::string>::basic_command(const std::string& cmd_name, const std::shared_ptr<command_parameters>& params)
    : std::enable_shared_from_this<basic_command<std::string>>()
    , can_execute_changed()
    , command_name("command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(std::bind(&basic_command::get_command_name, this));
}

template<>
inline basic_command<std::wstring>::basic_command(const std::wstring& cmd_name, const std::shared_ptr<command_parameters>& params)
    : std::enable_shared_from_this<basic_command<std::wstring>>()
    , can_execute_changed()
    , command_name(L"command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(std::bind(&basic_command::get_command_name, this));
}

template<class S>
inline basic_command<S>::basic_command(const S& cmd_name, const std::shared_ptr<command_parameters>& params)
    : std::enable_shared_from_this<basic_command<S>>()
    , can_execute_changed()
    , command_name(S(), nullptr)
    , _command_name(cmd_name)
    , _parameters(params)
{
    throw std::exception();
}

template<>
inline std::shared_ptr<command_parameters> basic_command<std::string>::parameters() const
{
    return _parameters;
}

template<>
inline std::shared_ptr<command_parameters> basic_command<std::wstring>::parameters() const
{
    return _parameters;
}

template<class S>
inline std::shared_ptr<command_parameters> basic_command<S>::parameters() const
{
    return _parameters;
}

template<>
inline void basic_command<std::string>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(std::enable_shared_from_this<basic_command<std::string>>::shared_from_this());
    }
}

template<>
inline void basic_command<std::wstring>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(std::enable_shared_from_this<basic_command<std::wstring>>::shared_from_this());
    }
}

template<class S>
inline void basic_command<S>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(std::enable_shared_from_this<basic_command<S>>::shared_from_this());
    }
}

template<>
inline std::string basic_command<std::string>::get_command_name() const
{
    return _command_name;
}

template<>
inline std::wstring basic_command<std::wstring>::get_command_name() const
{
    return _command_name;
}

template<class S>
inline S basic_command<S>::get_command_name() const
{
    return _command_name;
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_HPP_INCLUDED
