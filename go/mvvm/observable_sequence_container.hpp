#ifndef GO_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED

//
//  observable_sequence_container.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/observable_container.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C, class L = std::recursive_mutex>
class basic_observable_sequence_container
    : public basic_observable_container<S, C, L>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef L lockable_type;
    typedef basic_observable_sequence_container<string_type, container_type, lockable_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
        : basic_observable_container<string_type, container_type, lockable_type>()
    {
    }

public:
    iterator begin() noexcept
    {
        return this->container().begin();
    }

    GO_CONSTEXPR const_iterator begin() const noexcept
    {
        return this->container().begin();
    }

    iterator end() noexcept
    {
        return this->container().end();
    }

    GO_CONSTEXPR const_iterator end() const noexcept
    {
        return this_type::ontainer().end();
    }

    GO_CONSTEXPR const_iterator cbegin() const noexcept
    {
        return this->container().cbegin();
    }

    GO_CONSTEXPR const_iterator cend() const noexcept
    {
        return this->container().cend();
    }

    GO_CONSTEXPR size_type max_size() const noexcept
    {
        return this->container().max_size();
    }

    GO_CONSTEXPR bool empty() const noexcept
    {
        return this->container().empty();
    }

    reference front()
    {
        return this->container().front();
    }

    GO_CONSTEXPR const_reference front() const
    {
        return this->container().front();
    }

protected:
    void notify_assign(const std::size_t& before, const std::size_t& after)
    {
        if(before > 0)
        {
            this->notify_container_changed(after > 0 ? notify_container_changed_action::reset : notify_container_changed_action::remove, after, before, after);
        }
        else if(after > 0)
        {
            this->notify_container_changed(notify_container_changed_action::add, after, 0, after);
        }
    }

    void notify_insert(const std::size_t& before, const std::size_t& after)
    {
        if(after - before > 0)
        {
            this->notify_container_changed(notify_container_changed_action::add, after - before, 0, after);
        }
    }

    void notify_erase(const std::size_t& before, const std::size_t& after)
    {
        if(before - after > 0)
        {
            this->notify_container_changed(notify_container_changed_action::remove, 0, before - after, after);
        }
    }
};

template<class S, class C, class L>
inline basic_observable_sequence_container<S, C, L>::~basic_observable_sequence_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_SEQUENCE_CONTAINER_HPP_INCLUDED
