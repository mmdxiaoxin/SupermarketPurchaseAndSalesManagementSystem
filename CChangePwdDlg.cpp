// CChangePwdDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CChangePwdDlg.h"
#include "CInfoFile.h"

// CChangePwdDlg 对话框

IMPLEMENT_DYNAMIC(CChangePwdDlg, CDialogEx)

CChangePwdDlg::CChangePwdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_CHANGE_PWD, pParent)
	, m_OldPwd(_T(""))
	, m_NewPwd(_T(""))
	, m_RNewPwd(_T(""))
{

}

CChangePwdDlg::~CChangePwdDlg()
{
}

void CChangePwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_OldPwd);
	DDX_Text(pDX, IDC_EDIT2, m_NewPwd);
	DDX_Text(pDX, IDC_EDIT6, m_RNewPwd);
}


BEGIN_MESSAGE_MAP(CChangePwdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CChangePwdDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CChangePwdDlg::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChangePwdDlg 消息处理程序


void CChangePwdDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CChangePwdDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);//更新控件内容到对应的变量中

	if (m_NewPwd.IsEmpty() || m_OldPwd.IsEmpty() || m_RNewPwd.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}
	if (m_RNewPwd != m_NewPwd)
	{
		MessageBox(TEXT("输入新密码和确定密码不相等！"));
		return;
	}
	if (CPublic::GetJurisdiction() == "主管")
	{
		CInfoFile file;	//需要头文件#include "CInfoFile.h"
		CString name, pwd;
		file.ReadLogin(name, pwd); //读取文件的用户名和密码

		

		if (m_OldPwd != pwd)
		{
			MessageBox(TEXT("原密码错误！"));
			return;
		}
		

		if (m_NewPwd == pwd)
		{
			MessageBox(TEXT("输入密码和旧密码相等！"));
			return;
		}

		//把用户名和密码的CString类型转为char *
		char* tmpName, * tmpPwd;
		//用户名
		CStringA tmp1;
		tmp1 = name;
		tmpName = tmp1.GetBuffer();
		//密码
		CStringA tmp2;
		tmp2 = m_OldPwd;
		tmpPwd = tmp2.GetBuffer();

		file.WirtePwd(tmpName, tmpPwd); //修改密码
	}
	else
	{
		CInfoFile file;
		file.ReadLogin();
		for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
		{
			if (it->name == CPublic::GetStaffName())
			{
				if (m_OldPwd != it->pwd.c_str())
				{
					MessageBox(TEXT("原密码错误！"));
					return;
				}
				if (m_NewPwd == it->pwd.c_str())
				{
					MessageBox(TEXT("输入密码和旧密码相等！"));
					return;
				}
				char* tmpPwd;
				CStringA tmp;
				tmp = m_NewPwd;
				tmpPwd = tmp.GetBuffer();
				it->pwd = tmpPwd;
			}
		}
		file.WirteLogin();
	}
	MessageBox(TEXT("密码修改成功"));
	OnCancel();
	
}


void CChangePwdDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_REGISTER);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
		0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}


void CChangePwdDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
