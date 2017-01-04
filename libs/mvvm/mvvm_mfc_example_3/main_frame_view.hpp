#ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_HPP_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_HPP_INCLUDED

//
//  main_frame_view.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_organization_view.hpp"
#include "main_frame_view_menu_bar.hpp"
#include "main_frame_view_model.hpp"
#include "main_frame_view_tool_bar.hpp"
#include "mdi_frame_interface.hpp"
#include "output_view.hpp"
#include "properties_view.hpp"
#include "spaceship_view.hpp"

#include <go/mvvm.hpp>

class child_frame_view;

class main_frame_view
    : public CMDIFrameWndEx
    , public mdi_frame_interface
    , public m::data_context_interface<main_frame_view_model::ptr>
{
	DECLARE_DYNAMIC(main_frame_view)

private:
    typedef std::map<fleet_organization_id_type, child_frame_view*> fleet_organization_child_frame_view_type;

public:
    virtual ~main_frame_view() = default;
    main_frame_view(const m::wcommand_manager::ptr& command_manager, const m::wevent_manager::ptr& event_manager, const fleet_repository::ptr& fleet_repo);

public:
    virtual void on_show_spaceship(const fleet_organization_id_type id);
    virtual void on_close_spaceship(const fleet_organization_id_type id);

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnUpdateControlBarMenu(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

private:
    void initialize();

protected:
    main_frame_view_menu_bar _wndMenuBar;
    main_frame_view_tool_bar _wndToolBar;
    CMFCStatusBar _wndStatusBar;
    fleet_organization_view _fleet_organization_view;
    output_view _output_view;
    properties_view _properties_view;

private:
    m::wcommand_manager::wptr _command_manager;
    m::wevent_manager::wptr _event_manager;
    fleet_repository::wptr _fleet_repository;
    fleet_organization_child_frame_view_type _fleet_org_child_view;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_HPP_INCLUDED
