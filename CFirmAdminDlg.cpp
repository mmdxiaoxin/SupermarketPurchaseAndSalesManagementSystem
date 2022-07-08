// CFirmAdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "afxdialogex.h"
#include "CFirmAdminDlg.h"
#include "MainFrm.h"
#include "CInfoFile.h"
#include "CChangeFirmDlg.h"


// CFirmAdminDlg 对话框

IMPLEMENT_DYNAMIC(CFirmAdminDlg, CDialogEx)

CFirmAdminDlg::CFirmAdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_FIRM_ADMIN, pParent)
	, m_firm_id(_T(""))
	, m_firmInfo(_T(""))
{

}

CFirmAdminDlg::~CFirmAdminDlg()
{
}

void CFirmAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_caption);
	DDX_Control(pDX, IDC_COMBO_NAME, m_combo_name);
	DDX_Text(pDX, IDC_EDIT_ID, m_firm_id);
	DDX_Text(pDX, IDC_EDIT_INFO, m_firmInfo);
}


BEGIN_MESSAGE_MAP(CFirmAdminDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CFirmAdminDlg::OnBnClickedButtonAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME, &CFirmAdminDlg::OnCbnSelchangeComboName)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CFirmAdminDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CFirmAdminDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CFirmAdminDlg::OnBnClickedButtonChange)
END_MESSAGE_MAP()


// CFirmAdminDlg 消息处理程序


void CFirmAdminDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
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


void CFirmAdminDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_M, (WPARAM)NM_M, (LPARAM)0);
}


BOOL CFirmAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CFont m_font;
	m_font.CreatePointFont(150, _T("楷体"));  
	m_caption.SetFont(&m_font);            
	
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadFirm(); //读取厂商信息
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		m_combo_name.AddString((CString)it->name.c_str());
	}
	m_combo_name.SetCurSel(0);
	if (!file.fi.empty())
		m_firm_id = (CString)file.fi.front().id.c_str();
	else
		m_firm_id.Empty();
	CString str;
	str.Format(_T("厂商编号：%s \r\n厂商名称：%s\r\n厂商地址：%s\r\n厂商电话：%s\r\n厂商传真：%s "), 
		(CString)file.fi.front().id.c_str(), 
		(CString)file.fi.front().name.c_str(), 
		(CString)file.fi.front().address.c_str(), 
		(CString)file.fi.front().phoneNumber.c_str(), 
		(CString)file.fi.front().fax.c_str());
	m_firmInfo = str;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFirmAdminDlg::OnCbnSelchangeComboName()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	//获取当前选中项
	int index = m_combo_name.GetCurSel();
	//获取当前内容
	m_combo_name.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	CString str;
	file.ReadFirm(); //读取厂商信息
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		if (name == it->name.c_str())
		{
			m_firm_id = (CString)it->id.c_str();
			str.Format(_T("厂商编号：%s \r\n厂商名称：%s\r\n厂商地址：%s\r\n厂商电话：%s\r\n厂商传真：%s "),
				(CString)it->id.c_str(),
				(CString)it->name.c_str(),
				(CString)it->address.c_str(),
				(CString)it->phoneNumber.c_str(),
				(CString)it->fax.c_str());
		}
	}
	m_firmInfo = str;
	UpdateData(FALSE); //内容更新到对应的控件
}


void CFirmAdminDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadFirm(); //读取厂商信息
	m_combo_name.SetCurSel(0);
	if (!file.fi.empty())
		m_firm_id = (CString)file.fi.front().id.c_str();
	else
		m_firm_id.Empty();
	CString str;
	str.Format(_T("厂商编号：%s \r\n厂商名称：%s\r\n厂商地址：%s\r\n厂商电话：%s\r\n厂商传真：%s "),
		(CString)file.fi.front().id.c_str(),
		(CString)file.fi.front().name.c_str(),
		(CString)file.fi.front().address.c_str(),
		(CString)file.fi.front().phoneNumber.c_str(),
		(CString)file.fi.front().fax.c_str());
	m_firmInfo = str;
	UpdateData(FALSE);
}


void CFirmAdminDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	//获取当前选中项
	int index = m_combo_name.GetCurSel();
	//获取当前内容
	m_combo_name.GetLBText(index, name);

	//需要包含#include "CInfoFile.h"
	CInfoFile file;
	file.ReadFirm(); //读取厂商信息
	for (list<firm>::iterator it = file.fi.begin(); it != file.fi.end(); it++)
	{
		if (name == it->name.c_str())
		{
			file.fi.erase(it);
			MessageBox(_T("删除成功"));
			file.WirteFirm();
			break;
		}
	}
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);//初始化窗口
}


void CFirmAdminDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;

	int index = m_combo_name.GetCurSel();

	m_combo_name.GetLBText(index, name);

	char* tmpName;
	CStringA tmp;
	tmp = name;
	tmpName = tmp.GetBuffer();

	CPublic::SetFirmName((string)tmpName);
	//需要包含#include "CChangeFirmDlg.h"
	CChangeFirmDlg dlg;
	dlg.DoModal();
}
