#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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

template<class S, typename M> class basic_command_manager;
typedef basic_command_manager<std::string, std::recursive_mutex> command_manager;
typedef basic_command_manager<std::wstring, std::recursive_mutex> wcommand_manager;

template<class S, typename M = std::recursive_mutex>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, M>
    , public go::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_command_manager<S, M> this_type;
    typedef typename std::shared_ptr<basic_command_manager<S, M>> ptr;
    typedef typename std::weak_ptr<basic_command_manager<S, M>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager() GO_DEFAULT_CONSTRUCTOR

public:
    static ptr create();

    void execute(const std::shared_ptr<basic_command_interface<S, M>>& command) const;
    void post(const std::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable mutex_type _commands_guard;
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S, M>>, std::shared_ptr<basic_command_interface<S, M>>>> _commands;
};

template<>
inline basic_command_manager<std::string, std::recursive_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, std::recursive_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<class S, typename M>
inline basic_command_manager<S, M>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline void basic_command_manager<std::string, std::recursive_mutex>::execute(const std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>& command) const
{
    if(command)
    {
        const auto params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::wstring, std::recursive_mutex>::execute(const std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>& command) const
{
    if(command)
    {
        const auto params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute(const std::shared_ptr<basic_command_interface<S, M>>& command) const
{
#if defined(GO_COMP_CLANG) || defined(GO_COMP_GCC)
    throw go::exception::exception("Unsupported string class used by basic_command_manager<S, M>::execute(...)");
#else
    if(command)
    {
        const auto params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
#endif  // #if defined(GO_COMP_GCC) && defined(GO_GCC_VERSION < 60000)
}

template<>
inline void basic_command_manager<std::string, std::recursive_mutex>::post(const std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::string, std::recursive_mutex>>, std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>>(std::weak_ptr<basic_command_interface<std::string, std::recursive_mutex>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::wstring, std::recursive_mutex>::post(const std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>, std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>>(std::weak_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>(command), keep_command_alive ? command : nullptr));
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::post(const std::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<S, M>>, std::shared_ptr<basic_command_interface<S, M>>>(std::weak_ptr<basic_command_interface<S, M>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::string, std::recursive_mutex>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::string, std::recursive_mutex>>, std::shared_ptr<basic_command_interface<std::string, std::recursive_mutex>>>> commands;
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, std::recursive_mutex>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>, std::shared_ptr<basic_command_interface<std::wstring, std::recursive_mutex>>>> commands;
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S, M>>, std::shared_ptr<basic_command_interface<S, M>>>> commands;
    {
        const std::lock_guard<mutex_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline size_t basic_command_manager<std::string, std::recursive_mutex>::commands() const
{
    const std::lock_guard<mutex_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, std::recursive_mutex>::commands() const
{
    const std::lock_guard<mutex_type> lock(_commands_guard);
    return _commands.size();
}

template<class S, typename M>
inline size_t basic_command_manager<S, M>::commands() const
{
    const std::lock_guard<mutex_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline std::shared_ptr<basic_command_manager<std::string, std::recursive_mutex>> basic_command_manager<std::string, std::recursive_mutex>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

template<>
inline std::shared_ptr<basic_command_manager<std::wstring, std::recursive_mutex>> basic_command_manager<std::wstring, std::recursive_mutex>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

template<class S, typename M>
inline std::shared_ptr<basic_command_manager<S, M>> basic_command_manager<S, M>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
