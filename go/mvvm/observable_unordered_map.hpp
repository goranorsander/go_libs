#ifndef GO_MVVM_OBSERVABLE_UNORDERED_MAP_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_UNORDERED_MAP_HPP_INCLUDED

//
//  observable_unordered_map.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <unordered_map>

#include <go/mvvm/notify_container_changed_interface.hpp>
#include <go/mvvm/observable_unordered_associative_container.hpp>

namespace go
{
namespace mvvm
{

template<class K, class T, class S> class basic_observable_unordered_map
    : public basic_observable_unordered_associative_container<S, std::unordered_map<K, T>>
{
public:
    typedef S string_type;
    typedef typename std::unordered_map<K, T> container_type;
    typedef basic_observable_unordered_map<K, string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::hasher hasher;
    typedef typename container_type::key_equal key_equal;
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
    virtual ~basic_observable_unordered_map() GO_DEFAULT_DESTRUCTOR

protected:
    basic_observable_unordered_map()
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container()
    {
    }

    template <class InputIterator>
    basic_observable_unordered_map(InputIterator first, InputIterator last)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(first, last)
    {
    }

    basic_observable_unordered_map(const this_type& x)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_unordered_map(this_type&& x)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_unordered_map(std::initializer_list<value_type> il)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(il)
    {
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    mapped_type& operator[](const key_type& k)
    {
        return _container.operator[](k);
    }

    mapped_type& operator[](key_type&& k)
    {
        return _container.operator[](k);
    }

public:
    mapped_type& at(const key_type& k)
    {
        return _container.at(k);
    }

    const mapped_type& at(const key_type& k) const
    {
        return _container.at(k);
    }

    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().emplace(args...);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

    std::pair<iterator, bool> insert(const value_type& val)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().insert(val);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

    template <class P> std::pair<iterator, bool> insert(P&& val)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().insert(val);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

    iterator insert(const_iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        _container.insert(first, last);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

    void insert(std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        _container.insert(il);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

    iterator erase(const_iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    size_type erase(const key_type& k)
    {
        const std::size_t before = this->container().size();
        const size_type s = this->container().erase(k);
        if(s > 0)
        {
            const std::size_t after = this->container().size();
            this->notify_erase(before, after);
        }
        return s;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

private:
    container_type _container;
};

template<class K, class T, class S>
inline typename basic_observable_unordered_map<K, T, S>::container_type& basic_observable_unordered_map<K, T, S>::container()
{
    return _container;
}

template<class K, class T, class S>
inline const typename basic_observable_unordered_map<K, T, S>::container_type& basic_observable_unordered_map<K, T, S>::container() const
{
    return _container;
}

template<class K, class T> class observable_unordered_map
    : public basic_observable_unordered_map<K, T, std::string>
{
public:
    typedef std::string string_type;
    typedef typename std::unordered_map<K, T> container_type;
    typedef observable_unordered_map<K, T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::hasher hasher;
    typedef typename container_type::key_equal key_equal;
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
    virtual ~observable_unordered_map() GO_DEFAULT_DESTRUCTOR

protected:
    observable_unordered_map()
        //: basic_observable_unordered_map<key_type, value_type, string_type>()
    {
    }

    template <class InputIterator>
    observable_unordered_map(InputIterator first, InputIterator last)
        : basic_observable_unordered_map<key_type, value_type, string_type>(first, last)
    {
    }

    observable_unordered_map(const this_type& x)
        : basic_observable_unordered_map<key_type, value_type, string_type>(x)
    {
    }

    observable_unordered_map(this_type&& x)
        : basic_observable_unordered_map<key_type, value_type, string_type>(x)
    {
    }

    observable_unordered_map(std::initializer_list<value_type> il)
        : basic_observable_unordered_map<key_type, value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() : this_type() {}
        };

        return std::make_shared<make_shared_enabler>();
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last)
                : this_type(first, last)
            {
            }
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const this_type& x)
                : this_type(x)
            {
            }
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(this_type&& x)
                : this_type(x)
            {
            }
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(std::initializer_list<value_type> il)
                : this_type(il)
            {
            }
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_map<key_type, value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_map<key_type, value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(std::initializer_list<value_type> il)
    {
        this->container().operator=(il);
        return *this;
    }

public:
    template<class k, class t>
    void swap(observable_unordered_map<k, t>& x)
    {
        basic_observable_unordered_map<k, t, string_type>::swap(dynamic_cast<basic_observable_unordered_map<k, t, string_type>&>(x));
    }
};

template<class K, class T> class wobservable_unordered_map
    : public basic_observable_unordered_map<K, T, std::wstring>
{
public:
    typedef std::wstring string_type;
    typedef typename std::unordered_map<K, T> container_type;
    typedef wobservable_unordered_map<K, T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::hasher hasher;
    typedef typename container_type::key_equal key_equal;
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
    virtual ~wobservable_unordered_map() GO_DEFAULT_DESTRUCTOR

protected:
    wobservable_unordered_map()
        //: basic_observable_unordered_map<key_type, value_type, string_type>()
    {
    }

    template <class InputIterator>
    wobservable_unordered_map(InputIterator first, InputIterator last)
        : basic_observable_unordered_map<key_type, value_type, string_type>(first, last)
    {
    }

    wobservable_unordered_map(const this_type& x)
        : basic_observable_unordered_map<key_type, value_type, string_type>(x)
    {
    }

    wobservable_unordered_map(this_type&& x)
        : basic_observable_unordered_map<key_type, value_type, string_type>(x)
    {
    }

    wobservable_unordered_map(std::initializer_list<value_type> il)
        : basic_observable_unordered_map<key_type, value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() : this_type() {}
        };

        return std::make_shared<make_shared_enabler>();
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last)
                : this_type(first, last)
            {
            }
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const this_type& x)
                : this_type(x)
            {
            }
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(this_type&& x)
                : this_type(x)
            {
            }
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(std::initializer_list<value_type> il)
                : this_type(il)
            {
            }
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_map<key_type, value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_map<key_type, value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(std::initializer_list<value_type> il)
    {
        this->container().operator=(il);
        return *this;
    }

public:
    template<class k, class t>
    void swap(wobservable_unordered_map<k, t>& x)
    {
        basic_observable_unordered_map<k, t, string_type>::swap(dynamic_cast<basic_observable_unordered_map<k, t, string_type>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_UNORDERED_MAP_HPP_INCLUDED
