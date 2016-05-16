#ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  property_changed_arguments.hpp
//
//  Copyright 2014 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/signals/slot_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S>
class basic_property_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef typename S string_type;
    typedef typename basic_property_changed_arguments<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_property_changed_arguments()
    {
    }

protected:
    basic_property_changed_arguments(const string_type& property_name)
        : go_boost::signals::slot_arguments()
        , _property_name(property_name)
    {
    }

public:
    static ptr create(const string_type& property_name)
    {
        return ptr(new basic_property_changed_arguments(property_name));
    }

    string_type property_name() const
    {
        return _property_name;
    }

private:
    const string_type _property_name;
};

class property_changed_arguments
    : public basic_property_changed_arguments<std::string>
{
public:
    typedef typename property_changed_arguments this_type;

public:
    virtual ~property_changed_arguments()
    {
    }

protected:
    property_changed_arguments(const string_type& property_name)
        : basic_property_changed_arguments<string_type>(property_name)
    {
    }

public:
    static ptr create(const string_type& property_name)
    {
        return ptr(new this_type(property_name));
    }
};

class wproperty_changed_arguments
    : public basic_property_changed_arguments<std::wstring>
{
public:
    typedef typename wproperty_changed_arguments this_type;

public:
    virtual ~wproperty_changed_arguments()
    {
    }

protected:
    wproperty_changed_arguments(const string_type& property_name)
        : basic_property_changed_arguments<string_type>(property_name)
    {
    }

public:
    static ptr create(const string_type& property_name)
    {
        return ptr(new this_type(property_name));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
