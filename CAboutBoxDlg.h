#pragma once
#include "afxdialogex.h"


// CAboutBoxDlg 对话框

class CAboutBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutBoxDlg)

public:
	CAboutBoxDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAboutBoxDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
