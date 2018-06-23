#pragma once

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QImage>
#include <QLabel>

class LeftTitleBar : public QWidget
{
	Q_OBJECT

public:
	LeftTitleBar(QWidget *parent = 0);
	~LeftTitleBar();
	
	QVBoxLayout *vLayoutLeftTitle;
	QLabel *titleLabel;
	QListWidget *guideList;

};
