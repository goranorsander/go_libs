#ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/signals/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

class container_changed_arguments
    : public go::signals::slot_arguments
{
public:
    typedef container_changed_arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~container_changed_arguments() = default;

private:
    container_changed_arguments(const this_type&) = delete;
    container_changed_arguments(this_type&&) = delete;

    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = delete;

protected:
    container_changed_arguments(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
        : go::signals::slot_arguments()
        , _action(action)
        , _added_elements(added_elements)
        , _removed_elements(removed_elements)
        , _new_size(new_size)
    {
    }

public:
    static std::shared_ptr<container_changed_arguments> create(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() = default;
            make_shared_enabler(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
                : this_type(action, added_elements, removed_elements, new_size)
            {
            }
        };

        return std::make_shared<make_shared_enabler, const notify_container_changed_action&, const std::size_t&, const std::size_t&, const std::size_t&>(action, added_elements, removed_elements, new_size);
    }

    notify_container_changed_action action() const
    {
        return _action;
    }

    std::size_t added_elements() const
    {
        return _added_elements;
    }

    std::size_t removed_elements() const
    {
        return _removed_elements;
    }

    std::size_t new_size() const
    {
        return _new_size;
    }

private:
    const notify_container_changed_action _action;
    const std::size_t _added_elements;
    const std::size_t _removed_elements;
    const std::size_t _new_size;
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
