//
//  mvvm_example_3.cpp
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
#include "mvvm_example_3.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "mvvm_example_3_doc.h"
#include "mvvm_example_3_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mvvm_example_3_app theApp;

BEGIN_MESSAGE_MAP(mvvm_example_3_app, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &mvvm_example_3_app::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

mvvm_example_3_app::~mvvm_example_3_app()
{
}

mvvm_example_3_app::mvvm_example_3_app()
    : CWinAppEx()
    ,  m_bHiColorIcons(TRUE)
    , m_timer_id(0)
    , m_command_manager()
{
	SetAppID(_T("mvvm_example_3.AppID.NoVersion"));
}

BOOL mvvm_example_3_app::InitInstance()
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

    m_command_manager = m::wcommand_manager::create();
    m_timer_id = SetTimer(NULL, 0, 100, NULL);

    CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_mvvm_example_3TYPE,
		RUNTIME_CLASS(mvvm_example_3_doc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(mvvm_example_3_view));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	CMainFrame* pMainFrame = new CMainFrame(m_command_manager);
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int mvvm_example_3_app::ExitInstance()
{
    KillTimer(NULL, m_timer_id);
    return CWinAppEx::ExitInstance();
}

BOOL mvvm_example_3_app::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_TIMER)
    {
        m_command_manager->execute_commands();
    }
    return CWinAppEx::PreTranslateMessage(pMsg);
}

class CAboutDlg : public CDialogEx
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

void mvvm_example_3_app::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void mvvm_example_3_app::PreLoadState()
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

void mvvm_example_3_app::LoadCustomState()
{
}

void mvvm_example_3_app::SaveCustomState()
{
}
