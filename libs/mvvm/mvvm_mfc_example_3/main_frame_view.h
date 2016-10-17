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

class mvvm_mfc_example_3_doc;

class main_frame_view
    : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(main_frame_view)
public:
    virtual ~main_frame_view();
    main_frame_view(const m::wcommand_manager::ptr& command_manager, const fleet_repository::ptr& fleet_repo);

public:
    void on_show_spaceship(const fleet_organization_id_type id);

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCMenuBar _wndMenuBar;
	CMFCToolBar _wndToolBar;
	CMFCStatusBar _wndStatusBar;
	fleet_organization_view _fleet_organization_view;
	output_view _output_view;
	properties_view _properties_view;

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
    typedef std::map<fleet_organization_id_type, mvvm_mfc_example_3_doc*> fleet_organization_document_type;

    m::wcommand_manager::wptr _command_manager;
    fleet_repository::wptr _fleet_repository;
    main_frame_view_model::ptr _main_frame_view_model;
    fleet_organization_document_type _fleet_org_doc;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAIN_FRAME_VIEW_H_INCLUDED
