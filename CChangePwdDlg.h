#pragma once
#include "afxdialogex.h"


// CChangePwdDlg 对话框

class CChangePwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePwdDlg)

public:
	CChangePwdDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangePwdDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CHANGE_PWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_OldPwd;
	CString m_NewPwd;
	CString m_RNewPwd;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	virtual void OnOK();
};
