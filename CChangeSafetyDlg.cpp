// CChangeSafetyDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CChangeSafetyDlg.h"
#include "MainFrm.h"
#include "CInfoFile.h"

// CChangeSafetyDlg

IMPLEMENT_DYNCREATE(CChangeSafetyDlg, CFormView)

CChangeSafetyDlg::CChangeSafetyDlg()
	: CFormView(DIALOG_CHANGE_SAFETY)
	, m_ans1(_T(""))
	, m_ans2(_T(""))
	, m_ans1_Old(_T(""))
	, m_question(_T(""))
{

}

CChangeSafetyDlg::~CChangeSafetyDlg()
{
}

void CChangeSafetyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SAFETY, m_combo_Safety);
	DDX_Text(pDX, IDC_EDIT_ANS, m_ans1);
	DDX_Text(pDX, IDC_EDIT_ANS2, m_ans2);
	DDX_Text(pDX, IDC_EDIT_OLDANS, m_ans1_Old);
	DDX_Text(pDX, IDC_EDIT_SAFETY, m_question);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
}

BEGIN_MESSAGE_MAP(CChangeSafetyDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL1, &CChangeSafetyDlg::OnBnClickedButtonCancel1)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL2, &CChangeSafetyDlg::OnBnClickedButtonCancel2)
	ON_BN_CLICKED(IDC_BUTTON_OK1, &CChangeSafetyDlg::OnBnClickedButtonOk1)
	ON_CBN_SELCHANGE(IDC_COMBO_SAFETY, &CChangeSafetyDlg::OnCbnSelchangeComboSafety)
	ON_BN_CLICKED(IDC_BUTTON_OK2, &CChangeSafetyDlg::OnBnClickedButtonOk2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChangeSafetyDlg 诊断

#ifdef _DEBUG
void CChangeSafetyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChangeSafetyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChangeSafetyDlg 消息处理程序


void CChangeSafetyDlg::OnBnClickedButtonCancel1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString question;
	//获取当前选中项
	int index = m_combo_Safety.GetCurSel();
	//获取当前内容
	m_combo_Safety.GetLBText(index, question);

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
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_K, (WPARAM)NM_K, (LPARAM)0);//初始化窗口
}


void CChangeSafetyDlg::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	//同按钮1
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CChangeSafetyDlg::OnBnClickedButtonOk1()
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
	int index = m_combo_Safety.GetCurSel();
	//获取当前内容
	m_combo_Safety.GetLBText(index, text);
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


void CChangeSafetyDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CFont m_font;
	m_font.CreatePointFont(150, _T("楷体"));  //字体和大小根据自己的需要自行改变
	m_caption.SetFont(&m_font);             //将字体和想要改变的框体变量进行关联

	//读取安全信息
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety(); //读取问题信息
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		m_combo_Safety.AddString((CString)it->question.c_str());
	}
	//将第一个问题设为默认选中项
	m_combo_Safety.SetCurSel(0);
	if (!file.qa.empty())
		m_ans1_Old = (CString)file.qa.front().answer.c_str();
	else
		m_ans1_Old = "";
	
	file.ls.clear(); //清空list的内容
	UpdateData(FALSE);//内容更新到控件
}


void CChangeSafetyDlg::OnCbnSelchangeComboSafety()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	//获取当前选中项
	int index = m_combo_Safety.GetCurSel();
	//获取当前内容
	m_combo_Safety.GetLBText(index, text);

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


void CChangeSafetyDlg::OnBnClickedButtonOk2()
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
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_K, (WPARAM)NM_K, (LPARAM)0);//初始化

}


void CChangeSafetyDlg::OnPaint()
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
