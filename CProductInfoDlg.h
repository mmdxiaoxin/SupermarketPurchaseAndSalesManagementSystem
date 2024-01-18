#pragma once



// CProductInfoDlg 窗体视图

class CProductInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CProductInfoDlg)

protected:
	CProductInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CProductInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_PRODUCT_INFO };
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
private:
	CStatic m_caption;
};


