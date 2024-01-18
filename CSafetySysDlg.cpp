// CSafetySysDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CSafetySysDlg.h"
#include "CInfoFile.h"

// CSafetySysDlg 对话框

IMPLEMENT_DYNAMIC(CSafetySysDlg, CDialogEx)

CSafetySysDlg::CSafetySysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_SAFETY_SYS, pParent)
	, m_answer(_T(""))
{

}

CSafetySysDlg::~CSafetySysDlg()
{
}

void CSafetySysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_answer);
}


BEGIN_MESSAGE_MAP(CSafetySysDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CSafetySysDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSafetySysDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSafetySysDlg 消息处理程序


void CSafetySysDlg::OnPaint()
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
	bmpBackground.LoadBitmap(IDB_BITMAP_REGISTER);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
		0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}


void CSafetySysDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


BOOL CSafetySysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadSafety(); //读取安全问题
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		m_combo.AddString((CString)it->question.c_str());
	}
	//将第一个问题名设为默认选中项
	m_combo.SetCurSel(0);

	file.qa.clear(); //清空list的内容

	UpdateData(FALSE);//内容更新到对应的控件

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSafetySysDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CSafetySysDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);//将控件的值更新到变量
	//获取组合框中当前选中项的下标
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str); //获取指定下标的内容

	CInfoFile file;
	file.ReadSafety();
	for (list<safety>::iterator it = file.qa.begin(); it != file.qa.end(); it++)
	{
		if (str == (CString)it->question.c_str())
		{
			if (m_answer == (CString)it->answer.c_str())
			{
				MessageBox(TEXT("回答正确！"));
				file.qa.clear();
				OnCancel();
				dlg.DoModal();	
				return;
			}
		}
	}
	file.qa.clear();
	MessageBox(TEXT("回答错误！"));
}


BOOL CSafetySysDlg::PreTranslateMessage(MSG* pMsg)
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
