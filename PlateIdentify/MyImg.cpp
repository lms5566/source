#include "StdAfx.h"
#include "MyImg.h"

myimg::myimg()
{
}
void myimg::mSetImg(IplImage * pImg)
{
	m_img=cvCloneImage(pImg);
}

myimg::~myimg(void)
{
}