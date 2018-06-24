#include "UpTitleBar.h"

UpTitleBar::UpTitleBar(QWidget *parent)
	: QWidget(parent)
{
	//注意添加logo和blank 布局的顺序 窗体分了两部分logo和blank logo传入label 的构造函数 logo是label父类，具有父类特征，
	//所以在添加布局的时候应该先添加logo和blank
	ui.setupUi(this);
	//调整大小
	const float DEFAULT_DPI = 96.0;

	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	float scale = dpiX / DEFAULT_DPI;

	resize(scale* parent->width(), scale*120);
	setMaximumHeight(500);
	setMinimumHeight(120);
	//setMaximumHeight();
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);

	//填充背景
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setAutoFillBackground(true);
	setPalette(pal);

	//初始化logo
	logo = new QWidget(this);
	logo->setMinimumHeight(scale*120);
	logo->setMaximumHeight(scale * 120);

	logo->setMinimumWidth(scale * 120);
	logo->setMaximumWidth(scale * 120);
	logo->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(239, 240, 241));
	logo->setPalette(pal);
	//sizePolicy.setHorizontalStretch(1);
	logo->setSizePolicy(sizePolicy);

	//初始化blank
	blank = new QWidget(this);
	blank->setMinimumHeight(scale * 120);
	blank->setMaximumHeight(scale * 120);

	blank->setMinimumWidth(scale * 200);
	blank->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	blank->setPalette(pal);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);
	//总体布局
	hLayoutMain = new QHBoxLayout(this);
	hLayoutMain->addWidget(logo);
	hLayoutMain->addWidget(blank);

	hLayoutMain->setMargin(0);
	hLayoutMain->setSpacing(0);


	/*--------------------logo控件-------------------------------*/
	//QLabel
	QLabel *textLabel = new QLabel(logo);
	QFont font;// ("Microsoft YaHei", 14, 75);
	font.setFamily("Microsoft YaHei");
	font.setPixelSize( 20);
	font.setBold(true);
	font.setPointSize(12);
	textLabel->setFont(font);
	textLabel->setText(QStringLiteral("足迹采集软件"));
	textLabel->setAlignment(Qt::AlignCenter);

	titleLabel = new QLabel(logo);
	QImage logimg("Resources/logo1.png");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setPixmap(QPixmap::fromImage(logimg).scaled(scale * 70, scale * 70));

	/*-------------logo布局-------------------*/
	vLayoutLogo = new  QVBoxLayout(logo);
	vLayoutLogo->addWidget(titleLabel);
	vLayoutLogo->addWidget(textLabel);

	/*-------------blank控件-------------------*/
	QSizePolicy sizeFixed(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//button

	//	CloseButt->setStyleSheet(styleSheet1);
	//构建最小化、最大化、关闭按钮  
	MinimazeBtn = new QPushButton(this);
	MaximizeBtn = new QPushButton(this);
	CloseBtn = new QPushButton(this);
	//设置显示策略
	MinimazeBtn->setSizePolicy(sizeFixed);
	MinimazeBtn->setMinimumHeight(scale * 30);
	MinimazeBtn->setMaximumWidth(scale * 45);
	MinimazeBtn->setMinimumWidth(scale * 30);
	MaximizeBtn->setSizePolicy(sizeFixed);
	MaximizeBtn->setMinimumHeight(scale * 30);
	MaximizeBtn->setMaximumWidth(scale * 45);
	MaximizeBtn->setMinimumWidth(scale * 30);
	CloseBtn->setSizePolicy(sizeFixed);
	CloseBtn->setMinimumHeight(scale * 30);
	CloseBtn->setMaximumWidth(scale * 45);
	CloseBtn->setMinimumWidth(scale * 30);

	//获取最小化、关闭按钮图标  
	QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

	//MinimazeButt->setText(QStringLiteral("最小化"));
	//设置最小化、关闭按钮图标  
	MinimazeBtn->setIcon(minPix.scaled(20, 20));
	MinimazeBtn->setToolTip(QStringLiteral("最小化"));
	MaximizeBtn->setIcon(maxPix.scaled(20, 20));
	MaximizeBtn->setToolTip(QStringLiteral("最大化"));
	CloseBtn->setIcon(closePix.scaled(20, 20));
	CloseBtn->setToolTip(QStringLiteral("关闭"));
	//设置最小化、关闭按钮的样式  
	MinimazeBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		"QPushButton:hover{background-color:rgb(220,220,220);}");
	MaximizeBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non;}"
		"QPushButton:hover{background-color:rgb(220,220,220);}");
	CloseBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		"QPushButton:hover{background-color:rgb(220,220,220);}");

	//	MaximizeButt->setStyleSheet(styleSheet2);

	//connect(CloseButt, SIGNAL(clicked()), this, SLOT(test()));
	
	stateLabel = new QLabel(blank);
	stateLabel->setMaximumHeight(scale * 30);
	stateLabel->setMinimumHeight(scale * 30);

	QFont font2;  // ("Microsoft YaHei", 12, 50);
	font2.setFamily("Microsoft YaHei");
	font2.setPixelSize(20);
	font2.setBold(true);
	font2.setPointSize(13);

	stateLabel->setFont(font2);
	QPalette pa1;
	pa1.setColor(QPalette::WindowText, Qt::red);
	stateLabel->setPalette(pa1);
	stateLabel->setText(QStringLiteral("状态信息"));

	labelInfo = new QLabel(blank);
	labelInfo->setMaximumHeight(scale * 30);
	labelInfo->setMinimumHeight(scale * 30);

	QFont font1;  // ("Microsoft YaHei", 12, 50);
	font1.setFamily("Microsoft YaHei");
	font1.setPixelSize(20);
	font1.setBold(true);
	font1.setPointSize(13);

	labelInfo->setFont(font1);
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::red);
	labelInfo->setPalette(pa);

	CCyUSBDevice *device = new CCyUSBDevice(NULL);
	if (device->BulkInEndPt == NULL)
	{
		labelInfo->setText(QStringLiteral("设备未连接！"));
	}
	else
	{
		labelInfo->setText(QStringLiteral("设备已连接！"));
	}

	/*-------------blank布局-------------------*/
	//按钮布局

	QHBoxLayout *buttLayout = new QHBoxLayout(this);		//new QHBoxLayout(blank)
	buttLayout->addStretch(1);

	buttLayout->addWidget(MinimazeBtn);
	buttLayout->addWidget(MaximizeBtn);
	buttLayout->addWidget(CloseBtn);
	buttLayout->setContentsMargins(60, 0, 10, 0);

    //状态栏布局
	hLayoutState = new QHBoxLayout;
	hLayoutState->addWidget(labelInfo);
	hLayoutState->addWidget(stateLabel);

	//状态栏和按钮总体布局
	QVBoxLayout *blankLayout = new QVBoxLayout(blank);
	blankLayout->addLayout(buttLayout);
	blankLayout->addLayout(hLayoutState);

		
	 /***************************************信号连接**********************/

	 QObject::connect(CloseBtn, SIGNAL(clicked()), this->parent(), SLOT(close()));
	 QObject::connect(MaximizeBtn, SIGNAL(clicked()), this->parent(), SLOT(showWindowSized()));
	 QObject::connect(MinimazeBtn, SIGNAL(clicked()), this->parent(), SLOT(showMinimized()));

}

UpTitleBar::~UpTitleBar()
{
}


void UpTitleBar::mousePressEvent(QMouseEvent *event)
{
	isMoving = true;
	movePosition = event->globalPos() - this->window()->pos();
	return QWidget::mousePressEvent(event);
}

void UpTitleBar::mouseReleaseEvent(QMouseEvent *event) {
	isMoving = false;
}

void UpTitleBar::mouseMoveEvent(QMouseEvent *event) {
	//鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？  
	//通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标  
	if (isMoving && (event->buttons() && Qt::LeftButton)//鼠标左键按下
		&& (event->globalPos() - movePosition).manhattanLength() > QApplication::startDragDistance())
	{
		this->window()->move(event->globalPos() - movePosition);
		movePosition = event->globalPos() - this->window()->pos();
	}
	return QWidget::mouseMoveEvent(event);
}

void UpTitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
	if (Qt::WindowState::WindowMaximized == window()->windowState())
		window()->setWindowState(Qt::WindowState::WindowNoState);
	else
		window()->setWindowState(Qt::WindowState::WindowMaximized);
	return QWidget::mouseDoubleClickEvent(event);
}
