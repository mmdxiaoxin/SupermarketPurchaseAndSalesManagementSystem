#pragma once

#include "CInputDlg.h"
#include "COutputDlg.h"

// CTab_IO_Dlg 窗体视图

class CTab_IO_Dlg : public CFormView
{
	DECLARE_DYNCREATE(CTab_IO_Dlg)

protected:
	CTab_IO_Dlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CTab_IO_Dlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_IO_TAB };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	CTabCtrl m_tab;
	//需要包含#include "CInputDlg.h" 
	//需要包含#include "COutputDlg.h"
	CInputDlg m_page1;
	COutputDlg m_page2;
public:
	afx_msg void OnTcnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult);
};


