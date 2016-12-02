#ifndef GO_BOOST_MVVM_DATA_CONTEXT_CHANGING_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_DATA_CONTEXT_CHANGING_ARGUMENTS_HPP_INCLUDED

//
//  data_context_changing_arguments.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/signals/slot_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

class data_context_changing_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef data_context_changing_arguments this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~data_context_changing_arguments()
    {
    }

protected:
    data_context_changing_arguments()
        : go_boost::signals::slot_arguments()
    {
    }

public:
    static boost::shared_ptr<data_context_changing_arguments> create();
};

inline boost::shared_ptr<data_context_changing_arguments> data_context_changing_arguments::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler()
            : this_type()
        {
        }
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_DATA_CONTEXT_CHANGING_ARGUMENTS_HPP_INCLUDED
