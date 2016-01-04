#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED

//
//  notify_container_changed.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/mvvm/container_changed_arguments.hpp>
#include <go/mvvm/object.hpp>
#include <go/mvvm/signal.hpp>
//#include <boost/signals2.hpp>

namespace go
{
namespace mvvm
{

class notify_container_changed
    : public signal
{
public:
    typedef container_changed_arguments container_changed_arguments_type;
    typedef boost::shared_ptr<container_changed_arguments_type> container_changed_arguments_type_ptr;
    typedef boost::signals2::signal<void(const object::ptr&, const container_changed_arguments_type_ptr&)> container_changed_signal;

public:
    virtual ~notify_container_changed() = 0
    {
        container_changed.disconnect_all_slots();
    }

protected:
    notify_container_changed()
    {
    }

public:
    container_changed_signal container_changed;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED
