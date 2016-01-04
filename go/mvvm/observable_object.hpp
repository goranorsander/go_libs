#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/mvvm/notify_property_changed.hpp>

namespace go
{
namespace mvvm
{

template<class S = std::string>
class observable_object
    : public notify_property_changed<S>
    , public object
{
public:
    typedef S string_type;

public:
    virtual ~observable_object()
    {
    }

protected:
    observable_object()
        : notify_property_changed<string_type>()
        , object()
    {
    }

protected:
    virtual void on_property_changed(const string_type& property_name)
    {
        if(!property_changed.empty())
        {
            property_changed(shared_from_this(), property_changed_arguments<string_type>::create(property_name));
        }
    }

public:
    property_changed_signal property_changed;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
