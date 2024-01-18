
// SupermarketPurchaseAndSalesManagementSystemView.cpp: CSupermarketPurchaseAndSalesManagementSystemView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SupermarketPurchaseAndSalesManagementSystem.h"
#endif

#include "SupermarketPurchaseAndSalesManagementSystemDoc.h"
#include "SupermarketPurchaseAndSalesManagementSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSupermarketPurchaseAndSalesManagementSystemView

IMPLEMENT_DYNCREATE(CSupermarketPurchaseAndSalesManagementSystemView, CView)

BEGIN_MESSAGE_MAP(CSupermarketPurchaseAndSalesManagementSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// CSupermarketPurchaseAndSalesManagementSystemView 构造/析构

CSupermarketPurchaseAndSalesManagementSystemView::CSupermarketPurchaseAndSalesManagementSystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSupermarketPurchaseAndSalesManagementSystemView::~CSupermarketPurchaseAndSalesManagementSystemView()
{
}

BOOL CSupermarketPurchaseAndSalesManagementSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSupermarketPurchaseAndSalesManagementSystemView 绘图

void CSupermarketPurchaseAndSalesManagementSystemView::OnDraw(CDC* /*pDC*/)
{
	CSupermarketPurchaseAndSalesManagementSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSupermarketPurchaseAndSalesManagementSystemView 打印

BOOL CSupermarketPurchaseAndSalesManagementSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSupermarketPurchaseAndSalesManagementSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSupermarketPurchaseAndSalesManagementSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSupermarketPurchaseAndSalesManagementSystemView 诊断

#ifdef _DEBUG
void CSupermarketPurchaseAndSalesManagementSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSupermarketPurchaseAndSalesManagementSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSupermarketPurchaseAndSalesManagementSystemDoc* CSupermarketPurchaseAndSalesManagementSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSupermarketPurchaseAndSalesManagementSystemDoc)));
	return (CSupermarketPurchaseAndSalesManagementSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CSupermarketPurchaseAndSalesManagementSystemView 消息处理程序



