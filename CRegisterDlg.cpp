// CRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CRegisterDlg.h"
#include "CInfoFile.h"
#include "CSetSafetyDlg.h"

// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_REGISTER, pParent)
	, m_pwd(_T(""))
	, m_Rpwd(_T(""))
	, m_user(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Text(pDX, IDC_EDIT_RPWD, m_Rpwd);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CRegisterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegisterDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON4, &CRegisterDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


void CRegisterDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_combo.AddString(TEXT("主管"));
	m_combo.SetCurSel(0);//默认显示主管

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRegisterDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	UpdateData(TRUE);//更新控件内容到对应的变量中

	if (m_pwd.IsEmpty() || m_user.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}

	if (m_pwd != m_Rpwd)
	{
		MessageBox(TEXT("输入密码和确定密码不相等！"));
		return;
	}

	file.WirteLogin(m_user, m_pwd);
	MessageBox(TEXT("注册成功"));
	OnCancel();
}


void CRegisterDlg::OnPaint()
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
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}



void CRegisterDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CRegisterDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CSetSafetyDlg.h"
	CSetSafetyDlg dlg;
	dlg.DoModal();
}
