﻿// CInputDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CInputDlg.h"
#include "CInfoFile.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_INPUT, pParent)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInputDlg 消息处理程序


BOOL CInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 
	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 初始化表头
	CString field[] = { _T("商品ID"), _T("商品名称"), _T("购入单价/元"),  _T("购入数量"), _T("购入花销/元"), _T("购入日期") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		if (i == 0)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 70);
		}
		else if(i == 5)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 170);
		}
		else if (i == 2 || i == 4)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 150);
		}
		else
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadPurchaseRecord(); //读取商品信息
	//添加数据
	int i = 0;
	CString str;
	for (list<purchase>::iterator it = file.pu.begin(); it != file.pu.end(); it++)
	{
		str.Format(_T("%d"), it->id);
		m_list.InsertItem(i, str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());

		str.Format(_T("%.2lf"), it->in_price);
		m_list.SetItemText(i, column++, str);

		str.Format(_T("%d"), it->num);
		m_list.SetItemText(i, column++, str);

		str.Format(_T("%.2lf"), it->cost);
		m_list.SetItemText(i, column++, str);

		m_list.SetItemText(i, column++, (CString)it->date.c_str());
		i++;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInputDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_SELL_BACKGROUND);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}
