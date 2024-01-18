#pragma once



// CAdd_StaffDlg 窗体视图

class CAdd_StaffDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdd_StaffDlg)

protected:
	CAdd_StaffDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdd_StaffDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADD_STAFF };
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
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton4();
private:
	CString m_staff_name;
	CString m_staff_pwd;
	CString m_staff_user;
	CComboBox m_combo_jurisidiction;
public:
	virtual void OnInitialUpdate();
};


