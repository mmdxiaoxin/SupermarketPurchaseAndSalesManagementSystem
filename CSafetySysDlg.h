#pragma once
#include "afxdialogex.h"
#include "CForgotPwdDlg.h"

// CSafetySysDlg 对话框

class CSafetySysDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSafetySysDlg)

public:
	CSafetySysDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSafetySysDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_SAFETY_SYS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	CComboBox m_combo;
	CString m_answer;
	CForgotPwdDlg dlg;
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
