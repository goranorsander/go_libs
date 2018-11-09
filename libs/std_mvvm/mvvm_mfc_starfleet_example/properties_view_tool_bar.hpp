#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_TOOL_BAR_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_TOOL_BAR_HPP_INCLUDED

//
//  properties_view_tool_bar.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

class properties_view_tool_bar
    : public CMFCToolBar
{
public:
    virtual ~properties_view_tool_bar() GO_DEFAULT_DESTRUCTOR

    properties_view_tool_bar() GO_DEFAULT_CONSTRUCTOR
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_TOOL_BAR_HPP_INCLUDED
