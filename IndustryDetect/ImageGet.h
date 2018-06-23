#pragma once

#include<iostream>
#include <QThread>
#include <QString>
#include <QDateTime>
#include <QDir>
#include "qt_windows.h"
#include "cyapi.h"

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

#define  CIS1


#ifdef CIS1
#define PACKAGES 140//�ܰ����� 6
#define BUFLENGTH  1024*1024	//���ջ��泤�� 2M
#define DATALENGTH 140*1024*1024	//�������ݵĴ�С 12M

#define MAT_HEIGHT 6500 //ԭͼ��  �ɼ�����
#define MAT_WIDTH 7344 //ԭͼ��  ����������

//
#define COL  7344
#define ROW	 6500

#define StartCol 0
#define EndCol 7344

#endif // CIS1

#ifdef CIS2

#define PACKAGES 270//�ܰ����� 6
#define BUFLENGTH  1024*1024	//���ջ��泤�� 2M
#define DATALENGTH 270*1024*1024	//�������ݵĴ�С 12M

#define MAT_WIDTH 10000 //ԭͼ��  �ɼ�����
#define MAT_HEIGHT 7344 //ԭͼ��  ����������

#endif // CIS2


//��������Ϊ����ģʽ ���ݲ����� ������
class ImageGet : public QThread
{
	Q_OBJECT
	
	//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
	ImageGet(const ImageGet&);
	ImageGet& operator=(const ImageGet&);

	static ImageGet* ImageGetInstance;

	ImageGet(QObject *parent = 0);
	~ImageGet();
public:

	static ImageGet* getInstance();


	void DataAnalysis();   //��������

	void DataExtractToImg(unsigned char* data, int t, Mat&);  //ƴ��ͼ��
	
	void GenColorCorrectCoff(unsigned char* data);		//����У��ϵ��
	
	void FilterLinerStrech(Mat &img_origin, Mat&dst, int color);		//���ղ�����������

	void run();

	void test();
public:
	int modType = 0;
	//������ 1 ͼ��ϳ� 2 ͼ��У�� 3 ͼ��У��ϵ������
	char buffer1[100]; //���Ա���·��
	unsigned char* data = NULL;

	Mat DestImg;

	double BCoeff[MAT_WIDTH];//black
	double WCoeff[MAT_WIDTH];//white
	double MCoeff[MAT_WIDTH];//б��
	double NCoeff[MAT_WIDTH];//�ؾ�

	QString fileName;
	//����У��ϵ��
	//void CalCoefFilterLinerStrech(IplImage* img_origin, IplImage* dst, int color);//����ڰױ�׼ͼ������������

	void ImageGet::CalCoefFilterLinerStrech(Mat &img_origin, Mat &dst, int color);   //����У��ϵ��

	void CalColumnCoef(int column, int columnInstead, double b_coeff[7344], double w_coeff[7344]);		//����ÿһ����������У������
signals:
	void ShowProgress(int p);

};


//class linerCoefAdj
//{
//public:
//
//	void CalCoefFilterLinerStrech(IplImage* img_origin, IplImage* dst, int color);//����ڰױ�׼ͼ������������
//	
//	void CalColumnCoef(int column, int columnInstead, double b_coeff[7344], double w_coeff[7344]);		//����ÿһ����������У������
//	//void cal_column_coef_b(int column, int column_instead, double b_coeff[864], double w_coeff[864]);
//};

//void adjust(int mode);    // 0 ���� 1 ����

