#ifndef GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_associative_container.hpp
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

#include <go/mvvm/observable_container.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C, class L = std::recursive_mutex>
class basic_observable_associative_container
    : public basic_observable_container<S, C, L>
{
public:
    using string_type = S;
    using container_type = C;
    using lockable_type = L;
    using this_type = basic_observable_associative_container<string_type, container_type, lockable_type>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using allocator_type = typename container_type::allocator_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using difference_type = typename container_type::difference_type;
    using size_type = typename container_type::size_type;

public:
    virtual ~basic_observable_associative_container() = 0;

protected:
    basic_observable_associative_container()
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
        return this->container().end();
    }

    GO_CONSTEXPR const_iterator cbegin() const noexcept
    {
        return this->container().cbegin();
    }

    GO_CONSTEXPR const_iterator cend() const noexcept
    {
        return this->container().cend();
    }

    GO_CONSTEXPR size_type size() const noexcept
    {
        return this->container().size();
    }

    GO_CONSTEXPR size_type max_size() const noexcept
    {
        return this->container().max_size();
    }

    GO_CONSTEXPR bool empty() const noexcept
    {
        return this->container().empty();
    }

    template <class... Args>
    iterator emplace_hint(const_iterator position, Args&&... args)
    {
        const std::size_t before = this->container().size();
        const iterator it = this->container().emplace_hint(position, args...);
        const std::size_t after = this->container().size();
        notify_insert(before, after);
        return it;
    }

    void clear() noexcept
    {
        const std::size_t before = this->container().size();
        this->container().clear();
        this->notify_container_changed(notify_container_changed_action::reset, 0, before, 0);
    }

    template<class t, class s, typename m>
    void swap(basic_observable_associative_container<t, s, m>& x)
    {
        const std::size_t this_before = this->container().size();
        const std::size_t x_before = x.size();
        this->container().swap(x.container());
        x.notify_container_changed(notify_container_changed_action::swap, this_before, x_before, x.container().size());
        this->notify_container_changed(notify_container_changed_action::swap, x_before, this_before, this->container().size());
    }

    GO_CONSTEXPR size_type count(const value_type& val) const
    {
        return this->container().count(val);
    }

    GO_CONSTEXPR const_iterator find(const value_type& val) const
    {
        return this->container().find(val);
    }

    iterator find(const value_type& val)
    {
        return this->container().find(val);
    }

    GO_CONSTEXPR std::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
    {
        return this->container().equal_range(val);
    }

    std::pair<iterator, iterator> equal_range(const value_type& val)
    {
        return this->container().equal_range(val);
    }

    GO_CONSTEXPR allocator_type get_allocator() const noexcept
    {
        return this->container().get_allocator();
    }

protected:
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
inline basic_observable_associative_container<S, C, L>::~basic_observable_associative_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
