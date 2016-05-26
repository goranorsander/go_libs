#ifndef GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED

//
//  observable_forward_list.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <forward_list>

#include <go/mvvm/notify_container_changed.hpp>
#include <go/mvvm/observable_sequence_container.hpp>

namespace go
{
namespace mvvm
{

template<class T, class S> class basic_observable_forward_list
    : public basic_observable_sequence_container<S, std::forward_list<T>>
{
public:
    typedef S string_type;
    typedef typename std::forward_list<T> container_type;
    typedef basic_observable_forward_list<string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~basic_observable_forward_list()
    {
    }

protected:
    basic_observable_forward_list()
        : basic_observable_sequence_container<string_type, container_type>()
        , _container()
    {
    }

    explicit basic_observable_forward_list(size_type n)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n)
    {
    }

    basic_observable_forward_list(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(first, last)
    {
    }

    basic_observable_forward_list(const basic_observable_forward_list& x)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_forward_list(basic_observable_forward_list&& x)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_forward_list(std::initializer_list<value_type> il)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(il)
    {
    }

public:
    basic_observable_forward_list& operator=(const basic_observable_forward_list& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    basic_observable_forward_list& operator=(basic_observable_forward_list&& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    basic_observable_forward_list& operator=(std::initializer_list<value_type> il)
    {
        _container.operator=(il);
        return *this;
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

public:
    iterator before_begin() noexcept
    {
        return _container.before_begin();
    }

    const_iterator before_begin() const noexcept
    {
        return _container.before_begin();
    }

    size_type size() const noexcept;

    void resize(size_type n)
    {
        _container.resize(n);
    }

    void resize(size_type n, const value_type& val)
    {
        _container.resize(n, val);
    }

    void shrink_to_fit()
    {
        _container.shrink_to_fit();
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        const std::size_t before = size();
        _container.assign(first, last);
        const std::size_t after = size();
        notify_assign(before, after);
    }

    void assign(size_type n, const value_type& val)
    {
        const std::size_t before = size();
        _container.assign(n, val);
        const std::size_t after = size();
        notify_assign(before, after);
    }

    void assign(std::initializer_list<value_type> il)
    {
        const std::size_t before = size();
        _container.assign(il);
        const std::size_t after = size();
        notify_assign(before, after);
    }

    void push_front(const value_type& val)
    {
        _container.push_front(val);
        on_container_changed(notify_container_changed_action_add, 1, 0, size());
    }

    void push_front(value_type&& val)
    {
        _container.push_front(val);
        on_container_changed(notify_container_changed_action_add, 1, 0, size());
    }

    void pop_front()
    {
        const std::size_t before = size();
        _container.pop_front();
        const std::size_t after = size();
        if(before > after)
        {
            on_container_changed(notify_container_changed_action_remove, 0, before - after, size());
        }
    }

    template<class t, class s>
    void swap(basic_observable_forward_list<t, s>& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.swap(x._container);
        x.on_container_changed(notify_container_changed_action_swap, this_before, x_before, x.size());
        on_container_changed(notify_container_changed_action_swap, x_before, this_before, size());
    }

    void clear() noexcept
    {
        const std::size_t before = size();
        _container.clear();
        on_container_changed(notify_container_changed_action_reset, 0, before, size());
    }

    template <class... Args>
    void emplace_front(Args&&... args)
    {
        const std::size_t before = size();
        _container.emplace_front(args...);
        const std::size_t after = size();
        notify_insert(before, after);
    }

    template <class... Args>
    iterator emplace_after(const_iterator position, Args&&... args)
    {
        const std::size_t before = size();
        const iterator it = _container.emplace_after(position, args...);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, const value_type& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, val);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, value_type&& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, val);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, n, val);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, first, last);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, std::initializer_list<value_type> il)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, il);
        const std::size_t after = size();
        notify_insert(before, after);
        return it;
    }

    iterator erase_after(const_iterator position)
    {
        const std::size_t before = size();
        const iterator it = _container.erase_after(position);
        const std::size_t after = size();
        notify_erase(before, after);
        return it;
    }

    iterator erase_after(const_iterator position, const_iterator last)
    {
        const std::size_t before = size();
        const iterator it = _container.erase_after(position, last);
        const std::size_t after = size();
        notify_erase(before, after);
        return it;
    }

    allocator_type get_allocator() const noexcept
    {
        return _container.get_allocator();
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x)
    {
        const std::size_t x_before = x.size();
        _container.splice_after(position, x._container);
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, x_before, 0, size());
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x)
    {
        const std::size_t x_before = x.size();
        _container.splice_after(position, x._container);
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, x_before, 0, size());
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator i)
    {
        _container.splice_after(position, x._container, i);
        x.on_container_changed(notify_container_changed_action_remove, 0, 1, x.size());
        on_container_changed(notify_container_changed_action_add, 1, 0, size());
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator i)
    {
        _container.splice_after(position, x._container, i);
        x.on_container_changed(notify_container_changed_action_remove, 0, 1, x.size());
        on_container_changed(notify_container_changed_action_add, 1, 0, size());
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = size();
        _container.splice_after(position, x._container, first, last);
        const std::size_t transfer_count = size() - this_before;
        x.on_container_changed(notify_container_changed_action_remove, 0, transfer_count, x.size());
        on_container_changed(notify_container_changed_action_add, transfer_count, 0, size());
    }

    template<class t, class s>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = size();
        _container.splice_after(position, x._container, first, last);
        const std::size_t transfer_count = size() - this_before;
        x.on_container_changed(notify_container_changed_action_remove, 0, transfer_count, x.size());
        on_container_changed(notify_container_changed_action_add, transfer_count, 0, size());
    }

    void remove(const value_type& val)
    {
        const std::size_t before = size();
        _container.remove(val);
        const std::size_t after = size();
        notify_erase(before, after);
    }

    template <class Predicate>
    void remove_if(Predicate pred)
    {
        const std::size_t before = size();
        _container.remove_if(pred);
        const std::size_t after = size();
        notify_erase(before, after);
    }

    void unique()
    {
        const std::size_t before = size();
        _container.unique();
        const std::size_t after = size();
        notify_erase(before, after);
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        const std::size_t before = size();
        _container.unique(binary_pred);
        const std::size_t after = size();
        notify_erase(before, after);
    }

    template<class t, class s>
    void merge(basic_observable_forward_list<t, s>& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container);
        const std::size_t this_after = size();
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, this_after - this_before, 0, this_after);
    }

    template<class t, class s>
    void merge(basic_observable_forward_list<t, s>&& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container);
        const std::size_t this_after = size();
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, class Compare>
    void merge(basic_observable_forward_list<t, s>& x, Compare comp)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = size();
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, class Compare>
    void merge(basic_observable_forward_list<t, s>&& x, Compare comp)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = size();
        x.on_container_changed(notify_container_changed_action_remove, 0, x_before, x.size());
        on_container_changed(notify_container_changed_action_add, this_after - this_before, 0, this_after);
    }


    void sort()
    {
        _container.sort();
    }

    template <class Compare>
    void sort(Compare comp)
    {
        _container.sort(comp);
    }

    void reverse()
    {
        _container.reverse();
    }

private:
    container_type _container;
};

template<class T, class S>
inline typename basic_observable_forward_list<T, S>::size_type basic_observable_forward_list<T, S>::size() const noexcept
{
    size_type size = 0;
    const const_iterator end = _container.cend();
    for(const_iterator it = _container.cbegin(); it != end; ++it)
    {
        ++size;
    }
    return size;
}

template<class T, class S>
inline typename basic_observable_forward_list<T, S>::container_type& basic_observable_forward_list<T, S>::container()
{
    return _container;
}

template<class T, class S>
inline const typename basic_observable_forward_list<T, S>::container_type& basic_observable_forward_list<T, S>::container() const
{
    return _container;
}

template<class T> class observable_forward_list
    : public basic_observable_forward_list<T, std::string>
{
public:
    typedef std::string string_type;
    typedef typename std::forward_list<T> container_type;
    typedef observable_forward_list<T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~observable_forward_list()
    {
    }

protected:
    observable_forward_list()
        : basic_observable_forward_list<value_type, string_type>()
    {
    }

    explicit observable_forward_list(size_type n)
        : basic_observable_forward_list<value_type, string_type>(n)
    {
    }

    observable_forward_list(size_type n, const value_type& val)
        : basic_observable_forward_list<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_forward_list<value_type, string_type>(first, last)
    {
    }

    observable_forward_list(const observable_forward_list& x)
        : basic_observable_forward_list<value_type, string_type>(x)
    {
    }

    observable_forward_list(observable_forward_list&& x)
        : basic_observable_forward_list<value_type, string_type>(x)
    {
    }

    observable_forward_list(std::initializer_list<value_type> il)
        : basic_observable_forward_list<value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        return ptr(new observable_forward_list);
    }

    static ptr create(size_type n)
    {
        return ptr(new observable_forward_list(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new observable_forward_list(n, val));
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new observable_forward_list(first, last));
    }

    static ptr create(const observable_forward_list& x)
    {
        return ptr(new observable_forward_list(x));
    }

    static ptr create(observable_forward_list&& x)
    {
        return ptr(new observable_forward_list(x));
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new observable_forward_list(il));
    }

public:
    observable_forward_list& operator=(const observable_forward_list& x)
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    observable_forward_list& operator=(observable_forward_list&& x)
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    observable_forward_list& operator=(std::initializer_list<value_type> il)
    {
        basic_observable_forward_list<value_type, string_type>::operator=(il);
        return *this;
    }

public:
    template<class t>
    void swap(observable_forward_list<t>& x)
    {
        basic_observable_forward_list<t, string_type>::swap(dynamic_cast<basic_observable_forward_list<t, string_type>&>(x));
    }
};

template<class T> class wobservable_forward_list
    : public basic_observable_forward_list<T, std::wstring>
{
public:
    typedef std::wstring string_type;
    typedef typename std::forward_list<T> container_type;
    typedef wobservable_forward_list<T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~wobservable_forward_list()
    {
    }

protected:
    wobservable_forward_list()
        : basic_observable_forward_list<value_type, string_type>()
    {
    }

    explicit wobservable_forward_list(size_type n)
        : basic_observable_forward_list<value_type, string_type>(n)
    {
    }

    wobservable_forward_list(size_type n, const value_type& val)
        : basic_observable_forward_list<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_forward_list<value_type, string_type>(first, last)
    {
    }

    wobservable_forward_list(const wobservable_forward_list& x)
        : basic_observable_forward_list<value_type, string_type>(x)
    {
    }

    wobservable_forward_list(wobservable_forward_list&& x)
        : basic_observable_forward_list<value_type, string_type>(x)
    {
    }

    wobservable_forward_list(std::initializer_list<value_type> il)
        : basic_observable_forward_list<value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        return ptr(new wobservable_forward_list);
    }

    static ptr create(size_type n)
    {
        return ptr(new wobservable_forward_list(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new wobservable_forward_list(n, val));
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new wobservable_forward_list(first, last));
    }

    static ptr create(const wobservable_forward_list& x)
    {
        return ptr(new wobservable_forward_list(x));
    }

    static ptr create(wobservable_forward_list&& x)
    {
        return ptr(new wobservable_forward_list(x));
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new wobservable_forward_list(il));
    }

public:
    wobservable_forward_list& operator=(const wobservable_forward_list& x)
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    wobservable_forward_list& operator=(wobservable_forward_list&& x)
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    wobservable_forward_list& operator=(std::initializer_list<value_type> il)
    {
        basic_observable_forward_list<value_type, string_type>::operator=(il);
        return *this;
    }

public:
    template<class t>
    void swap(wobservable_forward_list<t>& x)
    {
        basic_observable_forward_list<t, string_type>::swap(dynamic_cast<basic_observable_forward_list<t, string_type>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED
