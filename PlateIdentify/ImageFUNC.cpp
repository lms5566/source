#include "StdAfx.h"
#include "ImageFUNC.h"

//=========================================
//  �������ܣ� ���캯������ʼ�����ݳ�Ա
//=========================================

ImageFUNC::ImageFUNC(void)
{

}

//=========================================
//  �������ܣ� �����������ͷ��ڴ�ռ�
//=========================================

ImageFUNC::~ImageFUNC(void)
{

}

//=========================================
//  �������ܣ� �ԻҶ�ͼ���������
//=========================================

void ImageFUNC::Stretch(IplImage *src, IplImage *dst,int min,int max)
{
		int low_value=min; //��������ص���Сֵ
		int high_value=max;//��������ص����ֵ
		float rate=0;//ͼ���������
		float stretch_p[256],stretch_p1[256],stretch_num[256];
		//�����������
		memset(stretch_p,0,sizeof(stretch_p));
		memset(stretch_p1,0,sizeof(stretch_p1));
		memset(stretch_num,0,sizeof(stretch_num));
	 
		//����ͼ������Ҷȼ����ֵĴ���
		for(int y=0;y<src->height;y++)
			{
				uchar * ptr=(uchar*)(src->imageData +y*src->widthStep);
				for(int x=0;x<src->width;x++)
				{
					stretch_num[ptr[x]]++;
				}
			}

		//����ͼ������Ҷȼ��ĳ��ָ���
		for(int i=0;i<256;i++)
			{
				stretch_p[i]=stretch_num[i]/(src->width*src->height);
			}

		//���Ÿ����Ҷȼ�֮ǰ�ĸ��ʺ�
		for(int i=0;i<256;i++)
			{
				for(int k=0;k<=i;k++)
					stretch_p1[i]+=stretch_p[k];
			}
		//ͳ�Ƴ�������ֵ���ֵ
		for(int i=0;i<256;i++)
			{
				if(stretch_p1[i]<0.1) //low_value ȡ�ӽ�10%�������صĻҶ�ֵ
				{
				  low_value=i;
				 }
				if(stretch_p1[i]>0.9) //high_valueȡ�ӽ�90%�������صĻҶ�ֵ
				{
				   high_value=i;
				   break;
				}
			}
		rate=(float)255/(high_value-low_value+1);
	  //���лҶ�����
		  for(int y=0;y<src->height;y++)
			{
				uchar * ptr_src=(uchar *)(src->imageData+y*src->widthStep);
				uchar * ptr_dst=(uchar *)(dst->imageData+y*dst->widthStep);
				for(int x=0;x<src->width;x++)
				{
					if(ptr_src[x]<low_value)
					{
						ptr_dst[x]=0;
					}
					else if(ptr_src[x]<high_value)
					{
						ptr_dst[x]=(uchar)((ptr_src[x]-low_value)*rate+0.5);
							if(ptr_dst[x]>255)
								ptr_dst[x]=high_value;
					}
					else if(ptr_src[x]>=high_value)
					{
						ptr_dst[x]=255;
					}
				}
		  }
	}
//=========================================
//  �������ܣ� ��ֵ�˲�
//=========================================
void ImageFUNC::Middle_Smooth(IplImage *src, IplImage *dst)
{
   int temp=0;// �м����
   int flag=0;//ѭ������
   int pFilter_Image_Pixel[5];//��������ֵ
   int mid_pixel_value=0;  // ��ֵ
  
    //������鲢����ʼֵΪ0
    memset(pFilter_Image_Pixel,0,sizeof(pFilter_Image_Pixel));
	//��ֵ�˲�
	for(int j=2;j<dst->height-2;j++)
	{  
        uchar *ptr_dst=(uchar*)(dst->imageData+j*dst->widthStep);
		for(int i=0;i<dst->width;i++)
		{
			//��5*1���δ��ڵ���������ֵ����pFilter_Image_Pixel[m]
			int m=0;
			for(int y=j-2;y<=j+2;y++)
			{
				uchar *ptr_src=(uchar*)(src->imageData+y*src->widthStep);
				for(int x=i;x<=i;x++)
				{
					pFilter_Image_Pixel[m]=ptr_src[i];
					m++;
				}
			}
			//��pFilter_Image_Pixel[m]�е�ֵ����������
			do{
					flag=0;
					for(int m=0;m<4;m++)
					{
						if(pFilter_Image_Pixel[m]<pFilter_Image_Pixel[m+1])
						{
							temp=pFilter_Image_Pixel[m];
							pFilter_Image_Pixel[m]=pFilter_Image_Pixel[m+1];
							pFilter_Image_Pixel[m+1]=temp;
							flag=1;
						}
				     }
			   }while(flag==1);
			mid_pixel_value=pFilter_Image_Pixel[2];//����ֵmid_pixel_value
			ptr_dst[i]=mid_pixel_value;//����ֵ����Ŀ��ͼ��ĵ�ǰ��
		}
	}
}