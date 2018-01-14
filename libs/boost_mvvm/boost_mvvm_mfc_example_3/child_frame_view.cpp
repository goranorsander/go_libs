//
//  child_frame_view.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "child_frame_view.hpp"
#include "boost_mvvm_mfc_example_3.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(child_frame_view, CMDIChildWndEx)

child_frame_view::~child_frame_view()
{
}

child_frame_view::child_frame_view()
    : CMDIChildWndEx()
    , _wndView()
{
}

BOOL child_frame_view::PreCreateWindow(CREATESTRUCT& cs)
{
    if(!CMDIChildWndEx::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0);
    return TRUE;
}

BOOL child_frame_view::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // let the view have first crack at the command
    if(_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // otherwise, do default handling
    return CMDIChildWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

CString child_frame_view::GetFrameText() const
{
    spaceship_view_model::ptr vm = _wndView.data_context();
    if(vm)
    {
        return vm->name().c_str();
    }
    return CMDIChildWndEx::GetFrameText();
}

#ifdef _DEBUG
void child_frame_view::AssertValid() const
{
    CMDIChildWndEx::AssertValid();
}

void child_frame_view::Dump(CDumpContext& dc) const
{
    CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

void child_frame_view::OnFileClose()
{
    // To close the frame, just send a WM_CLOSE, which is the equivalent
    // choosing close from the system menu.
    SendMessage(WM_CLOSE);
}

void child_frame_view::OnSetFocus(CWnd* pOldWnd)
{
    CMDIChildWndEx::OnSetFocus(pOldWnd);

    _wndView.SetFocus();
}

int child_frame_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create a view to occupy the client area of the frame
    if(!_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
    {
        TRACE0("Failed to create view window\n");
        return -1;
    }

    return 0;
}

void child_frame_view::OnClose()
{
    _wndView.on_close();
    CMDIChildWndEx::OnClose();
}

void child_frame_view::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
    CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
    if(bActivate == FALSE && pDeactivateWnd == this)
    {
        _wndView.on_deactivate();
    }
}

int child_frame_view::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    _wndView.on_activate();
    return CMDIChildWndEx::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BEGIN_MESSAGE_MAP(child_frame_view, CMDIChildWndEx)
    ON_COMMAND(ID_FILE_CLOSE, &child_frame_view::OnFileClose)
    ON_WM_SETFOCUS()
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_MDIACTIVATE()
    ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

void child_frame_view::initialization_complete()
{
    _wndView.initialization_complete();
}

void child_frame_view::spaceship_view_model(const spaceship_view_model::ptr& vm)
{
    _wndView.data_context = vm;
    CMDIChildWndEx::OnUpdateFrameTitle(FALSE);
}
