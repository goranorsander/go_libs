#ifndef GO_MVVM_EXAMPLE_2_H_INCLUDED
#define GO_MVVM_EXAMPLE_2_H_INCLUDED

//
//  mvvm_mfc_example_2.h
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

#include "resource.h"

#include <go/mvvm.hpp>

namespace m = go::mvvm;

class mvvm_mfc_example_2_app
    : public CWinApp
{
public:
    virtual ~mvvm_mfc_example_2_app();
    mvvm_mfc_example_2_app();

public:
	virtual BOOL InitInstance();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

private:
    UINT_PTR m_timer_id;
    m::wcommand_manager::ptr m_command_manager;
};

extern mvvm_mfc_example_2_app theApp;

#endif  // #ifndef GO_MVVM_EXAMPLE_2_H_INCLUDED
