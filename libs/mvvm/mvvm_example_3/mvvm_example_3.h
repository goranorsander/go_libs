#ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_H_INCLUDED

//
//  mvvm_example_3.h
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

#include "resource.h"       // main symbols


// mvvm_example_3_app:
// See mvvm_example_3.cpp for the implementation of this class
//

class mvvm_example_3_app : public CWinAppEx
{
public:
	mvvm_example_3_app();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern mvvm_example_3_app theApp;

#endif  // #ifndef GO_MVVM_EXAMPLE_3_H_INCLUDED
