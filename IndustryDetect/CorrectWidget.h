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
	CCyUSBDevice *CorrectUsbDevice;

	ImageGet *imagegetForCorrect;
	QPushButton *CorrectBtn;
	QPushButton *reStoreCorrectCoeff;

	QVBoxLayout *mainVLayout;
	QHBoxLayout *BtnHLayout;

	QLabel *illuLabel;

	unsigned char *databuf = NULL;
	unsigned char *inbuf = NULL;

	bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist); //¿½±´ÎÄ¼þ¼Ð
	public slots:
	void DataBackup();
	void CorrectCoffBtnClicked();

private:
	Ui::CorrectWidget ui;
};
