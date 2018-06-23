#include "IndustryDetect.h"

//UCHAR databuf[DATALENGTH]; //databuf�洢���յ����ܵ�ͼ������
//UCHAR inbuf[BUFLENGTH]; //inbuf�洢�ӻ�����ȡ�������� 2M


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
	progressBar->setOrientation(Qt::Horizontal);  // ˮƽ����
	progressBar->setMinimum(0);  // ��Сֵ
	progressBar->setMaximum(100);  // ���ֵ
	progressBar->setValue(0);  // ��ǰ����

	//��ť

	GetImgBtn = new QPushButton(QStringLiteral("�ɼ�ͼ��"));
	GetImgBtn->setMinimumWidth(100*scale);
	GetImgBtn->setMaximumWidth(100 * scale);
	GetImgBtn->setMinimumHeight(42 * scale);
	GetImgBtn->setMaximumHeight( 42* scale);

	GetImgBtn->setStyleSheet("QPushButton{background-color: rgb(230, 20, 20);color: rgb(255,255,255);border-radius:3px;}"
		"QPushButton:hover{ background-color: rgb(230, 80, 80);}");

	//CorrectCoffBtn = new QPushButton(QStringLiteral("У��ϵ������"));
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

	//���ñ߿�
	ImageLabel->setFrameShape(QFrame::Box);
	ImageLabel->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(230, 30, 30);");
	ImageLabel->setToolTip(QStringLiteral("˫��ͼƬ���鿴ͼƬ"));

	//
	
	//RGBImage = QImage("outP_011.jpg");
	//int a = RGBImage.width() > ImageLabel->width() ? ImageLabel->width() : RGBImage.width();

	//ImageLabel->setPixmap(QPixmap::fromImage(RGBImage).scaled(RGBImage.width() > ImageLabel->width() ? ImageLabel->width() : RGBImage.width()
	//	, RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()));
	//ImageLabel->setAlignment((Qt::AlignCenter));
		//(RGBImage.width() > ImageLabel->width() ?
		//	ImageLabel->width() : RGBImage.width(), RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()))

	//����
	VLayoutmain = new QVBoxLayout(this);
	HLayoutFunc = new QHBoxLayout(this);

	//HLayoutFunc->addWidget();
	//HLayoutFunc->addWidget(ConnectBtn);

	//HLayoutFunc->addWidget(CorrectCoffBtn);
	HLayoutFunc->addWidget(progressBar);
	HLayoutFunc->addWidget(GetImgBtn);



	VLayoutmain->addLayout(HLayoutFunc);
	VLayoutmain->addWidget(ImageLabel);
	

	//�ź�����
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
	
	QByteArray   aByteArray = cmd.toLocal8Bit();//�Ȱ�ת��ΪQByteArray�Ľ���洢����

	LPCSTR Cmd = aByteArray.data();//�ٵ���data()��constData()
	
	WinExec(Cmd, SW_NORMAL);

	//Mat Imgshow = imread( "image/test/outP_011.jpg"/*imageget->fileName.toStdString()*/);
	//imshow("Foot", Imgshow);
	//waitKey();
}

int IndustryDetect::ReceiveData()
{
	//progressBar->setValue(10);
	//��������
	long buflength = BUFLENGTH;

	//FILE* fp = fopen("temp", "wb+");
	int count = 0, decount = 0;

	if (m_pUSBDevice->BulkInEndPt == NULL)
	{
		//textEditNum->append(QStringLiteral("USB�豸δ����!"));
		GetImgBtn->setEnabled(true);
		return 0;
	}

	m_pUSBDevice->BulkInEndPt->TimeOut = 0xffffffff;	//�ȴ�ʱ������Ϊ���޳�

	//textEditNum->append(QStringLiteral("���ڽ���ͼ��..."));

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
		memcpy(databuf + i * buflength, inbuf, buflength); //��inbuf���ݿ�����databuf
	}

	//fwrite(databuf, 1, DATALENGTH, fp);
	//fclose(fp);

	//MessageBox("one");
	int a = decount;
	//textEditNum->append(QStringLiteral("����ͼ��ɹ�"));

	int t = count;
	//QString s = QString::number(t, 10);
	//textEditNum->append(QStringLiteral("�������ݰ���M��:") + s);
	return 1;
}


void IndustryDetect::GetImgBtnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//textEditNum->clear();
	//�ҵ���ť
	GetImgBtn->setEnabled(false);

	m_pUSBDevice = new CCyUSBDevice(NULL);//����class CCyUSBDeviceָ��
	
	//�����ڴ�
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
		//textEditNum->append(QStringLiteral("�ڴ����ʧ��!"));
		GetImgBtn->setEnabled(true);
		return;
	}

	progressBar->setValue(0);

	//����ָ��
	UCHAR bufOrder[2] = { 0xaa, 0xaa };

	long Two = 2;
	if (m_pUSBDevice->BulkOutEndPt == NULL)
	{
		GetImgBtn->setEnabled(true);
		emit UpdateTitle(2); //�豸����ʧ��
		return;
	}
	if (m_pUSBDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	{
		//textEditNum->append(QStringLiteral("����ָ��ʧ��!"));
		GetImgBtn->setEnabled(true);
		emit UpdateTitle(2); //�豸����ʧ��
		return;
	}
	else
	{
		emit UpdateTitle(1);  //�豸���ӳɹ�
	}

	progressBar->setValue(5);
	//QString s = textEditNum->toPlainText();

	//if (s != NULL)
	//{
	//	GetNum = s.toInt();
	//}

	//��������
	this->ReceiveData();
	progressBar->setValue(40);
	

	//����ͼ��
	imageget->modType = 1;
	imageget->data = databuf;	
	imageget->start();
	

	//��ʾͼ��
	//RGBImage = QImage("image//test//outP_001.jpg");
	//ImageLabel->setPixmap(QPixmap::fromImage(RGBImage).scaled(RGBImage.width() > ImageLabel->width() ? 
	//	ImageLabel->width() : RGBImage.width(), RGBImage.height() > ImageLabel->height() ? ImageLabel->height() : RGBImage.width()));

	//ʹ�ܰ�ť
	GetImgBtn->setEnabled(true);
	
}

void IndustryDetect::CorrectCoffBtnClicked()
{

	//CorrectCoffBtn->setEnabled(false);

	//m_pUSBDevice = new CCyUSBDevice(NULL);//����class CCyUSBDeviceָ��

	////�����ڴ�
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
	//	//textEditNum->append(QStringLiteral("�ڴ����ʧ��!"));
	//	CorrectCoffBtn->setEnabled(true);
	//	return;
	//}

	////����ָ��
	//UCHAR bufOrder[2] = { 0xaa, 0xaa };

	//long Two = 2;
	//if (m_pUSBDevice->BulkOutEndPt == NULL)
	//{
	//	CorrectCoffBtn->setEnabled(true);
	//	emit UpdateTitle(2);  //�豸����ʧ��
	//	return;
	//}
	//if (m_pUSBDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	//{
	//	//textEditNum->append(QStringLiteral("����ָ��ʧ��!"));
	//	CorrectCoffBtn->setEnabled(true);
	//	emit UpdateTitle(2);  //�豸����ʧ��
	//	return;
	//}
	//else
	//{
	//	emit UpdateTitle(1);  //�豸���ӳɹ�
	//}
	////��������
	//this->ReceiveData();

	////textEditNum->append(QStringLiteral("����У��ϵ��..."));
	////����У������
	//imageget->modType = 3;
	//imageget->data = databuf;
	//imageget->start();

	////textEditNum->append(QStringLiteral(""));

	////ʹ�ܰ�ť
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
	//������Ϣ��title����״̬
}