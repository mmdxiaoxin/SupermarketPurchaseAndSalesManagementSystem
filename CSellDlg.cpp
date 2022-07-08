// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CSellDlg.h"
#include "CInfoFile.h"

// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_num(0)
	, m_left(0)
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_left);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
	DDX_Control(pDX, IDC_EDIT4, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置标题字体大小
	m_font.CreatePointFont(150, _T("楷体"));  //字体和大小根据自己的需要自行改变
	m_caption.SetFont(&m_font);             //将字体和想要改变的框体变量进行关联

	//读取文件，获取商品名，给组合框添加字符串
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	if (file.ls.empty()) return;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}
	//将第一个商品名设为默认选中项
	m_combo.SetCurSel(0);
	m_left = file.ls.front().num;
	
	file.ls.clear(); //清空list的内容

	UpdateData(FALSE); //更新内容到控件上
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	double m_price;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_price = it->out_price;
			m_left = it->num;
			m_num = 0;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}

	file.ls.clear(); //清空list的内容
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取控件上的内容，更新到对应关联的变量中

	m_sellInfo.SetWindowTextW(_T(""));
	UpdateData(TRUE);

	if (m_num == 0)
	{
		MessageBox(TEXT("个数不能为0"));
		return;
	}

	CString name;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取组合框当前内容
	m_combo.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	CString str;
	double m_price, tmpINprice, tmpOUTprice;
	int tmpID;
	file.ReadDocline(); //读取商品信息
	file.ReadSalesRecord();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (name == it->name.c_str())
		{
			if (it->num - m_num < 0) 
			{
				MessageBox(TEXT("出售超过库存上限！"));
				break;
			}
			tmpID = it->id;
			tmpINprice = it->in_price;
			tmpOUTprice = m_price = it->out_price;
			it->num -= m_num;
			m_left = it->num;

			str.Format(_T("商品：%s \r\n单价：%.2lf \r\n个数：%d \r\n销售额：%.2lf 元"), name, m_price, m_num, m_price * m_num);

		}
	}
	m_sellInfo.SetWindowTextW(str); //销售信息
	CString date;
	CTime tm;
	tm = CTime::GetCurrentTime();//获取系统日期  
	date = tm.Format("%Y年%m月%d日");

	char* tmpDate, * tmpName;
	CStringA tmp1;
	tmp1 = date;
	CStringA tmp2;
	tmpDate = tmp1.GetBuffer();
	tmp2 = name;
	tmpName = tmp2.GetBuffer();

	file.Addline(tmpID, tmpName, tmpDate, tmpINprice, tmpOUTprice, m_num, m_num * tmpOUTprice, m_num * tmpOUTprice - m_num * tmpINprice);
	file.WirteDocline(); //更新文件内容
	file.WirteSalesRecord();
	file.ls.clear(); //清空list的内容
	m_num = 0;
	UpdateData(FALSE); //更新到对应的控件
}

void CSellDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	m_combo.SetCurSel(0); //选择第0项目
	m_sellInfo.SetWindowTextW(_T(""));
	m_num = 0;
	OnCbnSelchangeCombo1();
}

void CSellDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFormView::OnPaint()
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
