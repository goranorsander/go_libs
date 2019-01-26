#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2019 Göran Orsander
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
#include <go/exception.hpp>
#include <go/mvvm/notify_command_execution_interface.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>
#include <go/utility/placebo_lockable.hpp>
#include <go/utility/recursive_spin_lock.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_command_manager;
typedef basic_command_manager<std::string, go::utility::recursive_spin_lock> command_manager;
typedef basic_command_manager<std::wstring, go::utility::recursive_spin_lock> wcommand_manager;

namespace single_threaded
{

typedef basic_command_manager<std::string, go::utility::placebo_lockable> command_manager;
typedef basic_command_manager<std::wstring, go::utility::placebo_lockable> wcommand_manager;

}

template<class S, class L = go::utility::recursive_spin_lock>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, L>
    , public go::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_command_manager<S, L> this_type;
    typedef typename std::shared_ptr<basic_command_manager<S, L>> ptr;
    typedef typename std::weak_ptr<basic_command_manager<S, L>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager() GO_DEFAULT_CONSTRUCTOR

public:
    static ptr create();

    void execute(const std::shared_ptr<basic_command_interface<S, L>>& command) const;
    void post(const std::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable lockable_type _commands_guard;
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S, L>>, std::shared_ptr<basic_command_interface<S, L>>>> _commands;
};

template<class S, class L>
inline basic_command_manager<S, L>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline void basic_command_manager<std::string, go::utility::recursive_spin_lock>::execute(const std::shared_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>& command) const
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
inline void basic_command_manager<std::wstring, go::utility::recursive_spin_lock>::execute(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>& command) const
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
inline void basic_command_manager<std::string, go::utility::placebo_lockable>::execute(const std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>& command) const
{
    if (command)
    {
        const auto params = command->parameters();
        if (command->can_execute(params))
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
inline void basic_command_manager<std::wstring, go::utility::placebo_lockable>::execute(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>& command) const
{
    if (command)
    {
        const auto params = command->parameters();
        if (command->can_execute(params))
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

template<class S, class L>
inline void basic_command_manager<S, L>::execute(const std::shared_ptr<basic_command_interface<S, L>>& command) const
{
    if(command)
    {
        const auto params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            basic_notify_command_execution_interface<S, L>::notify_command_executed(command);
        }
        else
        {
            basic_notify_command_execution_interface<S, L>::notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::string, go::utility::recursive_spin_lock>::post(const std::shared_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>, std::shared_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>>(std::weak_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::wstring, go::utility::recursive_spin_lock>::post(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>, std::shared_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>>(std::weak_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::string, go::utility::placebo_lockable>::post(const std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>, std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>>(std::weak_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::wstring, go::utility::placebo_lockable>::post(const std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>, std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>>(std::weak_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>(command), keep_command_alive ? command : nullptr));
    }
}

template<class S, class L>
inline void basic_command_manager<S, L>::post(const std::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        _commands.push_back(std::pair<std::weak_ptr<basic_command_interface<S, L>>, std::shared_ptr<basic_command_interface<S, L>>>(std::weak_ptr<basic_command_interface<S, L>>(command), keep_command_alive ? command : nullptr));
    }
}

template<>
inline void basic_command_manager<std::string, go::utility::recursive_spin_lock>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>, std::shared_ptr<basic_command_interface<std::string, go::utility::recursive_spin_lock>>>> commands;
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, go::utility::recursive_spin_lock>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>, std::shared_ptr<basic_command_interface<std::wstring, go::utility::recursive_spin_lock>>>> commands;
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::string, go::utility::placebo_lockable>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>, std::shared_ptr<basic_command_interface<std::string, go::utility::placebo_lockable>>>> commands;
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for (const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, go::utility::placebo_lockable>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>, std::shared_ptr<basic_command_interface<std::wstring, go::utility::placebo_lockable>>>> commands;
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for (const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<class S, class L>
inline void basic_command_manager<S, L>::execute_commands()
{
    std::deque<std::pair<std::weak_ptr<basic_command_interface<S, L>>, std::shared_ptr<basic_command_interface<S, L>>>> commands;
    {
        const std::lock_guard<lockable_type> lock(_commands_guard);
        std::swap(commands, _commands);
    }
    for(const auto& wcommand : commands)
    {
        const auto command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline size_t basic_command_manager<std::string, go::utility::recursive_spin_lock>::commands() const
{
    const std::lock_guard<lockable_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, go::utility::recursive_spin_lock>::commands() const
{
    const std::lock_guard<lockable_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::string, go::utility::placebo_lockable>::commands() const
{
    const std::lock_guard<lockable_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, go::utility::placebo_lockable>::commands() const
{
    const std::lock_guard<lockable_type> lock(_commands_guard);
    return _commands.size();
}

template<class S, class L>
inline size_t basic_command_manager<S, L>::commands() const
{
    const std::lock_guard<lockable_type> lock(_commands_guard);
    return _commands.size();
}

template<>
inline std::shared_ptr<basic_command_manager<std::string, go::utility::recursive_spin_lock>> basic_command_manager<std::string, go::utility::recursive_spin_lock>::create()
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
inline std::shared_ptr<basic_command_manager<std::wstring, go::utility::recursive_spin_lock>> basic_command_manager<std::wstring, go::utility::recursive_spin_lock>::create()
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
inline std::shared_ptr<basic_command_manager<std::string, go::utility::placebo_lockable>> basic_command_manager<std::string, go::utility::placebo_lockable>::create()
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
inline std::shared_ptr<basic_command_manager<std::wstring, go::utility::placebo_lockable>> basic_command_manager<std::wstring, go::utility::placebo_lockable>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

template<class S, class L>
inline std::shared_ptr<basic_command_manager<S, L>> basic_command_manager<S, L>::create()
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
