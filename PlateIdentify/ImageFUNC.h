//=================================
// 文件:ImageFUNC
// 内容: 定义的一些图像处理函数
// 功能: 
//       图像灰度拉伸
//       中值滤波 模板采用矩阵(1,1,1,1,1)的转置
//==================================
#pragma once

#include "cv.h"
#include "highgui.h"

class ImageFUNC
{
public:
    ImageFUNC(void);
	~ImageFUNC(void);
	void Stretch(IplImage * src,IplImage * dst,int min,int max);
	void Middle_Smooth(IplImage * src,IplImage *dst);
};