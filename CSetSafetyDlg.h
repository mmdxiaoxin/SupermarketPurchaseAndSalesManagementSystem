#pragma once
#include "afxdialogex.h"


// CSetSafetyDlg 对话框

class CSetSafetyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSafetyDlg)

public:
	CSetSafetyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetSafetyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_SET_SAFETY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_combo_safety;
	CString m_ans1_Old;
public:
	afx_msg void OnBnClickedButtonOk1();
private:
	CString m_ans1;
public:
	afx_msg void OnBnClickedButtonCancel1();
	afx_msg void OnBnClickedButtonOk2();
private:
	CString m_question;
	CString m_ans2;
public:
	afx_msg void OnBnClickedButtonCancel2();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboSafety();
};
