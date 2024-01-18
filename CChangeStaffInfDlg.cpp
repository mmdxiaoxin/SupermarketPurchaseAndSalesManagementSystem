// CChangeStaffInfDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CChangeStaffInfDlg.h"
#include "MainFrm.h"
#include "CInfoFile.h"


// CChangeStaffInfDlg

IMPLEMENT_DYNCREATE(CChangeStaffInfDlg, CFormView)

CChangeStaffInfDlg::CChangeStaffInfDlg()
	: CFormView(DIALOG_CHANGE_STAFF)
	, m_staff_id(0)
	, m_staff_name2(_T(""))
	, m_staff_pwd(_T(""))
	, m_staff_pwd2(_T(""))
	, m_staff_user1(_T(""))
	, m_staff_user2(_T(""))
	, m_staff_jurisidiction(_T(""))
{

}

CChangeStaffInfDlg::~CChangeStaffInfDlg()
{
}

void CChangeStaffInfDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STAFF_ID, m_staff_id);
	//  DDX_Text(pDX, IDC_EDIT_STAFF_NAME, m_staff_name1);
	DDX_Text(pDX, IDC_EDIT_STAFF_NAME2, m_staff_name2);
	DDX_Text(pDX, IDC_EDIT_STAFF_PWD, m_staff_pwd);
	DDX_Text(pDX, IDC_EDIT_STAFF_PWD2, m_staff_pwd2);
	DDX_Text(pDX, IDC_EDIT_STAFF_USER, m_staff_user1);
	DDX_Text(pDX, IDC_EDIT_STAFF_USER2, m_staff_user2);
	DDX_Control(pDX, IDC_COMBO_STAFF_NAME, m_combo_name);
	DDX_Control(pDX, IDC_COMBO_JURISIDICTION2, m_combo_jurisidiction2);
	DDX_Text(pDX, IDC_EDIT_STAFF_JURISIDICTION, m_staff_jurisidiction);
}

BEGIN_MESSAGE_MAP(CChangeStaffInfDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CChangeStaffInfDlg::OnBnClickedButtonCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_STAFF_NAME, &CChangeStaffInfDlg::OnCbnSelchangeComboStaffName)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeStaffInfDlg::OnBnClickedButtonChange)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChangeStaffInfDlg 诊断

#ifdef _DEBUG
void CChangeStaffInfDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChangeStaffInfDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChangeStaffInfDlg 消息处理程序


void CChangeStaffInfDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin();
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++) 
	{
		m_combo_name.AddString((CString)it->name.c_str());
	}
	m_combo_name.SetCurSel(0);
	if (!file.st.empty())
	{
		m_staff_jurisidiction = (CString)file.st.front().jurisdiction.c_str();
		m_staff_user1 = (CString)file.st.front().user.c_str();
		m_staff_user2 = (CString)file.st.front().user.c_str();
		m_staff_name2 = (CString)file.st.front().name.c_str();
		m_staff_pwd = (CString)file.st.front().pwd.c_str();
		m_staff_id = file.st.front().id;
	}
	m_combo_jurisidiction2.AddString(_T("仓库管理员"));
	m_combo_jurisidiction2.AddString(_T("销售员"));
	m_combo_jurisidiction2.SetCurSel(0);
	UpdateData(FALSE);//将内容更新到控件
}


void CChangeStaffInfDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CChangeStaffInfDlg::OnCbnSelchangeComboStaffName()
{
	// TODO: 在此添加控件通知处理程序代码

	CString name;
	//获取当前选中项
	int index = m_combo_name.GetCurSel();
	//获取当前内容
	m_combo_name.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin(); //读取职工信息
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (name == it->name.c_str())
		{
			m_staff_jurisidiction = (CString)it->jurisdiction.c_str();
			m_staff_user1 = (CString)it->user.c_str();
			m_staff_user2 = (CString)it->user.c_str();
			m_staff_name2 = (CString)it->name.c_str();
			m_staff_pwd = (CString)it->pwd.c_str();
			m_staff_id = it->id;
		}
	}
	UpdateData(FALSE); //内容更新到对应的控件
}


void CChangeStaffInfDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);//更新控件内容到对应的变量中
	if (m_staff_name2.IsEmpty() || m_staff_pwd2.IsEmpty() || m_staff_user2.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}
	CString jurisidiction, name;
	//获取当前选中项
	int index1 = m_combo_jurisidiction2.GetCurSel(), index2 = m_combo_name.GetCurSel();
	//获取当前内容
	m_combo_jurisidiction2.GetLBText(index1, jurisidiction);
	m_combo_name.GetLBText(index2, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin(); //读取职工信息
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (name == it->name.c_str())
		{
			char* tmpName, * tmpPwd, * tmpJurisdiction, * tmpUser;
			CStringA tmp1, tmp2, tmp3, tmp4;
			tmp1 = m_staff_name2; tmpName = tmp1.GetBuffer();
			tmp2 = m_staff_pwd2; tmpPwd = tmp2.GetBuffer();
			tmp3 = jurisidiction; tmpJurisdiction = tmp3.GetBuffer();
			tmp4 = m_staff_user2; tmpUser = tmp4.GetBuffer();
			it->jurisdiction = tmpJurisdiction;
			it->name = tmpName;
			it->user = tmpUser;
			it->pwd = tmpPwd;
			MessageBox(TEXT("修改成功！"));
		}
	}
	file.WirteLogin();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_L, (WPARAM)NM_L, (LPARAM)0);//初始化
}


void CChangeStaffInfDlg::OnPaint()
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
