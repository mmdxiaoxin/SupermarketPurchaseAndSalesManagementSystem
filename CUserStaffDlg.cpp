// CUserStaffDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CUserStaffDlg.h"
#include "CChangePwdDlg.h"


// CUserStaffDlg

IMPLEMENT_DYNCREATE(CUserStaffDlg, CFormView)

CUserStaffDlg::CUserStaffDlg()
	: CFormView(DIALOG_USER_STAFF)
	, m_id(0)
	, m_jurisidiction(_T(""))
	, m_name(_T(""))
	, m_user(_T(""))
{

}

CUserStaffDlg::~CUserStaffDlg()
{
}

void CUserStaffDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_JURISDICTION, m_jurisidiction);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
}

BEGIN_MESSAGE_MAP(CUserStaffDlg, CFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CUserStaffDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserStaffDlg 诊断

#ifdef _DEBUG
void CUserStaffDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserStaffDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserStaffDlg 消息处理程序


void CUserStaffDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_name = CPublic::GetStaffName().c_str();
	m_user = CPublic::GetStaffUser().c_str();
	m_id = CPublic::GetStaffId();
	m_jurisidiction = CPublic::GetJurisdiction().c_str();

	UpdateData(FALSE);//更新内容到控件
}


void CUserStaffDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFormView::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_USER);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}


void CUserStaffDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangePwdDlg dlg;
	dlg.DoModal();
}
