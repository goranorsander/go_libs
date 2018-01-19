//
//  delete_dialog_view_command_parameters.cpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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

delete_dialog_view_command_parameters::delete_dialog_view_command_parameters()
    : m::command_parameters()
    , dialog()
{
}

delete_dialog_view_command_parameters::ptr delete_dialog_view_command_parameters::create(const dialog_view::ptr& dialog_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const dialog_view::ptr& dialog_) : this_type(dialog_) {}
    };

    return boost::make_shared<make_shared_enabler, const dialog_view::ptr&>(dialog_);
#else
    return boost::shared_ptr<this_type>(new this_type(dialog_));
#endif // BOOST_MSVC > 1500
}
