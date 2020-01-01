#ifndef GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED

//
//  observable_forward_list.hpp
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

#include <forward_list>

#include <go/mvvm/observable_sequence_container.hpp>

namespace go
{
namespace mvvm
{

template<class T, class S, class L = std::recursive_mutex>
class basic_observable_forward_list
    : public basic_observable_sequence_container<S, std::forward_list<T>, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef typename std::forward_list<T> container_type;
    typedef basic_observable_forward_list<T, S, L> this_type;
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
    virtual ~basic_observable_forward_list() GO_DEFAULT_DESTRUCTOR

protected:
    basic_observable_forward_list()
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container()
    {
    }

    explicit basic_observable_forward_list(size_type n)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(n)
    {
    }

    basic_observable_forward_list(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(first, last)
    {
    }

    explicit basic_observable_forward_list(const this_type& x)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_forward_list(this_type&& x)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_forward_list(const std::initializer_list<value_type>& il)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x) noexcept
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    this_type& operator=(this_type&& x) noexcept
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il) noexcept
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

    GO_CONSTEXPR const_iterator before_begin() const noexcept
    {
        return _container.before_begin();
    }

    GO_CONSTEXPR const_iterator cbefore_begin() const noexcept
    {
        return _container.cbefore_begin();
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
        this->notify_assign(before, after);
    }

    void assign(size_type n, const value_type& val)
    {
        const std::size_t before = size();
        _container.assign(n, val);
        const std::size_t after = size();
        this->notify_assign(before, after);
    }

    void assign(const std::initializer_list<value_type>& il)
    {
        const std::size_t before = size();
        _container.assign(il);
        const std::size_t after = size();
        this->notify_assign(before, after);
    }

    void push_front(const value_type& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, size());
    }

    void push_front(value_type&& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, size());
    }

    void pop_front()
    {
        const std::size_t before = size();
        _container.pop_front();
        const std::size_t after = size();
        if(before > after)
        {
            this->notify_container_changed(notify_container_changed_action::remove, 0, before - after, size());
        }
    }

    template<class t, class s, typename m>
    void swap(basic_observable_forward_list<t, s, m>& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.swap(x._container);
        x.notify_container_changed(notify_container_changed_action::swap, this_before, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::swap, x_before, this_before, size());
    }

    void clear() noexcept
    {
        const std::size_t before = size();
        _container.clear();
        this->notify_container_changed(notify_container_changed_action::reset, 0, before, 0);
    }

    template <class... Args>
    void emplace_front(Args&&... args)
    {
        const std::size_t before = size();
        _container.emplace_front(args...);
        const std::size_t after = size();
        this->notify_insert(before, after);
    }

    template <class... Args>
    iterator emplace_after(const_iterator position, Args&&... args)
    {
        const std::size_t before = size();
        const iterator it = _container.emplace_after(position, args...);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, const value_type& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, val);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, value_type&& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, val);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, n, val);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, first, last);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert_after(const_iterator position, std::initializer_list<value_type> il)
    {
        const std::size_t before = size();
        const iterator it = _container.insert_after(position, il);
        const std::size_t after = size();
        this->notify_insert(before, after);
        return it;
    }

    iterator erase_after(const_iterator position)
    {
        const std::size_t before = size();
        const iterator it = _container.erase_after(position);
        const std::size_t after = size();
        this->notify_erase(before, after);
        return it;
    }

    iterator erase_after(const_iterator position, const_iterator last)
    {
        const std::size_t before = size();
        const iterator it = _container.erase_after(position, last);
        const std::size_t after = size();
        this->notify_erase(before, after);
        return it;
    }

    GO_CONSTEXPR allocator_type get_allocator() const noexcept
    {
        return _container.get_allocator();
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>& x)
    {
        const std::size_t x_before = x.size();
        _container.splice_after(position, x._container);
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, x_before, 0, size());
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>&& x)
    {
        const std::size_t x_before = x.size();
        _container.splice_after(position, x._container);
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, x_before, 0, size());
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>& x, const_iterator i)
    {
        _container.splice_after(position, x._container, i);
        x.notify_container_changed(notify_container_changed_action::remove, 0, 1, x.size());
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, size());
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>&& x, const_iterator i)
    {
        _container.splice_after(position, x._container, i);
        x.notify_container_changed(notify_container_changed_action::remove, 0, 1, x.size());
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, size());
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = size();
        _container.splice_after(position, x._container, first, last);
        const std::size_t transfer_count = size() - this_before;
        x.notify_container_changed(notify_container_changed_action::remove, 0, transfer_count, x.size());
        this->notify_container_changed(notify_container_changed_action::add, transfer_count, 0, size());
    }

    template<class t, class s, typename m>
    void splice_after(const_iterator position, basic_observable_forward_list<t, s, m>&& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = size();
        _container.splice_after(position, x._container, first, last);
        const std::size_t transfer_count = size() - this_before;
        x.notify_container_changed(notify_container_changed_action::remove, 0, transfer_count, x.size());
        this->notify_container_changed(notify_container_changed_action::add, transfer_count, 0, size());
    }

    void remove(const value_type& val)
    {
        const std::size_t before = size();
        _container.remove(val);
        const std::size_t after = size();
        this->notify_erase(before, after);
    }

    template <class Predicate>
    void remove_if(Predicate pred)
    {
        const std::size_t before = size();
        _container.remove_if(pred);
        const std::size_t after = size();
        this->notify_erase(before, after);
    }

    void unique()
    {
        const std::size_t before = size();
        _container.unique();
        const std::size_t after = size();
        this->notify_erase(before, after);
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        const std::size_t before = size();
        _container.unique(binary_pred);
        const std::size_t after = size();
        this->notify_erase(before, after);
    }

    template<class t, class s, typename m>
    void merge(basic_observable_forward_list<t, s, m>& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container);
        const std::size_t this_after = size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m>
    void merge(basic_observable_forward_list<t, s, m>&& x)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container);
        const std::size_t this_after = size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m, class Compare>
    void merge(basic_observable_forward_list<t, s, m>& x, Compare comp)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m, class Compare>
    void merge(basic_observable_forward_list<t, s, m>&& x, Compare comp)
    {
        const std::size_t this_before = size();
        const std::size_t x_before = x.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
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

template<class T, class S, class L>
inline typename basic_observable_forward_list<T, S, L>::size_type basic_observable_forward_list<T, S, L>::size() const noexcept
{
    size_type size = 0;
    const const_iterator end = _container.cend();
    for(const_iterator it = _container.cbegin(); it != end; ++it)
    {
        ++size;
    }
    return size;
}

template<class T, class S, class L>
inline typename basic_observable_forward_list<T, S, L>::container_type& basic_observable_forward_list<T, S, L>::container()
{
    return _container;
}

template<class T, class S, class L>
inline const typename basic_observable_forward_list<T, S, L>::container_type& basic_observable_forward_list<T, S, L>::container() const
{
    return _container;
}

template<class T, class L = std::recursive_mutex> class observable_forward_list
    : public basic_observable_forward_list<T, std::string, L>
{
public:
    typedef std::string string_type;
    typedef L lockable_type;
    typedef typename std::forward_list<T> container_type;
    typedef observable_forward_list<T, L> this_type;
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
    virtual ~observable_forward_list() GO_DEFAULT_DESTRUCTOR

protected:
     observable_forward_list()
        : basic_observable_forward_list<value_type, string_type, lockable_type>()
    {
    }

    explicit observable_forward_list(size_type n)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(n)
    {
    }

    observable_forward_list(size_type n, const value_type& val)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit observable_forward_list(const this_type& x)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(x)
    {
    }

    explicit observable_forward_list(this_type&& x)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(x)
    {
    }

    explicit observable_forward_list(const std::initializer_list<value_type>& il)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il) noexcept
    {
        basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(il);
        return *this;
    }

public:
    template<class t, typename m>
    void swap(observable_forward_list<t, m>& x)
    {
        basic_observable_forward_list<t, string_type, m>::swap(dynamic_cast<basic_observable_forward_list<t, string_type, m>&>(x));
    }
};

template<class T, class L = std::recursive_mutex> class wobservable_forward_list
    : public basic_observable_forward_list<T, std::wstring, L>
{
public:
    typedef std::wstring string_type;
    typedef L lockable_type;
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
    virtual ~wobservable_forward_list() GO_DEFAULT_DESTRUCTOR

protected:
     wobservable_forward_list()
        : basic_observable_forward_list<value_type, string_type, lockable_type>()
    {
    }

    explicit wobservable_forward_list(size_type n)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(n)
    {
    }

    wobservable_forward_list(size_type n, const value_type& val)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_forward_list(InputIterator first, InputIterator last)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit wobservable_forward_list(const this_type& x)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(x)
    {
    }

    explicit wobservable_forward_list(this_type&& x)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(x)
    {
    }

    explicit wobservable_forward_list(const std::initializer_list<value_type>& il)
        : basic_observable_forward_list<value_type, string_type, lockable_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il) noexcept
    {
        basic_observable_forward_list<value_type, string_type, lockable_type>::operator=(il);
        return *this;
    }

public:
    template<class t, typename m>
    void swap(wobservable_forward_list<t, m>& x)
    {
        basic_observable_forward_list<t, string_type, m>::swap(dynamic_cast<basic_observable_forward_list<t, string_type, m>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_FORWARD_LIST_HPP_INCLUDED
