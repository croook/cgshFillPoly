#pragma once



// CCgSelectBox ������ͼ

class CCgSelectBox : public CFormView
{
	DECLARE_DYNCREATE(CCgSelectBox)

protected:
	CCgSelectBox();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCgSelectBox();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTBOX };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOrder();
	afx_msg void OnBnClickedSeed();
	afx_msg void OnBnClickedEverypoint();
	afx_msg void OnBnClickedPattern();
	afx_msg void OnBnClickedEarclipping();
	CString efficiency;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


