#ifndef GO_MVVM_EXAMPLE_3_FILEVIEW_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_FILEVIEW_H_INCLUDED

//
//  fleet_organization_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_organization_view_model.hpp"
#include "ViewTree.h"

namespace s = go::signals;

class fleet_organization_view_tool_bar
    : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class fleet_organization_view
    : public CDockablePane
    , public view_tree_observer
{
public:
    virtual ~fleet_organization_view();
    fleet_organization_view(const m::wcommand_manager::ptr& command_manager);

	void AdjustLayout();
	void OnChangeVisualStyle();

    void view_model(const fleet_organization_view_model::ptr view_model);

public:
    virtual void on_selected(const HTREEITEM hItem, DWORD_PTR pItemData);
    virtual void on_deselect(const HTREEITEM hItem, DWORD_PTR pItemData);
    virtual void on_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton);
    virtual void on_double_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton);

protected:
    virtual void on_data_context_changed();

    void populate();

    void add_fleet_organization(HTREEITEM parent, const fleet_organization_interface::ptr& child);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg void OnProperties();
	//afx_msg void OnFileOpen();
	//afx_msg void OnFileOpenWith();
	//afx_msg void OnDummyCompile();
	//afx_msg void OnEditCut();
	//afx_msg void OnEditCopy();
	//afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()

protected:
    std::unique_ptr<CViewTree> m_wndFileView;
    CImageList m_FileViewImages;
    fleet_organization_view_tool_bar m_wndToolBar;

private:
    m::wcommand_manager::wptr m_command_manager;
    fleet_organization_view_model::ptr m_fleet_organization_view_model;
    s::slot_key_type m_on_data_context_changed_slot_key;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_FILEVIEW_H_INCLUDED
