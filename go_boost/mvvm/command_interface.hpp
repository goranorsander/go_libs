#ifndef GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED

//
//  command_interface.hpp
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

#include <boost/enable_shared_from_this.hpp>
#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/read_only_property.hpp>
#include <go_boost/signals.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>
#include <go_boost/utility/placebo_lockable.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_command_manager;

template<class S, class L> class basic_command_interface;
typedef basic_command_interface<std::string, boost::recursive_mutex> command_interface;
typedef basic_command_interface<std::wstring, boost::recursive_mutex> wcommand_interface;

namespace single_threaded
{

typedef basic_command_interface<std::string, go_boost::utility::placebo_lockable> command_interface;
typedef basic_command_interface<std::wstring, go_boost::utility::placebo_lockable> wcommand_interface;

}

template<class S, class L = boost::recursive_mutex>
class basic_command_interface
    : public boost::enable_shared_from_this<basic_command_interface<S, L>>
    , private go_boost::utility::noncopyable_nonmovable
{
    friend class basic_command_manager<S, L>;

public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_command_interface<S, L> this_type;
    typedef typename boost::shared_ptr<basic_command_interface<S, L>> ptr;
    typedef typename boost::weak_ptr<basic_command_interface<S, L>> wptr;
    typedef typename boost::shared_ptr<command_parameters> command_parameters_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_command_interface<S, L>>&)> can_execute_changed_signal;
    typedef typename go_boost::property::nameless::read_only::property<S> command_name_type;

public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const command_parameters_type& params);

public:
    virtual boost::shared_ptr<command_parameters> parameters() const;

    virtual void notify_can_execute_changed();

protected:
    virtual bool can_execute(const command_parameters_type& params) = 0;

    virtual void execute(const command_parameters_type& params) = 0;

    virtual S get_command_name() const;

public:
    command_name_type command_name;
    can_execute_changed_signal can_execute_changed;

private:
    const S _command_name;
    command_parameters_type _parameters;
};

template<>
inline basic_command_interface<std::string, boost::recursive_mutex>::~basic_command_interface()
{
    this->can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command_interface<std::wstring, boost::recursive_mutex>::~basic_command_interface()
{
    this->can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command_interface<std::string, go_boost::utility::placebo_lockable>::~basic_command_interface()
{
    this->can_execute_changed.disconnect_all_slots();
}

template<>
inline basic_command_interface<std::wstring, go_boost::utility::placebo_lockable>::~basic_command_interface()
{
    this->can_execute_changed.disconnect_all_slots();
}

template<class S, class L>
inline basic_command_interface<S, L>::~basic_command_interface()
{
    this->can_execute_changed.disconnect_all_slots();
}

template<class S, class L>
inline basic_command_interface<S, L>::basic_command_interface(const S& cmd_name, const command_parameters_type& params)
    : boost::enable_shared_from_this<basic_command_interface<S, L>>()
    , go_boost::utility::noncopyable_nonmovable()
    , command_name()
    , can_execute_changed()
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter(boost::bind(&this_type::get_command_name, this));
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::string, boost::recursive_mutex>::parameters() const
{
    return _parameters;
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::wstring, boost::recursive_mutex>::parameters() const
{
    return _parameters;
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::string, go_boost::utility::placebo_lockable>::parameters() const
{
    return _parameters;
}

template<>
inline boost::shared_ptr<command_parameters> basic_command_interface<std::wstring, go_boost::utility::placebo_lockable>::parameters() const
{
    return _parameters;
}

template<class S, class L>
inline boost::shared_ptr<command_parameters> basic_command_interface<S, L>::parameters() const
{
    return _parameters;
}

template<>
inline void basic_command_interface<std::string, boost::recursive_mutex>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring, boost::recursive_mutex>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::string, go_boost::utility::placebo_lockable>::notify_can_execute_changed()
{
    if (!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring, go_boost::utility::placebo_lockable>::notify_can_execute_changed()
{
    if (!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<class S, class L>
inline void basic_command_interface<S, L>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<class S, class L>
inline S basic_command_interface<S, L>::get_command_name() const
{
    return _command_name;
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
