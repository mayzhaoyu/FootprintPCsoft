#include "ImageGet.h"
#include <fstream>
unsigned char mat0[3][MAT_HEIGHT][MAT_WIDTH];

unsigned char MAT[MAT_HEIGHT][MAT_WIDTH];

ImageGet::ImageGet(QObject *parent)
	:QThread(parent)
{
}


ImageGet::~ImageGet()
{
}

//在此处初始化
ImageGet* ImageGet::ImageGetInstance = new ImageGet();

ImageGet* ImageGet::getInstance()
{
	return ImageGetInstance;
}

/*void ImageGet::DataExtractToImg(unsigned char* data, Mat &DestImg)
{
	//int line_count = 0;
	//int line_count_g = 0;
	//int line_count_b = 0;		//行数

	//memset(mat0, 0, 3 * MAT_HEIGHT*MAT_WIDTH);
	////FPGA没有传废数据
	//for (int data_ref = 0; data_ref < DATALENGTH; data_ref++)//data_ref数据偏移量
	//{
	//	//1、 0xA500015A   r分量数据
	//	if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x01) && data[data_ref + 3] == unsigned char(0x5A))
	//	{
	//		data_ref += 4;
	//		for (int pix_count = 0; pix_count < 2592; pix_count++)
	//		{
	//			mat0[0][line_count][pix_count] = data[data_ref + pix_count * 3];
	//			mat0[0][line_count][2592 + pix_count] = data[data_ref + pix_count * 3 + 1];
	//			if (pix_count < 2159)
	//			{
	//				mat0[0][line_count][5184 + pix_count] = data[data_ref + pix_count * 3 + 2];
	//			}

	//		}
	//		line_count++;
	//		//line_count_r_2++;
	//		data_ref += 20000;
	//		if (line_count > MAT_WIDTH || data_ref >= DATALENGTH)break;
	//		//if(line_count_r>MAT_WIDTH)break;
	//		else continue;
	//	}


	//	//2、 0xA500025A g
	//	if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x02) && data[data_ref + 3] == unsigned char(0x5A))
	//	{
	//		data_ref += 4;
	//		for (int pix_count = 0; pix_count < 2592; pix_count++)
	//		{
	//			mat0[1][line_count][pix_count] = data[data_ref + pix_count * 3];
	//			mat0[1][line_count][2592 + pix_count] = data[data_ref + pix_count * 3 + 1];
	//			if (pix_count < 2159)
	//			{
	//				mat0[1][line_count][5184 + pix_count] = data[data_ref + pix_count * 3 + 2];
	//			}
	//		}
	//		line_count++;
	//		//line_count_r_2++;
	//		data_ref += 20000;
	//		if (line_count > MAT_WIDTH || data_ref >= DATALENGTH)break;
	//		//if(line_count_r>MAT_WIDTH)break;
	//		else continue;
	//	}


	//	//3、 A500035A  b
	//	if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x04) && data[data_ref + 3] == unsigned char(0x5A))
	//	{

	//		data_ref += 4;
	//		for (int pix_count = 0; pix_count < 2592; pix_count++)
	//		{
	//			mat0[2][line_count][pix_count] = data[data_ref + pix_count * 3];
	//			mat0[2][line_count][2592 + pix_count] = data[data_ref + pix_count * 3 + 1];
	//			if (pix_count < 2159)
	//			{
	//				mat0[2][line_count][5184 + pix_count] = data[data_ref + pix_count * 3 + 2];
	//			}

	//		}
	//		line_count++;
	//		//line_count_r_2++;
	//		data_ref += 20000;
	//		if (line_count > MAT_WIDTH || data_ref >= DATALENGTH)break;
	//		//if(line_count_r>MAT_WIDTH)break;
	//		else continue;
	//	}
	//}
	//IplImage* imgr0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1); //size为图像宽高，depth为位深度，channels为通道数
	//IplImage* imgg0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1);
	//IplImage* imgb0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1);

	//vector<Mat> RGBImg;
	//Mat imag01r = Mat(MAT_WIDTH, MAT_HEIGHT, CV_8UC1, mat0[0]);
	//Mat imag01g = Mat(MAT_WIDTH, MAT_HEIGHT, CV_8UC1, mat0[1]);
	//Mat imag01b = Mat(MAT_WIDTH, MAT_HEIGHT, CV_8UC1, mat0[2]);
	//Mat imag01 = Mat(MAT_WIDTH, MAT_HEIGHT, CV_8UC3, 3);
	//RGBImg.push_back(imag01b);
	//RGBImg.push_back(imag01g);
	//RGBImg.push_back(imag01r);
	//merge(RGBImg, imag01);

	//DestImg = imag01;

	//sprintf(buffer1, "image/test/outP_00%d.jpg", t);
	//imwrite(buffer1, imag01);

	//cvReleaseImage(&imgr0);
	//cvReleaseImage(&imgg0);
	//cvReleaseImage(&imgb0);




}*/

void ImageGet::DataAnalysis()
{
	int line_count_r = 0;
	int line_count_g = 0;
	int line_count_b = 0;		//行数

	memset(mat0, 0, 3 * MAT_HEIGHT*MAT_WIDTH);
	//FPGA没有传废数据
	for (int data_ref = 0; data_ref < DATALENGTH; data_ref++)//data_ref数据偏移量
	{
		//1、 0xA500015A   r分量数据
		if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x01) && data[data_ref + 3] == unsigned char(0x5A))
		{
			data_ref += 4;
			for (int pix_count = 0; pix_count < 2592; pix_count++)
			{
				mat0[0][line_count_r][pix_count] = data[data_ref + pix_count * 3 + 1];
				mat0[0][line_count_r][2592 + pix_count] = data[data_ref + pix_count * 3 + 2];
				if (pix_count < 2160)
				{
					mat0[0][line_count_r][5183 + pix_count] = data[data_ref + pix_count * 3];
				}

			}
			line_count_r++;
			//line_count_r_2++;
			data_ref += 5000;
			if (line_count_r > MAT_HEIGHT || data_ref >= DATALENGTH)break;
			//if(line_count_r>MAT_WIDTH)break;
			else continue;
		}


		//2、 0xA500025A g
		if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x02) && data[data_ref + 3] == unsigned char(0x5A))
		{
			data_ref += 4;
			for (int pix_count = 0; pix_count < 2592; pix_count++)
			{
				mat0[1][line_count_g][pix_count] = data[data_ref + pix_count * 3 + 1];
				mat0[1][line_count_g][2592 + pix_count] = data[data_ref + pix_count * 3 + 2];
				if (pix_count < 2160)
				{
					mat0[1][line_count_g][5183 + pix_count] = data[data_ref + pix_count * 3];
				}
			}
			line_count_g++;
			//line_count_r_2++;
			data_ref += 5000;
			if (line_count_g > MAT_HEIGHT || data_ref >= DATALENGTH)break;
			//if(line_count_r>MAT_WIDTH)break;
			else continue;
		}


		//3、 A500035A  b
		if (data[data_ref] == unsigned char(0xA5) && data[data_ref + 1] == unsigned char(0x00) && data[data_ref + 2] == unsigned char(0x04) && data[data_ref + 3] == unsigned char(0x5A))
		{

			data_ref += 4;
			for (int pix_count = 0; pix_count < 2592; pix_count++)
			{
				mat0[2][line_count_b][pix_count] = data[data_ref + pix_count * 3 + 1];
				mat0[2][line_count_b][2592 + pix_count] = data[data_ref + pix_count * 3 + 2];
				if (pix_count < 2160)
				{
					mat0[2][line_count_b][5183 + pix_count] = data[data_ref + pix_count * 3];
				}

			}
			line_count_b++;
			//line_count_r_2++;
			data_ref += 5000;
			if (line_count_b > MAT_HEIGHT || data_ref >= DATALENGTH)break;
			//if(line_count_r>MAT_WIDTH)break;
			else continue;
		}
	}

	ofstream file("test.txt", ios::out);

	file << line_count_r << endl
		<< line_count_g << endl
		<< line_count_b << endl
		<< mat0[0][3][5184] << endl;
	file.close();

}

void ImageGet::DataExtractToImg(unsigned char* data, int t, Mat& DestImg)
{
	fileName.clear();
	QDateTime time = QDateTime::currentDateTime();
	fileName = "image\\" + time.toString("yyyy-MM-dd_hh-mm-ss");
	QDir dir;
	dir.mkpath(fileName);

	//解析数据
	DataAnalysis();
	emit ShowProgress(50);
	//IplImage* imgr0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1); //size为图像宽高，depth为位深度，channels为通道数
	//IplImage* imgg0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1);
	//IplImage* imgb0 = cvCreateImage(cvSize(MAT_HEIGHT, MAT_WIDTH), IPL_DEPTH_8U, 1);

	vector<Mat> RGBImg;
	Mat img01r = Mat(MAT_HEIGHT,MAT_WIDTH , CV_8UC1, mat0[0]);
	Mat img01g = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1, mat0[1]);
	Mat img01b = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1, mat0[2]);

	Mat img01R = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);
	Mat	img01G = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);
	Mat	img01B = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);

	//校正图像

	//翻转图像

	flip(img01r, img01R, 0);
	flip(img01g, img01G, 0);
	flip(img01b, img01B, 0);

	//imwrite("image//校正前r.jpg", img01R);
	FilterLinerStrech(img01R, img01R, 1);
	//imwrite("image//校正后r.jpg", img01R);

	//imwrite("image//校正前g.jpg", img01G);
	FilterLinerStrech(img01G, img01G, 2);
	//imwrite("image//校正后g.jpg", img01G);

	//imwrite("image//校正前b.jpg", img01B);
	FilterLinerStrech(img01B, img01B, 3);
	//imwrite("image//校正后b.jpg", img01B);
	emit ShowProgress(90);

	Mat imag01 = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC3, 3);
	
	RGBImg.push_back(img01R);
	RGBImg.push_back(img01B);
	RGBImg.push_back(img01G);
	
	//imwrite("image//R.jpg", img01R);
	//imwrite("image//G.jpg", img01G);
	//imwrite("image//B.jpg", img01B);
	merge(RGBImg, imag01);

	//DestImg = imag01;

	//sprintf(buffer1, "image/test/outP_00%d.jpg", t);
	fileName = fileName + "\\Foot.jpg";

	imwrite(fileName.toStdString(), imag01);

	//imwrite("image/test/outP_001.bmp", imag01);
	emit ShowProgress(100);

	RGBImg.clear();

}
void ImageGet::GenColorCorrectCoff(unsigned char* data)
{
	//提取数据
	DataAnalysis();

	//正面白光
	//IplImage* img01rr = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1); //size为图像宽高，depth为位深度，channels为通道数
	//IplImage* img01gg = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1);
	//IplImage* img01bb = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1);
	//IplImage* img01RR = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1);
	//IplImage* img01GG = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1);
	//IplImage* img01BB = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 1);
	//IplImage *image01_dst = cvCreateImage(cvSize(ROW, COL), IPL_DEPTH_8U, 3);

	Mat img01rr = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1, mat0[0]);
	Mat img01gg = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1, mat0[1]);
	Mat img01bb = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1, mat0[2]);

	Mat img01RR = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);
	Mat	img01GG = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);
	Mat	img01BB = Mat(MAT_HEIGHT, MAT_WIDTH, CV_8UC1);

		/*mimg01BBemcpy(img01rr->imageData, mat0[0], ROW * COL);
	memcpy(img01gg->imageData, mat0[1], ROW * COL);
	memcpy(img01bb->imageData, mat0[2], ROW * COL);*/

	//imwrite("image//翻转前的图像.jpg", img01rr);

	flip(img01rr, img01RR, 0);
	flip(img01gg, img01GG, 0);
	flip(img01bb, img01BB, 0);

	//imwrite("image//翻转后的图像.jpg", img01RR);

	CalCoefFilterLinerStrech(img01RR, img01RR, 1);
	//imwrite("image//翻转后校正的图像.jpg", img01RR);

	CalCoefFilterLinerStrech(img01GG, img01GG, 2);
	CalCoefFilterLinerStrech(img01BB, img01BB, 3);

	//cvSaveImage("image//校正后图像.jpg", img01RR);

	/*cvReleaseImage(&img01rr);
	cvReleaseImage(&img01bb);
	cvReleaseImage(&img01gg);
	cvReleaseImage(&image01_dst);
	cvReleaseImage(&img01RR);
	cvReleaseImage(&img01GG);
	cvReleaseImage(&img01BB);*/

}

void ImageGet::CalCoefFilterLinerStrech(Mat &img_origin,Mat &dst, int color)
{
	std::ofstream bofs;//定义ofstream类的对象bofs,ofstream是从内存到硬盘，ifstream是从硬盘到内存
	std::ofstream wofs;
	std::ofstream mofs;
	std::ofstream nofs;

	if (color == 1)//RGB的R
	{
		bofs.open("Coeff//1_b_Coeff.txt");	//调用成员函数open打开1_B_Coeff.txt,假如open函数只有文档名一个参数，则是以读/写普通文档打开,没有这个文档就创建一个
		wofs.open("Coeff//1_w_Coeff.txt");
		mofs.open("Coeff//1_m_coeff.txt");
		nofs.open("Coeff//1_n_coeff.txt");
	}
	else if (color == 2)//G
	{
		bofs.open("Coeff//2_b_Coeff.txt");
		wofs.open("Coeff//2_w_Coeff.txt");
		mofs.open("Coeff//2_m_coeff.txt");
		nofs.open("Coeff//2_n_coeff.txt");
	}
	else if (color == 3)//B
	{
		bofs.open("Coeff//3_b_Coeff.txt");
		wofs.open("Coeff//3_w_Coeff.txt");
		mofs.open("Coeff//3_m_coeff.txt");
		nofs.open("Coeff//3_n_coeff.txt");
	}

	memcpy(MAT, img_origin.data, MAT_HEIGHT * MAT_WIDTH);//从img_origin->imageData所指向的内存地址的起始位置将MAT_HEIGHT*MAT_WIDTH大小的数据拷贝到MAT所指向的内存地址
	
	memset(BCoeff, 0, MAT_WIDTH *sizeof(double));
	memset(WCoeff, 0, MAT_WIDTH *sizeof(double));

	for (int j = StartCol; j < EndCol; j++)
	{

		////B_Coeff
		//for (int i = 3300; i < 3500; i++)//这个是逐条校正，每一条算两个校正参数,取十个像素点求平均值，减少误差   (600 700 1200 1300)
		//{
		//	BCoeff[j] = BCoeff[j] + MAT[i][j];
		//}
		//BCoeff[j] = BCoeff[j] / 200;

		////W_Coeff
		//for (int i = 1000; i < 1200; i++)
		//{
		//	WCoeff[j] = WCoeff[j] + MAT[i][j];
		//}

		//WCoeff[j] = WCoeff[j] / 200;

		//MCoeff[j] = 240 / (WCoeff[j] - BCoeff[j]);  //
		//NCoeff[j] = 0 - MCoeff[j] * BCoeff[j];


		//B_Coeff
		for (int i = 3300; i < 3400; i++)//这个是逐条校正，每一条算两个校正参数,取十个像素点求平均值，减少误差   (600 700 1200 1300)
		{
			BCoeff[j] = BCoeff[j] + MAT[i][j];
		}
		BCoeff[j] = BCoeff[j] / 100;

		//W_Coeff
		for (int i = 1100; i < 1300; i++)
		{
			WCoeff[j] = WCoeff[j] + MAT[i][j];
		}

		WCoeff[j] = WCoeff[j] / 200; 

		MCoeff[j] = 240 / (WCoeff[j] - BCoeff[j]);  //
		NCoeff[j] = 0 - MCoeff[j] * BCoeff[j];
	}

	double temp;
	for (int j = StartCol; j < EndCol; j++)
	{
		bofs << BCoeff[j] << "\n";
		wofs << WCoeff[j] << "\n";
		mofs << MCoeff[j] << "\n";
		nofs << NCoeff[j] << "\n";

		for (int i = 0; i < MAT_HEIGHT; i++)
		{

			 temp = (MAT[i][j]) * MCoeff[j] + NCoeff[j];
			/*if (MAT[i][j] == 0)
			{
				temp = MAT[i][j];
			}
			else
			{
				temp = (MAT[i][j]) * MCoeff[j] + NCoeff[j];
			}*/
			
			if (temp < 0)
			{
				temp = 0;
			}
			if (temp > 255)
			{
				temp = 255;
			}
			MAT[i][j] = temp;
		}
	}

	memcpy(dst.data, MAT, MAT_HEIGHT * MAT_WIDTH);
}


void ImageGet::FilterLinerStrech(Mat &img_origin, Mat &dst, int color)
{
	std::ifstream mifs;
	std::ifstream nifs;

	std::string  coeffDir = "Coeff//";
	if (color == 1)
	{
		mifs.open(coeffDir + "1_m_coeff.txt");
		nifs.open(coeffDir + "1_n_coeff.txt");
	}
	else if (color == 2)
	{
		mifs.open(coeffDir + "2_m_coeff.txt");
		nifs.open(coeffDir + "2_n_coeff.txt");
	}
	else if (color == 3)
	{
		mifs.open(coeffDir + "3_m_coeff.txt");
		nifs.open(coeffDir + "3_n_coeff.txt");
	}

	memset(MAT, 0, MAT_HEIGHT*MAT_WIDTH);

	memcpy(MAT, img_origin.data, MAT_HEIGHT*MAT_WIDTH);
	
	double temp;
	for (int j = StartCol; j < EndCol; j++)
	{
		mifs >> MCoeff[j];
		nifs >> NCoeff[j];
		for (int i = 0; i < MAT_HEIGHT; i++)
		{
			temp = (MAT[i][j]) * MCoeff[j] + NCoeff[j];

			if (temp < 0)
			{
				temp = 0;
			}
			if (temp > 255)
			{
				temp = 255;
			}
			MAT[i][j] = temp;
		}
	}
	memcpy(dst.data, MAT, MAT_HEIGHT*MAT_WIDTH);

	mifs.close();
	nifs.close();
}
void ImageGet::CalColumnCoef(int column, int columnInstead, double b_coeff[7344], double w_coeff[7344])
{

}

void ImageGet::run()
{
	
	if (data != NULL)
	{
		switch (modType)
		{
		case 1:
			this->DataExtractToImg(data, 1, DestImg); break;
		case 2:
			test();
			break;
		case 3:
			this->GenColorCorrectCoff(data);
			break;

		default:
			break;
		}
	}
	else
	{
		return;
	}

	return;
}

void ImageGet::test()
{
	emit ShowProgress(60);
}