#pragma once



// CChangeStaffInfDlg 窗体视图

class CChangeStaffInfDlg : public CFormView
{
	DECLARE_DYNCREATE(CChangeStaffInfDlg)

protected:
	CChangeStaffInfDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CChangeStaffInfDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CHANGE_STAFF };
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
	int m_staff_id;
	CString m_staff_name2;
	CString m_staff_pwd;
	CString m_staff_pwd2;
	CString m_staff_user1;
	CString m_staff_user2;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonCancel();
private:
	CComboBox m_combo_name;
	CComboBox m_combo_jurisidiction2;
	CString m_staff_jurisidiction;
public:
	afx_msg void OnCbnSelchangeComboStaffName();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnPaint();
};


