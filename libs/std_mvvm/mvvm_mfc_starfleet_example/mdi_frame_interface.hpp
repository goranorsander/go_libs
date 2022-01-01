#ifndef GO_MDI_FRAME_INTERFACE_HPP_INCLUDED
#define GO_MDI_FRAME_INTERFACE_HPP_INCLUDED

//
//  mdi_frame_interface.hpp
//
//  Copyright 2016-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "dialog_view.hpp"
#include "fleet_organization_id_type.hpp"

class mdi_frame_interface
{
public:
    using this_type = mdi_frame_interface;
    using pointer = typename mdi_frame_interface*;

public:
    virtual ~mdi_frame_interface() = 0;

protected:
    mdi_frame_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual void on_show_dialog(const dialog_view::ptr& dialog, const UINT template_id) = 0;
    virtual void on_close_dialog(const dialog_view::pointer dialog) = 0;
    virtual void on_show_spaceship(const fleet_organization_id_type id) = 0;
    virtual void on_close_spaceship(const fleet_organization_id_type id) = 0;
};

inline mdi_frame_interface::~mdi_frame_interface()
{
}

#endif  // #ifndef GO_MDI_FRAME_INTERFACE_HPP_INCLUDED
