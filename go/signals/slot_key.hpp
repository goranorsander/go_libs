#ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
#define GO_SIGNALS_SLOT_KEY_HPP_INCLUDED

//
//  slot_key.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <cstdint>

namespace go
{
namespace signals
{

class slot_key
{
private:
#if defined(GO_ADDRESS_MODEL_64)
    typedef uint64_t slot_key_type;
#else
    typedef uint32_t slot_key_type;
#endif  // #if defined(GO_ADDRESS_MODEL_64)

public:
    typedef slot_key this_type;

public:
    virtual ~slot_key() GO_DEFAULT_DESTRUCTOR

    slot_key()
        : _slot_key(0)
    {
    }

    slot_key(const slot_key& other)
        : _slot_key(other._slot_key)
    {
    }

    this_type& operator=(const this_type& other)
    {
        if (this != &other)
        {
            _slot_key = other._slot_key;
        }
        return *this;
    }

    bool operator==(const this_type& other) const
    {
        if(this != &other)
        {
            return _slot_key == other._slot_key;
        }
        return true;
    }

    bool operator!=(const this_type& other) const
    {
        return !operator==(other);
    }

    bool operator<(const this_type& other) const
    {
        if (this != &other)
        {
            return _slot_key < other._slot_key;
        }
        return false;
    }

    bool operator>(const this_type& other) const
    {
        if (this != &other)
        {
            return _slot_key > other._slot_key;
        }
        return false;
    }

    bool operator<=(const this_type& other) const
    {
        if (this != &other)
        {
            return _slot_key <= other._slot_key;
        }
        return true;
    }

    bool operator>=(const this_type& other) const
    {
        if (this != &other)
        {
            return _slot_key >= other._slot_key;
        }
        return true;
    }

    this_type& operator++()
    {
        // Prefix ++
        ++_slot_key;
        return *this;
    }

    this_type operator++(int)
    {
        // Postfix ++
        const this_type result(*this);
        ++(*this);
        return result;
    }

    void reset()
    {
        _slot_key = 0;
    }

    static bool is_null_key(const this_type& key)
    {
        return key._slot_key == 0;
    }

private:
    slot_key_type _slot_key;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
