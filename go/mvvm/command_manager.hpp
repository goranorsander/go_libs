#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>
#include <vector>
#include <go/mvvm/command.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_command_manager;
typedef basic_command_manager<std::string> command_manager;
typedef basic_command_manager<std::wstring> wcommand_manager;

template<class S>
class basic_command_manager
{
public:
    typedef S string_type;
    typedef basic_command_manager<S> this_type;
    typedef typename std::shared_ptr<basic_command_manager<S>> ptr;
    typedef typename std::weak_ptr<basic_command_manager<S>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager() = default;

private:
    basic_command_manager(const basic_command_manager<S>&) = delete;
    basic_command_manager(basic_command_manager<S>&&) = delete;

    basic_command_manager<S>& operator=(const basic_command_manager<S>&) = delete;
    basic_command_manager<S>& operator=(basic_command_manager<S>&&) = delete;

public:
    static std::shared_ptr<basic_command_manager<S>> create();

    void add_command(const std::shared_ptr<basic_command<S>>& cmd);

    void execute_commands();

    size_t commands() const;

private:
    mutable std::recursive_mutex _commands_guard;
    std::vector<std::weak_ptr<basic_command<S>>> _commands;
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

template<>
inline std::shared_ptr<basic_command_manager<std::string>> basic_command_manager<std::string>::create()
{
    struct make_shared_enabler
        : public basic_command_manager<std::string>
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() = default;
    };

    return std::make_shared<make_shared_enabler>();
}

template<>
inline std::shared_ptr<basic_command_manager<std::wstring>> basic_command_manager<std::wstring>::create()
{
    struct make_shared_enabler
        : public basic_command_manager<std::wstring>
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() = default;
    };

    return std::make_shared<make_shared_enabler>();
}

template<class S>
inline std::shared_ptr<basic_command_manager<S>> basic_command_manager<S>::create()
{
    struct make_shared_enabler
        : public basic_command_manager<S>
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() = default;
    };

    return std::make_shared<make_shared_enabler>();
}

template<>
inline void basic_command_manager<std::string>::add_command(const std::shared_ptr<basic_command<std::string>>& cmd)
{
    if(cmd)
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::weak_ptr<basic_command<std::string>>(cmd));
    }
}

template<>
inline void basic_command_manager<std::wstring>::add_command(const std::shared_ptr<basic_command<std::wstring>>& cmd)
{
    if(cmd)
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::weak_ptr<basic_command<std::wstring>>(cmd));
    }
}

template<class S>
inline void basic_command_manager<S>::add_command(const std::shared_ptr<basic_command<S>>& cmd)
{
    if(cmd)
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        _commands.push_back(std::weak_ptr<basic_command<S>>(cmd));
    }
}

template<>
inline void basic_command_manager<std::string>::execute_commands()
{
    std::vector<std::weak_ptr<basic_command<std::string>>> cmds;
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(std::weak_ptr<basic_command<std::string>> wcmd : cmds)
    {
        const std::shared_ptr<basic_command<std::string>> cmd = wcmd.lock();
        if(cmd)
        {
            const std::shared_ptr<command_parameters> params = cmd->parameters();
            if(cmd->can_execute(params))
            {
                cmd->execute(params);
            }
        }
    }
}

template<>
inline void basic_command_manager<std::wstring>::execute_commands()
{
    std::vector<std::weak_ptr<basic_command<std::wstring>>> cmds;
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(std::weak_ptr<basic_command<std::wstring>> wcmd : cmds)
    {
        const std::shared_ptr<basic_command<std::wstring>> cmd = wcmd.lock();
        if(cmd)
        {
            const std::shared_ptr<command_parameters> params = cmd->parameters();
            if(cmd->can_execute(params))
            {
                cmd->execute(params);
            }
        }
    }
}

template<class S>
inline void basic_command_manager<S>::execute_commands()
{
    std::vector<std::weak_ptr<basic_command<S>>> cmds;
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    for(std::weak_ptr<basic_command<S>> wcmd : cmds)
    {
        const std::shared_ptr<basic_command<S>> cmd = wcmd.lock();
        if(cmd)
        {
            const std::shared_ptr<command_parameters> params = cmd->parameters();
            if(cmd->can_execute(params))
            {
                cmd->execute(params);
            }
        }
    }
}

template<>
inline size_t basic_command_manager<std::string>::commands() const
{
    std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring>::commands() const
{
    std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

template<class S>
inline size_t basic_command_manager<S>::commands() const
{
    std::lock_guard<std::recursive_mutex> lock(_commands_guard);
    return _commands.size();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
