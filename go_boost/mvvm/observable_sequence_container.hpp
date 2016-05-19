#ifndef GO_BOOST_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED

//
//  observable_sequence_container.hpp
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

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C> class basic_observable_sequence_container
    : public basic_observable_container<S, C>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_sequence_container<string_type, container_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~basic_observable_sequence_container() = 0;

protected:
    basic_observable_sequence_container()
        : basic_observable_container<string_type, container_type>()
    {
    }

protected:
    virtual void on_container_changed(const notify_container_changed_action& /*action*/, const std::size_t& /*added_elements*/, const std::size_t& /*removed_elements*/, const std::size_t& /*new_size*/) = 0;

public:
    iterator begin()
    {
        return container().begin();
    }

    const_iterator begin() const
    {
        return container().begin();
    }

    iterator end()
    {
        return container().end();
    }

    const_iterator end() const
    {
        return container().end();
    }

    size_type max_size() const
    {
        return container().max_size();
    }

    bool empty() const
    {
        return container().empty();
    }

    reference front()
    {
        return container().front();
    }

    const_reference front() const
    {
        return container().front();
    }
};

template<class S, class C>
inline basic_observable_sequence_container<S, C>::~basic_observable_sequence_container()
{
}

template<class S, class C>
inline void basic_observable_sequence_container<S, C>::on_container_changed(const notify_container_changed_action& /*action*/, const std::size_t& /*added_elements*/, const std::size_t& /*removed_elements*/, const std::size_t& /*new_size*/)
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED
