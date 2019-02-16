#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_HPP_INCLUDED

//
//  mvvm_mfc_starfleet_example.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "fleet_repository.hpp"
#include "Resource.h"

#include <go/mvvm.hpp>

class main_frame_view;

class mvvm_mfc_starfleet_example_app
    : public CWinAppEx
{
public:
    virtual ~mvvm_mfc_starfleet_example_app() GO_DEFAULT_DESTRUCTOR
    mvvm_mfc_starfleet_example_app();

public:
    virtual BOOL InitInstance() override;
    virtual int ExitInstance() override;
    virtual BOOL PreTranslateMessage(MSG* pMsg) override;

    virtual void PreLoadState() override;
    virtual void LoadCustomState() override;
    virtual void SaveCustomState() override;

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

extern mvvm_mfc_starfleet_example_app theApp;

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_HPP_INCLUDED
