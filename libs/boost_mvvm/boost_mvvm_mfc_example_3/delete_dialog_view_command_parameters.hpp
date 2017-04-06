#ifndef GO_BOOST_DELETE_DIALOG_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_DELETE_DIALOG_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  delete_dialog_view_command_parameters.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>
#include "dialog_view.hpp"

class delete_dialog_view_command_parameters
    : public m::command_parameters
{
public:
    typedef delete_dialog_view_command_parameters this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~delete_dialog_view_command_parameters();

protected:
    explicit delete_dialog_view_command_parameters(const dialog_view::ptr& dialog_);

private:
    delete_dialog_view_command_parameters() = delete;

public:
    np::value_property<dialog_view::ptr> dialog;

public:
    static ptr create(const dialog_view::ptr& dialog_);
};

#endif  // #ifndef GO_BOOST_DELETE_DIALOG_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
