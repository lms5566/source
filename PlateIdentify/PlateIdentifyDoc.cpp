// PlateIdentifyDoc.cpp : CPlateIdentifyDoc ���ʵ��
//

#include "stdafx.h"
#include "PlateIdentify.h"

#include "PlateIdentifyDoc.h"
#include <iostream>
#include "deque"
using namespace std;
typedef deque<CRect> CRectLink;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlateIdentifyDoc

IMPLEMENT_DYNCREATE(CPlateIdentifyDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlateIdentifyDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CPlateIdentifyDoc::OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_PlateExtract, &CPlateIdentifyDoc::OnUpdatePlateextract)
	ON_COMMAND(ID_PlateExtract, &CPlateIdentifyDoc::OnPlateextract)
	ON_UPDATE_COMMAND_UI(ID_Revise, &CPlateIdentifyDoc::OnUpdateRevise)
	ON_COMMAND(ID_Revise, &CPlateIdentifyDoc::OnRevise)
	ON_UPDATE_COMMAND_UI(ID_Split, &CPlateIdentifyDoc::OnUpdateSplit)
	ON_COMMAND(ID_Split, &CPlateIdentifyDoc::OnSplit)
	ON_UPDATE_COMMAND_UI(ID_CharIdentify, &CPlateIdentifyDoc::OnUpdateCharidentify)
	ON_COMMAND(ID_CharIdentify, &CPlateIdentifyDoc::OnCharidentify)
END_MESSAGE_MAP()


// CPlateIdentifyDoc ����/����

CPlateIdentifyDoc::CPlateIdentifyDoc()
{
	// TODO: �ڴ����һ���Թ������
	

}

CPlateIdentifyDoc::~CPlateIdentifyDoc()
{
}

BOOL CPlateIdentifyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPlateIdentifyDoc ���л�

void CPlateIdentifyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPlateIdentifyDoc ���

#ifdef _DEBUG
void CPlateIdentifyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlateIdentifyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlateIdentifyDoc ����

void CPlateIdentifyDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	LPCTSTR lpszFilter="BMP Files(*.bmp)|*.bmp|�κ��ļ�|*.*||";
	CFileDialog dlg1(TRUE,lpszFilter,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	 
	//���ļ��Ի���
	if(dlg1.DoModal()==IDOK)
	{
		if(0==(src_image=cvLoadImage(dlg1.GetPathName(),1)))
		{  
			AfxMessageBox("�޷����ļ���");
			return;
		}
		else
		{
			m_Cimage.mSetImg(src_image);
			m_frame.m_openflag=true;
			UpdateAllViews(NULL);
			return ;
		}
	}
}

void CPlateIdentifyDoc::OnUpdatePlateextract(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_frame.m_openflag);
}

void CPlateIdentifyDoc::OnPlateextract()
{
	// TODO: �ڴ���������������
	//����ԭʼͼ��
	IplImage *pSrc_Image=NULL;
	pSrc_Image=cvCreateImage(cvGetSize(src_image),src_image->depth,src_image->nChannels);
	pSrc_Image=cvCloneImage(src_image);   

	//��ͼ��ת��Ϊ�Ҷ�ͼ��
	gray_image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	cvCvtColor(pSrc_Image,gray_image,CV_BGR2GRAY);
	
	
	//�Ҷ�����
	//����������ͼ��
	IplImage * pStretch_Image=NULL;
	pStretch_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	m_Func.Stretch(gray_image,pStretch_Image,0,255);


	//ͼ��ʴ
	//���帯ʴ���ͼ��
	IplImage *pErode_Image=NULL;
	pErode_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	cvErode(pStretch_Image,pErode_Image,0,1);

	

	//������ͼ���ȥ��ʴ���ͼ�񣬵õ����Ƶ�����
	//����������ͼ��
	IplImage *sub_Image=NULL;
	sub_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	cvAbsDiff(pStretch_Image,pErode_Image,sub_Image);


	//��ͼ����ж�ֵ������
	//�����ֵ��ͼ��
	IplImage *pBinary_Image=NULL;
	pBinary_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	cvThreshold(sub_Image,pBinary_Image,0,255,CV_THRESH_OTSU);


	//��ͼ�������ֵ�˲����˲��þ���(1,1,1,1,1)��ת��
	//������ֵ�˲�ͼ��
	IplImage *pFilter_Image=NULL;
	pFilter_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
	//�ȸ���һ��Ҫ������ֵ�˲���ͼ����Ϊǰ���к��������û�н��д���
	pFilter_Image=cvCloneImage(pBinary_Image);
	m_Func.Middle_Smooth(pBinary_Image,pFilter_Image);

	

   	//�Զ�ֵͼ������ʴ����ȥ�����������þ���1,1,1,1,1����ת����Ϊ��
	//���帯ʴ���ͼ��
	IplImage* pKernel_Erode_Image=NULL;
    pKernel_Erode_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
    IplConvKernel * pKernel_Erode=NULL;
	pKernel_Erode=cvCreateStructuringElementEx(1,3,0,1,CV_SHAPE_RECT,NULL);
	cvErode(pFilter_Image, pKernel_Erode_Image,pKernel_Erode,2);

	//�Զ�ֵͼ���������ʹ����ָ��������򣬲��þ���1,1,1����ת����Ϊ��
	IplConvKernel * pKernel_Dilate=NULL;
	pKernel_Dilate=cvCreateStructuringElementEx(1,3,0,1,CV_SHAPE_RECT,NULL);
	//�������ͺ��ͼ��
	IplImage* pKernel_Dilate_Image=NULL;
    pKernel_Dilate_Image=cvCreateImage(cvGetSize(pSrc_Image),8,1);
    cvDilate(pKernel_Erode_Image, pKernel_Dilate_Image,pKernel_Dilate,1);

	

	//�Գ���ͼ����ˮƽͶӰ
	//���������ۼӺ����飬ͼ��߶Ȳ�Ӧ����2048
	int level_shadow[2048]; 
	int height=pSrc_Image->height;
	int width=pSrc_Image->width ;
	CvScalar s_shadow;
 
	//��ղ���ʼ������
    memset(level_shadow,0,sizeof(level_shadow));

	//��ͼ����ˮƽͶӰ
	for(int y=height-1;y>=0;y--)
		{
			for(int x=0;x<width;x++)
				{
					s_shadow=cvGet2D(pKernel_Dilate_Image,y,x);
					if(s_shadow.val[0]!=0)
					level_shadow[y]++; //ͳ��ÿ�в�Ϊ������صĸ���				
				}
		}

	//��ͼ��ˮƽͶӰ��ֵ�����࣬���С����ֵ���Դ�����ֵ���̴���С��0.6��
	//����Ϊ�����в���һ�࣬��С����ֵ��Ϊ0
    for(int y=height-1;y>=1;y--)
	{
		 if(level_shadow[y-1]!=0)
		 {
		     if((float(level_shadow[y]))/(float(level_shadow[y-1]))<0.6)
				level_shadow[y]=0 ;
		 }
	}

	//ͳ��ˮƽͶӰ�в�Ϊ�������
	for(int y=height-1;y>=0;y--)
	{
		if(level_shadow[y]!=0)
			level_shadow[y]=level_shadow[y+1]+1;
	}
  
	//���ˮƽͶӰ������������Ϊ���������䣬�˼���Ϊ�ǳ��ƴ��¸߶�
	int Y_min=0;//���Ƹ߶�С����
	int Y_max=0;//���Ƹ߶ȴ�����
	int M_max_value=0;
    M_max_value=level_shadow[0]; //��level_shadow�ĵ�һ��ֵ����M_max_value
	for(int y=0;y<height;y++)
	{
		if(level_shadow[y]>M_max_value)
		{
			M_max_value=level_shadow[y];
			Y_min=y;
			Y_max=Y_min+M_max_value;
		}
	}
      
	if(M_max_value<10)
      	AfxMessageBox("��ȡ���Ƹ߶�ʧ��!"); 
   
	//����ROI�����и�����Ƶĸ߶�
	CvRect ROI_Plate_Height;
	ROI_Plate_Height.x=0;
	ROI_Plate_Height.y=Y_min;
	ROI_Plate_Height.width=pSrc_Image->width;
	ROI_Plate_Height.height=M_max_value;
	cvSetImageROI(pKernel_Dilate_Image,ROI_Plate_Height);

	//����������һ�ݣ��Ա��������
	IplImage * pROI_Height_Image=NULL;
	pROI_Height_Image=cvCreateImage(cvSize(ROI_Plate_Height.width,ROI_Plate_Height.height),8,1);
	cvCopyImage(pKernel_Dilate_Image,pROI_Height_Image);	


    //�Գ��Ƹ߶������������㣬�ó����Ƶľ����������и������
	//����˴�С���ã����Ƶĸ߶�*0.6)��
    int Copy_M_max_value=M_max_value; //���ƴ�ֵ��
    int Close_width=0;
	int Close_height=0;
	
	//�˴�С�涨Ϊ����
	while((Copy_M_max_value%3)!=0)
	{
		Copy_M_max_value--;
	}
    Close_width=int(Copy_M_max_value*0.6);
	Close_height=Copy_M_max_value;
	IplConvKernel * pKernel_Close=NULL;
	pKernel_Close=cvCreateStructuringElementEx(Close_width,Close_height,Close_width/2,Close_height/2,CV_SHAPE_RECT,NULL);
	cvMorphologyEx(pROI_Height_Image,pROI_Height_Image,NULL,pKernel_Close,CV_MOP_CLOSE,1);
    
	
	//����ͨ���������ȣ���λ���Ƶĺ�����
	int X_min=0;//���ƿ��С����
	int X_max=0;//���ƿ�ȴ�����
	int M_row_max_value=0;
	int count_row[2048];//ͼ���Ȳ�Ӧ����2048
	memset(count_row,0,sizeof(count_row));

	//ȡ�����м��һ��ֱ�߽��м��,���ֱ����������Ϊ0�����ص�����ȣ��˼�Ϊ���ƿ��
	int mid_height=M_max_value/2;
    uchar *ptr_mid=(uchar*)(pROI_Height_Image->imageData+mid_height*pROI_Height_Image->widthStep);
    for(int x=width-1;x>=0;x--)
	{
		if(ptr_mid[x]!=0)
			count_row[x]=count_row[x+1]+1;
	}
	
	//���count_row�����е����ֵ
	 int Max_value_count_row=0;
	 Max_value_count_row=count_row[0];
	 for(int x=0;x<width;x++)
	 {	
		 if(count_row[x]>Max_value_count_row)
		{
			Max_value_count_row=count_row[x];
			X_min=x;
			X_max=X_min+Max_value_count_row;
		}
	 }

	 //���ƵĿ��Ӧ���ڸ߶ȵ����������и���ĳ��ƽ�����֤
    if(float(Max_value_count_row)/float(M_max_value)<3||float(Max_value_count_row)/float(M_max_value)>6) 
		AfxMessageBox("��ȡ����ʧ��!");
	   
	//�и������,�Ա߽������ʵ�����
	CvRect ROI_Plate;
	ROI_Plate.x=X_min+2; 
	ROI_Plate.y=Y_min+5; 
	ROI_Plate.width=Max_value_count_row-6;
	ROI_Plate.height=M_max_value+3;

	//�жϳ��ƶ�λ�����Ƿ�Ϸ�
	if(ROI_Plate.x<0||ROI_Plate.x>width)
		AfxMessageBox("��ȡ����ʧ��!");
	if(ROI_Plate.y<0|| ROI_Plate.y>height)
		AfxMessageBox("��ȡ����ʧ��!");
	if((ROI_Plate.x+ROI_Plate.width)>width)
		AfxMessageBox("��ȡ����ʧ��!");
	if((ROI_Plate.y+ROI_Plate.height)>height)
		AfxMessageBox("��ȡ����ʧ��!");

	cvSetImageROI(gray_image,ROI_Plate);
	plate_image=cvCreateImage(cvSize(ROI_Plate.width,ROI_Plate.height),8,1);
	cvCopyImage(gray_image,plate_image);


	//�ͷŻҶ�ͼ���ROI����
	cvResetImageROI(gray_image);

	//�Գ���ͼ����лҶ�����
	m_Func.Stretch(plate_image,plate_image,0,255);

	

	//�Գ���ͼ����ж�ֵ��
	cvThreshold(plate_image,plate_image,0,255,CV_THRESH_OTSU);

	

	//������ͼ����ɫ��ת
	cvNot(plate_image,plate_image);

    //ͼ����ʾ
	m_Cimage.mSetImg(plate_image);
	UpdateAllViews(NULL);	

	
}

void CPlateIdentifyDoc::OnUpdateRevise(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_frame.m_openflag);
}

void CPlateIdentifyDoc::OnRevise()
{
	// TODO: �ڴ���������������
	//���峵��У�����ͼ��
	IplImage *pRoation=NULL;
	pRoation=cvCreateImage(cvGetSize(plate_image),8,1);
    CvScalar s,s_new;
    double num=0;
    double leftaverage=0;
    double rightaverage=0;
    int iHeight=plate_image->height;
    int iWidth=plate_image->width;
    double slope=0;
    int pix_new;
  
	//����ǰ�벿��б��
    for(int ht=0;ht<iHeight;ht++)
    {
        for(int wt=0;wt<iWidth/6;wt++)
        {
            s=cvGet2D(plate_image,ht,wt);
            if(0==s.val[0])
            {
                num+=iWidth/2-wt;
                leftaverage+=ht*(iWidth/2-wt);
            }
        }
    }
    leftaverage/=num;
    num=0;
   
	//�����벿��б��
    for(int ht=0;ht<iHeight;ht++)
    {
        for(int wt=(iWidth/6)*5;wt<iWidth;wt++)
        {
            s=cvGet2D(plate_image,ht,wt);
            if(0==s.val[0])
            {
                num+=iWidth/2-wt;
                rightaverage+=ht*(iWidth/2-wt);
            }
        }
    }

    rightaverage/=num;

	//���б�ʣ�����б�����ʵ����ű���У������
    slope=(leftaverage-rightaverage)/(iWidth/2)*0.6;    
  
	//ͼ��ӳ��
    for(int ht=0;ht<iHeight;ht++)
    {
        for(int wt=0;wt<iWidth/2;wt++)
        {
            pix_new=int((ht-(wt-iWidth/2)*slope));      
            if(pix_new<0||pix_new>=iHeight)
            { 
                s.val[0]=255;
				cvSet2D(pRoation,ht,wt,s);
            }
            else
            {
				s=cvGet2D(plate_image,pix_new,wt);
                s_new.val[0]=s.val[0];
                cvSet2D(pRoation,ht,wt,s_new);
            } 
        }
    }
	 for(int ht=0;ht<iHeight;ht++)
    {
        for(int wt=iWidth/2;wt<iWidth;wt++)
        {
            pix_new=int((ht-(wt-iWidth/2)*(slope)));      
            if(pix_new<0||pix_new>=iHeight)
            {
                s.val[0]=255;
              	cvSet2D(pRoation,ht,wt,s);
            }
            else
            {
				s=cvGet2D(plate_image,pix_new,wt);
                s_new.val[0]=s.val[0];
				cvSet2D(pRoation,ht,wt,s);
            } 
        }
	 } 	
	//ͼ����ʾ
	m_Cimage.mSetImg(pRoation);
	plate_image=cvCloneImage(pRoation);
	UpdateAllViews(NULL);
}

void CPlateIdentifyDoc::OnUpdateSplit(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_frame.m_openflag);
}

void CPlateIdentifyDoc::OnSplit()
{
	// TODO: �ڴ���������������
	//�ַ��ָ� 
	//�����������ÿ���ַ����������
	CRectLink charRect1,charRect2;
	charRect1.clear();
	charRect2.clear();
	int num2=0;   //ͳ�Ƶ�һ���и�����ַ��ĸ���
	int num_char=0;//ͳ�������ַ��ĸ���
	CvScalar s;
	int iHeight=plate_image->height;
    int iWidth=plate_image->width;
	int top;//�ַ��Ĵ��¶���
	int bottom;//�ַ��Ĵ��µײ�
 
    //������һ���ڵ�ȷ����������λ��
    for(int ht=0;ht<iHeight;ht++) 
    {
        for(int wt=0;wt<iWidth;wt++)
        {
            s=cvGet2D(plate_image,ht,wt);
            if(0==s.val[0])
            {
                //�ڵ�
                top=ht;
                ht=iHeight;//ǿ������ѭ��
                break;
            }
        }
    }
  
	//������һ���ڵ�ȷ���ײ�����λ��
    for(int ht=iHeight-1;ht>=0;ht--)
    {
        for(int wt=0;wt<iWidth;wt++)
        {
            s=cvGet2D(plate_image,ht,wt);
            if(0==s.val[0])
            {
                bottom=ht;//ǿ������ѭ��
                ht=-1;
                break;
            }
        }
    }

    bool lab=FALSE;  //�Ƿ����һ���ַ��ָ�״̬
	bool black=FALSE;	//ɨ�����Ƿ��ֺڵ� 							
    CRect rect; // ���λ����Ϣ�Ľṹ��

    for(int wt=0;wt<iWidth;wt++) 
    {	
		//��ʼɨ��һ��
		black=false;
        for(int ht=0;ht<iHeight;ht++)
        {
			// ��õ�ǰ����ֵ
            s=cvGet2D(plate_image,ht,wt);
            if(0==s.val[0])//�ж��Ƿ��Ǻڵ�
            {
				//������ֺڵ㣬���ñ�־λ
				black=true;
				//�����û�н���һ���ַ��ָ�
				if(lab==false)
				{
					//�������߽�
					rect.left=wt;
					//�ַ��ָʼ
					lab=true;
				}
				//����ַ��ָ��Ѿ���ʼ��
				else
					//����ѭ��
					break;
			}
		}
	
		//����Ѿ�ɨ�赽�����ұ����У�˵������ͼ��ɨ����ϡ��˳�
		if(wt==(iWidth-1))
			break;
		
		//�������ʱbalck��Ϊfalse��˵��ɨ����һ�ж�û�з��ֺڵ㡣���浱ǰ�ַ��ָ����
		if((lab==true)&&(black==false))
		{
			//��λ����Ϣ����ṹ����
			//�����ұ߽�
			rect.right=wt;
			
			//�����ϱ߽�
			rect.top=top;
			
			//�����±߽�
			rect.bottom=bottom;
			
			//��������һ�����أ�����ѹ���ַ�
			rect.InflateRect(1,1);
		
			//������ṹ�������λ����Ϣ������1�ĺ���
			charRect1.push_back(rect);
		
			//���ñ�־λ����ʼ��һ�ε��ַ��ָ�
			lab=false;
		
			//�ַ�������1
			num2++;
		}
			//������һ�е�ɨ��
	}

	//�ٽ�����������top��bottom��ȷ��
	
	//������1��ֵ������2
	charRect2=charRect1;
	
	//������2���������
	charRect2.clear();
	
	//����һ���µĴ��λ����Ϣ�Ľṹ��
	CRect rectnew;
	
	//��������1��ͷ��β�������ɨ��
	while(!charRect1.empty())
	{
		//������1ͷ�ϵõ�һ������
		rect=charRect1.front();
		
		//������1ͷ����ɾ��һ��
		charRect1.pop_front();
	
		//�ж��ַ��Ŀ�ȣ���ȥ���м��СԲ��
		
			//�ַ�������һ
			num_char++;
		
			//������Ӿ�ȷ�ľ�������
			//��þ�ȷ����߽�
			rectnew.left=rect.left-1;
		
			//��þ�ȷ���ұ߽�
			rectnew.right=rect.right-1;
		
			//ͨ����õľ�ȷ���ұ߽�����±߽����½��о�ȷ��λ
			//���϶���ɨ�裬�����ϱ߽�
			//��
			for(int ht=rect.top;ht<rect.bottom;ht++)
			{
				//��
				for(int wt=rect.left;wt<rect.right;wt++)
				{
					// ��õ�ǰ����ֵ
					s=cvGet2D(plate_image,ht,wt);
					if(0==s.val[0])
					{
						//�����ϱ߽�
						rectnew.top=ht-1;
						
						//��ht����ǿ�ƶ���������ѭ��
						ht=rect.bottom;
					
						//����ѭ��
						break;
					}

				}
			}
		
			//���¶���ɨ�裬�����±߽�
			//��
			for(int ht=rect.bottom-1;ht>=rect.top;ht--)
			{
				//��
				for(int wt=rect.left;wt<rect.right;wt++)
				{
					// ��õ�ǰ����ֵ
					s=cvGet2D(plate_image,ht,wt);
					if(0==s.val[0])
					{
						//�����ϱ߽�
						rectnew.bottom=ht+1;
					
						//��ht����ǿ�ƶ���������ѭ��
						ht=-1;
					
						//����ѭ��
						break;
					}
				}
			}
		//���õ����µ�׼ȷλ����Ϣ�Ӻ�����뵽����2��β��
		charRect2.push_back(rectnew);
		}
	
	//������2���ݸ�����1
	charRect1=charRect2;

	//�и�ͼ��
	CvRect dst_rect[100];
	CRect rect2;
	for(int i=0;i<num_char;i++)
	{  
		if(!charRect1.empty())
		{
			rect2=charRect1.front();
			charRect1.pop_front();
			dst_rect[i].x=rect2.left;
			dst_rect[i].y=rect2.top;
			dst_rect[i].width=rect2.right-rect2.left+1;
			dst_rect[i].height=rect2.bottom-rect2.top+1;
		}
	}
	
	//�ַ���һ�����ַ�ϸ��
	
	for(int i=0;i<num_char;i++)
	{ 
		dst_image[i]=cvCreateImage(cvSize(g_width,g_height),8,1);
		cvSetImageROI(plate_image,dst_rect[i]);
		cvNot(plate_image,plate_image);//�ַ���ɫ����
		cvResize(plate_image,dst_image[i],CV_INTER_NN);//ͼ������
		m_thin.Thin(dst_image[i],dst_image[i]);//ͼ��ϸ��
		cvResetImageROI(plate_image);
	}
	
    //��ʾ�ָ����ַ�
	IplImage * plate_char;
	//���ָ�������ַ��������е�ͼ��plate_char�ϣ�
	//Ϊ������ʾ�ָ�Ч�������ַ���ļ����Ϊ12������
	plate_char=cvCreateImage(cvSize(g_width*num_char+(num_char-1)*12,g_height),8,1);
	cvZero(plate_char);
	
	for(int i=0;i<num_char;i++)
		{
			int x=0+i*g_width+i*12;
			int y=0;
			int width=g_width;
			int height=g_height;
			cvSetImageROI(plate_char,cvRect(x,y,width,height));
			cvCopyImage(dst_image[i],plate_char);
			cvResetImageROI(plate_char);
		}
	//ͼ����ʾ
	cvShowImage("�ָ�����ַ�",plate_char);
	UpdateAllViews(NULL);
}

void CPlateIdentifyDoc::OnUpdateCharidentify(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_frame.m_openflag);
}

void CPlateIdentifyDoc::OnCharidentify()
{
	// TODO: �ڴ���������������
	
	IplImage * char_sample[34];//�ַ�����ͼ������
	IplImage * hanzi_sample[9];//��������ͼ������
	pattern char_pattern[34];//�����ַ���Ʒ��ṹ����
	pattern hanzi_pattern[9];//���庺����Ʒ��ṹ����
	pattern TestSample[7];//�����ʶ���ַ��ṹ����
    
	//�����ַ�ģ��
	char_sample[0]=cvLoadImage("template\\0.bmp",0);
	char_sample[1]=cvLoadImage("template\\1.bmp",0);
	char_sample[2]=cvLoadImage("template\\2.bmp",0);
	char_sample[3]=cvLoadImage("template\\3.bmp",0);
	char_sample[4]=cvLoadImage("template\\4.bmp",0);
	char_sample[5]=cvLoadImage("template\\5.bmp",0);
	char_sample[6]=cvLoadImage("template\\6.bmp",0);
	char_sample[7]=cvLoadImage("template\\7.bmp",0);
	char_sample[8]=cvLoadImage("template\\8.bmp",0);
	char_sample[9]=cvLoadImage("template\\9.bmp",0);
	char_sample[10]=cvLoadImage("template\\A.bmp",0);
	char_sample[11]=cvLoadImage("template\\B.bmp",0);
	char_sample[12]=cvLoadImage("template\\C.bmp",0);
	char_sample[13]=cvLoadImage("template\\D.bmp",0);
	char_sample[14]=cvLoadImage("template\\E.bmp",0);
	char_sample[15]=cvLoadImage("template\\F.bmp",0);
	char_sample[16]=cvLoadImage("template\\G.bmp",0);
	char_sample[17]=cvLoadImage("template\\H.bmp",0);
	char_sample[18]=cvLoadImage("template\\J.bmp",0);
	char_sample[19]=cvLoadImage("template\\K.bmp",0);
	char_sample[20]=cvLoadImage("template\\L.bmp",0);
	char_sample[21]=cvLoadImage("template\\M.bmp",0);
	char_sample[22]=cvLoadImage("template\\N.bmp",0);
	char_sample[23]=cvLoadImage("template\\P.bmp",0);
	char_sample[24]=cvLoadImage("template\\Q.bmp",0);
	char_sample[25]=cvLoadImage("template\\R.bmp",0);
	char_sample[26]=cvLoadImage("template\\S.bmp",0);
	char_sample[27]=cvLoadImage("template\\T.bmp",0);
	char_sample[28]=cvLoadImage("template\\U.bmp",0);
	char_sample[29]=cvLoadImage("template\\V.bmp",0);
	char_sample[30]=cvLoadImage("template\\W.bmp",0);
	char_sample[31]=cvLoadImage("template\\X.bmp",0);
	char_sample[32]=cvLoadImage("template\\Y.bmp",0);
	char_sample[33]=cvLoadImage("template\\Z.bmp",0);
	

	//���뺺��ģ��
	hanzi_sample[0]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[1]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[2]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[3]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[4]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[5]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[6]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[7]=cvLoadImage("template\\��.bmp",0);
	hanzi_sample[8]=cvLoadImage("template\\��.bmp",0);
	

	//��ȡ�ַ���������
	for(int i=0;i<34;i++)
	{
		GetFeature(char_sample[i],char_pattern[i]);
	}
	//��ȡ�����ַ�����
	for(int i=0;i<9;i++)
	{
		GetFeature(hanzi_sample[i],hanzi_pattern[i]);
	}
    //��ȡ��ʶ���ַ�����
	for(int i=0;i<7;i++)
	{
		GetFeature(dst_image[i],TestSample[i]);
	}
  
	//����ģ��ƥ��	
	double min=100000.0;
	for(int num=0;num<1;num++)
	{
		for(int i=0;i<9;i++)
		{
			double diff=0.0;
			for(int j=0;j<25;j++)
			{
				diff+=fabs(TestSample[num].feature[j]-hanzi_pattern[i].feature[j]);
			}
			for(int j=25;j<33;j++)
			{
				diff+=fabs(TestSample[num].feature[j]-hanzi_pattern[i].feature[j])*9;
			}
			if(diff<min)
			{
				min=diff;
				TestSample[num].number=i;
			}
		}
	}
	
	for(int num=1;num<7;num++)
	{
		double min_min=1000000.0;
		for(int i=0;i<34;i++)
		{
			double diff_diff=0.0;
			for(int j=0;j<25;j++)
			{
				diff_diff+=fabs(TestSample[num].feature[j]-char_pattern[i].feature[j]);
			}
			for(int j=25;j<33;j++)
			{
				diff_diff+=fabs(TestSample[num].feature[j]-char_pattern[i].feature[j]);
			}
			if(diff_diff<min_min)
			{
				min_min=diff_diff;
				TestSample[num].number=i;
			}
		}
	}
	
	CString result="";//���ʶ������ַ�

	for(int i=0;i<1;i++)
	{
		switch (TestSample[i].number)
		{
		case 0:
			result+="��";
		    break;
		case 1:
			result+="��";
			break;
		case 2:
			result+="��";
			break;
		case 3:
			result+="��";
			break;
		case 4:
			result+="��";
			break;
		case 5:
			result+="��";		
			break;
		case 6:
			result+="��";
			break;
		case 7:
			result+="��";
			break;
		case 8:
			result+="��";
			break;
		default:
			AfxMessageBox("ʶ��ʧ��");
			break;
		}
	}

	for(int i=1;i<7;i++)
	{
		switch (TestSample[i].number)
		{
		case 0:
			result+="0";
		    break;
		case 1:
			result+="1";
			break;
		case 2:
			result+="2";
			break;
		case 3:
			result+="3";
			break;
		case 4:
			result+="4";
			break;
		case 5:
			result+="5";
			break;
		case 6:
			result+="6";
			break;
		case 7:
			result+="7";
			break;
		case 8:
			result+="8";
			break;
		case 9:
			result+="9";
			break;
		case 10:
			result+="A";
			break;
		case 11:
			result+="B";
			break;
		case 12:
			result+="C";
			break;
		case 13:
			result+="D";
			break;
		case 14:
			result+="E";;
			break;
		case 15:
			result+="F";
		case 16:
			result+="G";
			break;
		case 17:
			result+="H";
			break;
		case 18:
			result+="J";
			break;
		case 19:
			result+="K";
			break;
		case 20:
			result+="L";
			break;
		case 21:
			result+="M";
			break;
		case 22:
			result+="N";
			break;
		case 23:
			result+="P";
			break;
		case 24:
			result+="Q";
			break;
		case 25:
			result+="R";
			break;
		case 26:
			result+="S";
			break;
		case 27:
			result+="T";
			break;
		case 28:
			result+="U";
			break;
		case 29:
			result+="U";
			break;
		case 30:
			result+="W";
			break;
		case 31:
			result+="X";
			break;
		case 32:
			result+="Y";
			break;
		case 33:
			result+="Z";
			break;			
		default:
			AfxMessageBox("ʶ��ʧ��");
			break;
		}
	}
	AfxMessageBox(result);//��ʾ���

}
