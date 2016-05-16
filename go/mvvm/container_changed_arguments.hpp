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
    typedef typename container_changed_arguments this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~container_changed_arguments()
    {
    }

private:
    container_changed_arguments(const container_changed_arguments&) = delete;

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
    static ptr create(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
    {
        return ptr(new this_type(action, added_elements, removed_elements, new_size));
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

#endif  // #ifndef GO_MVVM_CONTAINER_CHANGED_ARGUMENTS_HPP_INCLUDED
