#pragma once
#include "afxdialogex.h"


// CRegisterDlg 对话框

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
private:
	CComboBox m_combo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPaint();
private:
	CString m_pwd;
	CString m_Rpwd;
	CString m_user;
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton4();
};
