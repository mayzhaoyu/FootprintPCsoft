/***************************************************************\
* @Copyright(c) 2017 HUST-BIAC All rights reserved	
* @ClassName  CorrectWidget
* @Author  ZhaoYu
* @Date  2018��6��24��
* @Version 1.0
* @Description У��ϵ������ҳ��
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

	//��ť
	QPushButton *CorrectBtn;
	QPushButton *reStoreCorrectCoeff;
	//����
	QVBoxLayout *mainVLayout;
	QHBoxLayout *BtnHLayout;
	//Label
	QLabel *illuLabel;

	bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist); //�����ļ���
	
	public slots:
	void DataBackup();   //���ݱ���
	void CorrectCoffBtnClicked();

private:
	Ui::CorrectWidget ui;
};
