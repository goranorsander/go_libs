#ifndef GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  property_changed_arguments.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/mvvm/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

template<class S = std::string>
class property_changed_arguments
    : public slot_arguments
{
public:
    typedef S string_type;
    typedef std::shared_ptr<property_changed_arguments<string_type>> ptr;
    typedef std::weak_ptr<property_changed_arguments<string_type>> wptr;

public:
    virtual ~property_changed_arguments()
    {
    }

private:
    property_changed_arguments(const property_changed_arguments&) = delete;

protected:
    property_changed_arguments(const string_type& property_name)
        : slot_arguments()
        , _property_name(property_name)
    {
    }

public:
    static ptr create(const string_type& property_name)
    {
        return ptr(new property_changed_arguments(property_name));
    }

    string_type property_name() const
    {
        return _property_name;
    }

private:
    const string_type _property_name;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
