//
//  mvvm_mfc_starfleet_example.cpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "mvvm_mfc_starfleet_example.hpp"
#include "main_frame_view.hpp"
#include "spaceship_view.hpp"

#include <go_boost/utility.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mvvm_mfc_starfleet_example theApp;

class CAboutDlg
    : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX) GO_BOOST_OVERRIDE;

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg()
    : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

mvvm_mfc_starfleet_example::~mvvm_mfc_starfleet_example()
{
}

mvvm_mfc_starfleet_example::mvvm_mfc_starfleet_example()
    : CWinAppEx()
    , _bHiColorIcons(TRUE)
    , _hMDIMenu(0)
    , _hMDIAccel(0)
    , _timer_id(0)
    , _command_manager()
    , _event_manager()
    , _fleet_repository()
{
#if BOOST_MSVC > 1500
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
    SetAppID(_T("mvvm_mfc_starfleet_example.AppID.NoVersion"));
#endif // BOOST_MSVC > 1500
}

BOOL mvvm_mfc_starfleet_example::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();

    if(!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }

    AfxEnableControlContainer();
#if BOOST_MSVC > 1500
    EnableTaskbarInteraction();
#endif // BOOST_MSVC > 1500
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    InitContextMenuManager();
    InitKeyboardManager();
    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    _command_manager = m::wcommand_manager::create();
    _event_manager = m::wevent_manager::create();
    _fleet_repository = fleet_repository::create();
    _timer_id = SetTimer(NULL, 0, 100, NULL);

    {
        u::scope_guard_new<main_frame_view> pMainFrame(new main_frame_view(_command_manager, _event_manager, _fleet_repository));
        if(!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
        {
            return FALSE;
        }
        m_pMainWnd = pMainFrame.detach();
    }

    HINSTANCE hInst = AfxGetResourceHandle();
    _hMDIMenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MVVM_MFC_STARFLEET_EXAMPLETYPE));
    _hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_MVVM_MFC_STARFLEET_EXAMPLETYPE));

    m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

int mvvm_mfc_starfleet_example::ExitInstance()
{
    KillTimer(NULL, _timer_id);

    if(_hMDIMenu != NULL)
        FreeResource(_hMDIMenu);
    if(_hMDIAccel != NULL)
        FreeResource(_hMDIAccel);

    AfxOleTerm(FALSE);

    return CWinAppEx::ExitInstance();
}

BOOL mvvm_mfc_starfleet_example::PreTranslateMessage(MSG* pMsg)
{
    switch(pMsg->message)
    {
    case WM_TIMER:
        _command_manager->execute_commands();
        _event_manager->fire_events();
        break;
    }
    return CWinAppEx::PreTranslateMessage(pMsg);
}

void mvvm_mfc_starfleet_example::PreLoadState()
{
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
    bNameValid = strName.LoadString(IDS_EXPLORER);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void mvvm_mfc_starfleet_example::LoadCustomState()
{
}

void mvvm_mfc_starfleet_example::SaveCustomState()
{
}

void mvvm_mfc_starfleet_example::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

void mvvm_mfc_starfleet_example::OnFileNew()
{
}

void mvvm_mfc_starfleet_example::OnFileOpen()
{
}

void mvvm_mfc_starfleet_example::OnUpdateFileNew(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
}

void mvvm_mfc_starfleet_example::OnUpdateFileOpen(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
}

BEGIN_MESSAGE_MAP(mvvm_mfc_starfleet_example, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &mvvm_mfc_starfleet_example::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &mvvm_mfc_starfleet_example::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &mvvm_mfc_starfleet_example::OnFileOpen)
    ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &mvvm_mfc_starfleet_example::OnUpdateFileNew)
    ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &mvvm_mfc_starfleet_example::OnUpdateFileOpen)
END_MESSAGE_MAP()

HMENU mvvm_mfc_starfleet_example::mdiMenu() const
{
    return _hMDIMenu;
}

HACCEL mvvm_mfc_starfleet_example::mdiAccel() const
{
    return _hMDIAccel;
}
