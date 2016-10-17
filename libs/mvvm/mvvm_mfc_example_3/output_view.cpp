//
//  output_view.cpp
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

#include "output_view.h"
#include "Resource.h"
#include "main_frame_view.h"

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

std::wstring string_format(const std::wstring fmt_str, ...)
{
    int n = ((int)fmt_str.size()) * 2; // Reserve two times as much as the length of the fmt_str
    int final_n = 0;
    std::wstring str;
    std::unique_ptr<wchar_t[]> formatted;
    va_list ap;
    while(true)
    {
        formatted.reset(new wchar_t[n]); //* Wrap the plain char array into the unique_ptr
        wcscpy_s(&formatted[0], n, fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vswprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if(final_n < 0 || final_n >= n)
        {
            n += abs(final_n - n + 1);
        }
        else
        {
            break;
        }
    }
    return std::wstring(formatted.get());
}

std::wstring object_information(const m::object::ptr& o)
{
    equipment_interface::ptr e = std::dynamic_pointer_cast<equipment_interface>(o);
    if(e)
    {
        return string_format(L"class equipment_model[category=%s, name=%s, quantity=%d]",
            (*e->category).c_str(),
            (*e->name).c_str(),
            *e->quantity);
    }
    m::wobservable_list<equipment_interface::ptr>::ptr el = std::dynamic_pointer_cast<m::wobservable_list<equipment_interface::ptr>>(o);
    if(el)
    {
        return string_format(L"class go::mvvm::wobservable_list<equipment_model>[size=%d]",
            el->size());
    }
    fleet_organization_interface::ptr f = std::dynamic_pointer_cast<fleet_organization_interface>(o);
    if(f)
    {
        return string_format(L"class fleet_organization_model[name=%s, spaceship_model.name=%s, parent.name=%s, first_child.name=%s, previous_sibling.name=%s, next_sibling.name=%s]",
            (*f->name).c_str(),
            *f->spaceship_model ? (*(*f->spaceship_model)->name).c_str() : L"<null>",
            *f->parent ? (*(*f->parent)->name).c_str() : L"<null>",
            *f->first_child ? (*(*f->first_child)->name).c_str() : L"<null>",
            *f->previous_sibling ? (*(*f->previous_sibling)->name).c_str() : L"<null>",
            *f->next_sibling ? (*(*f->next_sibling)->name).c_str() : L"<null>");
    }
    spaceship_interface::ptr s = std::dynamic_pointer_cast<spaceship_interface>(o);
    if(s)
    {
        return string_format(L"class fleet_organization_model[spaceship_class=%s, name=%s, equipment_model={size=%d}, captain=%s, crew_complement=%d]",
            (*s->spaceship_class).c_str(),
            (*s->name).c_str(),
            *s->equipment ? (*s->equipment)->size() : 0,
            (*s->captain).c_str(),
            *s->crew_complement);
    }
    fleet_organization_view_model::ptr fvm = std::dynamic_pointer_cast<fleet_organization_view_model>(o);
    if(fvm)
    {
        return L"class fleet_organization_view_model";
    }
    return L"class go::mvvm::object";
}

}

/////////////////////////////////////////////////////////////////////////////
// COutputBar

output_view::~output_view()
{
}

output_view::output_view()
    : CDockablePane()
    , m::wcommand_execution_wobserver_interface()
    , m::object_wobserver_interface()
    , _wndTabs()
    , _wndOutputAllMvvmEvents()
    , _wndOutputCommandEvents()
    , _wndOutputObservableObjectEvents()
{
}

BEGIN_MESSAGE_MAP(output_view, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int output_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;
	}

	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!_wndOutputAllMvvmEvents.Create(dwStyle, rectDummy, &_wndTabs, 2) ||
		!_wndOutputCommandEvents.Create(dwStyle, rectDummy, &_wndTabs, 3) ||
		!_wndOutputObservableObjectEvents.Create(dwStyle, rectDummy, &_wndTabs, 4))
	{
		TRACE0("Failed to create output windows\n");
		return -1;
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	bNameValid = strTabName.LoadString(IDS_ALL_MVVM_EVENTS_TAB);
	ASSERT(bNameValid);
	_wndTabs.AddTab(&_wndOutputAllMvvmEvents, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_COMMAND_EVENTS_TAB);
	ASSERT(bNameValid);
	_wndTabs.AddTab(&_wndOutputCommandEvents, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_OBSERVABLE_OBJECT_EVENTS_TAB);
	ASSERT(bNameValid);
	_wndTabs.AddTab(&_wndOutputObservableObjectEvents, strTabName, (UINT)2);

	return 0;
}

void output_view::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void output_view::AdjustHorzScroll(CListBox& wndListBox)
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

void output_view::UpdateFonts()
{
	_wndOutputAllMvvmEvents.SetFont(&afxGlobalData.fontRegular);
	_wndOutputCommandEvents.SetFont(&afxGlobalData.fontRegular);
	_wndOutputObservableObjectEvents.SetFont(&afxGlobalData.fontRegular);
}

void output_view::on_command_executed(const m::wcommand::ptr& c)
{
    if(c)
    {
        const std::wstring msg = string_format(L"%s: Executed command %s", current_date_and_time().c_str(), c->command_name().c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void output_view::on_command_not_executed(const m::wcommand::ptr& c)
{
    if(c)
    {
        const std::wstring msg = string_format(L"%s: Command %s was not executed", current_date_and_time().c_str(), c->command_name().c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void output_view::on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a)
{
    if(o && a)
    {
        std::wstring msg;
        switch(a->action())
        {
        case m::notify_container_changed_action_add:
            msg = string_format(L"%s: Added %zu elements to container, %s", current_date_and_time().c_str(), a->added_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_remove:
            msg = string_format(L"%s: Removed %zu elements from container, %s", current_date_and_time().c_str(), a->removed_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_reset:
            msg = string_format(L"%s: Reset container, removed all %zu elements, %s", current_date_and_time().c_str(), a->removed_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_swap:
            msg = string_format(L"%s: Swapped container elements, had %zu, now got %zu, %s", current_date_and_time().c_str(), a->removed_elements(), a->added_elements(), object_information(o).c_str());
            break;
        default:
            msg = string_format(L"%s: Unknown container action, %s", current_date_and_time().c_str(), object_information(o).c_str());
            break;
        }
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputObservableObjectEvents.AddString(msg.c_str());
    }
}

void output_view::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a)
    {
        const std::wstring msg = string_format(L"%s: Changed property %s, %s", current_date_and_time().c_str(), a->property_name().c_str(), object_information(o).c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputObservableObjectEvents.AddString(msg.c_str());
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
