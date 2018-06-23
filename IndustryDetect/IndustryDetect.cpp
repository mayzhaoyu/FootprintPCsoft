#include "IndustryDetect.h"

//UCHAR databuf[DATALENGTH]; //databuf存储接收到的总的图像数据
//UCHAR inbuf[BUFLENGTH]; //inbuf存储从缓存区取到的数据 2M


IndustryDetect::IndustryDetect(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//setMinimumSize(1200, 1200 * 0.618);

	const float DEFAULT_DPI = 96.0;

	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	scale = dpiX / DEFAULT_DPI;


	//progressDlg = new QProgressDialog(this);
	progressBar = new QProgressBar(this);
	progressBar->setOrientation(Qt::Horizontal);  // 水平方向
	progressBar->setMinimum(0);  // 最小值
	progressBar->setMaximum(100);  // 最大值
	progressBar->setValue(0);  // 当前进度

	//按钮

	GetImgBtn = new QPushButton(QStringLiteral("采集图像"));
	GetImgBtn->setMinimumWidth(100*scale);
	GetImgBtn->setMaximumWidth(100 * scale);
	GetImgBtn->setMinimumHeight(42 * scale);
	GetImgBtn->setMaximumHeight( 42* scale);

	GetImgBtn->setStyleSheet("QPushButton{background-color: rgb(230, 20, 20);color: rgb(255,255,255);border-radius:3px;}"
		"QPushButton:hover{ background-color: rgb(230, 80, 80);}");

	//CorrectCoffBtn = new QPushButton(QStringLiteral("校正系数生成"));
	//CorrectCoffBtn->setMinimumWidth(100 * scale);
	//CorrectCoffBtn->setMaximumWidth(100 * scale);
	//CorrectCoffBtn->setMinimumHeight(42 * scale);
	//CorrectCoffBtn->setMaximumHeight(42 * scale);

	//CorrectCoffBtn->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border-radius:3px;}"
	//	"QPushButton:hover{ background-color: rgb(240, 240, 240);}");
	//label
	ImageLabel = new mQLabel(this);
	ImageLabel->setMinimumWidth((width() - 200) * scale);
	ImageLabel->setMinimumHeight((height() - 220) * scale);

	//设置边框
	ImageLabel->setFrameShape(QFrame::Box);
	ImageLabel->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(230, 30, 30);");
	ImageLabel->setToolTip(QStringLiteral("双击图片，查看图片"));

	//
	
	//RGBImage = QImage("outP_011.jpg");
	//int a = RGBImage.width() > ImageLabel->width() ? ImageLabel->width() : RGBImage.width();

	//ImageLabel->setPixmap(QPixmap::fromImage(RGBImage).scaled(RGBImage.width() > ImageLabel->width() ? ImageLabel->width() : RGBImage.width()
	//	, RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()));
	//ImageLabel->setAlignment((Qt::AlignCenter));
		//(RGBImage.width() > ImageLabel->width() ?
		//	ImageLabel->width() : RGBImage.width(), RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()))

	//布局
	VLayoutmain = new QVBoxLayout(this);
	HLayoutFunc = new QHBoxLayout(this);

	//HLayoutFunc->addWidget();
	//HLayoutFunc->addWidget(ConnectBtn);

	//HLayoutFunc->addWidget(CorrectCoffBtn);
	HLayoutFunc->addWidget(progressBar);
	HLayoutFunc->addWidget(GetImgBtn);



	VLayoutmain->addLayout(HLayoutFunc);
	VLayoutmain->addWidget(ImageLabel);
	

	//信号连接
	connect(GetImgBtn, SIGNAL(clicked()), this, SLOT(GetImgBtnClicked()));
	//connect(CorrectCoffBtn, SIGNAL(clicked()), this, SLOT(CorrectCoffBtnClicked()));

	imageget = ImageGet::getInstance();

	connect(imageget, SIGNAL(ShowProgress(int)), this, SLOT(setProgressBar(int))/*, Qt::QueuedConnection*/);
	connect(ImageLabel, SIGNAL(Doubleclicked()), this, SLOT(showDetail()));
}

void IndustryDetect::showDetail()
{
	//QString imageName = QFileDialog::getOpenFileName(this,"open file","")

	QString WorkDir = QCoreApplication::applicationDirPath();//

	WorkDir = WorkDir + "\\" + imageget->fileName;

	WorkDir.replace("/", "\\");
	QString cmd = "rundll32.exe C:\\Windows\\System32\\shimgvw.dll,ImageView_Fullscreen " + WorkDir;;
	
	QByteArray   aByteArray = cmd.toLocal8Bit();//先把转化为QByteArray的结果存储起来

	LPCSTR Cmd = aByteArray.data();//再调用data()或constData()
	
	WinExec(Cmd, SW_NORMAL);

	//Mat Imgshow = imread( "image/test/outP_011.jpg"/*imageget->fileName.toStdString()*/);
	//imshow("Foot", Imgshow);
	//waitKey();
}

int IndustryDetect::ReceiveData()
{
	//progressBar->setValue(10);
	//接收数据
	long buflength = BUFLENGTH;

	//FILE* fp = fopen("temp", "wb+");
	int count = 0, decount = 0;

	if (m_pUSBDevice->BulkInEndPt == NULL)
	{
		//textEditNum->append(QStringLiteral("USB设备未连接!"));
		GetImgBtn->setEnabled(true);
		return 0;
	}

	m_pUSBDevice->BulkInEndPt->TimeOut = 0xffffffff;	//等待时间设置为无限长

	//textEditNum->append(QStringLiteral("正在接收图像..."));

	for (int i = 0; i < PACKAGES; i++)
	{
		//cout<<i<<endl;
		if (m_pUSBDevice->BulkInEndPt)
		{

			if (m_pUSBDevice->BulkInEndPt->XferData(inbuf, buflength))
			{
				m_pUSBDevice->BulkInEndPt->TimeOut = 1000;
				count++;
			}
			else
			{
				decount++;
				//continue;
				break;
			}
		}

		buflength = BUFLENGTH;
		memcpy(databuf + i * buflength, inbuf, buflength); //将inbuf数据拷贝到databuf
	}

	//fwrite(databuf, 1, DATALENGTH, fp);
	//fclose(fp);

	//MessageBox("one");
	int a = decount;
	//textEditNum->append(QStringLiteral("接收图像成功"));

	int t = count;
	//QString s = QString::number(t, 10);
	//textEditNum->append(QStringLiteral("接收数据包（M）:") + s);
	return 1;
}


void IndustryDetect::GetImgBtnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	//textEditNum->clear();
	//灰掉按钮
	GetImgBtn->setEnabled(false);

	m_pUSBDevice = new CCyUSBDevice(NULL);//定义class CCyUSBDevice指针
	
	//分配内存
	if (databuf == NULL)
	{
		databuf = new unsigned char[DATALENGTH];
	}

	if (inbuf == NULL)
	{
		inbuf = new unsigned char[BUFLENGTH];
	}
	
	if ((databuf == NULL ) && (inbuf == NULL))
	{
		//textEditNum->append(QStringLiteral("内存分配失败!"));
		GetImgBtn->setEnabled(true);
		return;
	}

	progressBar->setValue(0);

	//发送指令
	UCHAR bufOrder[2] = { 0xaa, 0xaa };

	long Two = 2;
	if (m_pUSBDevice->BulkOutEndPt == NULL)
	{
		GetImgBtn->setEnabled(true);
		emit UpdateTitle(2); //设备连接失败
		return;
	}
	if (m_pUSBDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	{
		//textEditNum->append(QStringLiteral("发送指令失败!"));
		GetImgBtn->setEnabled(true);
		emit UpdateTitle(2); //设备连接失败
		return;
	}
	else
	{
		emit UpdateTitle(1);  //设备连接成功
	}

	progressBar->setValue(5);
	//QString s = textEditNum->toPlainText();

	//if (s != NULL)
	//{
	//	GetNum = s.toInt();
	//}

	//接收数据
	this->ReceiveData();
	progressBar->setValue(40);
	

	//生成图像
	imageget->modType = 1;
	imageget->data = databuf;	
	imageget->start();
	

	//显示图像
	//RGBImage = QImage("image//test//outP_001.jpg");
	//ImageLabel->setPixmap(QPixmap::fromImage(RGBImage).scaled(RGBImage.width() > ImageLabel->width() ? 
	//	ImageLabel->width() : RGBImage.width(), RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()));

	//使能按钮
	GetImgBtn->setEnabled(true);
	
}

void IndustryDetect::CorrectCoffBtnClicked()
{

	//CorrectCoffBtn->setEnabled(false);

	//m_pUSBDevice = new CCyUSBDevice(NULL);//定义class CCyUSBDevice指针

	////分配内存
	//if (databuf == NULL)
	//{
	//	databuf = new unsigned char[DATALENGTH];
	//}

	//if (inbuf == NULL)
	//{
	//	inbuf = new unsigned char[BUFLENGTH];
	//}

	//if ((databuf == NULL) && (inbuf == NULL))
	//{
	//	//textEditNum->append(QStringLiteral("内存分配失败!"));
	//	CorrectCoffBtn->setEnabled(true);
	//	return;
	//}

	////发送指令
	//UCHAR bufOrder[2] = { 0xaa, 0xaa };

	//long Two = 2;
	//if (m_pUSBDevice->BulkOutEndPt == NULL)
	//{
	//	CorrectCoffBtn->setEnabled(true);
	//	emit UpdateTitle(2);  //设备连接失败
	//	return;
	//}
	//if (m_pUSBDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	//{
	//	//textEditNum->append(QStringLiteral("发送指令失败!"));
	//	CorrectCoffBtn->setEnabled(true);
	//	emit UpdateTitle(2);  //设备连接失败
	//	return;
	//}
	//else
	//{
	//	emit UpdateTitle(1);  //设备连接成功
	//}
	////接收数据
	//this->ReceiveData();

	////textEditNum->append(QStringLiteral("生成校正系数..."));
	////计算校正参数
	//imageget->modType = 3;
	//imageget->data = databuf;
	//imageget->start();

	////textEditNum->append(QStringLiteral(""));

	////使能按钮
	//CorrectCoffBtn->setEnabled(true);

}


IndustryDetect::~IndustryDetect()
{
	if (databuf != NULL)
	{
	delete databuf;
	}
	if (inbuf != NULL)
	{
	delete inbuf;
	}
}
void IndustryDetect::setProgressBar(int p)
{
	progressBar->setValue(p);

	emit UpdateTitle(p);

	if (p == 100)
	{
		RGBImage = QImage(imageget->fileName);
		ImageLabel->setPixmap(QPixmap::fromImage(RGBImage).scaled(RGBImage.width() > ImageLabel->width() ? ImageLabel->width() : RGBImage.width()
			, RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()));
		ImageLabel->setAlignment((Qt::AlignCenter));
	}
	//发送消息给title更新状态
}