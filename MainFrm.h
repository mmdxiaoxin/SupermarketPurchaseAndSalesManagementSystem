
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

//WM_USER 是用户自定义消息的一个起始值
//WM_USER+100是为了区分系统消息和用户消息，避免冲突
#define NM_A	(WM_USER + 100)//
#define NM_B	(WM_USER + 101)//
#define NM_C	(WM_USER + 102)//
#define NM_D	(WM_USER + 103)//
#define NM_E	(WM_USER + 104)//
#define NM_F	(WM_USER + 105)//
#define NM_G	(WM_USER + 106)//
#define NM_H	(WM_USER + 107)//
#define NM_I	(WM_USER + 108)//
#define NM_J	(WM_USER + 109)//
#define NM_K	(WM_USER + 110)//
#define NM_L	(WM_USER + 111)//修改员工信息
#define NM_M	(WM_USER + 112)//添加供应商信息
#define NM_N	(WM_USER + 113)//职工信息窗口

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
private:
	CSplitterWnd m_splitter;
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32775();
	afx_msg void On32774();
	afx_msg void On32776();
	afx_msg void On32777();
	afx_msg void On32771();
	afx_msg void On32779();
	afx_msg void On32778();
};


