#pragma once
#include "CChangePwdDlg.h"


// CUserDlg 窗体视图

class CUserDlg : public CFormView
{
	DECLARE_DYNCREATE(CUserDlg)

protected:
	CUserDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_USER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_user;
public:
	virtual void OnInitialUpdate();
private:
	CString m_name;
	//需要包含#include "CChangePwdDlg.h"
	CChangePwdDlg dlg;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPaint();
private:
	CFont m_font;
	CStatic m_group;
	CStatic m_group3;
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
private:
	CComboBox m_combo_staff;
	int m_staff_id;
public:
	afx_msg void OnCbnSelchangeComboStaff();
	afx_msg void OnBnClickedButtonFindStaff();
	afx_msg void OnBnClickedButtonDelStaff();
	afx_msg void OnBnClickedButtonChangeStaff();
	afx_msg void OnBnClickedButtonChangeLogin();
};


