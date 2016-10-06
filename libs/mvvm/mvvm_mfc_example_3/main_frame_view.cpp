//
//  main_frame_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "main_frame_view.h"
#include "fleet_repository_populator.hpp"
#include "mvvm_mfc_example_3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace ph = std::placeholders;

IMPLEMENT_DYNAMIC(main_frame_view, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(main_frame_view, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &main_frame_view::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &main_frame_view::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &main_frame_view::OnToolbarCreateNew)
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

main_frame_view::~main_frame_view()
{
}

main_frame_view::main_frame_view(const m::wcommand_manager::ptr& command_manager, const fleet_repository::ptr& fleet_repo)
    : CMDIFrameWndEx()
    , m_wndMenuBar()
    , m_wndToolBar()
    , m_wndStatusBar()
    , m_fleet_organization_view(command_manager)
    , m_output_view()
    , m_properties_view()
    , m_command_manager(command_manager)
    , m_fleet_repository(fleet_repo)
    , m_main_frame_view_model()
{
}

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

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	CDockingManager::SetDockingMode(DT_SMART);
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_fleet_organization_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_fleet_organization_view);
	CDockablePane* pTabbedBar = NULL;
	m_output_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_output_view);
	m_properties_view.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_properties_view);

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	CMFCToolBar::EnableQuickCustomization();

	ModifyStyle(0, FWS_PREFIXTITLE);

    fleet_repository::ptr fleet_repo = m_fleet_repository.lock();
    if(fleet_repo)
    {
        fleet_repository_populator::ptr populator = fleet_repository_populator::create();
        if(populator)
        {
            populator->populate(fleet_repo, &m_output_view);
            fleet_organization_view_model::ptr fleet_org_view_model = fleet_organization_view_model::create();
            properties_view_model::ptr prop_view_model = properties_view_model::create(fleet_repo);
            m_main_frame_view_model = main_frame_view_model::create(fleet_repo, prop_view_model);
            fleet_org_view_model->property_changed.connect(std::bind(&output_view::on_property_changed, &m_output_view, ph::_1, ph::_2));
            fleet_org_view_model->property_changed.connect(std::bind(&main_frame_view_model::on_property_changed, m_main_frame_view_model, ph::_1, ph::_2));
            m_fleet_organization_view.view_model(fleet_org_view_model);
            m_properties_view.view_model(prop_view_model);
            fleet_org_view_model->data_context.set(std::dynamic_pointer_cast<fleet_organization_model>(fleet_repo->fleet_organization_model()));
        }
    }

	return 0;
}

BOOL main_frame_view::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

BOOL main_frame_view::CreateDockingWindows()
{
	BOOL bNameValid;

	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FLEET_ORGANIZATION);
	ASSERT(bNameValid);
	if (!m_fleet_organization_view.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE;
	}

	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_output_view.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE;
	}

    m::wcommand_manager::ptr command_manager = m_command_manager.lock();
    if (command_manager)
    {
        command_manager->command_executed.connect(std::bind(&output_view::on_command_executed, &m_output_view, ph::_1));
        command_manager->command_not_executed.connect(std::bind(&output_view::on_command_not_executed, &m_output_view, ph::_1));
    }

	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_properties_view.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE;
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void main_frame_view::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FLEET_ORGANIZATION_HC : IDI_FLEET_ORGANIZATION), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_fleet_organization_view.SetIcon(hFileViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_output_view.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_properties_view.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
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
	m_output_view.UpdateFonts();
}
