//=================================
// �ļ�:ImageFUNC
// ����: �����һЩͼ������
// ����: 
//       ͼ��Ҷ�����
//       ��ֵ�˲� ģ����þ���(1,1,1,1,1)��ת��
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