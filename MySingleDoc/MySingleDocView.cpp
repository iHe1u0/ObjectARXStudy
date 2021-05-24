
// MySingleDocView.cpp: CMySingleDocView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MySingleDoc.h"
#endif

#include "MySingleDocDoc.h"
#include "MySingleDocView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySingleDocView

IMPLEMENT_DYNCREATE(CMySingleDocView, CView)

BEGIN_MESSAGE_MAP(CMySingleDocView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMySingleDocView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMySingleDocView 构造/析构

CMySingleDocView::CMySingleDocView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMySingleDocView::~CMySingleDocView()
{
}

BOOL CMySingleDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMySingleDocView 绘图

void CMySingleDocView::OnDraw(CDC* /*pDC*/)
{
	CMySingleDocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMySingleDocView 打印


void CMySingleDocView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMySingleDocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMySingleDocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMySingleDocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMySingleDocView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMySingleDocView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMySingleDocView 诊断

#ifdef _DEBUG
void CMySingleDocView::AssertValid() const
{
	CView::AssertValid();
}

void CMySingleDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySingleDocDoc* CMySingleDocView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySingleDocDoc)));
	return (CMySingleDocDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySingleDocView 消息处理程序
