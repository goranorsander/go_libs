#ifndef GO_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_ordered_associative_container.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX)
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
    using string_type = S;
    using container_type = C;
    using lockable_type = L;
    using this_type = basic_observable_ordered_associative_container<S, C, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using key_compare = typename container_type::key_compare;
    using value_compare = typename container_type::value_compare;
    using allocator_type = typename container_type::allocator_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using difference_type = typename container_type::difference_type;
    using size_type = typename container_type::size_type;

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
