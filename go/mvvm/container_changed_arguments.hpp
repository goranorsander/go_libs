#ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/signals/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

class container_changed_arguments
    : public slot_arguments
{
public:
    typedef container_changed_arguments this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~container_changed_arguments()
    {
    }

private:
    container_changed_arguments(const container_changed_arguments&) = delete;

protected:
    container_changed_arguments(const notify_container_changed_action& action)
        : slot_arguments()
        , _action(action)
    {
    }

public:
    static ptr create(const notify_container_changed_action& action)
    {
        return ptr(new this_type(action));
    }

    notify_container_changed_action action() const
    {
        return _action;
    }

private:
    const notify_container_changed_action _action;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
