//
//  mvvm_mfc_example_1.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "mvvm_mfc_example_1.h"
#include "product_view.hpp"

#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mvvm_mfc_example_1_app theApp;

BEGIN_MESSAGE_MAP(mvvm_mfc_example_1_app, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

mvvm_mfc_example_1_app::~mvvm_mfc_example_1_app()
{
}

mvvm_mfc_example_1_app::mvvm_mfc_example_1_app()
    : CWinApp()
    , m_timer_id(0)
    , m_command_manager()
{
}

BOOL mvvm_mfc_example_1_app::InitInstance()
{
	CWinApp::InitInstance();
    std::unique_ptr<CShellManager> pShellManager = std::make_unique<CShellManager>();
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    m_command_manager = m::wcommand_manager::create();
    m_timer_id = SetTimer(NULL, 0, 100, NULL);

	product_view dlg(m_command_manager);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

    KillTimer(NULL, m_timer_id);

    pShellManager.reset();

	return FALSE;
}

BOOL mvvm_mfc_example_1_app::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_TIMER)
    {
        m_command_manager->execute_commands();
    }
    return CWinApp::PreTranslateMessage(pMsg);
}
