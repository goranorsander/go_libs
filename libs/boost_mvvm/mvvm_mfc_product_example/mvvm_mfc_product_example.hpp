#ifndef GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_HPP_INCLUDED
#define GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_HPP_INCLUDED

//
//  mvvm_mfc_product_example.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>

class mvvm_mfc_product_example_app
    : public CWinApp
{
public:
    virtual ~mvvm_mfc_product_example_app();
    mvvm_mfc_product_example_app();

public:
    virtual BOOL InitInstance() GO_BOOST_OVERRIDE;
    virtual BOOL PreTranslateMessage(MSG* pMsg) GO_BOOST_OVERRIDE;

    DECLARE_MESSAGE_MAP()

private:
    UINT_PTR m_timer_id;
    m::wcommand_manager::ptr m_command_manager;
};

extern mvvm_mfc_product_example_app theApp;

#endif  // #ifndef GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_HPP_INCLUDED
