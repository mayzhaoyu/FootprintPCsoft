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
