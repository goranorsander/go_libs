#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_TOOL_BAR_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_TOOL_BAR_HPP_INCLUDED

//
//  fleet_organization_view_tool_bar.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

class fleet_organization_view_tool_bar
    : public CMFCToolBar
{
public:
    virtual ~fleet_organization_view_tool_bar() GO_DEFAULT_DESTRUCTOR

    fleet_organization_view_tool_bar() GO_DEFAULT_CONSTRUCTOR
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_TOOL_BAR_HPP_INCLUDED
