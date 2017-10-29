#ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_HPP_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_HPP_INCLUDED

//
//  main_frame_view_menu_bar.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

class main_frame_view_menu_bar
    : public CMFCMenuBar
{
public:
    virtual ~main_frame_view_menu_bar() GO_DEFAULT_DESTRUCTOR

    main_frame_view_menu_bar() GO_DEFAULT_CONSTRUCTOR
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_HPP_INCLUDED
