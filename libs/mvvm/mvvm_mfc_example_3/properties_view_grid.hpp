#ifndef GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_HPP_INCLUDED
#define GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_HPP_INCLUDED

//
//  properties_view_grid.hpp
//
//  Copyright 2016 G�ran Orsander
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

#endif  // #ifndef GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_GRID_HPP_INCLUDED
