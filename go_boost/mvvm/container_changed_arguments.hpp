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
    container_changed_arguments(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
        : go_boost::signals::slot_arguments()
        , _action(action)
        , _added_elements(added_elements)
        , _removed_elements(removed_elements)
        , _new_size(new_size)
    {
    }

public:
    static boost::shared_ptr<container_changed_arguments> create(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size) : this_type(action, added_elements, removed_elements, new_size) {}
        };

        return boost::make_shared<make_shared_enabler, const notify_container_changed_action&, const std::size_t&, const std::size_t&, const std::size_t&>(action, added_elements, removed_elements, new_size);
#else
        return boost::shared_ptr<this_type>(new this_type(action, added_elements, removed_elements, new_size));
#endif // BOOST_MSVC > 1500
    }

    GO_BOOST_CONSTEXPR notify_container_changed_action action() const
    {
        return _action;
    }

    GO_BOOST_CONSTEXPR std::size_t added_elements() const
    {
        return _added_elements;
    }

    GO_BOOST_CONSTEXPR std::size_t removed_elements() const
    {
        return _removed_elements;
    }

    GO_BOOST_CONSTEXPR std::size_t new_size() const
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
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
