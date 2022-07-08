#pragma once



// CChangeSafetyDlg 窗体视图

class CChangeSafetyDlg : public CFormView
{
	DECLARE_DYNCREATE(CChangeSafetyDlg)

protected:
	CChangeSafetyDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CChangeSafetyDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CHANGE_SAFETY };
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
	CComboBox m_combo_Safety;
	CString m_ans1;
	CString m_ans2;
	CString m_ans1_Old;
	CString m_question;
public:
	afx_msg void OnBnClickedButtonCancel1();
	afx_msg void OnBnClickedButtonCancel2();
	afx_msg void OnBnClickedButtonOk1();
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeComboSafety();
	afx_msg void OnBnClickedButtonOk2();
	afx_msg void OnPaint();
private:
	CStatic m_caption;
};


