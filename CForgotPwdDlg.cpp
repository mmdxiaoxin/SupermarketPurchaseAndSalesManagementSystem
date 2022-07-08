// CForgotPwdDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CForgotPwdDlg.h"
#include "CInfoFile.h"
#include "CLoginDlg.h"

// CForgotPwdDlg 对话框

IMPLEMENT_DYNAMIC(CForgotPwdDlg, CDialogEx)

CForgotPwdDlg::CForgotPwdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_FORGOT_PWD, pParent)
	, m_pwd(_T(""))
	, m_Rpwd(_T(""))
{

}

CForgotPwdDlg::~CForgotPwdDlg()
{
}

void CForgotPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWPWD, m_pwd);
	DDX_Text(pDX, IDC_EDIT_RNEWPWD, m_Rpwd);
}


BEGIN_MESSAGE_MAP(CForgotPwdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CForgotPwdDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CForgotPwdDlg::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CForgotPwdDlg 消息处理程序


void CForgotPwdDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CForgotPwdDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CForgotPwdDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoFile file;	//需要头文件#include "CInfoFile.h"
	CString name, pwd;
	file.ReadLogin(name, pwd); //读取文件的用户名和密码

	UpdateData(TRUE);//更新控件内容到对应的变量中

	if (m_pwd.IsEmpty() || m_Rpwd.IsEmpty())
	{
		MessageBox(TEXT("输入密码不能为空！"));
		return;
	}

	if (m_pwd != m_Rpwd)
	{
		MessageBox(TEXT("输入密码和确定密码不相等！"));
		return;
	}

	if (m_pwd == pwd)
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
	tmp2 = m_pwd;
	tmpPwd = tmp2.GetBuffer();

	file.WirtePwd(tmpName, tmpPwd); //修改密码

	MessageBox(TEXT("密码修改成功"));
	
	OnCancel();
}


void CForgotPwdDlg::OnPaint()
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


BOOL CForgotPwdDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//实现按下回车键即登陆的功能
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT_NEWPWD) || GetFocus() == GetDlgItem(IDC_EDIT_RNEWPWD))
		{
			OnBnClickedButton1();
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
