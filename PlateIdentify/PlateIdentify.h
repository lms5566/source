// PlateIdentify.h : PlateIdentify Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPlateIdentifyApp:
// �йش����ʵ�֣������ PlateIdentify.cpp
//

class CPlateIdentifyApp : public CWinApp
{
public:
	CPlateIdentifyApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlateIdentifyApp theApp;