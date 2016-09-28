//
//  ViewTree.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

view_tree_observer::~view_tree_observer()
{
}

CViewTree::~CViewTree()
{
}

CViewTree::CViewTree(view_tree_observer* observer)
    : CTreeCtrl()
    , m_observer(observer)
    , m_hSelectedItem(NULL)
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
END_MESSAGE_MAP()

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if(pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(m_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        m_observer->on_click(hItem, GetItemData(hItem), GetClickPos(), mb_left);
    }
}

void CViewTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(m_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        m_observer->on_double_click(hItem, GetItemData(hItem), GetClickPos(), mb_left);
    }
}

void CViewTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(m_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        SelectItem(hItem);
        m_observer->on_click(hItem, GetItemData(hItem), GetClickPos(), mb_right);
    }
}

void CViewTree::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(m_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        m_observer->on_double_click(hItem, GetItemData(hItem), GetClickPos(), mb_right);
    }
}

void CViewTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(m_observer == NULL)
    {
        return;
    }
    if(m_hSelectedItem != NULL)
    {
        m_observer->on_deselect(m_hSelectedItem, GetItemData(m_hSelectedItem));
    }
    m_hSelectedItem = GetSelectedItem();
    if(m_hSelectedItem != NULL)
    {
        m_observer->on_selected(m_hSelectedItem, GetItemData(m_hSelectedItem));
    }
}

CPoint CViewTree::GetClickPos() const
{
    const DWORD messagePos = GetMessagePos();
    return CPoint(GET_X_LPARAM(messagePos), GET_Y_LPARAM(messagePos));
}
