#pragma once
#include "afxdialogex.h"


// CFirmInfoDlg 对话框

class CFirmInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmInfoDlg)

public:
	CFirmInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFirmInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_FIRM_INF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	CListCtrl m_list;
	CString m_firm_id;
	CString m_firm_name;
	CString m_firm_address;
	CString m_firm_phoneNumber;
	CString m_firm_fax;
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFirmFind();
	afx_msg void OnBnClickedButtonFirmReset();
	virtual void OnOK();
};
