// CgSelectBox.cpp : ʵ���ļ�
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


// CCgSelectBox ���

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


// CCgSelectBox ��Ϣ�������


void CCgSelectBox::OnBnClickedOrder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 0;

	pDoc->UpdateAllViews(this);
	

}


void CCgSelectBox::OnBnClickedSeed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 1;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedEverypoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 2;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedPattern()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 3;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnBnClickedEarclipping()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	pDoc->m_drawMode = 4;

	pDoc->UpdateAllViews(this);
}


void CCgSelectBox::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();
	CString ans;
	ans.Format(_T("%.5f"), pDoc -> m_caltime / pDoc -> m_polyarea);
	this->efficiency = ans;
	UpdateData(FALSE);
}
