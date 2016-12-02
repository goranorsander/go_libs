#ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_H_INCLUDED

//
//  mvvm_mfc_example_3.h
//
//  Copyright 2016 G�ran Orsander
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

#include <go/mvvm.hpp>

class main_frame_view;

class mvvm_mfc_example_3_app
    : public CWinAppEx
{
public:
    virtual ~mvvm_mfc_example_3_app() = default;
	mvvm_mfc_example_3_app();

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

    void on_show_spaceship(const fleet_organization_id_type id);
    void on_close_spaceship(const fleet_organization_id_type id);

private:
    static main_frame_view* get_main_frame_view();

public:
    BOOL  _bHiColorIcons;

protected:
    HMENU  _hMDIMenu;
    HACCEL _hMDIAccel;

private:
    static main_frame_view* _main_frame_view;

    UINT_PTR _timer_id;
    m::wcommand_manager::ptr _command_manager;
    fleet_repository::ptr _fleet_repository;
};

extern mvvm_mfc_example_3_app theApp;

#endif  // #ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
