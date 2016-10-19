// PlateIdentifyDoc.h : CPlateIdentifyDoc 类的接口
//

#include "MyImg.h"
#include "ImageFUNC.h"
#include "MainFrm.h"
#include "Image_thin.h"
#include "Classification.h"
#include "afx.h" 
#include "afxwin.h"

#pragma once


const int g_width=20;                      //设置归一化的宽度 
const int g_height=40;					   //设置归一化的高度 
class CPlateIdentifyDoc : public CDocument
{
protected: // 仅从序列化创建
	CPlateIdentifyDoc();
	DECLARE_DYNCREATE(CPlateIdentifyDoc)

// 属性
public:
	IplImage *src_image; //原始车辆图像像
	IplImage *gray_image; //原始灰度图像
	IplImage *plate_image;//分割出的车牌图像
	IplImage * dst_image[7];//存放归一化后的字符的图像数组,
	
	ImageFUNC m_Func;//图像处理函数对象
	myimg m_Cimage; //显示图像对象
	ImgThin m_thin;  //图像细化对象
	CMainFrame m_frame;
	

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CPlateIdentifyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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


