﻿#pragma once



// CWarnStockDlg 窗体视图

class CWarnStockDlg : public CFormView
{
	DECLARE_DYNCREATE(CWarnStockDlg)

protected:
	CWarnStockDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CWarnStockDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_WARN_STOCK };
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
};


