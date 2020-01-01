#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED

//
//  main_frame_view_tool_bar.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

class main_frame_view_tool_bar
    : public CMFCToolBar
{
public:
    virtual ~main_frame_view_tool_bar() GO_DEFAULT_DESTRUCTOR

    main_frame_view_tool_bar() GO_DEFAULT_CONSTRUCTOR
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_MAIN_FRAME_VIEW_TOOL_BAR_HPP_INCLUDED
