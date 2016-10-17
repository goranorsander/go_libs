//
//  mvvm_mfc_example_3.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "mvvm_mfc_example_3.h"
#include "main_frame_view.h"

#include "child_frame_view.h"
#include "mvvm_mfc_example_3_doc.h"
#include "mvvm_mfc_example_3_view.h"

#include <go/utility.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mvvm_mfc_example_3_app theApp;

class CAboutDlg
    : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

mvvm_mfc_example_3_app::~mvvm_mfc_example_3_app()
{
}

mvvm_mfc_example_3_app::mvvm_mfc_example_3_app()
    : CWinAppEx()
    , _bHiColorIcons(TRUE)
    , _timer_id(0)
    , _command_manager()
    , _fleet_repository()
{
	SetAppID(_T("mvvm_mfc_example_3.AppID.NoVersion"));
}

BOOL mvvm_mfc_example_3_app::InitInstance()
{
	CWinAppEx::InitInstance();
	EnableTaskbarInteraction();
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    _command_manager = m::wcommand_manager::create();
    _fleet_repository = fleet_repository::create();
    _timer_id = SetTimer(NULL, 0, 100, NULL);

    CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MVVM_MFC_EXAMPLE_3TYPE,
		RUNTIME_CLASS(mvvm_mfc_example_3_doc),
		RUNTIME_CLASS(child_frame_view),
		RUNTIME_CLASS(mvvm_mfc_example_3_view));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

    {
        u::scope_guard_new<main_frame_view> pMainFrame(new main_frame_view(_command_manager, _fleet_repository));
        if(!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
        {
            return FALSE;
        }
        m_pMainWnd = pMainFrame.detach();
    }

	CCommandLineInfo cmdInfo;
    if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
    {
        cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
    }
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
    m_pMainWnd->UpdateWindow();

	return TRUE;
}

int mvvm_mfc_example_3_app::ExitInstance()
{
    KillTimer(NULL, _timer_id);
    return CWinAppEx::ExitInstance();
}

BOOL mvvm_mfc_example_3_app::PreTranslateMessage(MSG* pMsg)
{
    switch(pMsg->message)
    {
    case WM_TIMER:
        _command_manager->execute_commands();
        break;
    case WM_USER_SHOW_SPACESHIP:
        {
            const fleet_organization_id_type id = static_cast<fleet_organization_id_type>(pMsg->wParam);
            on_show_spaceship(id);
            return TRUE;
        }
        break;
    }
    return CWinAppEx::PreTranslateMessage(pMsg);
}

void mvvm_mfc_example_3_app::PreLoadState()
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

void mvvm_mfc_example_3_app::LoadCustomState()
{
}

void mvvm_mfc_example_3_app::SaveCustomState()
{
}

void mvvm_mfc_example_3_app::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BEGIN_MESSAGE_MAP(mvvm_mfc_example_3_app, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &mvvm_mfc_example_3_app::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

void mvvm_mfc_example_3_app::on_show_spaceship(const fleet_organization_id_type id)
{
    main_frame_view* main_frame = get_main_frame_view();
    if(main_frame != nullptr)
    {
        main_frame->on_show_spaceship(id);
    }
}

main_frame_view* mvvm_mfc_example_3_app::get_main_frame_view()
{
    return dynamic_cast<main_frame_view*>(m_pMainWnd);
}
