#ifndef GO_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_ordered_associative_container.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/observable_associative_container.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C, class L = std::recursive_mutex>
class basic_observable_ordered_associative_container
    : public basic_observable_associative_container<S, C, L>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef L lockable_type;
    typedef basic_observable_ordered_associative_container<S, C, L> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::key_compare key_compare;
    typedef typename container_type::value_compare value_compare;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::reverse_iterator reverse_iterator;
    typedef typename container_type::const_reverse_iterator const_reverse_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~basic_observable_ordered_associative_container() = 0;

protected:
    basic_observable_ordered_associative_container()
        : basic_observable_associative_container<string_type, container_type, lockable_type>()
    {
    }

public:
    reverse_iterator rbegin() noexcept
    {
        return this->container().rbegin();
    }

    GO_CONSTEXPR const_reverse_iterator rbegin() const noexcept
    {
        return this->container().rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return this->container().rend();
    }

    GO_CONSTEXPR const_reverse_iterator rend() const noexcept
    {
        return this->container().rend();
    }

    GO_CONSTEXPR const_reverse_iterator crbegin() const noexcept
    {
        return this->container().crbegin();
    }

    GO_CONSTEXPR const_reverse_iterator crend() const noexcept
    {
        return this->container().crend();
    }

    iterator lower_bound(const value_type& val)
    {
        return this->container().lower_bound(val);
    }

    GO_CONSTEXPR const_iterator lower_bound(const value_type& val) const
    {
        return this->container().lower_bound(val);
    }

    iterator upper_bound(const value_type& val)
    {
        return this->container().upper_bound(val);
    }

    GO_CONSTEXPR const_iterator upper_bound(const value_type& val) const
    {
        return this->container().upper_bound(val);
    }

    GO_CONSTEXPR key_compare key_comp() const
    {
        return this->container().key_comp();
    }

    GO_CONSTEXPR value_compare value_comp() const
    {
        return this->container().key_comp();
    }
};

template<class S, class C, class L>
inline basic_observable_ordered_associative_container<S, C, L>::~basic_observable_ordered_associative_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
