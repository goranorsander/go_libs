//
//  tree_control.cpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "tree_control.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

tree_control::tree_control(tree_control_observer* observer)
    : CTreeCtrl()
    , _observer(observer)
    , _hSelectedItem(NULL)
{
}

BEGIN_MESSAGE_MAP(tree_control, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
END_MESSAGE_MAP()

BOOL tree_control::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void tree_control::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        _observer->on_click(hItem, GetItemData(hItem), GetClickPos(), mb_left);
    }
}

void tree_control::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        _observer->on_double_click(hItem, GetItemData(hItem), GetClickPos(), mb_left);
    }
}

void tree_control::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        SelectItem(hItem);
        _observer->on_click(hItem, GetItemData(hItem), GetClickPos(), mb_right);
    }
}

void tree_control::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(_observer == NULL)
    {
        return;
    }
    const HTREEITEM hItem = GetSelectedItem();
    if(hItem != NULL)
    {
        _observer->on_double_click(hItem, GetItemData(hItem), GetClickPos(), mb_right);
    }
}

void tree_control::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    if(_observer == NULL)
    {
        return;
    }
    if(_hSelectedItem != NULL)
    {
        _observer->on_deselect(_hSelectedItem, GetItemData(_hSelectedItem));
    }
    _hSelectedItem = GetSelectedItem();
    if(_hSelectedItem != NULL)
    {
        _observer->on_selected(_hSelectedItem, GetItemData(_hSelectedItem));
    }
}

CPoint tree_control::GetClickPos() const
{
    const DWORD messagePos = GetMessagePos();
    return CPoint(GET_X_LPARAM(messagePos), GET_Y_LPARAM(messagePos));
}
