// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#include "CSelectView.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化 树视图
	
	//图标资源的加载 CWinApp::LoadIcon
	HICON icon[6];
	icon[0] = AfxGetApp()->LoadIconW(IDI_ICON_USER);
	icon[1] = AfxGetApp()->LoadIconW(IDI_ICON_SELL);
	icon[2] = AfxGetApp()->LoadIconW(IDI_ICON_INFO);
	icon[3] = AfxGetApp()->LoadIconW(IDI_ICON_INPUT);
	icon[4] = AfxGetApp()->LoadIconW(IDI_ICON_OUTPUT);
	icon[5] = AfxGetApp()->LoadIconW(IDI_ICON_RECORD);

	//1、准备图片集合
	//30, 30：指定图标的宽度和高度
	//ILC_COLOR32：图标格式
	//6, 6：有多少图标就写多少
	m_imageList.Create(30, 30, ILC_COLOR32,6,6);
	//图片列表追加图标 CImageList::Add
	for (int i = 0; i < 6; i++) {
		//图片列表加载图标
		m_imageList.Add(icon[i]);
	}
	//获取树控件
	m_treeCtrl = &GetTreeCtrl();
	//树控件设置图片列表 CTreeCtrl::SetImageList
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);
	//2、添加节点
	//树控件设置节点 CTreeCtrl::InsertItem
	//注意InsertItem( lpszItem, nImage, nSelectedImage, hParent) nImage, nSelectedImage 的变化
	HTREEITEM root1 = m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
	if (CPublic::GetJurisdiction() != "仓库管理员") 
	{
		HTREEITEM root3 = m_treeCtrl->InsertItem(TEXT("销售管理"), 1, 1, NULL);
	}
	if (CPublic::GetJurisdiction() != "销售员") 
	{
		m_treeCtrl->InsertItem(TEXT("供应商管理"), 1, 1, NULL);
		HTREEITEM root2 = m_treeCtrl->InsertItem(TEXT("库存信息(双击以更改库存)"), 2, 2, NULL);
		m_treeCtrl->InsertItem(TEXT("库存添加"), 3, 3, root2);
		m_treeCtrl->InsertItem(TEXT("库存删除"), 4, 4, root2);
	}
	m_treeCtrl->InsertItem(TEXT("商品信息"), 2, 2, NULL);
	if (CPublic::GetJurisdiction() == "主管")
		m_treeCtrl->InsertItem(TEXT("进销记录"), 5, 5, NULL);

	//设置默认
	m_treeCtrl->SelectItem(root1);
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前节点选中项目 CTreeCtrl::GetSelectedItem
	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//获取选中项的文本内容 CTreeCtrl::GetItemText
	CString str = m_treeCtrl->GetItemText(item);

	if (str == TEXT("个人信息"))
	{
		//需要包含框架类头文件#include "CMainFrm.h" 
		//CWnd::PostMessage 将一个消息放入窗口的消息队列
		//AfxGetMainWnd()：框架窗口对象的指针
		//AfxGetMainWnd()->GetSafeHwnd()：获取返回窗口的句柄，CWnd::GetSafeHwnd
		//NM_A：发送自定义消息
		//(WPARAM)NM_A：指定了附加的消息信息
		//(LPARAM)0：指定了附加的消息信息，此参数这里没有意义
		if (CPublic::GetJurisdiction() == "主管")
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
		else
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_N, (WPARAM)NM_N, (LPARAM)0);
	}
	else if (str == TEXT("销售管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (str == TEXT("库存信息(双击以更改库存)"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (str == TEXT("库存添加"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else if (str == TEXT("库存删除"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
	}
	else if (str == TEXT("进销记录"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_F, (WPARAM)NM_F, (LPARAM)0);
	}
	else if (str == TEXT("供应商管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);
	}
	else if (str == TEXT("商品信息"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_H, (WPARAM)NM_H, (LPARAM)0);
	}
}
