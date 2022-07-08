#pragma once



// CAdd_Dlg 窗体视图

class CAdd_Dlg : public CFormView
{
	DECLARE_DYNCREATE(CAdd_Dlg)

protected:
	CAdd_Dlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdd_Dlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADD };
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
	CComboBox m_combo;
public:
	afx_msg void OnBnClickedButton4();
private:
	int m_num1;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
private:
	CString m_name2;
	int m_num2;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
private:
	CStatic m_caption;
	CFont m_font;
	CStatic m_group1;
	CStatic m_group2;
	CFont m_font_group;
	double m_out_price2;
	int kind;
	double m_in_price2;
	double m_in_price1;
	int m_firmID;
public:
	afx_msg void OnBnClickedButton7();
};


