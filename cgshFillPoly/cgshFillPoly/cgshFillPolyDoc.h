
// cgshFillPolyDoc.h : CcgshFillPolyDoc ��Ľӿ�
//


#pragma once


class CcgshFillPolyDoc : public CDocument
{
protected: // �������л�����
	CcgshFillPolyDoc();
	DECLARE_DYNCREATE(CcgshFillPolyDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CcgshFillPolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	int m_drawMode;
	float m_caltime;
	float m_polyarea;
	float m_efficiency;
};
