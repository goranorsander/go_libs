#ifndef GO_BOOST_MVVM_EXAMPLE_3_H_INCLUDED
#define GO_BOOST_MVVM_EXAMPLE_3_H_INCLUDED

//
//  boost_mvvm_mfc_example_3.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "fleet_repository.hpp"
#include "resource.h"

#include <go_boost/mvvm.hpp>

class main_frame_view;

class boost_mvvm_mfc_example_3
    : public CWinAppEx
{
public:
    virtual ~boost_mvvm_mfc_example_3();
	boost_mvvm_mfc_example_3();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
    afx_msg void OnFileNew();
    afx_msg void OnFileOpen();
    afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);

    DECLARE_MESSAGE_MAP()

public:
    HMENU mdiMenu() const;
    HACCEL mdiAccel() const;

public:
    BOOL  _bHiColorIcons;

protected:
    HMENU  _hMDIMenu;
    HACCEL _hMDIAccel;

private:
    UINT_PTR _timer_id;
    m::wcommand_manager::ptr _command_manager;
    m::wevent_manager::ptr _event_manager;
    fleet_repository::ptr _fleet_repository;
};

extern boost_mvvm_mfc_example_3 theApp;

#endif  // #ifndef GO_BOOST_MVVM_EXAMPLE_3_H_INCLUDED
