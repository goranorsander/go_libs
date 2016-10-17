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
    if(_on_data_context_changed_slot_key != 0 && _fleet_organization_view_model)
    {
        _fleet_organization_view_model->property_changed.disconnect(_on_data_context_changed_slot_key);
    }
}

fleet_organization_view::fleet_organization_view(const m::wcommand_manager::ptr& command_manager)
    : CDockablePane()
    , _wndFileView()
    , _fileViewImages()
    , _wndToolBar()
    , _command_manager(command_manager)
    , _fleet_organization_view_model()
    , _on_data_context_changed_slot_key(0)
{
    _wndFileView.reset(new tree_control(this));
}

void fleet_organization_view::view_model(const fleet_organization_view_model::ptr view_model)
{
    if(_fleet_organization_view_model == view_model) { return; }
    if(_on_data_context_changed_slot_key != 0 && _fleet_organization_view_model)
    {
        _fleet_organization_view_model->data_context_changed.disconnect(_on_data_context_changed_slot_key);
        _on_data_context_changed_slot_key = 0;
    }
    _fleet_organization_view_model = view_model;
    if(_fleet_organization_view_model)
    {
        _on_data_context_changed_slot_key = _fleet_organization_view_model->data_context_changed.connect(std::bind(&fleet_organization_view::on_data_context_changed, this));
    }
}

BEGIN_MESSAGE_MAP(fleet_organization_view, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
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

	if (!_wndFileView->Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;
	}

	_fileViewImages.Create(IDB_FLEET_ORGANIZATION, 16, 0, RGB(255, 0, 255));
	_wndFileView->SetImageList(&_fileViewImages, TVSIL_NORMAL);

	_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	_wndToolBar.SetPaneStyle(_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	_wndToolBar.SetPaneStyle(_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	_wndToolBar.SetOwner(this);
	_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void fleet_organization_view::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void fleet_organization_view::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = _wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	_wndFileView->SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void fleet_organization_view::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	_wndFileView->GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void fleet_organization_view::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	_wndFileView->SetFocus();
}

void fleet_organization_view::OnChangeVisualStyle()
{
	_wndToolBar.CleanUpLockedImages();
	_wndToolBar.LoadBitmap(theApp._bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	_fileViewImages.DeleteImageList();

	UINT uiBmpId = theApp._bHiColorIcons ? IDB_FLEET_ORGANIZATION_24 : IDB_FLEET_ORGANIZATION;

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

	nFlags |= (theApp._bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	_fileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	_fileViewImages.Add(&bmp, RGB(255, 0, 255));

	_wndFileView->SetImageList(&_fileViewImages, TVSIL_NORMAL);
}

void fleet_organization_view::on_selected(const HTREEITEM hItem, DWORD_PTR pItemData)
{
    if(_fleet_organization_view_model)
    {
        _fleet_organization_view_model->selected_fleet_organization_id = static_cast<fleet_organization_id_type>(pItemData);
    }
}

void fleet_organization_view::on_deselect(const HTREEITEM hItem, DWORD_PTR pItemData)
{
    if(_fleet_organization_view_model)
    {
        _fleet_organization_view_model->selected_fleet_organization_id = 0;
    }
}

void fleet_organization_view::on_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton)
{
}

void fleet_organization_view::on_double_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton)
{
    if(_fleet_organization_view_model && mouseButton == mb_left)
    {
        m::wcommand_manager::ptr command_manager = _command_manager.lock();
        if(command_manager)
        {
            command_manager->issue_command(_fleet_organization_view_model->on_left_double_click_command);
        }
    }
}

void fleet_organization_view::on_data_context_changed()
{
    if(_fleet_organization_view_model && _fleet_organization_view_model->fleet_organization_root.get())
    {
        populate();
    }
}

void fleet_organization_view::populate()
{
    const HTREEITEM hRoot = _wndFileView->InsertItem(_fleet_organization_view_model->fleet_organization_root.get()->name.get().c_str(), 0, 0, TVI_ROOT, TVI_LAST);
    add_fleet_organization(hRoot, _fleet_organization_view_model->fleet_organization_root.get()->first_child);
    _wndFileView->Expand(hRoot, TVE_EXPAND);
}

void fleet_organization_view::add_fleet_organization(HTREEITEM parent, const fleet_organization_interface::ptr& child)
{
    if(parent == 0 || !child) { return; }
    const int image = child->spaceship_model.get() ? 1 : 0;
    const HTREEITEM item = _wndFileView->InsertItem(child->name.get().c_str(), image, image, parent, TVI_LAST);
    const fleet_organization_id_type id = std::dynamic_pointer_cast<fleet_organization_model>(child)->id;
    _wndFileView->SetItemData(item, static_cast<DWORD_PTR>(id));
    add_fleet_organization(item, child->first_child);
    add_fleet_organization(parent, child->next_sibling);
    _wndFileView->Expand(item, TVE_EXPAND);
}
