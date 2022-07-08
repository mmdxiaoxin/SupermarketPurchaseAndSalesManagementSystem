// CAdd_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CAdd_Dlg.h"
#include "CInfoFile.h"

// CAdd_Dlg

IMPLEMENT_DYNCREATE(CAdd_Dlg, CFormView)

CAdd_Dlg::CAdd_Dlg()
	: CFormView(DIALOG_ADD)
	, m_num1(0)
	, m_name2(_T(""))
	, m_num2(0)
	, m_out_price2(0)
	, kind(0)
	, m_in_price2(0)
	, m_in_price1(0)
	, m_firmID(0)
{

}

CAdd_Dlg::~CAdd_Dlg()
{
}

void CAdd_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT3, m_name2);
	DDX_Text(pDX, IDC_EDIT5, m_num2);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
	DDX_Control(pDX, IDC_STATIC_GROUP1, m_group1);
	DDX_Control(pDX, IDC_STATIC_GROUP2, m_group2);
	DDX_Text(pDX, IDC_EDIT_OUT_PRICE2, m_out_price2);
	DDX_Text(pDX, IDC_EDIT_KIND, kind);
	DDX_Text(pDX, IDC_EDIT_IN_PRICE2, m_in_price2);
	DDX_Text(pDX, IDC_EDIT_IN_PRICE1, m_in_price1);
	DDX_Text(pDX, IDC_EDIT_FIRMID, m_firmID);
}

BEGIN_MESSAGE_MAP(CAdd_Dlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdd_Dlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAdd_Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CAdd_Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAdd_Dlg::OnBnClickedButton6)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON7, &CAdd_Dlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAdd_Dlg 诊断

#ifdef _DEBUG
void CAdd_Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdd_Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdd_Dlg 消息处理程序


void CAdd_Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//调整标题字体
	m_font.CreatePointFont(150, _T("宋体"));  //字体和大小根据自己的需要自行改变
	m_caption.SetFont(&m_font);             //将字体和想要改变的框体变量进行关联
	m_font_group.CreatePointFont(120, _T("宋体"));
	m_group1.SetFont(&m_font_group);
	m_group2.SetFont(&m_font_group);
	
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
	{
		m_in_price1 = file.ls.front().in_price;
	}
	else
	{
		m_in_price1 = 0;
	}
	file.ls.clear(); //清空list的内容
	UpdateData(FALSE); //内容更新到对应的控件
}


void CAdd_Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件上的内容，更新到对应关联的变量中
	UpdateData(TRUE);

	if (m_num1 == 0)
	{
		MessageBox(TEXT("个数不能为0"));
		return;
	}

	CString type;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取组合框当前内容
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("购入了 商品：%s \r\n商品进货单价：%.2lf \r\n个数：%d \r\n总共花费：%.2lf元"), type, m_in_price1, m_num1, m_in_price1 * m_num1);
	MessageBox(str);


	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	file.ReadPurchaseRecord();
	int tmpID;
	string tmpName;
	double tmpIn_price;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
			tmpID = it->id;
			tmpName = it->name;
			tmpIn_price = it->in_price;
		}
	}
	CString date;
	CTime tm;
	tm = CTime::GetCurrentTime();//获取系统日期  
	date = tm.Format("%Y年%m月%d日");
	char* tmpDate;
	CStringA tmp;
	tmp = date;
	tmpDate = tmp.GetBuffer();
	file.Addline(tmpID, tmpName, tmpIn_price, tmpDate, m_num1, m_num1 * tmpIn_price);
	file.WirteDocline(); //更新文件内容
	file.WirtePurchaseRecord();
	file.ls.clear(); //清空list的内容

	m_num1 = 0;
	UpdateData(FALSE); //更新到对应的控件

}


void CAdd_Dlg::OnCbnSelchangeCombo1()
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
			m_in_price1 = it->in_price;
			m_num1 = 0;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}

	file.ls.clear(); //清空list的内容
}


void CAdd_Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO:  在此添加控件通知处理程序代码

	m_combo.SetCurSel(0);
	m_num1 = 0;
	OnCbnSelchangeCombo1();
}


void CAdd_Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE); //获取控件内容

	if (m_num2 <= 0 || m_in_price2 <= 0 || m_out_price2 <= 0  || m_name2.IsEmpty() || kind <= 120000 && kind > 120015 || m_firmID <= 0)
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	file.ReadPurchaseRecord();
	int tmpID = file.Addline(m_name2, m_num2, m_out_price2, m_in_price2, kind, m_firmID); //添加商品
	file.WirteDocline(); //写文件
	MessageBox(_T("添加成功"));

	CString date;
	CTime tm;
	tm = CTime::GetCurrentTime();//获取系统日期  
	date = tm.Format("%Y年%m月%d日");

	char* tmpDate,* tmpName;
	CStringA tmp1;
	tmp1 = date;
	CStringA tmp2;
	tmpDate = tmp1.GetBuffer();
	tmp2 = m_name2;
	tmpName = tmp2.GetBuffer();
	
	file.Addline(tmpID, (string)tmpName, m_in_price2, tmpDate, m_num2, m_num2 * m_in_price2);//添加购买记录
	file.WirteDocline(); //更新文件内容
	file.WirtePurchaseRecord();

	//初始化
	m_name2.Empty();
	m_num2 = 0;
	m_in_price2 = 0;
	m_out_price2 = 0;
	kind = 0;
	m_firmID = 0;
	UpdateData(FALSE);
}


BOOL CAdd_Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//实现按下回车键即登陆的功能
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT2))
		{
			OnBnClickedButton4();
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT3) ||
			GetFocus() == GetDlgItem(IDC_EDIT5) ||
			GetFocus() == GetDlgItem(IDC_EDIT6))
		{
			OnBnClickedButton6();
		}
		return TRUE;
	}
	return CFormView::PreTranslateMessage(pMsg);
}


void CAdd_Dlg::OnPaint()
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
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0,
		m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}


void CAdd_Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
}
