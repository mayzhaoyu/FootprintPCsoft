/***************************************************************\
* @Copyright(c) 2017 HUST-BIAC All rights reserved	
* @ClassName  mQLabel
* @Author  ZhaoYu
* @Date  2018��6��24��
* @Version 1.0
* @Description �̳�QLabel ��д˫������¼�
*
******************************************************************/
#pragma once

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>


class mQLabel : public QLabel
{
	Q_OBJECT

public:
	mQLabel(QWidget *parent = 0);
	~mQLabel();

	void mouseDoubleClickEvent(QMouseEvent *event);
signals:
	void Doubleclicked();
};
