
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"

#include "MainFrm.h"
#include "CSelectView.h"
#include "CDispalyView.h"
#include "CUserDlg.h"
#include "CTabCtrlDlg.h"
#include "CSellDlg.h"
#include "CInfoDlg.h"
#include "CDelDlg.h"
#include "CAdd_Dlg.h"
#include "CTab_IO_Dlg.h"
#include "CTab_FIRM_Dlg.h"
#include "CProductInfoDlg.h"
#include "CWarnStockDlg.h"
#include "CAdd_StaffDlg.h"
#include "CChangeSafetyDlg.h"
#include "CChangeStaffInfDlg.h"
#include "CAdd_FirmDlg.h"
#include "CUserStaffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	//ON_MESSAGE响应的是自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)//
	ON_MESSAGE(NM_B, OnMyChange)//
	ON_MESSAGE(NM_C, OnMyChange)//
	ON_MESSAGE(NM_D, OnMyChange)//
	ON_MESSAGE(NM_E, OnMyChange)//
	ON_MESSAGE(NM_F, OnMyChange)//
	ON_MESSAGE(NM_G, OnMyChange)//
	ON_MESSAGE(NM_H, OnMyChange)//
	ON_MESSAGE(NM_I, OnMyChange)//
	ON_MESSAGE(NM_J, OnMyChange)//
	ON_MESSAGE(NM_K, OnMyChange)//
	ON_MESSAGE(NM_L, OnMyChange)//修改员工信息
	ON_MESSAGE(NM_M, OnMyChange)//添加供应商信息
	ON_MESSAGE(NM_N, OnMyChange)//职工信息窗口
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32776, &CMainFrame::On32776)
	ON_COMMAND(ID_32777, &CMainFrame::On32777)
	ON_COMMAND(ID_32771, &CMainFrame::On32771)
ON_COMMAND(ID_32779, &CMainFrame::On32779)
ON_COMMAND(ID_32778, &CMainFrame::On32778)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_WIN);
	SetIcon(m_hIcon, TRUE);

	//设置窗口的位置和大小：CWnd::MoveWindow
	//0, 0, 起点坐标x和y
	//1300, 680, 窗口宽度和高度
	MoveWindow(0, 0, 1300, 680);

	//将窗口移动到屏幕中央，CWnd::CenterWindow
	CenterWindow();

	//设置窗口右侧标题，CDocument::SetTitle

	//实现对今日时间的显示
	CString str;
	CTime tm;
	tm = CTime::GetCurrentTime();//获取系统日期  
	str = tm.Format("现在时间是%Y年%m月%d日");
	SetTitle(str);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWnd::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//拆成一行两列
	m_splitter.CreateStatic(this, 1, 2);
	//左侧和右侧具体的显示内容
	//0 行 0 列
	//250, 800设置窗体大小
	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(250, 800), pContext);
	//0 行 1 列
	//600, 800设置窗体大小
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDispalyView), CSize(600, 800), pContext);
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE; //自己拆分
}

CCreateContext   Context;
LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_A:
	{
		//个人信息
		//需要包含头文件#include "CUserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
		CUserDlg* pNewView = (CUserDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_B:
	{
		//销售管理
		//需要包含头文件#include "CSellDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 0), &Context);
		CSellDlg* pNewView = (CSellDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_C:
	{
		//库存信息
		//需要包含头文件#include "CInfoDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 0), &Context);
		CInfoDlg* pNewView = (CInfoDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_D:
	{
		//库存添加
		//需要包含头文件#include "CAdd_Dlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdd_Dlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdd_Dlg), CSize(600, 0), &Context);
		CAdd_Dlg* pNewView = (CAdd_Dlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_E:
	{
		//库存删除
		//需要包含头文件#include "CDelDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDelDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDelDlg), CSize(600, 0), &Context);
		CDelDlg* pNewView = (CDelDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_F:
	{
		//进销记录
		//需要包含头文件#include "CTab_IO_Dlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CTab_IO_Dlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTab_IO_Dlg), CSize(600, 0), &Context);
		CTab_IO_Dlg* pNewView = (CTab_IO_Dlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_G:
	{
		//供应商管理
		//需要包含头文件#include "CTab_FIRM_Dlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CTab_FIRM_Dlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTab_FIRM_Dlg), CSize(600, 0), &Context);
		CTab_FIRM_Dlg* pNewView = (CTab_FIRM_Dlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_H:
	{
		//商品信息
		//需要包含头文件#include "CProductInfoDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CProductInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CProductInfoDlg), CSize(600, 0), &Context);
		CProductInfoDlg* pNewView = (CProductInfoDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_I:
	{
		//库存阈值警告设置
		//需要包含头文件#include "CWarnStockDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CWarnStockDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CWarnStockDlg), CSize(600, 0), &Context);
		CWarnStockDlg* pNewView = (CWarnStockDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_J:
	{
		//CAdd_StaffDlg视窗类中添加员工功能
		//需要包含头文件#include "CAdd_StaffDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdd_StaffDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdd_StaffDlg), CSize(600, 0), &Context);
		CAdd_StaffDlg* pNewView = (CAdd_StaffDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_K:
	{
		//CUserDlg视窗类中的设置安全问题窗口的窗口类CChangeSafetyDlg
		//需要包含头文件#include "CChangeSafetyDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CChangeSafetyDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CChangeSafetyDlg), CSize(600, 0), &Context);
		CChangeSafetyDlg* pNewView = (CChangeSafetyDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_L:
	{
		//CUserDlg视窗类中的更改职工信息窗口的窗口类CChangeStaffInfDlg
		//需要包含头文件#include "CChangeStaffInfDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CChangeStaffInfDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CChangeStaffInfDlg), CSize(600, 0), &Context);
		CChangeStaffInfDlg* pNewView = (CChangeStaffInfDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_M:
	{
		//CFirmAdminDlg视窗类中的添加供应商窗口的窗口类CAdd_FirmDlg
		//需要包含头文件#include "CAdd_FirmDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdd_FirmDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdd_FirmDlg), CSize(600, 0), &Context);
		CAdd_FirmDlg* pNewView = (CAdd_FirmDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_N:
	{
		//职工个人信息窗口类CUserStaffDlg
		//需要包含头文件#include "CUserStaffDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserStaffDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CUserStaffDlg), CSize(600, 0), &Context);
		CUserStaffDlg* pNewView = (CUserStaffDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	default:
		MessageBox(_T("error"));
	}
	return 0;
}

void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}

void CMainFrame::On32772()
{
	// TODO: 在此添加命令处理程序代码
	//个人信息
	if (CPublic::GetJurisdiction() == "主管")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	else
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_N, (WPARAM)NM_N, (LPARAM)0);
}

void CMainFrame::On32773()
{
	// TODO: 在此添加命令处理程序代码
	//销售管理
	if (CPublic::GetJurisdiction() != "仓库管理员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}

void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	//库存信息
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}

void CMainFrame::On32775()
{
	// TODO: 在此添加命令处理程序代码
	//库存添加
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}

void CMainFrame::On32776()
{
	// TODO: 在此添加命令处理程序代码
	//库存删除
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}

void CMainFrame::On32777()
{
	// TODO: 在此添加命令处理程序代码
	//进销记录
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_F, (WPARAM)NM_F, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}

void CMainFrame::On32779()
{
	// TODO: 在此添加命令处理程序代码
	//供应商管理
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}


void CMainFrame::On32778()
{
	// TODO: 在此添加命令处理程序代码
	//库存阈值警告设置
	//暂时不做
	MessageBox(_T("抱歉！暂未实现该功能。"));
	return;
	if (CPublic::GetJurisdiction() != "销售员")
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_I, (WPARAM)NM_I, (LPARAM)0);
	else
		MessageBox(_T("您没有权限！"));
}
