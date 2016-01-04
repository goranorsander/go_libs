#ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  container_changed_arguments.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/mvvm/signal_arguments.hpp>

namespace go
{
namespace mvvm
{

class container_changed_arguments
    : public signal_arguments
{
public:
    typedef boost::shared_ptr<container_changed_arguments> ptr;

public:
    virtual ~container_changed_arguments()
    {
    }

protected:
    container_changed_arguments(const notify_container_changed_action& action)
        : signal_arguments()
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
