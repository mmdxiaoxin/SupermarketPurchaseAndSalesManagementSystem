// CAdd_StaffDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CAdd_StaffDlg.h"
#include "MainFrm.h"
#include "CInfoFile.h"

// CAdd_StaffDlg

IMPLEMENT_DYNCREATE(CAdd_StaffDlg, CFormView)

CAdd_StaffDlg::CAdd_StaffDlg()
	: CFormView(DIALOG_ADD_STAFF)
	, m_staff_name(_T(""))
	, m_staff_pwd(_T(""))
	, m_staff_user(_T(""))
{

}

CAdd_StaffDlg::~CAdd_StaffDlg()
{
}

void CAdd_StaffDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_STAFF_ID, m_staff_id);
	DDX_Text(pDX, IDC_EDIT_STAFF_NAME, m_staff_name);
	DDX_Text(pDX, IDC_EDIT_STAFF_PWD, m_staff_pwd);
	DDX_Text(pDX, IDC_EDIT_STAFF_USER, m_staff_user);
	DDX_Control(pDX, IDC_COMBO_JURISIDICTION, m_combo_jurisidiction);
}

BEGIN_MESSAGE_MAP(CAdd_StaffDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON5, &CAdd_StaffDlg::OnBnClickedButton5)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON4, &CAdd_StaffDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAdd_StaffDlg 诊断

#ifdef _DEBUG
void CAdd_StaffDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdd_StaffDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdd_StaffDlg 消息处理程序


void CAdd_StaffDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CAdd_StaffDlg::OnPaint()
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


void CAdd_StaffDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新内容到变量
	UpdateData(TRUE);
	CString jurisidiction;
	//获取当前选中项
	int index = m_combo_jurisidiction.GetCurSel();
	//获取组合框当前内容
	m_combo_jurisidiction.GetLBText(index, jurisidiction);
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin();
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++) 
	{
		if (m_staff_user == it->user.c_str())
		{
			MessageBox(_T("用户名重复！"));
			return;
		}
	}
	file.Addline(m_staff_user, m_staff_pwd, m_staff_name, jurisidiction);
	file.WirteLogin();

	MessageBox(_T("添加成功"));
	//初始化
	m_staff_user.Empty();
	m_staff_pwd.Empty();
	m_staff_name.Empty();

	UpdateData(FALSE);//更新内容回控件
}


void CAdd_StaffDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置下拉框
	m_combo_jurisidiction.AddString(TEXT("销售员"));
	m_combo_jurisidiction.AddString(TEXT("仓库管理员"));

	//将第一个权限名设为默认选中项
	m_combo_jurisidiction.SetCurSel(0);
}
