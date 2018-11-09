#ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_GRID_HPP_INCLUDED
#define GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_GRID_HPP_INCLUDED

//
//  properties_view_grid.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

class properties_view_grid
    : public CMFCPropertyGridCtrl
{
public:
    virtual ~properties_view_grid();

    properties_view_grid();
};

#endif  // #ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_GRID_HPP_INCLUDED
