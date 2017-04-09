#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <deque>
#include <mutex>
#include <go/exception.hpp>
#include <go/mvvm/notify_command_execution_interface.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_manager;
typedef basic_command_manager<std::string> command_manager;
typedef basic_command_manager<std::wstring> wcommand_manager;

template<class S>
class basic_command_manager
    : public basic_notify_command_execution_interface<S>
    , public go::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef basic_command_manager<S> this_type;
    typedef typename std::shared_ptr<basic_command_manager<S>> ptr;
    typedef typename std::weak_ptr<basic_command_manager<S>> wptr;

public:
    virtual ~basic_command_manager();

protected:

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    basic_command_manager();

#else

    basic_command_manager() = default;

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

public:
    static std::shared_ptr<basic_command_manager<S>> create();

    void execute(const std::shared_ptr<basic_command_interface<S>>& cmd) const;
    void post(const std::shared_ptr<basic_command_interface<S>>& cmd, const bool keep_cmd_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable std::recursive_mutex _commands_guard;
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S>>, std::shared_ptr<basic_command_interface<S>>>> _commands;
};

template<>
inline basic_command_manager<std::string>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring>::~basic_command_manager()
{
    _commands.clear();
}

template<class S>
inline basic_command_manager<S>::~basic_command_manager()
{
    _commands.clear();
}

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

template<>
inline basic_command_manager<std::string>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string>()
    , go::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
}

template<>
inline basic_command_manager<std::wstring>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring>()
    , go::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
}

template<class S>
inline basic_command_manager<S>::basic_command_manager()
    : basic_notify_command_execution_interface<S>()
    , go::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
}

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

template<>
inline void basic_command_manager<std::string>::execute(const std::shared_ptr<basic_command_interface<std::string>>& cmd) const
{
    if(cmd)
    {
        const auto params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed.call(cmd);
        }
        else
        {
            command_not_executed.call(cmd);
        }
    }
}

template<>
inline void basic_command_manager<std::wstring>::execute(const std::shared_ptr<basic_command_interface<std::wstring>>& cmd) const
{
    if(cmd)
    {
        const auto params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed.call(cmd);
        }
        else
        {
            command_not_executed.call(cmd);
        }
    }
}

template<class S>
inline void basic_command_manager<S>::execute(const std::shared_ptr<basic_command_interface<S>>& cmd) const
{
#if defined(GO_COMP_CLANG) || defined(GO_COMP_GCC)
    throw go::exception::exception("Unsupported string class used by basic_command_manager<S>::execute(...)");
#else
    if(cmd)
    {
        const auto params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed.call(cmd);
        }
        else
        {
            command_not_executed.call(cmd);
        }
    }
#endif  // #if defined(GO_COMP_GCC) && defined(GO_GCC_VERSION < 60000)
}

template<>
inline void basic_command_manager<std::string>::post(const std::shared_ptr<basic_command_interface<std::string>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::string>>, std::shared_ptr<basic_command_interface<std::string>>>(std::weak_ptr<basic_command_interface<std::string>>(cmd), keep_cmd_alive ? cmd : nullptr));
    }
}

template<>
inline void basic_command_manager<std::wstring>::post(const std::shared_ptr<basic_command_interface<std::wstring>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::wstring>>, std::shared_ptr<basic_command_interface<std::wstring>>>(std::weak_ptr<basic_command_interface<std::wstring>>(cmd), keep_cmd_alive ? cmd : nullptr));
    }
}

template<class S>
inline void basic_command_manager<S>::post(const std::shared_ptr<basic_command_interface<S>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<S>>, std::shared_ptr<basic_command_interface<S>>>(std::weak_ptr<basic_command_interface<S>>(cmd), keep_cmd_alive ? cmd : nullptr));
    }
}

template<>
inline void basic_command_manager<std::string>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::string>>, std::shared_ptr<basic_command_interface<std::string>>>> cmds;
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(const auto& wcmd : cmds)
    {
        const auto cmd = wcmd.first.lock();
        execute(cmd);
    }
}

template<>
inline void basic_command_manager<std::wstring>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::wstring>>, std::shared_ptr<basic_command_interface<std::wstring>>>> cmds;
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(const auto& wcmd : cmds)
    {
        const auto cmd = wcmd.first.lock();
        execute(cmd);
    }
}

template<class S>
inline void basic_command_manager<S>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S>>, std::shared_ptr<basic_command_interface<S>>>> cmds;
    {
        const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(const auto& wcmd : cmds)
    {
        const auto cmd = wcmd.first.lock();
        execute(cmd);
    }
}

template<>
inline size_t basic_command_manager<std::string>::commands() const
{
    const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring>::commands() const
{
    const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

template<class S>
inline size_t basic_command_manager<S>::commands() const
{
    const std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

template<>
inline std::shared_ptr<basic_command_manager<std::string>> basic_command_manager<std::string>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

template<>
inline std::shared_ptr<basic_command_manager<std::wstring>> basic_command_manager<std::wstring>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

template<class S>
inline std::shared_ptr<basic_command_manager<S>> basic_command_manager<S>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
