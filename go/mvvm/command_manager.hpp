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

template<class S>
class basic_command_manager
{
public:
    typedef S string_type;
    typedef basic_command_manager<string_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef typename go::signals::signal<std::function<void(const string_type&)>> requery_suggested_signal;

protected:
    typedef basic_command<string_type> command_type;
    typedef typename std::shared_ptr<command_type> command_type_ptr;
    typedef typename std::weak_ptr<command_type> command_type_wptr;
    typedef typename std::vector<command_type_wptr> command_vector;

public:
    virtual ~basic_command_manager()
    {
        _commands.clear();
    }

protected:
    basic_command_manager() = default;

private:
    basic_command_manager(const this_type&) = delete;
    basic_command_manager(this_type&&) = delete;

    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = delete;

public:
    requery_suggested_signal requery_suggested;

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() = default;
            make_shared_enabler() = default;
        };

        return std::make_shared<make_shared_enabler>();
    }

    void add_command(const command_type_ptr& cmd)
    {
        if(cmd)
        {
            std::lock_guard<std::recursive_mutex> lock(_commands_guard);
            _commands.push_back(command_type_wptr(cmd));
        }
    }

    void execute_commands()
    {
        command_vector cmds;
        {
            std::lock_guard<std::recursive_mutex> lock(_commands_guard);
            std::swap(cmds, _commands);
        }
        for(command_type_wptr wcmd : cmds)
        {
            const command_type_ptr cmd = wcmd.lock();
            if(cmd)
            {
                const command_parameters::ptr params = cmd->parameters();
                if(cmd->can_execute(params))
                {
                    cmd->execute(params);
                }
            }
        }
    }

    size_t commands() const
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        return _commands.size();
    }

private:
    mutable std::recursive_mutex _commands_guard;
    command_vector _commands;
};

class command_manager
    : public basic_command_manager<std::string>
{
public:
    typedef command_manager this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~command_manager() = default;

protected:
    command_manager()
        : basic_command_manager<string_type>()
    {
    }

private:
    command_manager(const this_type&) = delete;
    command_manager(this_type&&) = delete;

    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = delete;

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() = default;
            make_shared_enabler() = default;
        };

        return std::make_shared<make_shared_enabler>();
    }
};

class wcommand_manager
    : public basic_command_manager<std::wstring>
{
public:
    typedef wcommand_manager this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~wcommand_manager() = default;

protected:
    wcommand_manager()
        : basic_command_manager<string_type>()
    {
    }

private:
    wcommand_manager(const this_type&) = delete;
    wcommand_manager(this_type&&) = delete;

    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = delete;

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() = default;
            make_shared_enabler() = default;
        };

        return std::make_shared<make_shared_enabler>();
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
