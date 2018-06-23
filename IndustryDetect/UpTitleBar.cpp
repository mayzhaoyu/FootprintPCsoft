#include "UpTitleBar.h"

UpTitleBar::UpTitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//������С

	const float DEFAULT_DPI = 96.0;

	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	float scale = dpiX / DEFAULT_DPI;


	resize(scale* parent->width(), scale*120);
	
	setMaximumHeight(500);
	//setMaximumHeight();
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);

	//��䱳��
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setAutoFillBackground(true);
	setPalette(pal);

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

	QLabel *textLabel = new QLabel(logo);
	//��������
	QFont font;// ("Microsoft YaHei", 14, 75);
	font.setFamily("Microsoft YaHei");
	font.setPixelSize( 20);
	font.setBold(true);
	font.setPointSize(12);
	textLabel->setFont(font);
	textLabel->setText(QStringLiteral("�㼣�ɼ����"));
	textLabel->setAlignment(Qt::AlignCenter);


	titleLabel = new QLabel(logo);
	QImage logimg("Resources/logo1.png");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setPixmap(QPixmap::fromImage(logimg).scaled(scale * 70, scale * 70));


	vLayoutLogo = new  QVBoxLayout(logo);
	//hLayoutLogo->addStretch();
	vLayoutLogo->addWidget(titleLabel);
	vLayoutLogo->addWidget(textLabel);
	//hLayoutLogo->addStretch();

	blank = new QWidget(this);
	blank->setMinimumHeight(scale * 120);
	blank->setMaximumHeight(scale * 120);

	blank->setMinimumWidth(scale * 200);
	blank->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	blank->setPalette(pal);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);

	 hLayoutMain = new QHBoxLayout(this);
	 hLayoutMain->addWidget(logo);
	 hLayoutMain->addWidget(blank);

	 hLayoutMain->setMargin(0);
	 hLayoutMain->setSpacing(0);


	 QSizePolicy sizeFixed(QSizePolicy::Expanding, QSizePolicy::Fixed);
	 //button

	 //	CloseButt->setStyleSheet(styleSheet1);
	 //������С������󻯡��رհ�ť  
	 MinimazeBtn = new QPushButton(this);
	 MaximizeBtn = new QPushButton(this);
	 CloseBtn = new QPushButton(this);
	 //������ʾ����
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

	 //��ȡ��С�����رհ�ťͼ��  
	 QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	 QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	 QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

	 //MinimazeButt->setText(QStringLiteral("��С��"));
	 //������С�����رհ�ťͼ��  
	 MinimazeBtn->setIcon(minPix.scaled(20,20));
	 MinimazeBtn->setToolTip(QStringLiteral("��С��"));
	 MaximizeBtn->setIcon(maxPix.scaled(20, 20));
	 MaximizeBtn->setToolTip(QStringLiteral("���"));
	 CloseBtn->setIcon(closePix.scaled(20, 20));
	 CloseBtn->setToolTip(QStringLiteral("�ر�"));
	 //������С�����رհ�ť����ʽ  
	 MinimazeBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		 "QPushButton:hover{background-color:rgb(220,220,220);}");
	 MaximizeBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non;}"
		 "QPushButton:hover{background-color:rgb(220,220,220);}");
	 CloseBtn->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		 "QPushButton:hover{background-color:rgb(220,220,220);}");

	 //	MaximizeButt->setStyleSheet(styleSheet2);

	 //connect(CloseButt, SIGNAL(clicked()), this, SLOT(test()));
	 QObject::connect(CloseBtn, SIGNAL(clicked()), this->parent(), SLOT(close()));
	 QObject::connect(MaximizeBtn, SIGNAL(clicked()), this->parent(), SLOT(showWindowSized()));
	 QObject::connect(MinimazeBtn, SIGNAL(clicked()), this->parent(), SLOT(showMinimized()));

	 QVBoxLayout *blankLayout = new QVBoxLayout(blank);

	 QHBoxLayout *buttLayout = new QHBoxLayout(this);		//new QHBoxLayout(blank)
	
	 hLayoutState = new QHBoxLayout(this);

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
	 stateLabel->setText(QStringLiteral("״̬��Ϣ"));


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

	 //��Ӳ���
	 hLayoutState->addWidget(labelInfo);
	 hLayoutState->addWidget(stateLabel);

	 CCyUSBDevice *device = new CCyUSBDevice(NULL);
	 if (device->BulkInEndPt == NULL)
	 {
		 labelInfo->setText(QStringLiteral("�豸δ���ӣ�"));
	 }
	 else
	 {
		 labelInfo->setText(QStringLiteral("�豸�����ӣ�"));
	 }
	 
	 buttLayout->addStretch(1);

	 buttLayout->addWidget(MinimazeBtn);
	 buttLayout->addWidget(MaximizeBtn);
	 buttLayout->addWidget(CloseBtn);

	 buttLayout->setContentsMargins(60, 0, 10, 0);

	 blankLayout->addLayout(buttLayout);
	 blankLayout->addLayout(hLayoutState);

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
	//����ƶ��¼���Ҫ�ƶ����ڣ������ƶ��������أ�����Ҫ��ȡ����ƶ��У�������������Ļ�����꣬Ȼ��move��������꣬��ô��ȡ���ꣿ  
	//ͨ���¼�event->globalPos()֪��������꣬��������ȥ�������ڴ���λ�ã����Ǵ�����������Ļ������  
	if (isMoving && (event->buttons() && Qt::LeftButton)//����������
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
