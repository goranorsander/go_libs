#ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/make_shared.hpp>

#include <go_boost/mvvm/command_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_relay_command;
typedef basic_relay_command<std::string, boost::recursive_mutex> relay_command;
typedef basic_relay_command<std::wstring, boost::recursive_mutex> relay_wcommand;

namespace single_threaded
{

typedef basic_relay_command<std::string, go_boost::async::placebo_lockable> relay_command;
typedef basic_relay_command<std::wstring, go_boost::async::placebo_lockable> relay_wcommand;

}

template<class S, class L = boost::recursive_mutex>
class basic_relay_command
    : public basic_command_interface<S, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_relay_command<S, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;
    typedef typename boost::shared_ptr<command_parameters> command_parameters_type;
    typedef typename boost::function<bool(const command_parameters_type&)> can_execute_command_signature;
    typedef typename boost::function<void(const command_parameters_type&)> execute_command_signature;

public:
    virtual ~basic_relay_command() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    basic_relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

public:
    static boost::shared_ptr<basic_relay_command<S, L>> create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

protected:
    virtual bool can_execute(const command_parameters_type& params) GO_BOOST_OVERRIDE;

    virtual void execute(const command_parameters_type& params) GO_BOOST_OVERRIDE;

private:
    can_execute_command_signature _can_execute;
    execute_command_signature _execute;
};

template<>
inline basic_relay_command<std::string, boost::recursive_mutex>::basic_relay_command(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::string, boost::recursive_mutex>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::wstring, boost::recursive_mutex>::basic_relay_command(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::wstring, boost::recursive_mutex>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::string, go_boost::async::placebo_lockable>::basic_relay_command(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::string, go_boost::async::placebo_lockable>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::wstring, go_boost::async::placebo_lockable>::basic_relay_command(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::wstring, go_boost::async::placebo_lockable>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<class S, class L>
inline basic_relay_command<S, L>::basic_relay_command(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<S, L>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline bool basic_relay_command<std::string, boost::recursive_mutex>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::wstring, boost::recursive_mutex>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::string, go_boost::async::placebo_lockable>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::wstring, go_boost::async::placebo_lockable>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<class S, class L>
inline bool basic_relay_command<S, L>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline void basic_relay_command<std::string, boost::recursive_mutex>::execute(const command_parameters_type& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::wstring, boost::recursive_mutex>::execute(const command_parameters_type& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::string, go_boost::async::placebo_lockable>::execute(const command_parameters_type& params)
{
    if (_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::wstring, go_boost::async::placebo_lockable>::execute(const command_parameters_type& params)
{
    if (_execute)
    {
        _execute(params);
    }
}

template<class S, class L>
inline void basic_relay_command<S, L>::execute(const command_parameters_type& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline boost::shared_ptr<basic_relay_command<std::string, boost::recursive_mutex>> basic_relay_command<std::string, boost::recursive_mutex>::create(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::string&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_relay_command<std::wstring, boost::recursive_mutex>> basic_relay_command<std::wstring, boost::recursive_mutex>::create(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_relay_command<std::string, go_boost::async::placebo_lockable>> basic_relay_command<std::string, go_boost::async::placebo_lockable>::create(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::string&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_relay_command<std::wstring, go_boost::async::placebo_lockable>> basic_relay_command<std::wstring, go_boost::async::placebo_lockable>::create(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<class S, class L>
inline boost::shared_ptr<basic_relay_command<S, L>> basic_relay_command<S, L>::create(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const S&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
