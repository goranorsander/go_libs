#ifndef GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/make_shared.hpp>
#include <go_boost/mvvm/notify_container_changed_action.hpp>
#include <go_boost/property/nameless/read_only_value_property.hpp>
#include <go_boost/signals/slot_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

class container_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef container_changed_arguments this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~container_changed_arguments() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    container_changed_arguments(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_)
        : go_boost::signals::slot_arguments()
        , action(action_)
        , added_elements(added_elements_)
        , removed_elements(removed_elements_)
        , new_size(new_size_)
    {
    }

public:
    go_boost::property::nameless::read_only::value_property<notify_container_changed_action> action;
    go_boost::property::nameless::read_only::value_property<std::size_t> added_elements;
    go_boost::property::nameless::read_only::value_property<std::size_t> removed_elements;
    go_boost::property::nameless::read_only::value_property<std::size_t> new_size;

public:
    static boost::shared_ptr<container_changed_arguments> create(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_) : this_type(action_, added_elements_, removed_elements_, new_size_) {}
        };

        return boost::make_shared<make_shared_enabler, const notify_container_changed_action&, const std::size_t&, const std::size_t&, const std::size_t&>(action_, added_elements_, removed_elements_, new_size_);
#else
        return boost::shared_ptr<this_type>(new this_type(action_, added_elements_, removed_elements_, new_size_));
#endif // BOOST_MSVC > 1500
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
