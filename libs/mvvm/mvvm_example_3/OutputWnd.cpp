//
//  OutputWnd.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"

#include <cstdio>
#include <locale>
#include  <time.h>

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{

std::wstring current_date_and_time()
{
    const std::time_t t = std::time(NULL);
    std::tm lt;
    localtime_s(&lt, &t);
    std::wstring dt(100, 0);
    std::wcsftime(&(dt[0]), 100, _T("%F %T"), &lt);
    return dt;
}

}

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::~COutputWnd()
{
}

COutputWnd::COutputWnd()
    : CDockablePane()
    , m::wcommand_execution_wobserver_interface()
    , m::object_wobserver_interface()
    , m_wndTabs()
    , m_wndOutputAllMvvmEvents()
    , m_wndOutputCommandEvents()
    , m_wndOutputObservableObjectEvents()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;
	}

	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputAllMvvmEvents.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputCommandEvents.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputObservableObjectEvents.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("Failed to create output windows\n");
		return -1;
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	bNameValid = strTabName.LoadString(IDS_ALL_MVVM_EVENTS_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputAllMvvmEvents, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_COMMAND_EVENTS_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputCommandEvents, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_OBSERVABLE_OBJECT_EVENTS_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputObservableObjectEvents, strTabName, (UINT)2);

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputAllMvvmEvents.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputCommandEvents.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputObservableObjectEvents.SetFont(&afxGlobalData.fontRegular);
}

void COutputWnd::on_command_executed(const m::wcommand::ptr& c)
{
    if(c)
    {
        const std::wstring msg = current_date_and_time() + _T(": Executed command ") + c->command_name();
        m_wndOutputAllMvvmEvents.AddString(msg.c_str());
        m_wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void COutputWnd::on_command_not_executed(const m::wcommand::ptr& c)
{
    if(c)
    {
        const std::wstring msg = current_date_and_time() + _T(": Command ") + c->command_name() + _T(" was not executed");
        m_wndOutputAllMvvmEvents.AddString(msg.c_str());
        m_wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void COutputWnd::on_container_changed(const m::object::ptr& o, const std::shared_ptr<m::container_changed_arguments>& a)
{
    if(o && a)
    {
        std::wstring msg(1000, 0);
        switch(a->action())
        {
        case m::notify_container_changed_action_add:
            swprintf_s(&(msg[0]), 1000, _T("%s: Added %zu elements to container"), current_date_and_time().c_str(), a->added_elements());
            break;
        case m::notify_container_changed_action_remove:
            swprintf_s(&(msg[0]), 1000, _T("%s: Removed %zu elements from container"), current_date_and_time().c_str(), a->removed_elements());
            break;
        case m::notify_container_changed_action_reset:
            swprintf_s(&(msg[0]), 1000, _T("%s: Reset container, removed all %zu elements"), current_date_and_time().c_str(), a->removed_elements());
            break;
        case m::notify_container_changed_action_swap:
            swprintf_s(&(msg[0]), 1000, _T("%s: Swapped container elements, had %zu, now got %zu"), current_date_and_time().c_str(), a->removed_elements(), a->added_elements());
            break;
        default:
            swprintf_s(&(msg[0]), 1000, _T("%s: Unknown container action"), current_date_and_time().c_str());
            break;
        }
        m_wndOutputAllMvvmEvents.AddString(msg.c_str());
        m_wndOutputObservableObjectEvents.AddString(msg.c_str());
    }
}

void COutputWnd::on_property_changed(const m::object::ptr& o, const std::shared_ptr<m::wproperty_changed_arguments>& a)
{
    if(o && a)
    {
        const std::wstring msg = current_date_and_time() + _T(": Changed property ") + a->property_name();
        m_wndOutputAllMvvmEvents.AddString(msg.c_str());
        m_wndOutputObservableObjectEvents.AddString(msg.c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////

COutputList::~COutputList()
{
}

COutputList::COutputList()
    : CListBox()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("Copy output"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("Clear output"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
