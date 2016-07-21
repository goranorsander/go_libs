#ifndef GO_MVVM_EXAMPLE_3_MAINFRM_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_MAINFRM_H_INCLUDED

//
//  MainFrm.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

#include <go/mvvm.hpp>

namespace m = go::mvvm;

class CMainFrame
    : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
    virtual ~CMainFrame();
    CMainFrame(const m::wcommand_manager::ptr& command_manager);

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
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;

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
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_MAINFRM_H_INCLUDED
