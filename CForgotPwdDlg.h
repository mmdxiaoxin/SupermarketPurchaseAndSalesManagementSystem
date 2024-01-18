#pragma once
#include "afxdialogex.h"


// CForgotPwdDlg 对话框

class CForgotPwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CForgotPwdDlg)

public:
	CForgotPwdDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CForgotPwdDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_FORGOT_PWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
private:
	CString m_pwd;
	CString m_Rpwd;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
