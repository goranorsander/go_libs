#ifndef GO_BOOST_MDI_FRAME_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MDI_FRAME_INTERFACE_HPP_INCLUDED

//
//  mdi_frame_interface.hpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

typedef unsigned long fleet_organization_id_type;

class mdi_frame_interface
{
public:
    typedef mdi_frame_interface this_type;
    typedef typename mdi_frame_interface* pointer;

public:
    virtual ~mdi_frame_interface() = 0;

protected:
    mdi_frame_interface();

public:
    virtual void on_show_spaceship(const fleet_organization_id_type id) = 0;
    virtual void on_close_spaceship(const fleet_organization_id_type id) = 0;
};

inline mdi_frame_interface::~mdi_frame_interface()
{
}

inline mdi_frame_interface::mdi_frame_interface()
{
}

#endif  // #ifndef GO_BOOST_MDI_FRAME_INTERFACE_HPP_INCLUDED