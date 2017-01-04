#ifndef GO_BOOST_MVVM_EXAMPLE_1_HPP_INCLUDED
#define GO_BOOST_MVVM_EXAMPLE_1_HPP_INCLUDED

//
//  boost_mvvm_mfc_example_1.hpp
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

#include <go_boost/mvvm.hpp>

namespace m = go_boost::mvvm;

class boost_mvvm_mfc_example_1_app
    : public CWinApp
{
public:
    virtual ~boost_mvvm_mfc_example_1_app();
    boost_mvvm_mfc_example_1_app();

public:
	virtual BOOL InitInstance();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

private:
    UINT_PTR m_timer_id;
    m::wcommand_manager::ptr m_command_manager;
};

extern boost_mvvm_mfc_example_1_app theApp;

#endif  // #ifndef GO_BOOST_MVVM_EXAMPLE_1_HPP_INCLUDED
