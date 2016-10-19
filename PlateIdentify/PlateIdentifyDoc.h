// PlateIdentifyDoc.h : CPlateIdentifyDoc ��Ľӿ�
//

#include "MyImg.h"
#include "ImageFUNC.h"
#include "MainFrm.h"
#include "Image_thin.h"
#include "Classification.h"
#include "afx.h" 
#include "afxwin.h"

#pragma once


const int g_width=20;                      //���ù�һ���Ŀ�� 
const int g_height=40;					   //���ù�һ���ĸ߶� 
class CPlateIdentifyDoc : public CDocument
{
protected: // �������л�����
	CPlateIdentifyDoc();
	DECLARE_DYNCREATE(CPlateIdentifyDoc)

// ����
public:
	IplImage *src_image; //ԭʼ����ͼ����
	IplImage *gray_image; //ԭʼ�Ҷ�ͼ��
	IplImage *plate_image;//�ָ���ĳ���ͼ��
	IplImage * dst_image[7];//��Ź�һ������ַ���ͼ������,
	
	ImageFUNC m_Func;//ͼ����������
	myimg m_Cimage; //��ʾͼ�����
	ImgThin m_thin;  //ͼ��ϸ������
	CMainFrame m_frame;
	

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPlateIdentifyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnUpdatePlateextract(CCmdUI *pCmdUI);
	afx_msg void OnPlateextract();
	afx_msg void OnUpdateRevise(CCmdUI *pCmdUI);
	afx_msg void OnRevise();
	afx_msg void OnUpdateSplit(CCmdUI *pCmdUI);
	afx_msg void OnSplit();
	afx_msg void OnUpdateCharidentify(CCmdUI *pCmdUI);
	afx_msg void OnCharidentify();
};


