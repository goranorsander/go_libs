#ifndef GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED

//
//  command_interface.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <boost/config.hpp>
#include <boost/predef.h>

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

template<class S> class basic_command_interface;
typedef basic_command_interface<std::string> command_interface;
typedef basic_command_interface<std::wstring> wcommand_interface;

template<class S>
class basic_command_interface
    : public boost::enable_shared_from_this<basic_command_interface<S>>
    , private boost::noncopyable
{
    friend class basic_command_manager<S>;

public:
    typedef S string_type;
    typedef basic_command_interface<S> this_type;
    typedef typename boost::shared_ptr<basic_command_interface<S>> ptr;
    typedef typename boost::weak_ptr<basic_command_interface<S>> wptr;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_command_interface<S>>&)> can_execute_changed_signal;
    typedef typename go_boost::property::read_only::basic_property<S, S> command_name_type;

public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const boost::shared_ptr<command_parameters>& params);

public:
    command_name_type command_name;

public:
    virtual boost::shared_ptr<command_parameters> parameters() const;

    virtual void notify_can_execute_changed();

    virtual S get_command_name() const;

protected:
    virtual bool can_execute(const boost::shared_ptr<command_parameters>& params) = 0;

    virtual void execute(const boost::shared_ptr<command_parameters>& params) = 0;

public:
    can_execute_changed_signal can_execute_changed;

private:
    const S _command_name;
    boost::shared_ptr<command_parameters> _parameters;
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

template<>
inline basic_command_interface<std::string>::basic_command_interface(const std::string& cmd_name, const boost::shared_ptr<command_parameters>& params)
    : boost::enable_shared_from_this<basic_command_interface<std::string>>()
    , boost::noncopyable()
    , can_execute_changed()
    , command_name("command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(boost::bind(&this_type::get_command_name, this));
}

template<>
inline basic_command_interface<std::wstring>::basic_command_interface(const std::wstring& cmd_name, const boost::shared_ptr<command_parameters>& params)
    : boost::enable_shared_from_this<basic_command_interface<std::wstring>>()
    , boost::noncopyable()
    , can_execute_changed()
    , command_name(L"command_name")
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(boost::bind(&this_type::get_command_name, this));
}

template<class S>
inline basic_command_interface<S>::basic_command_interface(const S& cmd_name, const boost::shared_ptr<command_parameters>& params)
    : boost::enable_shared_from_this<basic_command_interface<S>>()
    , boost::noncopyable()
    , can_execute_changed()
    , command_name(S())
    , _command_name(cmd_name)
    , _parameters(params)
{
    throw std::exception();
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::string>::parameters() const
{
    return _parameters;
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::wstring>::parameters() const
{
    return _parameters;
}

template<class S>
inline boost::shared_ptr<command_parameters> basic_command_interface<S>::parameters() const
{
    return _parameters;
}

template<>
inline void basic_command_interface<std::string>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(boost::enable_shared_from_this<basic_command_interface<std::string>>::shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(boost::enable_shared_from_this<basic_command_interface<std::wstring>>::shared_from_this());
    }
}

template<class S>
inline void basic_command_interface<S>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(boost::enable_shared_from_this<basic_command_interface<S>>::shared_from_this());
    }
}

//#if defined(BOOST_COMP_MSVC)
//template<>
//inline std::string basic_command_interface<std::string>::get_command_name() const
//{
//    return _command_name;
//}
//#endif  // defined(BOOST_COMP_MSVC)
//
//#if defined(BOOST_COMP_MSVC)
//template<>
//inline std::wstring basic_command_interface<std::wstring>::get_command_name() const
//{
//    return _command_name;
//}
//#endif  // defined(BOOST_COMP_MSVC)

template<class S>
inline S basic_command_interface<S>::get_command_name() const
{
    return _command_name;
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
