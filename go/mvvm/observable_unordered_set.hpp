#ifndef GO_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED

//
//  observable_unordered_set.hpp
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

#include <unordered_set>

#include <go/mvvm/observable_unordered_associative_container.hpp>

namespace go
{
namespace mvvm
{

template<class K, class S, class L = std::recursive_mutex>
class basic_observable_unordered_set
    : public basic_observable_unordered_associative_container<S, std::unordered_set<K>, L>
{
public:
    using string_type = S;
    using lockable_type = L;
    using container_type = typename std::unordered_set<K>;
    using this_type = basic_observable_unordered_set<K, S, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using hasher = typename container_type::hasher;
    using key_equal = typename container_type::key_equal;
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
    virtual ~basic_observable_unordered_set() GO_DEFAULT_DESTRUCTOR

protected:
    basic_observable_unordered_set()
        : basic_observable_unordered_associative_container<string_type, container_type, lockable_type>()
        , _container()
    {
    }

    template <class InputIterator>
    basic_observable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_associative_container<string_type, container_type, lockable_type>()
        , _container(first, last)
    {
    }

    explicit basic_observable_unordered_set(const this_type& x)
        : basic_observable_unordered_associative_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_unordered_set(this_type&& x)
        : basic_observable_unordered_associative_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_unordered_set(const std::initializer_list<value_type>& il)
        : basic_observable_unordered_associative_container<string_type, container_type, lockable_type>()
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
        this->container().operator=(il);
        return *this;
    }

public:
    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.emplace(args...);
        if(p.second)
        {
            const std::size_t after = _container.size();
            this->notify_insert(before, after);
        }
        return p;
    }

    std::pair<iterator, bool> insert(const value_type& val)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.insert(val);
        if(p.second)
        {
            const std::size_t after = _container.size();
            this->notify_insert(before, after);
        }
        return p;
    }

    std::pair<iterator, bool> insert(value_type&& val)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.insert(val);
        if(p.second)
        {
            const std::size_t after = _container.size();
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

    void insert(const std::initializer_list<value_type>& il)
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

    size_type erase(const value_type& val)
    {
        const std::size_t before = _container.size();
        const size_type s = _container.erase(val);
        if(s > 0)
        {
            const std::size_t after = _container.size();
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

template<class K, class S, class L>
inline typename basic_observable_unordered_set<K, S, L>::container_type& basic_observable_unordered_set<K, S, L>::container()
{
    return _container;
}

template<class K, class S, class L>
inline const typename basic_observable_unordered_set<K, S, L>::container_type& basic_observable_unordered_set<K, S, L>::container() const
{
    return _container;
}

template<class K, class L = std::recursive_mutex>
class observable_unordered_set
    : public basic_observable_unordered_set<K, std::string, L>
{
public:
    using string_type = std::string;
    using lockable_type = L;
    using container_type = typename std::unordered_set<K>;
    using this_type = observable_unordered_set<K, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using hasher = typename container_type::hasher;
    using key_equal = typename container_type::key_equal;
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
    virtual ~observable_unordered_set() GO_DEFAULT_DESTRUCTOR

protected:
     observable_unordered_set()
        : basic_observable_unordered_set<value_type, string_type, lockable_type>()
    {
    }

    template <class InputIterator>
    observable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit observable_unordered_set(const this_type& x)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(x)
    {
    }

    explicit observable_unordered_set(this_type&& x)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(x)
    {
    }

    explicit observable_unordered_set(const std::initializer_list<value_type>& il)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(il)
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
            basic_observable_unordered_set<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il) noexcept
    {
        this->container().operator=(il);
        return *this;
    }

public:
    template<class k, typename m>
    void swap(observable_unordered_set<k, m>& x)
    {
        basic_observable_unordered_set<k, string_type, m>::swap(dynamic_cast<basic_observable_unordered_set<k, string_type, m>&>(x));
    }
};

template<class K, class L = std::recursive_mutex>
class wobservable_unordered_set
    : public basic_observable_unordered_set<K, std::wstring, L>
{
public:
    using string_type = std::wstring;
    using lockable_type = L;
    using container_type = typename std::unordered_set<K>;
    using this_type = wobservable_unordered_set<K, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using hasher = typename container_type::hasher;
    using key_equal = typename container_type::key_equal;
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
    virtual ~wobservable_unordered_set() GO_DEFAULT_DESTRUCTOR

protected:
     wobservable_unordered_set()
        : basic_observable_unordered_set<value_type, string_type, lockable_type>()
    {
    }

    template <class InputIterator>
    wobservable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit wobservable_unordered_set(const this_type& x)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(x)
    {
    }

    explicit wobservable_unordered_set(this_type&& x)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(x)
    {
    }

    explicit wobservable_unordered_set(const std::initializer_list<value_type>& il)
        : basic_observable_unordered_set<value_type, string_type, lockable_type>(il)
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
            basic_observable_unordered_set<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x) noexcept
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il) noexcept
    {
        this->container().operator=(il);
        return *this;
    }

public:
    template<class k, typename m>
    void swap(wobservable_unordered_set<k, m>& x)
    {
        basic_observable_unordered_set<k, string_type, m>::swap(dynamic_cast<basic_observable_unordered_set<k, string_type, m>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED
