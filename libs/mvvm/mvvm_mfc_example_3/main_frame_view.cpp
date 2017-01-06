//
//  main_frame_view.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "main_frame_view.hpp"
#include "child_frame_view.hpp"
#include "fleet_repository_populator.hpp"
#include "mvvm_mfc_example_3.hpp"

#include <go/utility/scope_guard.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
    ID_SEPARATOR,
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

IMPLEMENT_DYNAMIC(main_frame_view, CMDIFrameWndEx)

main_frame_view::main_frame_view(const m::wcommand_manager::ptr& command_manager, const m::wevent_manager::ptr& event_manager, const fleet_repository::ptr& fleet_repo)
    : CMDIFrameWndEx()
    , m::data_context_interface<main_frame_view_model::ptr>()
    , _wndMenuBar()
    , _wndToolBar()
    , _wndStatusBar()
    , _fleet_organization_view()
    , _output_view()
    , _properties_view()
    , _command_manager(command_manager)
    , _event_manager(event_manager)
    , _fleet_repository(fleet_repo)
    , _fleet_org_child_view()
{
}

void main_frame_view::on_show_spaceship(const fleet_organization_id_type id)
{
    fleet_organization_child_frame_view_type::iterator it = _fleet_org_child_view.find(id);
    if(it != _fleet_org_child_view.end())
    {
        it->second->MDIActivate();
    }
    else
    {
        fleet_repository::ptr fleet_repo = _fleet_repository.lock();
        if(fleet_repo)
        {
            fleet_organization_interface::ptr fleet_org = fleet_repo->fleet_organization_model(id);
            if(fleet_org && fleet_org->spaceship_model())
            {
                spaceship_view_model::ptr spaceship_vm = spaceship_view_model::create(std::dynamic_pointer_cast<spaceship_model>(fleet_org->spaceship_model()), id, data_context());
                LockWindowUpdate();
                const u::scope_guard unlock(std::bind(&main_frame_view::UnlockWindowUpdate, this));
                child_frame_view* newChild = dynamic_cast<child_frame_view*>(CreateNewChild(RUNTIME_CLASS(child_frame_view), IDR_MVVM_MFC_EXAMPLE_3TYPE, theApp.mdiMenu(), theApp.mdiAccel()));
                _fleet_org_child_view[id] = newChild;
                newChild->spaceship_view_model(spaceship_vm);
                newChild->initialization_complete();
            }
        }
    }
}

void main_frame_view::on_close_spaceship(const fleet_organization_id_type id)
{
    fleet_organization_child_frame_view_type::iterator it = _fleet_org_child_view.find(id);
    if(it != _fleet_org_child_view.end())
    {
        _fleet_org_child_view.erase(it);
    }
}

BOOL main_frame_view::PreCreateWindow(CREATESTRUCT& cs)
{
    if(!CMDIFrameWndEx::PreCreateWindow(cs))
        return FALSE;

    cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
        | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

    return TRUE;
}

#ifdef _DEBUG
void main_frame_view::AssertValid() const
{
    CMDIFrameWndEx::AssertValid();
}

void main_frame_view::Dump(CDumpContext& dc) const
{
    CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG

int main_frame_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;
	mdiTabParams.m_bActiveTabCloseButton = TRUE;
	mdiTabParams.m_bTabIcons = FALSE;
	mdiTabParams.m_bAutoColor = TRUE;
	mdiTabParams.m_bDocumentMenu = TRUE;
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;
	}

	_wndMenuBar.SetPaneStyle(_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!_wndToolBar.LoadToolBar(theApp._bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&_wndMenuBar);
	DockPane(&_wndToolBar);

	CDockingManager::SetDockingMode(DT_SMART);
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp._bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	_fleet_organization_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&_fleet_organization_view);
	CDockablePane* pTabbedBar = NULL;
	_output_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&_output_view);
	_properties_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&_properties_view);

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	CMFCToolBar::EnableQuickCustomization();

	ModifyStyle(0, FWS_PREFIXTITLE);

    initialize();

	return 0;
}

void main_frame_view::OnWindowManager()
{
	ShowWindowsDialog();
}

void main_frame_view::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->Create();
}

LRESULT main_frame_view::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void main_frame_view::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	_output_view.UpdateFonts();
}

void main_frame_view::OnUpdateControlBarMenu(CCmdUI* pCmdUI)
{
    CMDIFrameWndEx::OnUpdateControlBarMenu(pCmdUI);
    if(pCmdUI == NULL) { return; }
    switch(pCmdUI->m_nID)
    {
    case ID_FILE_NEW:
    case ID_FILE_OPEN:
        pCmdUI->Enable(FALSE);
        break;
    default:
        break;
    }
}

BEGIN_MESSAGE_MAP(main_frame_view, CMDIFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND(ID_WINDOW_MANAGER, &main_frame_view::OnWindowManager)
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &main_frame_view::OnViewCustomize)
    ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &main_frame_view::OnToolbarCreateNew)
    ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

BOOL main_frame_view::CreateDockingWindows()
{
    BOOL bNameValid;

    CString strFileView;
    bNameValid = strFileView.LoadString(IDS_FLEET_ORGANIZATION);
    ASSERT(bNameValid);
    if(!_fleet_organization_view.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
    {
        TRACE0("Failed to create File View window\n");
        return FALSE;
    }

    CString strOutputWnd;
    bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
    ASSERT(bNameValid);
    if(!_output_view.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
    {
        TRACE0("Failed to create Output window\n");
        return FALSE;
    }

    m::wcommand_manager::ptr command_manager = _command_manager.lock();
    if(command_manager)
    {
        command_manager->command_executed.connect(std::bind(&output_view::on_command_executed, &_output_view, ph::_1));
        command_manager->command_not_executed.connect(std::bind(&output_view::on_command_not_executed, &_output_view, ph::_1));
    }

    m::wevent_manager::ptr event_manager = _event_manager.lock();
    if(event_manager)
    {
        event_manager->event_fired.connect(std::bind(&output_view::on_event_fired, &_output_view, ph::_1));
    }

    CString strPropertiesWnd;
    bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
    ASSERT(bNameValid);
    if(!_properties_view.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
    {
        TRACE0("Failed to create Properties window\n");
        return FALSE;
    }

    SetDockingWindowIcons(theApp._bHiColorIcons);
    return TRUE;
}

void main_frame_view::SetDockingWindowIcons(BOOL bHiColorIcons)
{
    HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FLEET_ORGANIZATION_HC : IDI_FLEET_ORGANIZATION), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    _fleet_organization_view.SetIcon(hFileViewIcon, FALSE);

    HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    _output_view.SetIcon(hOutputBarIcon, FALSE);

    HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    _properties_view.SetIcon(hPropertiesBarIcon, FALSE);

    UpdateMDITabbedBarsIcons();
}

void main_frame_view::initialize()
{
    m::wcommand_manager::ptr command_manager = _command_manager.lock();
    m::wevent_manager::ptr event_manager = _event_manager.lock();
    fleet_repository::ptr fleet_repo = _fleet_repository.lock();
    if(command_manager && event_manager && fleet_repo)
    {
        fleet_repository_populator::ptr populator = fleet_repository_populator::create();
        if(populator)
        {
            populator->populate(fleet_repo, &_output_view);

            data_context = main_frame_view_model::create(this, command_manager, event_manager, fleet_repo);
            data_context()->property_changed.connect(std::bind(&output_view::on_property_changed, &_output_view, ph::_1, ph::_2));

            fleet_organization_view_model::ptr fleet_org_vm = fleet_organization_view_model::create();
            fleet_org_vm->property_changed.connect(std::bind(&output_view::on_property_changed, &_output_view, ph::_1, ph::_2));
            fleet_org_vm->view_model_will_change.connect(std::bind(&fleet_organization_view::on_view_model_will_change, &_fleet_organization_view, ph::_1));
            fleet_org_vm->view_model_changed.connect(std::bind(&fleet_organization_view::on_view_model_changed, &_fleet_organization_view, ph::_1));

            properties_view_model::ptr prop_vm = properties_view_model::create();
            prop_vm->property_changed.connect(std::bind(&output_view::on_property_changed, &_output_view, ph::_1, ph::_2));
            prop_vm->view_model_will_change.connect(std::bind(&properties_view::on_view_model_will_change, &_properties_view, ph::_1));
            prop_vm->view_model_changed.connect(std::bind(&properties_view::on_view_model_changed, &_properties_view, ph::_1));
            prop_vm->main_frame_vm = data_context();
            _properties_view.data_context = prop_vm;

            fleet_org_vm->main_frame_vm = data_context();
            _fleet_organization_view.data_context = fleet_org_vm;
            fleet_org_vm->set_data_context(std::dynamic_pointer_cast<fleet_organization_model>(fleet_repo->fleet_organization_model()));
        }
    }
}
