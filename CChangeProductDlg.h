#pragma once
#include "afxdialogex.h"


// CChangeProductDlg 对话框

class CChangeProductDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeProductDlg)

public:
	CChangeProductDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangeProductDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CHANGE_PRODUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChange();
private:
	int m_firmID;
	double m_in_price;
	int m_kind;
	CString m_name;
	int m_num;
	double m_out_price;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnPaint();
};
