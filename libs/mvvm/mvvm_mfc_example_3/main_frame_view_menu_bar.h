#ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_H_INCLUDED

//
//  main_frame_view_menu_bar.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

class main_frame_view_menu_bar
    : public CMFCMenuBar
{
public:
    virtual ~main_frame_view_menu_bar() = default;

    main_frame_view_menu_bar() = default;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_MENU_BAR_H_INCLUDED
