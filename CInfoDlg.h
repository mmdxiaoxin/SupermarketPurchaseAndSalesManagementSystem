#pragma once



// CInfoDlg 窗体视图

class CInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CInfoDlg)

protected:
	CInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO };
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
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonFind();
private:
	CComboBox m_combo_name1;
	CComboBox m_combo_name2;
	int m_id1;
	int m_id2;
	CString m_name;
public:
	afx_msg void OnBnClickedButtonPut();
	afx_msg void OnCbnSelchangeComboName2();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonPutAll();
	afx_msg void OnBnClickedButtonDownAll();
	afx_msg void OnBnClickedButtonCancel1();
	afx_msg void OnBnClickedButtonCancel2();
	afx_msg void OnBnClickedButtonChange();
};


