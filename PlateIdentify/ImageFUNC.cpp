#include "StdAfx.h"
#include "ImageFUNC.h"

//=========================================
//  函数功能： 构造函数，初始化数据成员
//=========================================

ImageFUNC::ImageFUNC(void)
{

}

//=========================================
//  函数功能： 析构函数，释放内存空间
//=========================================

ImageFUNC::~ImageFUNC(void)
{

}

//=========================================
//  函数功能： 对灰度图像进行拉伸
//=========================================

void ImageFUNC::Stretch(IplImage *src, IplImage *dst,int min,int max)
{
		int low_value=min; //拉伸后像素的最小值
		int high_value=max;//拉伸后像素的最大值
		float rate=0;//图像的拉伸率
		float stretch_p[256],stretch_p1[256],stretch_num[256];
		//清空三个数组
		memset(stretch_p,0,sizeof(stretch_p));
		memset(stretch_p1,0,sizeof(stretch_p1));
		memset(stretch_num,0,sizeof(stretch_num));
	 
		//求存放图象各个灰度级出现的次数
		for(int y=0;y<src->height;y++)
			{
				uchar * ptr=(uchar*)(src->imageData +y*src->widthStep);
				for(int x=0;x<src->width;x++)
				{
					stretch_num[ptr[x]]++;
				}
			}

		//求存放图像各个灰度级的出现概率
		for(int i=0;i<256;i++)
			{
				stretch_p[i]=stretch_num[i]/(src->width*src->height);
			}

		//求存放各个灰度级之前的概率和
		for(int i=0;i<256;i++)
			{
				for(int k=0;k<=i;k++)
					stretch_p1[i]+=stretch_p[k];
			}
		//统计出两个阈值点的值
		for(int i=0;i<256;i++)
			{
				if(stretch_p1[i]<0.1) //low_value 取接近10%的总像素的灰度值
				{
				  low_value=i;
				 }
				if(stretch_p1[i]>0.9) //high_value取接近90%的总像素的灰度值
				{
				   high_value=i;
				   break;
				}
			}
		rate=(float)255/(high_value-low_value+1);
	  //进行灰度拉伸
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
//  函数功能： 中值滤波
//=========================================
void ImageFUNC::Middle_Smooth(IplImage *src, IplImage *dst)
{
   int temp=0;// 中间变量
   int flag=0;//循环变量
   int pFilter_Image_Pixel[5];//窗口像素值
   int mid_pixel_value=0;  // 中值
  
    //清空数组并赋初始值为0
    memset(pFilter_Image_Pixel,0,sizeof(pFilter_Image_Pixel));
	//中值滤波
	for(int j=2;j<dst->height-2;j++)
	{  
        uchar *ptr_dst=(uchar*)(dst->imageData+j*dst->widthStep);
		for(int i=0;i<dst->width;i++)
		{
			//把5*1屏蔽窗口的所有像素值放入pFilter_Image_Pixel[m]
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
			//把pFilter_Image_Pixel[m]中的值按降序排列
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
			mid_pixel_value=pFilter_Image_Pixel[2];//求中值mid_pixel_value
			ptr_dst[i]=mid_pixel_value;//将中值赋给目标图像的当前点
		}
	}
}