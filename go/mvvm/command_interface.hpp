#ifndef GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED

//
//  command_interface.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/read_only_property.hpp>
#include <go/signals/signal.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_manager;

template<class S> class basic_command_interface;
typedef basic_command_interface<std::string> command_interface;
typedef basic_command_interface<std::wstring> wcommand_interface;

template<class S>
class basic_command_interface
    : public std::enable_shared_from_this<basic_command_interface<S>>
    , public go::utility::noncopyable_nonmovable
{
    friend class basic_command_manager<S>;

public:
    typedef S string_type;
    typedef basic_command_interface<S> this_type;
    typedef typename std::shared_ptr<basic_command_interface<S>> ptr;
    typedef typename std::weak_ptr<basic_command_interface<S>> wptr;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<S>>&)>> can_execute_changed_signal;
    typedef typename go::property::nameless::read_only::property<S> command_name_type;

public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const std::shared_ptr<command_parameters>& params);

public:
    command_name_type command_name;

public:
    virtual std::shared_ptr<command_parameters> parameters() const;

    virtual void notify_can_execute_changed();

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
inline basic_command_interface<std::string>::~basic_command_interface()
{
    can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command_interface<std::wstring>::~basic_command_interface()
{
    can_execute_changed.disconnect_all_slots();
}

template<class S>
inline basic_command_interface<S>::~basic_command_interface()
{
    can_execute_changed.disconnect_all_slots();
}

template<class S>
inline basic_command_interface<S>::basic_command_interface(const S& cmd_name, const std::shared_ptr<command_parameters>& params)
    : std::enable_shared_from_this<basic_command_interface<S>>()
    , go::utility::noncopyable_nonmovable()
    , can_execute_changed()
    , command_name(nullptr)
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter([this]() -> S { return _command_name; });
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::string>::parameters() const
{
    return _parameters;
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::wstring>::parameters() const
{
    return _parameters;
}

template<class S>
inline std::shared_ptr<command_parameters> basic_command_interface<S>::parameters() const
{
    return _parameters;
}

template<>
inline void basic_command_interface<std::string>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this_type::shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this_type::shared_from_this());
    }
}

template<class S>
inline void basic_command_interface<S>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this_type::shared_from_this());
    }
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
