// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "CInfoFile.h"
#include "CRegisterDlg.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Control(pDX, IDC_REGISTER, m_rigister);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_REGISTER, &CLoginDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_CHANGE_PWD, &CLoginDlg::OnBnClickedChangePwd)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//登陆按钮点击事件

	UpdateData(TRUE);
	if (m_user.IsEmpty() || m_pwd.IsEmpty()) {
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	
	//获取到正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	file.ReadLogin();
	for (list<staff>::iterator it = file.st.begin(); it != file.st.end(); it++)
	{
		if (m_user == it->user.c_str())
		{
			if (m_pwd == it->pwd.c_str()) {
				//关闭当前对话框
				CDialog::OnCancel();
				CPublic::SetJurisdiction(it->jurisdiction);
				CPublic::SetStaffInf(it->id, it->user, it->name);
				return;
			}
			else {
				MessageBox(TEXT("密码错误"));
				return;
			}
		}

	}
	if (name == m_user) { //用户名一致
		if (m_pwd == pwd) {
			//关闭当前对话框
			CDialog::OnCancel();
			CPublic::SetJurisdiction("主管");
			return;
		}
		else {
			MessageBox(TEXT("密码错误"));
			return;
		}
	}
	else {
		MessageBox(TEXT("用户名有误"));
		return;
	}


}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	//添加代码对话框背景贴图
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_LOGIN);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 
				0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	//设置图标，IDI_ICON_WIN为图标资源ID
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_WIN);
	SetIcon(m_hIcon, TRUE);

	//默认登陆信息
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	
	m_user = name;
	m_pwd = pwd;
	//同步到控件中
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//实现按下回车键即登陆的功能
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT2) || GetFocus() == GetDlgItem(IDC_EDIT1))
		{
			OnBnClickedButton1();
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLoginDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码

	//清空登陆信息
	m_user = TEXT("");
	m_pwd = TEXT("");
	UpdateData(FALSE);//将内容更新到控件
	ifstream ifs; //判断现在是否存在主管账号
	char buffer[256] = {0};
	ifs.open(_F_LOGIN); 
	ifs.getline(buffer, 100);
	if ((string)buffer == "") {
		dlg.DoModal(); //以模态方式运行
		return;
	}
	ifs.close();
	MessageBox(TEXT("现在已经存在主管账号！"));
}


void CLoginDlg::OnBnClickedChangePwd()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空登陆信息
	m_user = TEXT("");
	m_pwd = TEXT("");
	UpdateData(FALSE);//将内容更新到控件
	dlg1.DoModal();
}
