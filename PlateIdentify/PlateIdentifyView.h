// PlateIdentifyView.h : CPlateIdentifyView ��Ľӿ�
//


#pragma once


class CPlateIdentifyView : public CView
{
protected: // �������л�����
	CPlateIdentifyView();
	DECLARE_DYNCREATE(CPlateIdentifyView)

// ����
public:
	CPlateIdentifyDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlateIdentifyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PlateIdentifyView.cpp �еĵ��԰汾
inline CPlateIdentifyDoc* CPlateIdentifyView::GetDocument() const
   { return reinterpret_cast<CPlateIdentifyDoc*>(m_pDocument); }
#endif

