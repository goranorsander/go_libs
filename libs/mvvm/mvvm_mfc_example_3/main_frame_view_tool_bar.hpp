#ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED

//
//  main_frame_view_tool_bar.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

class main_frame_view_tool_bar
    : public CMFCToolBar
{
public:
    virtual ~main_frame_view_tool_bar() = default;

    main_frame_view_tool_bar() = default;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED
