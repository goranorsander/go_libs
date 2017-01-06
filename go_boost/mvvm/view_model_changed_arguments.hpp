#ifndef GO_BOOST_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  view_model_changed_arguments.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/signals/slot_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

class view_model_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef view_model_changed_arguments this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~view_model_changed_arguments()
    {
    }

protected:
    view_model_changed_arguments()
        : go_boost::signals::slot_arguments()
    {
    }

public:
    static boost::shared_ptr<view_model_changed_arguments> create();
};

inline boost::shared_ptr<view_model_changed_arguments> view_model_changed_arguments::create()
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

#endif  // #ifndef GO_BOOST_MVVM_VIEW_MODEL_CHANGED_ARGUMENTS_HPP_INCLUDED
