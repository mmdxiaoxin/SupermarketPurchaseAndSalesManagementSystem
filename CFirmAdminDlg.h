#pragma once
#include "afxdialogex.h"


// CFirmAdminDlg 对话框

class CFirmAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmAdminDlg)

public:
	CFirmAdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFirmAdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_FIRM_ADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonAdd();
private:
	CStatic m_caption;
	CComboBox m_combo_name;
	CString m_firm_id;
	CString m_firmInfo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboName();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonChange();
};
