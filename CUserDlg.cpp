// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CUserDlg.h"
#include "CInfoFile.h"
#include "MainFrm.h"
#include "CRegisterDlg.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_staff_id(0)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT3, m_name);
	//  DDX_Control(pDX, IDC_BUTTON2, m_group);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_group);
	DDX_Control(pDX, IDC_STATIC_GROUP3, m_group3);
	DDX_Control(pDX, IDC_COMBO_STAFF, m_combo_staff);
	DDX_Text(pDX, IDC_EDIT_STAFF_ID, m_staff_id);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUserDlg::OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO_STAFF, &CUserDlg::OnCbnSelchangeComboStaff)
	ON_BN_CLICKED(IDC_BUTTON_FIND_STAFF, &CUserDlg::OnBnClickedButtonFindStaff)
	ON_BN_CLICKED(IDC_BUTTON_DEL_STAFF, &CUserDlg::OnBnClickedButtonDelStaff)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_STAFF, &CUserDlg::OnBnClickedButtonChangeStaff)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_LOGIN, &CUserDlg::OnBnClickedButtonChangeLogin)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置GroupBox字体大小
	m_font.CreatePointFont(150, _T("宋体"));  //字体和大小根据自己的需要自行改变
	m_group.SetFont(&m_font);             //将字体和想要改变的框体变量进行关联
	m_group3.SetFont(&m_font);
	
	CInfoFile file;	//需要头文件#include "CInfoFile.h"
	CString name, pwd;
	file.ReadLogin(name, pwd); //读取主管文件的用户名和密码
	file.ReadLogin();//读取职工文件的用户名和密码

	//初始化个人信息
	m_user = TEXT("主管");	//身份
	m_name = name;	//用户名
	//初始化职工信息
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++) 
	{
		m_combo_staff.AddString((CString)it->name.c_str());//初始化职员名称
	}
	//将第一个职员名称设为默认选中项
	m_combo_staff.SetCurSel(0);
	if (!file.st.empty())
	{
		m_staff_id = file.st.front().id;
	}
	else
	{
		m_staff_id = 0;
	}
	file.st.clear(); //清空list的内容
	UpdateData(FALSE); //把数据更新到控件上
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	dlg.DoModal();//以模态方式运行
}


void CUserDlg::OnPaint()
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


void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加员工
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_J, (WPARAM)NM_J, (LPARAM)0);
}


void CUserDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置安全问题
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_K, (WPARAM)NM_K, (LPARAM)0);
}


void CUserDlg::OnCbnSelchangeComboStaff()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	//获取当前选中项
	int index = m_combo_staff.GetCurSel();
	//获取当前内容
	m_combo_staff.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin(); //读取职工信息
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_staff_id = it->id;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}

	file.st.clear(); //清空list的内容
}


void CUserDlg::OnBnClickedButtonFindStaff()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	CString name;
	//获取当前选中项
	int index = m_combo_staff.GetCurSel();
	//获取组合框当前内容
	m_combo_staff.GetLBText(index, name);
	CInfoFile file;
	file.ReadLogin();
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (name == it->name.c_str())
		{
			CString str;
			str.Format(_T("姓名：%s \r\nID：%d \r\n权限：%s\r\n用户名：%s\r\n密码：%s"), 
				(CString)it->name.c_str(),
				it->id,
				(CString)it->jurisdiction.c_str(),
				(CString)it->user.c_str(),
				(CString)it->pwd.c_str());
			MessageBox(str);
		}
	}
}


void CUserDlg::OnBnClickedButtonDelStaff()
{
	// TODO: 在此添加控件通知处理程序代码

	CString name;
	//获取当前选中项
	int index = m_combo_staff.GetCurSel();
	//获取当前内容
	m_combo_staff.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadLogin(); //读取职工信息

	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (name == it->name.c_str())
		{
			file.st.erase(it);
			MessageBox(_T("删除成功"));
			if (file.st.empty())
			{
				file.WirteLogin();//写入职工信息
				//需要包含#include "CMainFrame.h"
				::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);//初始化窗口
				return;
			}
			//重新对职工ID编号
			int i = 0;
			for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
			{
				it->id = ++i;
			}
			file.WirteLogin();//写入职工信息
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);//初始化窗口
			break;
		}
	}
}


void CUserDlg::OnBnClickedButtonChangeStaff()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_L, (WPARAM)NM_L, (LPARAM)0);
}


void CUserDlg::OnBnClickedButtonChangeLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CRegisterDlg.h"
	CRegisterDlg dlg;
	dlg.DoModal();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);//初始化个人信息窗口
}
