// CWarnStockDlg.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CWarnStockDlg.h"


// CWarnStockDlg

IMPLEMENT_DYNCREATE(CWarnStockDlg, CFormView)

CWarnStockDlg::CWarnStockDlg()
	: CFormView(DIALOG_WARN_STOCK)
{

}

CWarnStockDlg::~CWarnStockDlg()
{
}

void CWarnStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWarnStockDlg, CFormView)
END_MESSAGE_MAP()


// CWarnStockDlg 诊断

#ifdef _DEBUG
void CWarnStockDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWarnStockDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWarnStockDlg 消息处理程序
