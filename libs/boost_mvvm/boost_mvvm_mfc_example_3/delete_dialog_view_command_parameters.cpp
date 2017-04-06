//
//  delete_dialog_view_command_parameters.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "delete_dialog_view_command_parameters.hpp"

delete_dialog_view_command_parameters::~delete_dialog_view_command_parameters()
{
}

delete_dialog_view_command_parameters::delete_dialog_view_command_parameters(const dialog_view::ptr& dialog_)
    : m::command_parameters()
    , dialog(dialog_)
{
}

delete_dialog_view_command_parameters::ptr delete_dialog_view_command_parameters::create(const dialog_view::ptr& dialog_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        explicit make_shared_enabler(const dialog_view::ptr& dialog_) : this_type(dialog_) {}
    };

    return boost::make_shared<make_shared_enabler, const dialog_view::ptr&>(dialog_);
}
