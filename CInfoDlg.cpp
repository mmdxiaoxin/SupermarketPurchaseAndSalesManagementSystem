// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CInfoDlg.h"
#include "CInfoFile.h"
#include "MainFrm.h"
#include "CChangeProductDlg.h"

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
	, m_id1(0)
	, m_id2(0)
	, m_name(_T(""))
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO_NAME1, m_combo_name1);
	DDX_Control(pDX, IDC_COMBO_NAME2, m_combo_name2);
	DDX_Text(pDX, IDC_EDIT_ID, m_id1);
	DDX_Text(pDX, IDC_EDIT_ID2, m_id2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CInfoDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_PUT, &CInfoDlg::OnBnClickedButtonPut)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME2, &CInfoDlg::OnCbnSelchangeComboName2)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CInfoDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_PUT_ALL, &CInfoDlg::OnBnClickedButtonPutAll)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_ALL, &CInfoDlg::OnBnClickedButtonDownAll)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL1, &CInfoDlg::OnBnClickedButtonCancel1)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL2, &CInfoDlg::OnBnClickedButtonCancel2)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CInfoDlg::OnBnClickedButtonChange)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("商品ID"), _T("商品名称"), _T("库存"), _T("商品类别号"), _T("供应商编号"),_T("是否上架") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//添加数据
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(_T("%d"), it->id);
		m_list.InsertItem(i, str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());

		str.Format(_T("%d"), it->num);
		m_list.SetItemText(i, column++, str);

		str.Format(_T("%d"), it->kind);
		m_list.SetItemText(i, column++, str);

		str.Format(_T("%d"), it->firmID);
		m_list.SetItemText(i, column++, str);

		m_list.SetItemText(i, column++, (CString)it->isPut.c_str());

		m_combo_name1.AddString((CString)it->name.c_str());//添加商品名称到修改信息下拉框
		m_combo_name2.AddString((CString)it->name.c_str());//添加商品名称到上架下架控制控件

		i++;
	}
	m_combo_name1.SetCurSel(0);
	m_combo_name2.SetCurSel(0);
	if (!file.ls.empty())
		m_id2 = file.ls.front().id;
	else
		m_id2 = 0;
	UpdateData(FALSE);//内容更新到控件上
}


void CInfoDlg::OnPaint()
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


void CInfoDlg::OnBnClickedButtonFind()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	UpdateData(TRUE);//控件内容更新到变量
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (m_name == it->name.c_str())
		{
			CString str;
			str.Format(_T("商品ID：%d\r\n"
				"商品名称：%s\r\n"
				"商品零售价格：%.2lf\r\n"
				"商品进货价格：%.2lf\r\n"
				"库存：%d\r\n"
				"商品类别号：%d\r\n"
				"供应商编号：%d\r\n"
				"是否上架：%s"), 
				it->id, 
				(CString)it->name.c_str(), 
				it->out_price, 
				it->in_price,
				it->num, 
				it->kind, 
				it->firmID, 
				(CString)it->isPut.c_str());
			m_name.Empty();
			m_id1 = 0;
			MessageBox(str);
			return;
		}
		else if (m_id1 == it->id) 
		{
			CString str;
			str.Format(_T("商品ID：%d\r\n"
				"商品名称：%s\r\n"
				"商品零售价格：%.2lf\r\n"
				"商品进货价格：%.2lf\r\n"
				"库存：%d\r\n"
				"商品类别号：%d\r\n"
				"供应商编号：%d\r\n"
				"是否上架：%s"), 
				it->id,
				(CString)it->name.c_str(),
				it->out_price,
				it->in_price,
				it->num,
				it->kind,
				it->firmID,
				(CString)it->isPut.c_str());
			m_name.Empty();
			m_id1 = 0;
			MessageBox(str);
			return;
		}
	}
	MessageBox(_T("没有找到该商品！"));
}


void CInfoDlg::OnBnClickedButtonPut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	int index = m_combo_name2.GetCurSel();
	m_combo_name2.GetLBText(index, name);
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (name == (CString)it->name.c_str())
		{
			if (it->isPut == "已上架")
			{
				MessageBox(_T("请勿重复上架！"));
				return;
			}
			it->isPut = "已上架";
			MessageBox(_T("上架成功"));
		}
	}
	file.WirteDocline();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);//重新绘出窗口来初始化
}


void CInfoDlg::OnCbnSelchangeComboName2()
{
	// TODO: 在此添加控件通知处理程序代码

	CString name;
	int index = m_combo_name2.GetCurSel();
	m_combo_name2.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (name == (CString)it->name.c_str())
		{
			m_id2 = it->id;
		}
	}
	UpdateData(FALSE);
}


void CInfoDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	int index = m_combo_name2.GetCurSel();
	m_combo_name2.GetLBText(index, name);
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (name == (CString)it->name.c_str())
		{
			if (it->isPut == "未上架")
			{
				MessageBox(_T("请勿重复下架！"));
				return;
			}
			it->isPut = "未上架";
			MessageBox(_T("下架成功"));
		}
	}
	file.WirteDocline();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);//重新绘出窗口来初始化
}


void CInfoDlg::OnBnClickedButtonPutAll()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		it->isPut = "已上架";
	}
	file.WirteDocline();
	MessageBox(_T("全部上架成功"));
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);//重新绘出窗口来初始化
}


void CInfoDlg::OnBnClickedButtonDownAll()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		it->isPut = "未上架";
	}
	file.WirteDocline();
	MessageBox(_T("全部下架成功"));
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);//重新绘出窗口来初始化
}


void CInfoDlg::OnBnClickedButtonCancel1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name.Empty();
	m_id1 = 0;
	UpdateData(FALSE);
}


void CInfoDlg::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo_name1.SetCurSel(0);
}


void CInfoDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;

	int index = m_combo_name1.GetCurSel();

	m_combo_name1.GetLBText(index, name);

	char* tmpName;
	CStringA tmp;
	tmp = name;
	tmpName = tmp.GetBuffer();

	CPublic::SetProductName(tmpName);
	//需要包含#include "CChangeProductDlg.h"
	CChangeProductDlg dlg;
	dlg.DoModal();

}
