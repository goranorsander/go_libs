#ifndef GO_BOOST_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_H_INCLUDED
#define GO_BOOST_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_H_INCLUDED

//
//  properties_view_grid.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

class properties_view_grid
    : public CMFCPropertyGridCtrl
{
public:
    virtual ~properties_view_grid() = default;

    properties_view_grid() = default;
};

#endif  // #ifndef GO_BOOST_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_H_INCLUDED
