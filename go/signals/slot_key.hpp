#ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
#define GO_SIGNALS_SLOT_KEY_HPP_INCLUDED

//
//  slot_key.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace signals
{

class slot_key
{
private:
#if defined(GO_ADDRESS_MODEL_64)
    typedef unsigned __int64 slot_key_type;
#else
    typedef unsigned __int32 slot_key_type;
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

    template<typename F>
    slot_key(const F& f)
        : _slot_key(reinterpret_cast<slot_key_type>(&f))
    {
    }

    this_type operator=(const this_type& other)
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

private:
    slot_key_type _slot_key;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
