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
#include <go/property/ro_property.hpp>
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class S> class command_manager;

template<class S = std::string>
class command
    : public std::enable_shared_from_this<command<S>>
{
    friend class command_manager<S>;

public:
    typedef S string_type;
    typedef command<string_type> this_type;
    typedef std::shared_ptr<command<string_type>> ptr;
    typedef std::weak_ptr<command<string_type>> wptr;
    typedef std::shared_ptr<command_parameters> command_parameters_type_ptr;
    typedef go::signals::signal<std::function<void(const ptr&)>> can_execute_changed_signal;
    typedef go::property::ro_property<string_type> command_name_type;

public:
    virtual ~command() = 0;

private:
    command(const command&) = delete;

protected:
    command(const string_type& cmd_name, const command_parameters::ptr& params)
        : std::enable_shared_from_this<command<string_type>>()
        , can_execute_changed()
        , command_name("command_name", std::bind(&this_type::get_command_name, this))
        , _command_name(cmd_name)
        , _parameters(params)
    {
        can_execute_changed.disconnect_all_slots();
    }

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
            can_execute_changed(std::enable_shared_from_this<command<string_type>>::shared_from_this());
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
inline command<S>::~command()
{
}

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_COMMAND_HPP_INCLUDED
