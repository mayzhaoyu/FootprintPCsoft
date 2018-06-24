#pragma once

#include <QWidget>
#include "ui_UpTitleBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QtGui/QMouseEvent>
#include<qt_windows.h>
#include <CyAPI.h>

class UpTitleBar : public QWidget
{
	Q_OBJECT

public:
	UpTitleBar(QWidget *parent = Q_NULLPTR);
	~UpTitleBar();
	//UI
	QLabel *titleLabel;
	QWidget *logo;
	QWidget *blank;
	QPushButton *CloseBtn;
	QPushButton *MaximizeBtn;
	QPushButton *MinimazeBtn;
	QLabel *labelInfo;
	QLabel *stateLabel;  //��ʾ������Ϣ

	QHBoxLayout *hLayoutMain;

	QVBoxLayout *vLayoutLogo;

	QHBoxLayout *hLayoutState;



protected:
	// ��д��������¼�
	virtual void mousePressEvent(QMouseEvent *event);
	//��д�ƶ�����¼�
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
	Ui::UpTitleBar ui;
	bool isMoving;
	QPoint movePosition;
};
