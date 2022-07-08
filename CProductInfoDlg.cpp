// CProductInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CProductInfoDlg.h"
#include "CInfoFile.h"
#include "CCategory.h"

// CProductInfoDlg

IMPLEMENT_DYNCREATE(CProductInfoDlg, CFormView)

CProductInfoDlg::CProductInfoDlg()
	: CFormView(DIALOG_PRODUCT_INFO)
{

}

CProductInfoDlg::~CProductInfoDlg()
{
}

void CProductInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
}

BEGIN_MESSAGE_MAP(CProductInfoDlg, CFormView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProductInfoDlg 诊断

#ifdef _DEBUG
void CProductInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProductInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProductInfoDlg 消息处理程序


void CProductInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CFont m_font;
	//设置标题字体大小
	m_font.CreatePointFont(150, _T("楷体")); 
	m_caption.SetFont(&m_font);             

	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("商品ID"), _T("商品名称"), _T("商品零售价格/元"), _T("商品进货价格/元"), _T("厂家"), _T("商品分区"), _T("商品种类") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		if (i > 1 && i < 4) 
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 130);
		}
		else if (i == 0)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 60);
		} 
		else if (i == 4)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 190);
		}
		else
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 120);
		}
	}

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	file.ReadFirm(); //读取厂商信息
	//商品分类
	//需要包含#include "CCategory.h"
	CCategory category;
	//添加数据
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (it->isPut != "已上架")
			continue;
		str.Format(_T("%d"), it->id);
		m_list.InsertItem(i, str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());

		str.Format(_T("%.2lf"), it->out_price);
		m_list.SetItemText(i, column++, str);

		str.Format(_T("%.2lf"), it->in_price);
		m_list.SetItemText(i, column++, str);

		bool flag = false;
		for (list<firm>::iterator _it = file.fi.begin(); _it != file.fi.end(); _it++)
		{
			if (_it->id == to_string(it->firmID))
			{
				flag = true;
				m_list.SetItemText(i, column++, (CString)_it->name.c_str());
			}
		}

		if (!flag) m_list.SetItemText(i, column++, _T("未知"));

		category.SetCategory(it->kind);
		m_list.SetItemText(i, column++, (CString)category.Area().c_str());

		m_list.SetItemText(i, column++, (CString)category.SmallCategory().c_str());
		i++;
	}
}


void CProductInfoDlg::OnPaint()
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
