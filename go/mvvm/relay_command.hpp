#ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/command_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_relay_command;
typedef basic_relay_command<std::string, std::recursive_mutex> relay_command;
typedef basic_relay_command<std::wstring, std::recursive_mutex> relay_wcommand;

namespace single_threaded
{

typedef basic_relay_command<std::string, go::utility::placebo_lockable> relay_command;
typedef basic_relay_command<std::wstring, go::utility::placebo_lockable> relay_wcommand;

}

template<class S, class L = std::recursive_mutex>
class basic_relay_command
    : public basic_command_interface<S, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_relay_command<S, L> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef typename std::shared_ptr<command_parameters> command_parameters_type;
    typedef typename std::function<bool(const command_parameters_type&)> can_execute_command_signature;
    typedef typename std::function<void(const command_parameters_type&)> execute_command_signature;

public:
    virtual ~basic_relay_command() GO_DEFAULT_DESTRUCTOR

protected:
    basic_relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

public:
    static std::shared_ptr<basic_relay_command<S, L>> create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

protected:
    virtual bool can_execute(const command_parameters_type& params);

    virtual void execute(const command_parameters_type& params);

private:
    can_execute_command_signature _can_execute;
    execute_command_signature _execute;
};

template<>
inline basic_relay_command<std::string, std::recursive_mutex>::basic_relay_command(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::string, std::recursive_mutex>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::wstring, std::recursive_mutex>::basic_relay_command(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::wstring, std::recursive_mutex>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::string, go::utility::placebo_lockable>::basic_relay_command(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::string, go::utility::placebo_lockable>(cmd_name, params)
    , _can_execute(can_execute_command)
    , _execute(execute_command)
{
}

template<>
inline basic_relay_command<std::wstring, go::utility::placebo_lockable>::basic_relay_command(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
    : basic_command_interface<std::wstring, go::utility::placebo_lockable>(cmd_name, params)
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
inline bool basic_relay_command<std::string, std::recursive_mutex>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::wstring, std::recursive_mutex>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::string, go::utility::placebo_lockable>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline bool basic_relay_command<std::wstring, go::utility::placebo_lockable>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<class S, class L>
inline bool basic_relay_command<S, L>::can_execute(const command_parameters_type& params)
{
    return _can_execute ? _can_execute(params) : true;
}

template<>
inline void basic_relay_command<std::string, std::recursive_mutex>::execute(const command_parameters_type& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::wstring, std::recursive_mutex>::execute(const command_parameters_type& params)
{
    if(_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::string, go::utility::placebo_lockable>::execute(const command_parameters_type& params)
{
    if (_execute)
    {
        _execute(params);
    }
}

template<>
inline void basic_relay_command<std::wstring, go::utility::placebo_lockable>::execute(const command_parameters_type& params)
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
inline std::shared_ptr<basic_relay_command<std::string, std::recursive_mutex>> basic_relay_command<std::string, std::recursive_mutex>::create(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return std::make_shared<make_shared_enabler, const std::string&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
}

template<>
inline std::shared_ptr<basic_relay_command<std::wstring, std::recursive_mutex>> basic_relay_command<std::wstring, std::recursive_mutex>::create(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return std::make_shared<make_shared_enabler, const std::wstring&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
}

template<>
inline std::shared_ptr<basic_relay_command<std::string, go::utility::placebo_lockable>> basic_relay_command<std::string, go::utility::placebo_lockable>::create(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const std::string& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return std::make_shared<make_shared_enabler, const std::string&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
}

template<>
inline std::shared_ptr<basic_relay_command<std::wstring, go::utility::placebo_lockable>> basic_relay_command<std::wstring, go::utility::placebo_lockable>::create(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const std::wstring& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return std::make_shared<make_shared_enabler, const std::wstring&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
}

template<class S, class L>
inline std::shared_ptr<basic_relay_command<S, L>> basic_relay_command<S, L>::create(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const S& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params) : this_type(cmd_name, execute_command, can_execute_command, params) {}
    };

    return std::make_shared<make_shared_enabler, const S&, const execute_command_signature&, const can_execute_command_signature&, const command_parameters_type&>(cmd_name, execute_command, can_execute_command, params);
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
