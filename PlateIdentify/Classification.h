#pragma once
#include "cv.h"
#include "highgui.h"

struct pattern
{
	
	double feature[33]; //��������������
	int number;        //��ʶ���ַ����������е����к�
	
};

//������ȡ����
	void GetFeature(IplImage *src,pattern &pat);
