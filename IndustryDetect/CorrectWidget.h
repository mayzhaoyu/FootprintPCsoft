/***************************************************************\
* @Copyright(c) 2017 HUST-BIAC All rights reserved	
* @ClassName  CorrectWidget
* @Author  ZhaoYu
* @Date  2018年6月24日
* @Version 1.0
* @Description 校正系数生成页面
*
******************************************************************/
#pragma once

#include <QWidget>
#include "ui_CorrectWidget.h"
#include "ImageGet.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QTextL>
#include "qt_windows.h"
#include "cyapi.h"
#include <QDir>
#include <QDialog>
#include <QMessageBox>

class CorrectWidget : public QWidget
{
	Q_OBJECT

public:
	CorrectWidget(QWidget *parent = Q_NULLPTR);
	~CorrectWidget();
	//func
	CCyUSBDevice *CorrectUsbDevice;
	ImageGet *imagegetForCorrect;
	unsigned char *databuf = NULL;
	unsigned char *inbuf = NULL;

	//按钮
	QPushButton *CorrectBtn;
	QPushButton *reStoreCorrectCoeff;
	//布局
	QVBoxLayout *mainVLayout;
	QHBoxLayout *BtnHLayout;
	//Label
	QLabel *illuLabel;

	bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist); //拷贝文件夹
	
	public slots:
	void DataBackup();   //数据备份
	void CorrectCoffBtnClicked();

private:
	Ui::CorrectWidget ui;
};
