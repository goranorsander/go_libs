#ifndef GO_BOOST_MVVM_EVENT_HPP_INCLUDED
#define GO_BOOST_MVVM_EVENT_HPP_INCLUDED

//
//  event.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <string>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>
#include <go_boost/property/nameless/read_only_property.hpp>
#include <go_boost/type_traits/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_event;
typedef basic_event<std::string> event;
typedef basic_event<std::wstring> wevent;

template<class S>
class basic_event
    : public boost::enable_shared_from_this<basic_event<S>>
    , go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef basic_event<S> this_type;
    typedef typename boost::shared_ptr<basic_event<S>> ptr;
    typedef typename boost::weak_ptr<basic_event<S>> wptr;
    typedef typename go_boost::property::nameless::read_only::property<S> event_type_type;

public:
    virtual ~basic_event() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit basic_event(const S& event_type_);

public:
    event_type_type event_type;

public:
    static ptr create(const S& event_type_);

protected:
    virtual S get_event_type() const;

private:
    const S _event_type;
};

template<class S>
inline basic_event<S>::basic_event(const S& event_type_)
    : boost::enable_shared_from_this<basic_event<S>>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , event_type()
    , _event_type(event_type_)
{
    event_type.getter(boost::bind(&this_type::get_event_type, this));
}

template<class S>
inline S basic_event<S>::get_event_type() const
{
    return _event_type;
}

template<class S>
inline boost::shared_ptr<basic_event<S>> basic_event<S>::create(const S& event_type_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const S& event_type_) : this_type(event_type_) {}
    };

    return boost::make_shared<make_shared_enabler, const S&>(event_type_);
#else
    return boost::shared_ptr<this_type>(new this_type(event_type_));
#endif // BOOST_MSVC > 1500
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_EVENT_HPP_INCLUDED
