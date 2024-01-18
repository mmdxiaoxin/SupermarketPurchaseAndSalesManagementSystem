#pragma once
#include "afxdialogex.h"


// CChangeFirmDlg 对话框

class CChangeFirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeFirmDlg)

public:
	CChangeFirmDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangeFirmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CHANGE_FIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CStatic m_caption;
	CString m_id;
	CString m_name;
	CString m_address;
	CString m_phoneNumber;
	CString m_fax;
public:
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnPaint();
};
