//
//  mvvm_mfc_lambda_product_example.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "mvvm_mfc_lambda_product_example.hpp"
#include "product_view.hpp"

#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mvvm_mfc_lambda_product_example_app theApp;

BEGIN_MESSAGE_MAP(mvvm_mfc_lambda_product_example_app, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

mvvm_mfc_lambda_product_example_app::~mvvm_mfc_lambda_product_example_app()
{
}

mvvm_mfc_lambda_product_example_app::mvvm_mfc_lambda_product_example_app()
    : CWinApp()
    , m_timer_id(0)
    , m_command_manager()
{
}

BOOL mvvm_mfc_lambda_product_example_app::InitInstance()
{
    CWinApp::InitInstance();
    std::unique_ptr<CShellManager> pShellManager = std::make_unique<CShellManager>();
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    m_command_manager = m::wcommand_manager::create();
    m_timer_id = SetTimer(nullptr, 0, 100, nullptr);

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

    KillTimer(nullptr, m_timer_id);

    pShellManager.reset();

    return FALSE;
}

BOOL mvvm_mfc_lambda_product_example_app::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_TIMER)
    {
        m_command_manager->execute_commands();
    }
    return CWinApp::PreTranslateMessage(pMsg);
}
