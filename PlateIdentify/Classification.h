#pragma once
#include "cv.h"
#include "highgui.h"

struct pattern
{
	
	double feature[33]; //样本的特征向量
	int number;        //待识别字符在样本库中的序列号
	
};

//特征提取函数
	void GetFeature(IplImage *src,pattern &pat);
