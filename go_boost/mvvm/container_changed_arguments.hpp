#ifndef GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

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
    typedef typename container_changed_arguments this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~container_changed_arguments()
    {
    }

protected:
    container_changed_arguments(const notify_container_changed_action& action)
        : slot_arguments()
        , _action(action)
    {
    }

public:
    static ptr create(const notify_container_changed_action& action)
    {
        return ptr(new container_changed_arguments(action));
    }

    notify_container_changed_action action() const
    {
        return _action;
    }

private:
    const notify_container_changed_action _action;
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
