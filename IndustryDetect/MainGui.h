#pragma once

#include <QWidget>
#include "ui_MainGui.h"

#include "UpTitleBar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>

#include "IndustryDetect.h"
#include "CorrectWidget.h"

class MainGui : public QWidget
{
	Q_OBJECT

	QListWidgetItem *currentItem;
public:
	MainGui(QWidget *parent = Q_NULLPTR);
	~MainGui();
	//UI
	//Layout
	QVBoxLayout *mainLayout;
	QStackedLayout *stackLayout;
	QVBoxLayout * guideLayout;
	QWidget * window;
	QWidget * function;
	QWidget * blank;
	QHBoxLayout *windowLayout;

	//guide
	QListWidget* guideList;
	QListWidgetItem * captureListItem;
	QListWidgetItem * correctListItem;
	QListWidgetItem * AboutListItem;

	//function
	UpTitleBar *upTitlebar;
	IndustryDetect *industryDetect;
	CorrectWidget *correctWidget;

	public slots:
	void guidItemChanged(QListWidgetItem* item);
	void showWindowSized();
	void Updatetitle(int);
private:
	Ui::MainGui ui;
	//QVBoxLayout *mainLayout;

};
