// PlateIdentifyView.cpp : CPlateIdentifyView ���ʵ��
//

#include "stdafx.h"
#include "PlateIdentify.h"

#include "PlateIdentifyDoc.h"
#include "PlateIdentifyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlateIdentifyView

IMPLEMENT_DYNCREATE(CPlateIdentifyView, CView)

BEGIN_MESSAGE_MAP(CPlateIdentifyView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPlateIdentifyView ����/����

CPlateIdentifyView::CPlateIdentifyView()
{
	// TODO: �ڴ˴���ӹ������

}

CPlateIdentifyView::~CPlateIdentifyView()
{
}

BOOL CPlateIdentifyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlateIdentifyView ����

void CPlateIdentifyView::OnDraw(CDC* pDC)
{
	CPlateIdentifyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	myimg & img=pDoc->m_Cimage;
    CRect m_rect;
    GetClientRect(&m_rect) ;
    //����ͼ��Ŀ�Ⱥ͸߶ȣ��ܹ�����ԭʼ��С��ʾ
    m_rect.right=img.Width();
    m_rect.bottom=img.Height();
    img.DrawToHDC(pDC->GetSafeHdc(),m_rect);
}


// CPlateIdentifyView ��ӡ

BOOL CPlateIdentifyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlateIdentifyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlateIdentifyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlateIdentifyView ���

#ifdef _DEBUG
void CPlateIdentifyView::AssertValid() const
{
	CView::AssertValid();
}

void CPlateIdentifyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlateIdentifyDoc* CPlateIdentifyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlateIdentifyDoc)));
	return (CPlateIdentifyDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlateIdentifyView ��Ϣ�������
