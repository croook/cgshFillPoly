
// cgshFillPolyView.cpp :  CcgshFillPolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgshFillPoly.h"
#endif

#include "cgshFillPolyDoc.h"
#include "cgshFillPolyView.h"
#include "CgSelectBox.h"
//#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//  CcgshFillPolyView

IMPLEMENT_DYNCREATE( CcgshFillPolyView, CView)

BEGIN_MESSAGE_MAP( CcgshFillPolyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//  CcgshFillPolyView 构造/析构

 CcgshFillPolyView:: CcgshFillPolyView()
{
	// TODO: 在此处添加构造代码
}

 CcgshFillPolyView::~ CcgshFillPolyView()
{
}

BOOL  CcgshFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

//  CcgshFillPolyView 绘制

void  CcgshFillPolyView::OnDraw(CDC* /*pDC*/)
{
	CcgshFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	
	if (m_polygon.size() > 2) {
		for (int i = 0; i < m_polygon.size() - 1; i++) {
			dc.MoveTo(m_polygon[i]);
			dc.LineTo(m_polygon[i + 1]);
		}
		dc.MoveTo(m_polygon.back());
		dc.LineTo(m_polygon.front());
	}
	
	// TODO: 在此处为本机数据添加绘制代码
}


//  CcgshFillPolyView 打印

BOOL  CcgshFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void  CcgshFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void  CcgshFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


//  CcgshFillPolyView 诊断

#ifdef _DEBUG
void  CcgshFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void  CcgshFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgshFillPolyDoc*  CcgshFillPolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgshFillPolyDoc)));
	return (CcgshFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


//  CcgshFillPolyView 消息处理程序


void  CcgshFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (!m_polygon.empty()) {

		CClientDC dc(this);
		dc.SetROP2(2);
		dc.MoveTo(m_polygon.back());
		dc.LineTo(m_mousePoint);

		dc.MoveTo(m_polygon.back());
		dc.LineTo(point);
		m_mousePoint = point;
	}

	CView::OnMouseMove(nFlags, point);
}

float  CcgshFillPolyView::CalArea(std::vector <CPoint> m_polygon) {
	float sum = 0;
	for (int j = 0; j < m_polygon.size() - 1; j++) {
		sum += -0.5 * (m_polygon[j].y + m_polygon[j + 1].y) * (m_polygon[j + 1].x - m_polygon[j].x);
	}
	return  fabs(sum);
}

void  CcgshFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CcgshFillPolyDoc* pDC =(CcgshFillPolyDoc * )GetDocument();
	CClientDC dc(this);
	dc.MoveTo(m_polygon.back());
	dc.LineTo(m_polygon.front());

	m_polygon.push_back(m_polygon[0]);

	int opStart, opFinish;

	if (pDC -> m_drawMode == 0 || pDC->m_drawMode == 3) {

		opStart = GetTickCount();

		Fillpolygon(m_polygon, &dc);

		opFinish = GetTickCount();
		pDC -> m_caltime = opFinish - opStart;
		pDC->m_polyarea = CalArea(m_polygon);
		pDC -> UpdateAllViews(this);
	}

	else if (pDC -> m_drawMode == 1) {

		BoxRect_t box;
		box = GetPolygonRect(m_polygon);

		CPoint p;
		p.y = (box.maxY + box.minY) / 2;

		for (p.x = box.minX; p.x < box.maxX; p.x++) {

				if (PointInPolygon(m_polygon, p) && dc.GetPixel(p.x , p.y) != RGB(0,0,0)) {
					break;
				}
		}
		opStart = GetTickCount();

		SeedFill(&dc, p, RGB(0, 0, 0));

		opFinish = GetTickCount();
		pDC->m_caltime = opFinish - opStart;
		pDC->m_polyarea = CalArea(m_polygon);
		pDC->UpdateAllViews(this);
	}

	else if(pDC->m_drawMode == 2){
		opStart = GetTickCount();

		pointfillpoly(m_polygon, &dc);

		opFinish = GetTickCount();
		pDC->m_caltime = opFinish - opStart;
		pDC->m_polyarea = CalArea(m_polygon);
		pDC->UpdateAllViews(this);
	}
	else {
		std::vector <CPoint> copy(m_polygon);
		EarClippling(copy, &dc);
	}

	m_polygon.clear();
	CView::OnLButtonDblClk(nFlags, point);
}


void  CcgshFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_polygon.push_back(point);
	m_mousePoint = point;

	CView::OnLButtonDown(nFlags, point);
}
//ear clippling

bool  CcgshFillPolyView::InTrigon(std::vector <CPoint> m_polygon, int i, int point) {
	//if (a.x - c.x)*(b.y - c.y) - (a.y - c.y)*(b.x - c.x) > 0 , c locate in ab's left

	if ((m_polygon[i - 1].x - m_polygon[point].x)*(m_polygon[i].y - m_polygon[point].y) - (m_polygon[i - 1].y - m_polygon[point].y)*(m_polygon[i].x - m_polygon[point].x) > 0) {
		if ((m_polygon[i].x - m_polygon[point].x)*(m_polygon[i + 1].y - m_polygon[point].y) - (m_polygon[i].y - m_polygon[point].y)*(m_polygon[i + 1].x - m_polygon[point].x) > 0) {
			if ((m_polygon[i + 1].x - m_polygon[point].x)*(m_polygon[i - 1].y - m_polygon[point].y) - (m_polygon[i + 1].y - m_polygon[point].y)*(m_polygon[i - 1].x - m_polygon[point].x) > 0) {
				return true;
			}
		}
	}
	if ((m_polygon[i - 1].x - m_polygon[point].x)*(m_polygon[i].y - m_polygon[point].y) - (m_polygon[i - 1].y - m_polygon[point].y)*(m_polygon[i].x - m_polygon[point].x) < 0) {
		if ((m_polygon[i].x - m_polygon[point].x)*(m_polygon[i + 1].y - m_polygon[point].y) - (m_polygon[i].y - m_polygon[point].y)*(m_polygon[i + 1].x - m_polygon[point].x) < 0) {
			if ((m_polygon[i + 1].x - m_polygon[point].x)*(m_polygon[i - 1].y - m_polygon[point].y) - (m_polygon[i + 1].y - m_polygon[point].y)*(m_polygon[i - 1].x - m_polygon[point].x) < 0) {
				return true;
			}
		}
	}

	return false;
}

int CcgshFillPolyView::IsASalientPoint(std::vector <CPoint> m_polygon, int i) {

	//(vPts[i + 1].y + vPts[i].y)*(vPts[i + 1].x - vPts[i].x)
	int flagpoint = -1;
	if ((m_polygon[i].x - m_polygon[i - 1].x) * (m_polygon[i + 1].y - m_polygon[i].y) - (m_polygon[i + 1].x - m_polygon[i].x) * (m_polygon[i].y - m_polygon[i - 1].y) > 0) flagpoint = 1;

	return (flagpoint);

}

bool  CcgshFillPolyView::IsAnEar(std::vector <CPoint> m_polygon,int flagpolygon , int i) {

	//point 0 stay at the end , because a n-point polygon just have to cut n-3 ears

	if (IsASalientPoint(m_polygon,i) * flagpolygon > 0) {
		for (int j = 0; j < m_polygon.size()-1; j++) {
			if (j == i - 1 || j == i || j == i + 1) {
				continue;
			}
			else if(InTrigon(m_polygon,i,j)){
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void  CcgshFillPolyView::EarClippling(std::vector <CPoint> m_polygon,CDC *pDC) {

	float sum = 0;
	int flagpolygon = -1;
	for (int j = 0; j < m_polygon.size() - 1; j++) {
		sum += -0.5 * (m_polygon[j].y + m_polygon[j + 1].y) * (m_polygon[j + 1].x - m_polygon[j].x);
	}
	if (sum > 0) flagpolygon = 1;



	for (int i = 1; i < m_polygon.size()-1; i++) {
		if (IsAnEar(m_polygon,flagpolygon, i)) {
			pDC -> MoveTo(m_polygon[i - 1]);
			pDC -> LineTo(m_polygon[i + 1]);
			m_polygon.erase(m_polygon.begin()+i);
			EarClippling(m_polygon, pDC);
			return;
		}
	}

}

//FillPolygon

void CcgshFillPolyView::Fillpolygon(std::vector <CPoint> m_polygon, CDC *pDC)
{

	m_edgeNumbers = 0;
	pLoadPolygon(m_polygon);   // Polygon Loading, calculates every edge's m_yMax[],m_yMin[],m_Xa[],m_Dx[]

	m_Begin = m_End = 0;              // Initializing intersect edge set
	m_Scan = (int)m_yMax[0];          // Initial scan-line
	Include();                        // Checking whether exist enter intersecting.
	UpdateXvalue();                   // Calculating intersect point
	while (m_Begin != m_End) {
		pFillScan(pDC);
		m_Scan--;
		Include();
		UpdateXvalue();
	}

}

void CcgshFillPolyView::pLoadPolygon(std::vector <CPoint> m_polygon)
{
	float x1, y1, x2, y2;

	x1 = m_polygon[0].x;    y1 = m_polygon[0].y + 0.5;
	for (int i = 1; i < m_polygon.size(); i++) {
		x2 = m_polygon[i].x;    y2 = m_polygon[i].y + 0.5;
		/* fill the right condition below */
		if (y1 != y2) pInsertLine(x1, y1, x2, y2);
		x1 = x2;      y1 = y2;
	}
}

void CcgshFillPolyView::pInsertLine(float x1, float y1,float x2, float y2)
{
	int i;
	float Ymax, Ymin;

	Ymax = (y2 > y1) ? y2 : y1;
	Ymin = (y2 < y1) ? y2 : y1;
	i = m_edgeNumbers;
	/* fill the right condition code below */
	while (i > 0 && Ymax > m_yMax[i - 1] /* uncomparing to the begin && current line's yMax less than the last */) {
		i--;
	}
	m_yMax.insert(m_yMax.begin()+i,Ymax);
	m_yMin.insert(m_yMin.begin()+i,Ymin);
	if (y2 > y1) m_Xa.insert(m_Xa.begin()+i,x2);
	else         m_Xa.insert(m_Xa.begin()+i,x1);

	/* fill the right calculation code below */
	m_Dx.insert(m_Dx.begin()+i, (x2 - x1) / (y2 - y1))  /* current line's 1/m */;
	m_edgeNumbers++;
}

void CcgshFillPolyView::Include()
{
	/* fill the right condition code below */
	while (m_End < m_edgeNumbers && m_Scan < m_yMax[m_End]/* Have exist edge &&  m_scan less than m_End line's yMax */) {
		m_Xa[m_End] = m_Xa[m_End] - 0.5*m_Dx[m_End];
		m_Dx[m_End] = -m_Dx[m_End];
		m_End++;
	}
}

void CcgshFillPolyView::UpdateXvalue()
{
	int i, start = m_Begin;

	for (i = start; i < m_End; i++) {
		if (m_Scan > m_yMin[i]) { //have intersection
								  /* fill the right calculation code below */
			m_Xa[i] += m_Dx[i];       /* Calculating intersect point x value */;
			pXsort(m_Begin, i);
		}
		else {
			for (int j = i; j > m_Begin; j--) {
				m_yMin[j] = m_yMin[j - 1];
				m_Xa[j] = m_Xa[j - 1];
				m_Dx[j] = m_Dx[j - 1];
				//m_yMax[j] = m_yMax[j - 1];
			}
			m_Begin++;
		}
	}

}

bool SortUp(int v1, int v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{
	return v1 < v2; //升序排列  
}

void CcgshFillPolyView::pXsort(int Begin, int i)
{
	float temp;

	while (i > Begin && m_Xa[i] < m_Xa[i - 1]) {
		temp = m_Xa[i];   m_Xa[i] = m_Xa[i - 1];   m_Xa[i - 1] = temp;
		temp = m_Dx[i];   m_Dx[i] = m_Dx[i - 1];   m_Dx[i - 1] = temp;
		temp = m_yMin[i]; m_yMin[i] = m_yMin[i - 1]; m_yMin[i - 1] = temp;
		//temp = m_yMax[i]; m_yMax[i] = m_yMax[i - 1]; m_yMax[i - 1] = temp;
		i--;
	}
}

int m_patternData[7][8]{
	0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,

};

void CcgshFillPolyView::pFillScan(CDC* pDC)
{
	int x, y;
	CcgshFillPolyDoc* pDoc = GetDocument();


	for (int i = m_Begin; i < m_End; i += 2) {

		pDC->SetROP2(10);

		if (pDoc -> m_drawMode == 0) {
			pDC->MoveTo(m_Xa[i], m_Scan);
			pDC->LineTo(m_Xa[i + 1], m_Scan);

		}
		else {
			y = m_Scan;
			for (int x = m_Xa[i]; x < m_Xa[i + 1]; x++)
				if (m_patternData[y % 7][x % 8])
					pDC->SetPixel(x, y, RGB(255, 0, 0));
		}

	}

}

//Seed Fill

void CcgshFillPolyView::SeedFill(CDC* pDC, CPoint point, int color)
{

	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	std::vector <CPoint> Stack;
	CPoint po;

	int clr;
	int x, y, x0, y0, xl, xr, flag, xnextspan;
	pDC->SetROP2(10);
	x = point.x;
	y = point.y;
	y0 = y;

	po.x = x; po.y = y;
	Stack.push_back(po);

	pDC->SetPixel(x, y, color); //color is the color of border , clr is the fill color
	while (!Stack.empty())
	{
		x = Stack.back().x;
		y = Stack.back().y;
		Stack.pop_back();
		clr = pDC->SetPixel(x, y, RGB(0, 0, 0));
		x0 = x + 1;
		while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr)
		{
			pDC->SetPixel(x0, y, clr);
			x0++;
		}
		xr = x0 - 1;
		x0 = x - 1;
		while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr)
		{
			pDC->SetPixel(x0, y, clr);
			x0--;
		}
		xl = x0 + 1;

		x0 = xl;
		y = y + 1;
		
		while(x0 <= xr) {

			while ((pDC->GetPixel(x0, y) == color || pDC->GetPixel(x0, y) == clr) && x0 <= xr) {
				x0++;
			}
			if (x0 == xr + 1) break;
			else {
				while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr && x0 <= xr) {
					if (x0 == xr) {
						po.x = x0; po.y = y;
						Stack.push_back(po);
					}
					else if (pDC->GetPixel(x0 + 1, y) == color || pDC->GetPixel(x0 + 1, y) == clr) {
						po.x = x0; po.y = y;
						Stack.push_back(po);
					}
					x0++;
				}
			}
		}
		
		x0 = xl;
		y = y - 2;
		while (x0 <= xr) {

			while ((pDC->GetPixel(x0, y) == color || pDC->GetPixel(x0, y) == clr) && x0 <= xr) {
				x0++;
			}
			if (x0 == xr + 1) break;
			else {
				while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr && x0 <= xr) {
					if (x0 == xr) {
						po.x = x0; po.y = y;
						Stack.push_back(po);
					}
					else if (pDC->GetPixel(x0 + 1, y) == color || pDC->GetPixel(x0 + 1, y) == clr) {
						po.x = x0; po.y = y;
						Stack.push_back(po);
					}
					x0++;
				}
			}
		}
	}
}

/*
void CcgshFillPolyView::SeedFill(CDC* pDC, CPoint point, int color)
{

	CcgshFillPolyDoc* pDoc = (CcgshFillPolyDoc*)GetDocument();

	std::vector <CPoint> Stack;
	CPoint po;

	int clr;
	int x, y, x0, y0, xl, xr, flag, xnextspan;
	pDC->SetROP2(10);
	x = point.x;
	y = point.y;
	y0 = y;

	po.x = x; po.y = y;
	Stack.push_back(po);

	pDC->SetPixel(x, y, color); //color is the color of border , clr is the fill color
	while (!Stack.empty())
	{
		x = Stack.back().x;
		y = Stack.back().y;
		Stack.pop_back();
		clr = pDC->SetPixel(x, y, RGB(0, 0, 0));
		x0 = x + 1;
		while (pDC->GetPixel(x0, y) != color)
		{
			pDC->SetPixel(x0, y, clr);
			x0++;
		}
		xr = x0 - 1;
		x0 = x - 1;
		while (pDC->GetPixel(x0, y) != color)
		{
			pDC->SetPixel(x0, y, clr);
			x0--;
		}
		xl = x0 + 1;

		x0 = xl;
		y = y + 1;
		while (x0 <= xr)
		{
			flag = 0;
			while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr &&  x0<xr)
			{
				if (flag == 0) flag = 1;
				x0++;
			}
			if (flag == 1)
			{
				if (x0 == xr && pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr) {
					po.x = x0; po.y = y;
					Stack.push_back(po);
				}
				else {
					po.x = x0 - 1; po.y = y;
					Stack.push_back(po);
				}

				flag = 0;
			}
			xnextspan = x0;
			while (pDC->GetPixel(x0, y) == color || pDC->GetPixel(x0, y) == clr &&  x0 <= xr)
				x0++;
			if (xnextspan == x0) x0++;
		}

		x0 = xl;
		y = y - 2;
		while (x0 <= xr)
		{
			flag = 0;
			while (pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr &&  x0<xr)
			{
				if (flag == 0) flag = 1;
				x0++;
			}
			if (flag == 1)
			{
				if (x0 == xr && pDC->GetPixel(x0, y) != color && pDC->GetPixel(x0, y) != clr) {
					po.x = x0; po.y = y;
					Stack.push_back(po);
				}

				else {
					po.x = x0 - 1; po.y = y;
					Stack.push_back(po);
				}

				flag = 0;
			}
			xnextspan = x0;
			while (pDC->GetPixel(x0, y) == color || pDC->GetPixel(x0, y) == clr &&  x0 <= xr)
				x0++;
			if (xnextspan == x0) x0++;
		}
	}
}
*/
//everypoint

void  CcgshFillPolyView::pointfillpoly(std::vector<CPoint> m_polygon, CDC *pDC)
{
	BoxRect_t polyrect;

	polyrect = GetPolygonRect(m_polygon);

	pDC->MoveTo(polyrect.minX, polyrect.minY);
	pDC->LineTo(polyrect.minX, polyrect.maxY);
	pDC->LineTo(polyrect.maxX, polyrect.maxY);
	pDC->LineTo(polyrect.maxX, polyrect.minY);
	pDC->LineTo(polyrect.minX, polyrect.minY);

	CPoint testpoint;

	for (testpoint.x = polyrect.minX; testpoint.x < polyrect.maxX; testpoint.x++)
		for (testpoint.y = polyrect.minY; testpoint.y < polyrect.maxY; testpoint.y++) {

			if (PointInPolygon(m_polygon, testpoint))
				pDC->SetPixel(testpoint.x, testpoint.y, RGB(255, 0, 0));
		}
}


BoxRect_t  CcgshFillPolyView::GetPolygonRect(std::vector<CPoint> m_polygon)
{
	BoxRect_t boxRect;

	boxRect.minX = 50000;
	boxRect.minY = 50000;
	boxRect.maxX = -50000;
	boxRect.maxY = -50000;

	for (int i = 0; i < m_polygon.size(); i++) {
		if (m_polygon[i].x < boxRect.minX) boxRect.minX = m_polygon[i].x;
		if (m_polygon[i].y < boxRect.minY) boxRect.minY = m_polygon[i].y;
		if (m_polygon[i].x > boxRect.maxX) boxRect.maxX = m_polygon[i].x;
		if (m_polygon[i].y > boxRect.maxY) boxRect.maxY = m_polygon[i].y;
	}
	return boxRect;
}

BOOL  CcgshFillPolyView::PointInPolygon(std::vector<CPoint> m_polygon,CPoint testPoint)
{
	if (m_polygon.size() < 3) return false;

	bool  inSide = FALSE;
	float lineSlope, interSectX;
	int   i = 0, j = m_polygon.size() - 1;

	for (i = 0; i < m_polygon.size(); i++) {
		if ((m_polygon[i].y < testPoint.y && m_polygon[j].y >= testPoint.y ||
			m_polygon[j].y < testPoint.y && m_polygon[i].y >= testPoint.y) &&
			(m_polygon[i].x <= testPoint.x || m_polygon[j].x <= testPoint.x)) {

			if (m_polygon[j].x != m_polygon[i].x) {
				lineSlope = (float)(m_polygon[j].y - m_polygon[i].y) / (m_polygon[j].x - m_polygon[i].x);
				interSectX = (int)(m_polygon[i].x + (testPoint.y - m_polygon[i].y) / lineSlope);
			}
			else interSectX = m_polygon[i].x;
			if (interSectX < testPoint.x)	inSide = !inSide; //if the number of intersec is odd, the testpoint is inside
		}
		j = i;
	}

	return inSide;
}
