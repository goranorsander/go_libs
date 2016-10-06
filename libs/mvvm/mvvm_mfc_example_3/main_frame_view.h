#ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_H_INCLUDED

//
//  main_frame_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_organization_view.h"
#include "main_frame_view_model.hpp"
#include "output_view.h"
#include "properties_view.h"

#include <go/mvvm.hpp>

namespace m = go::mvvm;

class main_frame_view
    : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(main_frame_view)
public:
    virtual ~main_frame_view();
    main_frame_view(const m::wcommand_manager::ptr& command_manager, const fleet_repository::ptr& fleet_repo);

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	fleet_organization_view m_fleet_organization_view;
	output_view        m_output_view;
	properties_view    m_properties_view;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

private:
    m::wcommand_manager::wptr m_command_manager;
    fleet_repository::wptr m_fleet_repository;
    main_frame_view_model::ptr m_main_frame_view_model;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_H_INCLUDED
