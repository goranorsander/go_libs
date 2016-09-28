#ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_H_INCLUDED

//
//  mvvm_mfc_example_3.h
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

#include <go/mvvm.hpp>

namespace m = go::mvvm;

class mvvm_mfc_example_3_app
    : public CWinAppEx
{
public:
    virtual ~mvvm_mfc_example_3_app();
	mvvm_mfc_example_3_app();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()

public:
    BOOL  m_bHiColorIcons;

private:
    UINT_PTR m_timer_id;
    m::wcommand_manager::ptr m_command_manager;
    fleet_repository::ptr m_fleet_repository;
};

extern mvvm_mfc_example_3_app theApp;

#endif  // #ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
