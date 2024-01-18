// CTab_IO_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CTab_IO_Dlg.h"


// CTab_IO_Dlg

IMPLEMENT_DYNCREATE(CTab_IO_Dlg, CFormView)

CTab_IO_Dlg::CTab_IO_Dlg()
	: CFormView(DIALOG_IO_TAB)
{

}

CTab_IO_Dlg::~CTab_IO_Dlg()
{
}

void CTab_IO_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCTRL, m_tab);
}

BEGIN_MESSAGE_MAP(CTab_IO_Dlg, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, &CTab_IO_Dlg::OnTcnSelchangeTabctrl)
END_MESSAGE_MAP()


// CTab_IO_Dlg 诊断

#ifdef _DEBUG
void CTab_IO_Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTab_IO_Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTab_IO_Dlg 消息处理程序


void CTab_IO_Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	//为Tab Control增加两个页面，看自己的需求也可以增加更多 
	m_tab.InsertItem(0, _T("购入记录"));
	m_tab.InsertItem(1, _T("出售记录"));
	//创建两个对话框  
	m_page1.Create(DIALOG_INPUT, &m_tab);
	m_page2.Create(DIALOG_OUTPUT, &m_tab);
	//设定在Tab内显示的范围  
	CRect tabRect;
	m_tab.GetClientRect(tabRect);
	//调整子对话框在父窗口中的位置 
	tabRect.left += 10;
	tabRect.right -= 10;
	tabRect.top += 30;
	tabRect.bottom -= 10;
	//设置子对话框尺寸并移动到指定位置 
	m_page1.MoveWindow(&tabRect);
	m_page2.MoveWindow(&tabRect);

	//显示初始页面  
	m_page1.ShowWindow(TRUE);
	m_page2.ShowWindow(FALSE);
	//设置默认标签页
	m_tab.SetCurSel(0);

}


void CTab_IO_Dlg::OnTcnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_page1.ShowWindow(TRUE);
		m_page2.ShowWindow(FALSE);
		break;
	case 1:
		m_page1.ShowWindow(FALSE);
		m_page2.ShowWindow(TRUE);
		break;
	default:break;
	}
}
