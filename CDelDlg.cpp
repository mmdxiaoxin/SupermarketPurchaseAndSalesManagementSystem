// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CDelDlg.h"
#include "CInfoFile.h"
#include "MainFrm.h"

// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DEL)
	, m_id(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_group);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ALL_SELL, &CDelDlg::OnBnClickedButtonAllSell)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//调整标题字体
	m_font.CreatePointFont(150, _T("宋体"));  //字体和大小根据自己的需要自行改变
	m_caption.SetFont(&m_font);             //将字体和想要改变的框体变量进行关联
	m_font_group.CreatePointFont(120, _T("宋体"));
	m_group.SetFont(&m_font_group);

	//读取文件，获取商品名，给组合框添加字符串
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}
	//将第一个商品名设为默认选中项
	m_combo.SetCurSel(0);
	if (!file.ls.empty())
		m_id = file.ls.front().id;
	
	file.ls.clear();//清空链表内容

	UpdateData(FALSE); //内容更新到对应的控件
	
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_id = it->id;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			if (it->num != 0) 
			{
				MessageBox(_T("商品库存不为0，无法删除！"));
				return;
			}
			file.ls.erase(it);
			MessageBox(_T("删除成功"));
			if (file.ls.empty())
			{
				file.WirteDocline();//写入商品信息
				//需要包含#include "CMainFrame.h"
				::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);//初始化窗口
				return;
			}
			//重新对商品ID编号
			int i = 0;
			for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
			{
				it->id = ++i;
			}
			file.WirteDocline();//写入商品信息
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);//初始化窗口
			break;
		}
	}
}


void CDelDlg::OnPaint()
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


void CDelDlg::OnBnClickedButtonAllSell()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	file.ReadSalesRecord();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			CString date;
			CTime tm;
			tm = CTime::GetCurrentTime();//获取系统日期  
			date = tm.Format("%Y年%m月%d日");

			char* tmpDate;
			CStringA tmp;
			tmp = date;
			tmpDate = tmp.GetBuffer();
			file.Addline(it->id,it->name,(string)tmpDate,it->in_price,it->out_price,it->num,it->num * it->out_price,it->num * it->out_price - it->in_price * it->num);
			it->num = 0;
			MessageBox(_T("出售成功"));
			break;
		}
	}
	file.WirteSalesRecord();
	file.WirteDocline();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);//初始化窗口
}
