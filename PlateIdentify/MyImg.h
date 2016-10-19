#pragma once
#include "highgui.h"
#include "cv.h"

class myimg:public CvvImage
{
public:
	myimg();
	void mSetImg(IplImage *pImg);
public:
	~myimg();
};