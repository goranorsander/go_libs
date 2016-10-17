//
//  properties_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"

#include <go/utility.hpp>

#include "properties_view.h"
#include "Resource.h"
#include "main_frame_view.h"
#include "mvvm_mfc_example_3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

properties_view::~properties_view()
{
}

properties_view::properties_view()
    : CDockablePane()
    , _wndToolBar()
    , _wndPropList()
    , _properties_view_model()
    , _on_data_context_changed_slot_key(0)
{
}

BEGIN_MESSAGE_MAP(properties_view, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

void properties_view::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = _wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb, rectClient.Width(), rectClient.Height() - cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
}

void properties_view::view_model(const properties_view_model::ptr view_model)
{
    if(_properties_view_model == view_model) { return; }
    if(_on_data_context_changed_slot_key != 0 && _properties_view_model)
    {
        _properties_view_model->data_context_changed.disconnect(_on_data_context_changed_slot_key);
        _on_data_context_changed_slot_key = 0;
    }
    _properties_view_model = view_model;
    if(_properties_view_model)
    {
        _on_data_context_changed_slot_key = _properties_view_model->data_context_changed.connect(std::bind(&properties_view::on_data_context_changed, this));
    }
}

void properties_view::on_data_context_changed()
{
    _wndPropList.RemoveAll();
    populate();
}

void properties_view::populate()
{
    if(!_properties_view_model) { return; }
    if(!_properties_view_model->data_context.get()) { return; }
    populate_with(_properties_view_model->data_context.get());
}

void properties_view::populate_with(const fleet_organization_interface::ptr& fleet_organization)
{
    u::scope_guard_new<CMFCPropertyGridProperty> fleet_organization_group(new CMFCPropertyGridProperty(_T("Fleet organization")));

    u::scope_guard_new<CMFCPropertyGridProperty> name_prop(new CMFCPropertyGridProperty(_T("Name"), fleet_organization->name.get().c_str(), _T("Spaceships name in the fleet organization")));
    name_prop->AllowEdit(FALSE);
    fleet_organization_group->AddSubItem(name_prop.detach());

    _wndPropList.AddProperty(fleet_organization_group.detach());

    if(fleet_organization->spaceship_model.get() != nullptr)
    {
        populate_with(fleet_organization->spaceship_model.get());
    }
}

void properties_view::populate_with(const spaceship_interface::ptr& spaceship)
{
    u::scope_guard_new<CMFCPropertyGridProperty> spaceship_group(new CMFCPropertyGridProperty(_T("Spaceship")));

    u::scope_guard_new<CMFCPropertyGridProperty> class_prop(new CMFCPropertyGridProperty(_T("Class"), spaceship->spaceship_class.get().c_str(), _T("Spaceship class")));
    class_prop->AllowEdit(FALSE);
    spaceship_group->AddSubItem(class_prop.detach());

    u::scope_guard_new<CMFCPropertyGridProperty> name_prop(new CMFCPropertyGridProperty(_T("Name"), spaceship->name.get().c_str(), _T("Spaceship name")));
    name_prop->AllowEdit(FALSE);
    spaceship_group->AddSubItem(name_prop.detach());

    u::scope_guard_new<CMFCPropertyGridProperty> captain_prop(new CMFCPropertyGridProperty(_T("Captain"), spaceship->captain.get().c_str(), _T("Spaceship captain")));
    captain_prop->AllowEdit(FALSE);
    spaceship_group->AddSubItem(captain_prop.detach());

    u::scope_guard_new<CMFCPropertyGridProperty> crew_complement_prop(new CMFCPropertyGridProperty(_T("Crew complement"), std::to_wstring(spaceship->crew_complement.get()).c_str(), _T("Spaceship crew complement")));
    crew_complement_prop->AllowEdit(FALSE);
    spaceship_group->AddSubItem(crew_complement_prop.detach());

    _wndPropList.AddProperty(spaceship_group.detach());

    if(spaceship->equipment.get() != nullptr)
    {
        populate_with(spaceship->equipment.get());
    }
}

void properties_view::populate_with(const m::wobservable_list<equipment_interface::ptr>::ptr& equipment)
{
    typedef std::map<std::wstring, std::list<equipment_interface::ptr>> equipment_category_map_type;
    equipment_category_map_type equipment_category;
    for(const m::wobservable_list<equipment_interface::ptr>::value_type& e : *equipment)
    {
        if(e != nullptr)
        {
            equipment_category_map_type::iterator it = equipment_category.find(e->category.get().c_str());
            if(it != equipment_category.end())
            {
                it->second.push_back(e);
            }
            else
            {
                std::list<equipment_interface::ptr> c;
                c.push_back(e);
                equipment_category[e->category.get().c_str()] = c;
            }
        }
    }

    u::scope_guard_new<CMFCPropertyGridProperty> equipment_group(new CMFCPropertyGridProperty(_T("Equipment")));

    for(const equipment_category_map_type::value_type& ec : equipment_category)
    {
        u::scope_guard_new<CMFCPropertyGridProperty> category_group(new CMFCPropertyGridProperty(ec.first.c_str()));

        for(const equipment_interface::ptr& e : ec.second)
        {
            u::scope_guard_new<CMFCPropertyGridProperty> name_prop(new CMFCPropertyGridProperty(_T("Name"), e->name.get().c_str(), _T("Equipment name")));
            name_prop->AllowEdit(FALSE);
            category_group->AddSubItem(name_prop.detach());

            u::scope_guard_new<CMFCPropertyGridProperty> quantity_prop(new CMFCPropertyGridProperty(_T("Quantity"), std::to_wstring(e->quantity.get()).c_str(), _T("Equipment quantity")));
            quantity_prop->AllowEdit(FALSE);
            category_group->AddSubItem(quantity_prop.detach());
        }

        equipment_group->AddSubItem(category_group.detach());
    }

    _wndPropList.AddProperty(equipment_group.detach());
}

int properties_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;
	}

	InitPropList();

	_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE);
	_wndToolBar.CleanUpLockedImages();
	_wndToolBar.LoadBitmap(theApp._bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE);

	_wndToolBar.SetPaneStyle(_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	_wndToolBar.SetPaneStyle(_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	_wndToolBar.SetOwner(this);
	_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void properties_view::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void properties_view::OnExpandAllProperties()
{
	_wndPropList.ExpandAll();
}

void properties_view::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void properties_view::OnSortProperties()
{
	_wndPropList.SetAlphabeticMode(!_wndPropList.IsAlphabeticMode());
}

void properties_view::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(_wndPropList.IsAlphabeticMode());
}

void properties_view::InitPropList()
{
	_wndPropList.EnableHeaderCtrl(FALSE);
	_wndPropList.EnableDescriptionArea();
	_wndPropList.SetVSDotNetLook();
	_wndPropList.MarkModifiedProperties();
}

void properties_view::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	_wndPropList.SetFocus();
}
