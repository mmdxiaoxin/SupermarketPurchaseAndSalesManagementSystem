#pragma once
#include "CFirmAdminDlg.h"
#include "CFirmInfoDlg.h"


// CTab_FIRM_Dlg 窗体视图

class CTab_FIRM_Dlg : public CFormView
{
	DECLARE_DYNCREATE(CTab_FIRM_Dlg)

protected:
	CTab_FIRM_Dlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CTab_FIRM_Dlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_FIRM_TAB };
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
	//需要包含#include "CFirmAdminDlg.h" 
	//需要包含#include "CFirmInfoDlg.h"
	CFirmAdminDlg m_page1;
	CFirmInfoDlg m_page2;
public:
	afx_msg void OnTcnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
};


