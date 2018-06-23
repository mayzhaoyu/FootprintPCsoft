#include "MainGui.h"

//background-color: rgb(240, 240, 240);
//background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #C7F8FA);
char guideStyleSheet[] = "QListWidget { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(240,240,240), stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #C7F8FA);"
"color: rgb(102, 102, 102);border-style: none;  "
" font: 14pt \"Microsoft YaHei\" ; "
" }"
"QListWidget::Item {min-height: 120px;border-left-color: rgb(255, 255, 255)}"
"QListWidget::item:selected{color:rgb(217, 20, 20);border-style: none;  }"
"QListWidget::item:hover{background: rgb(240, 220, 220);color:rgb(217, 20, 20);  }";


MainGui::MainGui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(":/UploadClient/UploadClient.ico"));

	const float DEFAULT_DPI = 96.0;

	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	float scale = dpiX / DEFAULT_DPI;


	setMinimumSize(1000 * scale, (770)*scale);
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());

	//背景填充
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setAutoFillBackground(true);
	setPalette(pal);

	upTitlebar = new UpTitleBar(this);

	//主窗体
	window = new QWidget(this);
	window->resize(width(), height() - upTitlebar->height());
	//QPalette pal1(palette());
	//pal.setColor(QPalette::Window, QColor(255, 255, 255));
	//window->setAutoFillBackground(true);
	//window->setPalette(pal);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(sizePolicy);

	//正文区
	blank = new QWidget(window);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);
	blank->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	blank->setPalette(pal);

	//功能栏
	function = new QWidget(window);
	function->setMaximumWidth(120*scale);
	function->setMinimumWidth(120*scale);
	function->setSizePolicy(sizePolicy);
	function->setAutoFillBackground(true);

	pal.setColor(QPalette::Window, QColor(239, 0, 0));
	function->setPalette(pal);
	
	guideLayout = new QVBoxLayout(function);
	guideList = new QListWidget;
	captureListItem = new QListWidgetItem(QStringLiteral("采集图像"), guideList);
	captureListItem->setTextAlignment(Qt::AlignCenter);
	
	correctListItem = new QListWidgetItem(QStringLiteral("图像校正"), guideList);
	correctListItem->setTextAlignment(Qt::AlignCenter);

	AboutListItem = new QListWidgetItem(QStringLiteral("关于"), guideList);
	AboutListItem->setTextAlignment(Qt::AlignCenter);

	guideList->insertItem(1, captureListItem);
	guideList->insertItem(2, correctListItem);
	guideList->insertItem(2, AboutListItem);

	guideList->setItemSelected(captureListItem, true);
	guideList->setStyleSheet(guideStyleSheet);
	guideList->setFocusPolicy(Qt::NoFocus);
	//自使用缩放
	QFont font1;
	font1.setFamily("Microsoft YaHei");
	font1.setPixelSize(18 * scale);
	captureListItem->setFont(font1);
	
	correctListItem->setFont(font1);


	currentItem = captureListItem;	//同步默认选项

	connect(guideList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(guidItemChanged(QListWidgetItem*)));
	guideLayout->addWidget(guideList);
	guideLayout->setMargin(0);
	//布局
	mainLayout = new QVBoxLayout(this);
	windowLayout = new QHBoxLayout(window); //布局主窗口：导航栏与正文窗
	stackLayout = new QStackedLayout(blank);

	//industryDetect = new IndustryDetect(this);

	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(upTitlebar);
	mainLayout->addWidget(window);

	windowLayout->addWidget(function);
	windowLayout->addWidget(blank);
	windowLayout->setMargin(0);
	windowLayout->setSpacing(0);

	industryDetect = new IndustryDetect(this);
	correctWidget = new CorrectWidget(this);

	stackLayout->addWidget(industryDetect);
	stackLayout->addWidget(correctWidget);

	connect(industryDetect, SIGNAL(UpdateTitle(int)), this, SLOT(Updatetitle(int)));
}

void MainGui::Updatetitle(int p)
{
	if (p == 1)
	{
		upTitlebar->labelInfo->setText(QStringLiteral("设备连接成功"));
	}
	if (p == 2)
	{
		upTitlebar->labelInfo->setText(QStringLiteral("设备断开连接"));
	}

	if (p == 5)
	{
		upTitlebar->stateLabel->setText(QStringLiteral("发送指令"));
	}
	if (p == 40)
	{
		upTitlebar->stateLabel->setText(QStringLiteral("正在接收数据"));
	}
	if (p == 50)
	{
		upTitlebar->stateLabel->setText(QStringLiteral("正在解析数据"));
	}
	if (p == 90)
	{
		upTitlebar->stateLabel->setText(QStringLiteral("图像校正完成"));
	}
	if (p == 100)
	{
		upTitlebar->stateLabel->setText(QStringLiteral("显示图像"));
	}

}


void MainGui::guidItemChanged(QListWidgetItem* item) 
{
	if (item != currentItem) 
	{//自检
		currentItem = item;
		//debugWidget-> print(QStringLiteral("\"") + item->text() + QStringLiteral("\"选项\n"));
		if (captureListItem == item) 
		{
			stackLayout->setCurrentWidget(industryDetect);
		}
		if (correctListItem == item)
		{
			stackLayout->setCurrentWidget(correctWidget);
		}
	}
}


void MainGui::showWindowSized() {
	if (Qt::WindowState::WindowMaximized == this->windowState())
		this->setWindowState(Qt::WindowState::WindowNoState);
	else
		this->setWindowState(Qt::WindowState::WindowMaximized);
}

MainGui::~MainGui()
{
}
