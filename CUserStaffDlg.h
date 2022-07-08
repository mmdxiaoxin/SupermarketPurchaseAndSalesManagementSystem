#pragma once



// CUserStaffDlg 窗体视图

class CUserStaffDlg : public CFormView
{
	DECLARE_DYNCREATE(CUserStaffDlg)

protected:
	CUserStaffDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserStaffDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_USER_STAFF };
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
	virtual void OnInitialUpdate();
private:
	int m_id;
	CString m_jurisidiction;
	CString m_name;
	CString m_user;
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
};


