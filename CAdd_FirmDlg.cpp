// CAdd_FirmDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CAdd_FirmDlg.h"
#include "MainFrm.h"
#include "CInfoFile.h"


// CAdd_FirmDlg

IMPLEMENT_DYNCREATE(CAdd_FirmDlg, CFormView)

CAdd_FirmDlg::CAdd_FirmDlg()
	: CFormView(DIALOG_FIRM_ADD)
	, m_address(_T(""))
	, m_fax(_T(""))
	, m_name(_T(""))
	, m_phoneNumber(_T(""))
	, m_id(_T(""))
{

}

CAdd_FirmDlg::~CAdd_FirmDlg()
{
}

void CAdd_FirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_FAX, m_fax);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PHONENUMBER, m_phoneNumber);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
}

BEGIN_MESSAGE_MAP(CAdd_FirmDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAdd_FirmDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAdd_FirmDlg::OnBnClickedButtonAdd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAdd_FirmDlg 诊断

#ifdef _DEBUG
void CAdd_FirmDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdd_FirmDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdd_FirmDlg 消息处理程序


void CAdd_FirmDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);
}


void CAdd_FirmDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_id.IsEmpty() || m_name.IsEmpty() || m_address.IsEmpty() || m_phoneNumber.IsEmpty() || m_fax.IsEmpty())
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}
	CInfoFile file;
	file.ReadFirm();

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

	file.Addline(tmpID, tmpName, tmpAddress, tmpPhoneNumber, tmpFax);
	file.WirteFirm();
	MessageBox(_T("添加成功！"));
}


void CAdd_FirmDlg::OnPaint()
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
