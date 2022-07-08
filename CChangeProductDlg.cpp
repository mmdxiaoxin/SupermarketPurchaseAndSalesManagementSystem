// CChangeProductDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CChangeProductDlg.h"
#include "CInfoFile.h"
#include "MainFrm.h"


// CChangeProductDlg 对话框

IMPLEMENT_DYNAMIC(CChangeProductDlg, CDialogEx)

CChangeProductDlg::CChangeProductDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_CHANGE_PRODUCT, pParent)
	, m_firmID(0)
	, m_in_price(0)
	, m_kind(0)
	, m_name(_T(""))
	, m_num(0)
	, m_out_price(0)
{

}

CChangeProductDlg::~CChangeProductDlg()
{
}

void CChangeProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRMID, m_firmID);
	DDX_Text(pDX, IDC_EDIT_IN_PRICE, m_in_price);
	DDX_Text(pDX, IDC_EDIT_KIND, m_kind);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT_OUT_PRICE, m_out_price);
}


BEGIN_MESSAGE_MAP(CChangeProductDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeProductDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CChangeProductDlg::OnBnClickedButtonCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChangeProductDlg 消息处理程序


void CChangeProductDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_num <= 0 || m_in_price <= 0 || m_out_price <= 0 || m_name.IsEmpty() || m_kind <= 120000 && m_kind > 120015 || m_firmID <= 0)
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CPublic::GetProductName() == it->name)
		{
			char* tmpName;
			CStringA tmp;
			tmp = m_name;
			tmpName = tmp.GetBuffer();

			it->name = (string)tmpName;
			it->in_price = m_in_price;
			it->out_price = m_out_price;
			it->num = m_num;
			it->firmID = m_firmID;
			it->kind = m_kind;

			break;
		}
	}
	MessageBox(_T("修改成功！"));
	file.WirteDocline();
	OnCancel();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);//初始化窗口
}


BOOL CChangeProductDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CPublic::GetProductName() == it->name)
		{
			m_name = it->name.c_str();
			m_in_price = it->in_price;
			m_out_price = it->out_price;
			m_num = it->num;
			m_firmID = it->firmID;
			m_kind = it->kind;
			break;
		}
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChangeProductDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CChangeProductDlg::OnPaint()
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
