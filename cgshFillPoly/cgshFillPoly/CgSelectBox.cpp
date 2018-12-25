// CgSelectBox.cpp : 实现文件
//

#include "stdafx.h"
#include "cgshFillPoly.h"
#include "CgSelectBox.h"
#include "cgshFillPolyView.h"
#include "cgshFillPolyDoc.h"


// CCgSelectBox

IMPLEMENT_DYNCREATE(CCgSelectBox, CFormView)

CCgSelectBox::CCgSelectBox()
	: CFormView(IDD_SELECTBOX)
	, efficiency(_T(""))
{

}

CCgSelectBox::~CCgSelectBox()
{
}

void CCgSelectBox::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EFFICIENCY, efficiency);
}

BEGIN_MESSAGE_MAP(CCgSelectBox, CFormView)
	ON_BN_CLICKED(IDC_ORDER, &CCgSelectBox::OnBnClickedOrder)
	ON_BN_CLICKED(IDC_SEED, &CCgSelectBox::OnBnClickedSeed)
	ON_BN_CLICKED(IDD_EVERYPOINT, &CCgSelectBox::OnBnClickedEverypoint)
	ON_BN_CLICKED(IDD_PATTERN, &CCgSelectBox::OnBnClickedPattern)
	ON_BN_CLICKED(IDD_EARCLIPPING, &CCgSelectBox::OnBnClickedEarclipping)
END_MESSAGE_MAP()


// CCgSelectBox 诊断

#ifdef _DEBUG
void CCgSelectBox::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgSelectBox::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgSelectBox 消息处理程序


void CCgSelectBox::OnBnClickedOrder()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 0;

	pDoc->UpdateAllViews(this);
	

}


void CCgSelectBox::OnBnClickedSeed()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 1;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedEverypoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 2;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedPattern()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 3;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedEarclipping()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 4;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();
	CString ans;
	ans.Format(_T("%.5f"), pDoc -> m_caltime / pDoc -> m_polyarea);
	this->efficiency = ans;
	UpdateData(FALSE);
}
