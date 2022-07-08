// CFirmInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CFirmInfoDlg.h"
#include "CInfoFile.h"


// CFirmInfoDlg 对话框

IMPLEMENT_DYNAMIC(CFirmInfoDlg, CDialogEx)

CFirmInfoDlg::CFirmInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_FIRM_INF, pParent)
	, m_firm_id(_T(""))
	, m_firm_name(_T(""))
	, m_firm_address(_T(""))
	, m_firm_phoneNumber(_T(""))
	, m_firm_fax(_T(""))
{

}

CFirmInfoDlg::~CFirmInfoDlg()
{
}

void CFirmInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_ID, m_firm_id);
	DDX_Text(pDX, IDC_EDIT_NAME, m_firm_name);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_firm_address);
	DDX_Text(pDX, IDC_EDIT_PHONENUMBER, m_firm_phoneNumber);
	DDX_Text(pDX, IDC_EDIT_FAX, m_firm_fax);
}


BEGIN_MESSAGE_MAP(CFirmInfoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CFirmInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_FIRM_FIND, &CFirmInfoDlg::OnBnClickedButtonFirmFind)
	ON_BN_CLICKED(IDC_BUTTON_FIRM_RESET, &CFirmInfoDlg::OnBnClickedButtonFirmReset)
END_MESSAGE_MAP()


// CFirmInfoDlg 消息处理程序


void CFirmInfoDlg::OnPaint()
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


void CFirmInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CFirmInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("厂商编号"), _T("厂商名称"), _T("厂商地址"), _T("厂商电话"), _T("厂商传真") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		if (i == 1)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 130);
		}
		else if (i == 0)
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 100);
		}
		else if (i == 2)
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
	file.ReadFirm(); //读取商品信息

	//添加数据
	int i = 0;
	CString str;
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		
		m_list.InsertItem(i, (CString)it->id.c_str());
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());

		m_list.SetItemText(i, column++, (CString)it->address.c_str());

		m_list.SetItemText(i, column++, (CString)it->phoneNumber.c_str());

		m_list.SetItemText(i, column++, (CString)it->fax.c_str());
		i++;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFirmInfoDlg::OnBnClickedButtonFirmFind()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CInfoFile file;
	file.ReadFirm();
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		if (m_firm_id == (CString)it->id.c_str())
		{
			m_firm_address = (CString)it->address.c_str();
			m_firm_name = (CString)it->name.c_str();
			m_firm_phoneNumber = (CString)it->phoneNumber.c_str();
			m_firm_fax = (CString)it->fax.c_str();
			UpdateData(FALSE);
			return;
		}
	}
	MessageBox(_T("没有找到该厂商！"));
}


void CFirmInfoDlg::OnBnClickedButtonFirmReset()
{
	// TODO: 在此添加控件通知处理程序代码

	m_firm_id.Empty();
	m_firm_address.Empty();
	m_firm_name.Empty();
	m_firm_phoneNumber.Empty();
	m_firm_fax.Empty();

	UpdateData(FALSE);
}


void CFirmInfoDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
