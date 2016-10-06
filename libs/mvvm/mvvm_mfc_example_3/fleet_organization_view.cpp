//
//  fleet_organization_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "main_frame_view.h"
#include "fleet_organization_view.h"
#include "Resource.h"
#include "mvvm_mfc_example_3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

fleet_organization_view::~fleet_organization_view()
{
    if(m_on_data_context_changed_slot_key != 0 && m_fleet_organization_view_model)
    {
        m_fleet_organization_view_model->property_changed.disconnect(m_on_data_context_changed_slot_key);
    }
}

fleet_organization_view::fleet_organization_view(const m::wcommand_manager::ptr& command_manager)
    : CDockablePane()
    , m_wndFileView()
    , m_FileViewImages()
    , m_wndToolBar()
    , m_command_manager(command_manager)
    , m_fleet_organization_view_model()
    , m_on_data_context_changed_slot_key(0)
{
    m_wndFileView.reset(new tree_control(this));
}

void fleet_organization_view::view_model(const fleet_organization_view_model::ptr view_model)
{
    if(m_fleet_organization_view_model == view_model) { return; }
    if(m_on_data_context_changed_slot_key != 0 && m_fleet_organization_view_model)
    {
        m_fleet_organization_view_model->data_context_changed.disconnect(m_on_data_context_changed_slot_key);
        m_on_data_context_changed_slot_key = 0;
    }
    m_fleet_organization_view_model = view_model;
    if(m_fleet_organization_view_model)
    {
        m_on_data_context_changed_slot_key = m_fleet_organization_view_model->data_context_changed.connect(std::bind(&fleet_organization_view::on_data_context_changed, this));
    }
}

BEGIN_MESSAGE_MAP(fleet_organization_view, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//ON_WM_CONTEXTMENU()
	//ON_COMMAND(ID_PROPERTIES, OnProperties)
	//ON_COMMAND(ID_OPEN, OnFileOpen)
	//ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	//ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	//ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	//ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

int fleet_organization_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView->Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;
	}

	m_FileViewImages.Create(IDB_FLEET_ORGANIZATION, 16, 0, RGB(255, 0, 255));
	m_wndFileView->SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void fleet_organization_view::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

//void fleet_organization_view::OnContextMenu(CWnd* pWnd, CPoint point)
//{
//	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
//	ASSERT_VALID(pWndTree);
//
//	if (pWnd != pWndTree)
//	{
//		CDockablePane::OnContextMenu(pWnd, point);
//		return;
//	}
//
//	if (point != CPoint(-1, -1))
//	{
//		CPoint ptTree = point;
//		pWndTree->ScreenToClient(&ptTree);
//
//		UINT flags = 0;
//		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
//		if (hTreeItem != NULL)
//		{
//			pWndTree->SelectItem(hTreeItem);
//		}
//	}
//
//	pWndTree->SetFocus();
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
//}

void fleet_organization_view::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView->SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

//void fleet_organization_view::OnProperties()
//{
//	AfxMessageBox(_T("Properties...."));
//
//}
//
//void fleet_organization_view::OnFileOpen()
//{
//	// TODO: Add your command handler code here
//}
//
//void fleet_organization_view::OnFileOpenWith()
//{
//	// TODO: Add your command handler code here
//}
//
//void fleet_organization_view::OnDummyCompile()
//{
//	// TODO: Add your command handler code here
//}
//
//void fleet_organization_view::OnEditCut()
//{
//	// TODO: Add your command handler code here
//}
//
//void fleet_organization_view::OnEditCopy()
//{
//	// TODO: Add your command handler code here
//}
//
//void fleet_organization_view::OnEditClear()
//{
//	// TODO: Add your command handler code here
//}

void fleet_organization_view::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wndFileView->GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void fleet_organization_view::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView->SetFocus();
}

void fleet_organization_view::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FLEET_ORGANIZATION_24 : IDB_FLEET_ORGANIZATION;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView->SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void fleet_organization_view::on_selected(const HTREEITEM hItem, DWORD_PTR pItemData)
{
    if(m_fleet_organization_view_model)
    {
        m_fleet_organization_view_model->selected_fleet_organization_id = static_cast<fleet_organization_id_type>(pItemData);
    }
}

void fleet_organization_view::on_deselect(const HTREEITEM hItem, DWORD_PTR pItemData)
{
    if(m_fleet_organization_view_model)
    {
        m_fleet_organization_view_model->selected_fleet_organization_id = 0;
    }
}

void fleet_organization_view::on_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton)
{
    if(mouseButton == mb_right)
    {
        // Track context menu
        int i = 1;
        ++i;
    }
}

void fleet_organization_view::on_double_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton)
{
    if(mouseButton == mb_left)
    {
        // issue show fleet object command
        int i = 1;
        ++i;
    }
}

void fleet_organization_view::on_data_context_changed()
{
    if(m_fleet_organization_view_model && m_fleet_organization_view_model->fleet_organization_root.get())
    {
        populate();
    }
}

void fleet_organization_view::populate()
{
    const HTREEITEM hRoot = m_wndFileView->InsertItem(m_fleet_organization_view_model->fleet_organization_root.get()->name.get().c_str(), 0, 0, TVI_ROOT, TVI_LAST);
    add_fleet_organization(hRoot, m_fleet_organization_view_model->fleet_organization_root.get()->first_child);
    m_wndFileView->Expand(hRoot, TVE_EXPAND);
}

void fleet_organization_view::add_fleet_organization(HTREEITEM parent, const fleet_organization_interface::ptr& child)
{
    if(parent == 0 || !child) { return; }
    const int image = child->spaceship_model.get() ? 1 : 0;
    const HTREEITEM item = m_wndFileView->InsertItem(child->name.get().c_str(), image, image, parent, TVI_LAST);
    const fleet_organization_id_type id = std::dynamic_pointer_cast<fleet_organization_model>(child)->id;
    m_wndFileView->SetItemData(item, static_cast<DWORD_PTR>(id));
    add_fleet_organization(item, child->first_child);
    add_fleet_organization(parent, child->next_sibling);
    m_wndFileView->Expand(item, TVE_EXPAND);
}
