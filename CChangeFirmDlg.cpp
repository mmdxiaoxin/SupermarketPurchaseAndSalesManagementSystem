// CChangeFirmDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CChangeFirmDlg.h"
#include "CInfoFile.h"
#include "MainFrm.h"


// CChangeFirmDlg 对话框

IMPLEMENT_DYNAMIC(CChangeFirmDlg, CDialogEx)

CChangeFirmDlg::CChangeFirmDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_CHANGE_FIRM, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_address(_T(""))
	, m_phoneNumber(_T(""))
	, m_fax(_T(""))
{

}

CChangeFirmDlg::~CChangeFirmDlg()
{
}

void CChangeFirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_IN_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phoneNumber);
	DDX_Text(pDX, IDC_EDIT_FAX, m_fax);
}


BEGIN_MESSAGE_MAP(CChangeFirmDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeFirmDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CChangeFirmDlg::OnBnClickedButtonCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChangeFirmDlg 消息处理程序


void CChangeFirmDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CChangeFirmDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CFont m_font;
	m_font.CreatePointFont(150, _T("楷体"));
	m_caption.SetFont(&m_font);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadFirm();
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		if (CPublic::GetFirmName() == it->name)
		{
			m_name = it->name.c_str();
			m_id = it->id.c_str();
			m_address = it->address.c_str();
			m_fax = it->fax.c_str();
			m_phoneNumber = it->phoneNumber.c_str();
			break;
		}
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChangeFirmDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_id.IsEmpty() || m_name.IsEmpty() || m_address.IsEmpty() || m_phoneNumber.IsEmpty() || m_fax.IsEmpty())
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadFirm();
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		if (CPublic::GetFirmName() == it->name)
		{
			char* tmpID, * tmpName, * tmpAddress, * tmpPhoneNumber, * tmpFax;
			CStringA tmp1;
			tmp1 = m_id;
			tmpID = tmp1.GetBuffer();

			CStringA tmp2;
			tmp2 = m_name;
			tmpName = tmp2.GetBuffer();

			CStringA tmp3;
			tmp3 = m_address;
			tmpAddress = tmp3.GetBuffer();

			CStringA tmp4;
			tmp4 = m_phoneNumber;
			tmpPhoneNumber = tmp4.GetBuffer();

			CStringA tmp5;
			tmp5 = m_fax;
			tmpFax = tmp5.GetBuffer();

			it->id = tmpID;
			it->name = tmpName;
			it->address = tmpAddress;
			it->fax = tmpFax;
			it->phoneNumber = tmpPhoneNumber;
			
			break;
		}
	}
	file.WirteFirm();
	MessageBox(_T("修改成功！"));
	OnCancel();
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);//初始化
}


void CChangeFirmDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CChangeFirmDlg::OnPaint()
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
