#ifndef GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
#define GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED

//
//  command_interface.hpp
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

#include <mutex>
#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/read_only_property.hpp>
#include <go/signals/signal.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>
#include <go/utility/placebo_mutex.hpp>

namespace go
{
namespace mvvm
{

template<class S, typename M> class basic_command_manager;

template<class S, typename M> class basic_command_interface;
typedef basic_command_interface<std::string, std::recursive_mutex> command_interface;
typedef basic_command_interface<std::wstring, std::recursive_mutex> wcommand_interface;

namespace single_threaded
{

typedef basic_command_interface<std::string, go::utility::placebo_mutex> command_interface;
typedef basic_command_interface<std::wstring, go::utility::placebo_mutex> wcommand_interface;

}

template<class S, typename M = std::recursive_mutex>
class basic_command_interface
    : public std::enable_shared_from_this<basic_command_interface<S, M>>
    , public go::utility::noncopyable_nonmovable
{
    friend class basic_command_manager<S, M>;

public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_command_interface<S, M> this_type;
    typedef typename std::shared_ptr<basic_command_interface<S, M>> ptr;
    typedef typename std::weak_ptr<basic_command_interface<S, M>> wptr;
    typedef typename std::shared_ptr<command_parameters> command_parameters_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_command_interface<S, M>>&)>, M> can_execute_changed_signal;
    typedef typename go::property::nameless::read_only::property<S> command_name_type;

public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const command_parameters_type& params);

public:
    virtual std::shared_ptr<command_parameters> parameters() const;

    virtual void notify_can_execute_changed();

protected:
    virtual bool can_execute(const command_parameters_type& params) = 0;

    virtual void execute(const command_parameters_type& params) = 0;

public:
    command_name_type command_name;
    can_execute_changed_signal can_execute_changed;

private:
    const S _command_name;
    command_parameters_type _parameters;
};

template<class S, typename M>
inline basic_command_interface<S, M>::~basic_command_interface()
{
    can_execute_changed.disconnect_all_slots();
}

template<class S, typename M>
inline basic_command_interface<S, M>::basic_command_interface(const S& cmd_name, const command_parameters_type& params)
    : std::enable_shared_from_this<basic_command_interface<S, M>>()
    , go::utility::noncopyable_nonmovable()
    , command_name(nullptr)
    , can_execute_changed()
    , _command_name(cmd_name)
    , _parameters(params)
{
    command_name.getter([this]() -> S { return _command_name; });
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::string, std::recursive_mutex>::parameters() const
{
    return _parameters;
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::wstring, std::recursive_mutex>::parameters() const
{
    return _parameters;
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::string, go::utility::placebo_mutex>::parameters() const
{
    return _parameters;
}

template<>
inline std::shared_ptr<command_parameters> basic_command_interface<std::wstring, go::utility::placebo_mutex>::parameters() const
{
    return _parameters;
}

template<class S, typename M>
inline std::shared_ptr<command_parameters> basic_command_interface<S, M>::parameters() const
{
    return _parameters;
}

template<>
inline void basic_command_interface<std::string, std::recursive_mutex>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring, std::recursive_mutex>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::string, go::utility::placebo_mutex>::notify_can_execute_changed()
{
    if (!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<>
inline void basic_command_interface<std::wstring, go::utility::placebo_mutex>::notify_can_execute_changed()
{
    if (!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

template<class S, typename M>
inline void basic_command_interface<S, M>::notify_can_execute_changed()
{
    if(!can_execute_changed.empty())
    {
        can_execute_changed(this->shared_from_this());
    }
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_COMMAND_INTERFACE_HPP_INCLUDED
