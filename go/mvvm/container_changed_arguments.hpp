#ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/mvvm/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

class container_changed_arguments
    : public slot_arguments
{
public:
    typedef std::shared_ptr<container_changed_arguments> ptr;
    typedef std::weak_ptr<container_changed_arguments> wptr;

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
} // namespace go

#endif  // #ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
