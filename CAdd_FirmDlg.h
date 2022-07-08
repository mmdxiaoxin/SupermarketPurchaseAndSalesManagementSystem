#pragma once



// CAdd_FirmDlg 窗体视图

class CAdd_FirmDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdd_FirmDlg)

protected:
	CAdd_FirmDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdd_FirmDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_FIRM_ADD };
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
	CString m_address;
	CString m_fax;
	CString m_name;
	CString m_phoneNumber;
	CString m_id;
public:
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnPaint();
};


