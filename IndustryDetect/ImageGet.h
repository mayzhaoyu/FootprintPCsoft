/***************************************************************\
* @Copyright(c) 2017 HUST-BIAC All rights reserved	
* @ClassName  ImageGet
* @Author  ZhaoYu
* @Date  2018年6月24日
* @Version 1.0
* @Description  CIS 采集图像配置文件以及ImageGet工具类
*
******************************************************************/

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

//CIS 1代表第一种CIS管类型   CIS管2代表第二种类型
#define  CIS1

#ifdef CIS1
//采集图像设置
#define PACKAGES 140			//总包个数 
#define BUFLENGTH  1024*1024	//接收缓存长度 
#define DATALENGTH 140*1024*1024	//接收数据的大小 

#define MAT_HEIGHT 6500		//原图高  采集长度
#define MAT_WIDTH 7344	   //原图宽  传感器个数

//黑白校正设置 
#define COL  7344
#define ROW	 6500

#define StartCol 0
#define EndCol 7344

//取黑纸3300行到3400行 白纸 1100行到1300行
#define BLACK_ROW_START 3300
#define BLACK_ROW_END 3400

#define WHITE_ROW_START 1100
#define WHITE_ROW_END 1300


#endif // CIS1

#ifdef CIS2

#define PACKAGES 270//总包个数 6
#define BUFLENGTH  1024*1024	//接收缓存长度 2M
#define DATALENGTH 270*1024*1024	//接收数据的大小 12M

#define MAT_WIDTH 10000 //原图宽  采集长度
#define MAT_HEIGHT 7344 //原图高  传感器个数

#endif // CIS2


//将其设置为单例模式 数据不敏感 工具类

class ImageGet : public QThread
{
	Q_OBJECT
	
	//把复制构造函数和=操作符也设为私有,防止被复制
	ImageGet(const ImageGet&);
	ImageGet& operator=(const ImageGet&);

	static ImageGet* ImageGetInstance;

	ImageGet(QObject *parent = 0);
	~ImageGet();
public:

	static ImageGet* getInstance();

	void DataAnalysis();   //解析数据

	void DataExtractToImg(unsigned char* data, int t, Mat&);  //拼接图像
	
	void GenColorCorrectCoff(unsigned char* data);		//生成校正系数
	
	void CalCoefFilterLinerStrech(Mat &img_origin, Mat &dst, int color);   //计算校正系数

	void FilterLinerStrech(Mat &img_origin, Mat&dst, int color);		//按照参数线性拉伸

	void run();

	void test();
public:
	int modType = 0;
	//功能码 1 图像合成 2 图像校正 3 图像校正系数生成

	char buffer1[100]; //测试保存路径
	unsigned char* data = NULL;  //图像数据指针

	Mat DestImg;  //保存采集的图像

	double BCoeff[MAT_WIDTH];//black
	double WCoeff[MAT_WIDTH];//white
	double MCoeff[MAT_WIDTH];//斜率
	double NCoeff[MAT_WIDTH];//截距

	QString fileName;		//图片保存路径

signals:
	void ShowProgress(int p);  //改变进度条

};


