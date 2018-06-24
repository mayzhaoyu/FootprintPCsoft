#pragma once

#include <QtWidgets/QWidget>
#include "ui_IndustryDetect.h"
#include "ImageGet.h"
#include <QPushButton>
#include <QLabel>
#include "mQLabel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTextEdit>
#include <QProgressbar>
#include "qt_windows.h"
#include "cyapi.h"

#include <QFileDialog>
class IndustryDetect : public QWidget
{
	Q_OBJECT

public:
	IndustryDetect(QWidget *parent = Q_NULLPTR);
	~IndustryDetect();

	int ReceiveData();

	//UI
	QPushButton *GetImgBtn;
	QProgressBar *progressBar; //进度条
	
	mQLabel *ImageLabel;   //显示图片

	QVBoxLayout *VLayoutmain;
	QHBoxLayout *HLayoutFunc;

	//功能
	ImageGet *imageget;
	QImage RGBImage;
	Mat Image;
	
	unsigned char *databuf = NULL;
    unsigned char *inbuf = NULL;

   CCyUSBDevice *m_pUSBDevice;
   float scale; //自适用尺度
	public slots:
	void GetImgBtnClicked();
	void CorrectCoffBtnClicked();
	void setProgressBar(int);
	void showDetail();

signals:
	void UpdateTitle(int);

private:
	Ui::IndustryDetectClass ui;
};


