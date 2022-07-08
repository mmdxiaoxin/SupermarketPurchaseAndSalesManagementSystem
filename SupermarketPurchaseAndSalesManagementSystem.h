
// SupermarketPurchaseAndSalesManagementSystem.h: SupermarketPurchaseAndSalesManagementSystem 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号
#include "CPublic.h" //包含公用类头文件

// CSupermarketPurchaseAndSalesManagementSystemApp:
// 有关此类的实现，请参阅 SupermarketPurchaseAndSalesManagementSystem.cpp
//

class CSupermarketPurchaseAndSalesManagementSystemApp : public CWinAppEx
{
public:
	CSupermarketPurchaseAndSalesManagementSystemApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSupermarketPurchaseAndSalesManagementSystemApp theApp;
