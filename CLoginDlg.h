#pragma once
#include "afxdialogex.h"
#include "CRegisterDlg.h"
#include "CSafetySysDlg.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
private:
	CString m_pwd;
	CString m_user;
	//需要包含#include "CRegisterDlg.h"
	CRegisterDlg dlg;
	//需要包含#include "CSafetySysDlg.h"
	CSafetySysDlg dlg1;
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedChangePwd();
private:
	CButton m_rigister;
};
