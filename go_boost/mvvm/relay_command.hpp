#ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/make_shared.hpp>

#include <go_boost/mvvm/command_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_relay_command;
typedef basic_relay_command<std::string> relay_command;
typedef basic_relay_command<std::wstring> relay_wcommand;

template<class S>
class basic_relay_command
    : public basic_command_interface<S>
{
public:
    typedef S string_type;
    typedef basic_relay_command<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;
    typedef typename boost::function<bool(const boost::shared_ptr<command_parameters>&)> can_execute_command_signature;
    typedef typename boost::function<void(const boost::shared_ptr<command_parameters>&)> execute_command_signature;

public:
    virtual ~basic_relay_command();

protected:
    basic_relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params);

public:
    static boost::shared_ptr<basic_relay_command<S>> create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params);

private:
    virtual bool can_execute(const boost::shared_ptr<command_parameters>& params);

    virtual void execute(const boost::shared_ptr<command_parameters>& params);

private:
    can_execute_command_signature _can_execute;
    execute_command_signature _execute;
};

template<>
inline basic_relay_command<std::string>::~basic_relay_command()
{
}

template<>
inline basic_relay_command<std::wstring>::~basic_relay_command()
{
}

template<class S>
inline basic_relay_command<S>::~basic_relay_command()
{
}

template<>
inline basic_relay_command<std::string>::basic_relay_command(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
    : basic_command_interface<std::string>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::wstring>::basic_relay_command(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
    : basic_command_interface<std::wstring>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<class S>
inline basic_relay_command<S>::basic_relay_command(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
    : basic_command_interface<S>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline boost::shared_ptr<basic_relay_command<std::string>> basic_relay_command<std::string>::create(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::string&, const execute_command_signature&, const can_execute_command_signature&, const boost::shared_ptr<command_parameters>&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_relay_command<std::wstring>> basic_relay_command<std::wstring>::create(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const execute_command_signature&, const can_execute_command_signature&, const boost::shared_ptr<command_parameters>&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<class S>
inline boost::shared_ptr<basic_relay_command<S>> basic_relay_command<S>::create(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const boost::shared_ptr<command_parameters>& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return boost::make_shared<make_shared_enabler, const S&, const execute_command_signature&, const can_execute_command_signature&, const boost::shared_ptr<command_parameters>&>(cmd_name, execute_command, can_execute_command, params);
#else
    return boost::shared_ptr<this_type>(new this_type(cmd_name, execute_command, can_execute_command, params));
#endif // BOOST_MSVC > 1500
}

template<>
inline bool basic_relay_command<std::string>::can_execute(const boost::shared_ptr<command_parameters>& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::wstring>::can_execute(const boost::shared_ptr<command_parameters>& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<class S>
inline bool basic_relay_command<S>::can_execute(const boost::shared_ptr<command_parameters>& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline void basic_relay_command<std::string>::execute(const boost::shared_ptr<command_parameters>& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::wstring>::execute(const boost::shared_ptr<command_parameters>& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<class S>
inline void basic_relay_command<S>::execute(const boost::shared_ptr<command_parameters>& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
