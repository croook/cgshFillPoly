
// cgshFillPolyView.h : CcgshFillPolyView 类的接口
//

#pragma once
#include <vector>
#include "cgshFillPolyDoc.h"

struct BoxRect_t {
	int minX;
	int minY;
	int maxX;
	int maxY;
};

class CcgshFillPolyView : public CView
{
protected: // 仅从序列化创建
	CcgshFillPolyView();
	DECLARE_DYNCREATE(CcgshFillPolyView)

public:
	CcgshFillPolyDoc * GetDocument() const;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CcgshFillPolyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	std::vector<CPoint> m_polygon;
	CPoint m_mousePoint;
	int m_Begin, m_End, m_edgeNumbers, m_Scan;
	std::vector<float> m_yMax, m_yMin, m_Xa, m_Dx;

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	float CalArea(std::vector<CPoint> m_polygon);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	bool InTrigon(std::vector<CPoint> m_polygon, int i, int point);
	int IsASalientPoint(std::vector<CPoint> m_polygon, int i);
	bool IsAnEar(std::vector<CPoint> m_polygon, int flagpolygon, int i);
	void EarClippling(std::vector<CPoint> m_polygon, CDC * pDC);
	void Fillpolygon(std::vector<CPoint> m_polygon, CDC * pDC);
	void pLoadPolygon(std::vector<CPoint> m_polygon);
	void pInsertLine(float x1, float y1, float x2, float y2);
	void Include();
	void UpdateXvalue();
	void pXsort(int Begin, int i);
	void pFillScan(CDC * pDC);
	void SeedFill(CDC * pDC, CPoint point, int color0);
	void pointfillpoly(std::vector<CPoint> m_polygon, CDC * pDC);
	BoxRect_t GetPolygonRect(std::vector<CPoint> m_polygon);
	BOOL PointInPolygon(std::vector<CPoint> m_polygon, CPoint testPoint);
};

#ifndef _DEBUG  // cgshFillPolyView.cpp 中的调试版本
inline CcgshFillPolyDoc* CcgshFillPolyView::GetDocument() const
   { return reinterpret_cast<CcgshFillPolyDoc*>(m_pDocument); }
#endif

