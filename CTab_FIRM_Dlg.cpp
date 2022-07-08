// CTab_FIRM_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CTab_FIRM_Dlg.h"


// CTab_FIRM_Dlg

IMPLEMENT_DYNCREATE(CTab_FIRM_Dlg, CFormView)

CTab_FIRM_Dlg::CTab_FIRM_Dlg()
	: CFormView(DIALOG_FIRM_TAB)
{

}

CTab_FIRM_Dlg::~CTab_FIRM_Dlg()
{
}

void CTab_FIRM_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCTRL, m_tab);
}

BEGIN_MESSAGE_MAP(CTab_FIRM_Dlg, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, &CTab_FIRM_Dlg::OnTcnSelchangeTabctrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTab_FIRM_Dlg 诊断

#ifdef _DEBUG
void CTab_FIRM_Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTab_FIRM_Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTab_FIRM_Dlg 消息处理程序


void CTab_FIRM_Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//为Tab Control增加两个页面，看自己的需求也可以增加更多 
	m_tab.InsertItem(0, _T("供应商管理"));
	m_tab.InsertItem(1, _T("供应商信息"));
	//创建两个对话框  
	m_page1.Create(DIALOG_FIRM_ADMIN, &m_tab);
	m_page2.Create(DIALOG_FIRM_INF, &m_tab);
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


void CTab_FIRM_Dlg::OnTcnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult)
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


void CTab_FIRM_Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFormView::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_SELL_BACKGROUND);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}
