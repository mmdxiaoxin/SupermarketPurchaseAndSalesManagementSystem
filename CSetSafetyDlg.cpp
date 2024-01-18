// CSetSafetyDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CSetSafetyDlg.h"
#include "CInfoFile.h"


// CSetSafetyDlg 对话框

IMPLEMENT_DYNAMIC(CSetSafetyDlg, CDialogEx)

CSetSafetyDlg::CSetSafetyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_SET_SAFETY, pParent)
	, m_ans1_Old(_T(""))
	, m_ans1(_T(""))
	, m_question(_T(""))
	, m_ans2(_T(""))
{

}

CSetSafetyDlg::~CSetSafetyDlg()
{
}

void CSetSafetyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SAFETY, m_combo_safety);
	DDX_Text(pDX, IDC_EDIT_OLDANS, m_ans1_Old);
	DDX_Text(pDX, IDC_EDIT_ANS, m_ans1);
	DDX_Text(pDX, IDC_EDIT_SAFETY, m_question);
	DDX_Text(pDX, IDC_EDIT_ANS2, m_ans2);
}


BEGIN_MESSAGE_MAP(CSetSafetyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK1, &CSetSafetyDlg::OnBnClickedButtonOk1)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL1, &CSetSafetyDlg::OnBnClickedButtonCancel1)
	ON_BN_CLICKED(IDC_BUTTON_OK2, &CSetSafetyDlg::OnBnClickedButtonOk2)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL2, &CSetSafetyDlg::OnBnClickedButtonCancel2)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_SAFETY, &CSetSafetyDlg::OnCbnSelchangeComboSafety)
END_MESSAGE_MAP()


// CSetSafetyDlg 消息处理程序


void CSetSafetyDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CSetSafetyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	//读取安全信息
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety(); //读取问题信息
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		m_combo_safety.AddString((CString)it->question.c_str());
	}
	//将第一个问题设为默认选中项
	m_combo_safety.SetCurSel(0);
	if (!file.qa.empty())
		m_ans1_Old = (CString)file.qa.front().answer.c_str();
	else
		m_ans1_Old = "";

	file.ls.clear(); //清空list的内容
	UpdateData(FALSE);//内容更新到控件

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSetSafetyDlg::OnBnClickedButtonOk1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);//更新控件内容到对应的变量中

	if (m_ans1.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}

	CString text;
	//获取当前选中项
	int index = m_combo_safety.GetCurSel();
	//获取当前内容
	m_combo_safety.GetLBText(index, text);
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety();
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		if (text == it->question.c_str())
		{
			CStringA tmp1;
			tmp1 = m_ans1;////CString转CStirngA
			it->answer = tmp1.GetBuffer();//CStirngA转char *
			m_ans1_Old = m_ans1;
			m_ans1.Empty();
			UpdateData(FALSE);//内容更新到控件
			MessageBox(TEXT("修改成功！"));
			file.WirteSafety();
			return;
		}
	}
	MessageBox(TEXT("输入原答案错误！"));
}


void CSetSafetyDlg::OnBnClickedButtonCancel1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString question;
	//获取当前选中项
	int index = m_combo_safety.GetCurSel();
	//获取当前内容
	m_combo_safety.GetLBText(index, question);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety(); //读取安全信息

	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		if (question == it->question.c_str())
		{
			file.qa.erase(it);
			MessageBox(_T("删除成功"));
			break;
		}
	}
	file.WirteSafety();
}


void CSetSafetyDlg::OnBnClickedButtonOk2()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新内容到变量
	UpdateData(TRUE);
	if (m_question.IsEmpty() || m_ans2.IsEmpty()) 
	{
		MessageBox(_T("输入不能为空！"));
		return;
	}
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety();
	file.Addline(m_question, m_ans2);
	file.WirteSafety();
	MessageBox(_T("添加成功"));
	m_question.Empty();
	m_ans2.Empty();
	UpdateData(FALSE);//初始化
	OnCancel();
}


void CSetSafetyDlg::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CSetSafetyDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
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


void CSetSafetyDlg::OnCbnSelchangeComboSafety()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_combo_safety.GetCurSel();
	//获取当前内容
	m_combo_safety.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety(); //读取安全信息
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		if (text == it->question.c_str())
		{
			m_ans1_Old = it->answer.c_str();
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}

}
