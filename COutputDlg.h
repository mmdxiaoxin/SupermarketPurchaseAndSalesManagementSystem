#pragma once
#include "afxdialogex.h"


// COutputDlg 对话框

class COutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutputDlg)

public:
	COutputDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COutputDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
