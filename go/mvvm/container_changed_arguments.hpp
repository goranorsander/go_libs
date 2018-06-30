#ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
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

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/property/nameless/read_only_value_property.hpp>
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
    virtual ~container_changed_arguments() GO_DEFAULT_DESTRUCTOR

protected:
    container_changed_arguments(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_)
        : go::signals::slot_arguments()
        , action(action_)
        , added_elements(added_elements_)
        , removed_elements(removed_elements_)
        , new_size(new_size_)
    {
    }

public:
    go::property::nameless::read_only::value_property<notify_container_changed_action> action;
    go::property::nameless::read_only::value_property<std::size_t> added_elements;
    go::property::nameless::read_only::value_property<std::size_t> removed_elements;
    go::property::nameless::read_only::value_property<std::size_t> new_size;

public:
    static std::shared_ptr<container_changed_arguments> create(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_) : this_type(action_, added_elements_, removed_elements_, new_size_) {}
        };

        return std::make_shared<make_shared_enabler, const notify_container_changed_action&, const std::size_t&, const std::size_t&, const std::size_t&>(action_, added_elements_, removed_elements_, new_size_);
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
