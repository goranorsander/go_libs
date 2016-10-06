#ifndef GO_MVVM_EXAMPLE_3_PROPERTIESWND_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_PROPERTIESWND_H_INCLUDED

//
//  properties_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "properties_view_model.hpp"

namespace s = go::signals;

class CPropertiesToolBar
    : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class properties_view
    : public CDockablePane
{
public:
    virtual ~properties_view();
    properties_view();

	void AdjustLayout();

public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

    void view_model(const properties_view_model::ptr view_model);

protected:
    virtual void on_data_context_changed();

    void populate();

private:
    void populate_with(const fleet_organization_interface::ptr& fleet_organization);
    void populate_with(const spaceship_interface::ptr& spaceship);
    void populate_with(const m::wobservable_list<equipment_interface::ptr>::ptr& equipment);

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;

private:
    properties_view_model::ptr m_properties_view_model;
    s::slot_key_type m_on_data_context_changed_slot_key;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_PROPERTIESWND_H_INCLUDED
