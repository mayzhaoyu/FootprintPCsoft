#include "CorrectWidget.h"



CorrectWidget::CorrectWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(sizePolicy);

	//����
	const float DEFAULT_DPI = 96.0;
	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	float scale = dpiX / DEFAULT_DPI;

	imagegetForCorrect = ImageGet::getInstance();

	//�ؼ�
	//��ť��ʼ UI���
	CorrectBtn = new QPushButton(QStringLiteral("У��ϵ������"));
	CorrectBtn->setMinimumWidth(110 * scale);
	CorrectBtn->setMaximumWidth(110 * scale);
	CorrectBtn->setMinimumHeight(50 * scale);
	CorrectBtn->setMaximumHeight(50 * scale);

	CorrectBtn->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border-radius:3px;}"
		"QPushButton:hover{ background-color: rgb(240, 240, 240);}");

	reStoreCorrectCoeff = new QPushButton(QStringLiteral("��ԭУ������"));
	reStoreCorrectCoeff->setMinimumWidth(110 * scale);
	reStoreCorrectCoeff->setMaximumWidth(110 * scale);
	reStoreCorrectCoeff->setMinimumHeight(50 * scale);
	reStoreCorrectCoeff->setMaximumHeight(50 * scale);

	reStoreCorrectCoeff->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border-radius:3px;}"
		"QPushButton:hover{ background-color: rgb(240, 240, 240);}");

	illuLabel = new QLabel;

	//illuLabel->setMaximumHeight(scale *);

	illuLabel->setMinimumHeight(scale * 300);
	illuLabel->setMinimumWidth(scale * 300);
	//illuLabel->alignment(QT::);

	//QFont font2;  // ("Microsoft YaHei", 12, 50);
	//font2.setFamily("Microsoft YaHei");
	//font2.setPixelSize(17);
	//font2.setBold(true);
	//font2.setPointSize(13);

	//illuLabel->setFont(font2);
	illuLabel->setFrameShape(QFrame::Box);
	illuLabel->setStyleSheet("color:rgb(100,100,100);border-width: 1px;border-style: solid;border-color: rgb(230, 30, 30);");
	//illuLabel->setWordWrap(true);  860 570

	QImage DemoImg("Resources/Demo.png");
	illuLabel->setSizePolicy(sizePolicy);
	illuLabel->setPixmap(QPixmap::fromImage(DemoImg).scaled(scale * 860, scale * 570));

	illuLabel->setAlignment(Qt::AlignCenter);
	//����
	//��ť����
	BtnHLayout = new QHBoxLayout;

	BtnHLayout->addWidget(CorrectBtn);
	BtnHLayout->addWidget(reStoreCorrectCoeff);
	//���岼��
	mainVLayout = new QVBoxLayout(this);
	//mainVLayout->addStretch();
	mainVLayout->addWidget(illuLabel);
	mainVLayout->addLayout(BtnHLayout);

	//�ź�����
	connect(CorrectBtn, SIGNAL(clicked()), this, SLOT(CorrectCoffBtnClicked()));
	connect(reStoreCorrectCoeff, SIGNAL(clicked()), this, SLOT(DataBackup()));

}

CorrectWidget::~CorrectWidget()
{
	if (databuf != NULL)
	{
		delete databuf;
		databuf = nullptr;
	}
	if (inbuf != NULL)
	{
		delete inbuf;
		inbuf = nullptr;
	}
}


bool CorrectWidget::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	if (!targetDir.exists()){    /**< ���Ŀ��Ŀ¼�����ڣ�����д��� */
		if (!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList){
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()){    /**< ��ΪĿ¼ʱ���ݹ�Ľ���copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else{            /**< �������ǲ���ʱ�������ļ�����ɾ������ */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())){
				targetDir.remove(fileInfo.fileName());
			}

			/// �����ļ�copy  
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))){
				return false;
			}
		}
	}
	return true;

}//�����ļ���
void CorrectWidget::DataBackup()
{
	int result = QMessageBox::question(this, QStringLiteral("Warning"),
		QStringLiteral("�Ƿ�ԭУ���������ò��������棡"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
	if (result == QMessageBox::Cancel)
	{
		return;
	}
	
	QString sourcedir = "CoeffBackUp/";
	QString destdir = "Coeff/";

	bool coverFile = true;
	bool flag = copyDirectoryFiles(sourcedir, destdir, coverFile);

	if (flag == true)
	{
		MessageBox(NULL, TEXT("�����ɹ�"), TEXT("Info"), MB_OK);
	}
	else
	{
		MessageBox(NULL,TEXT("����ʧ��"),TEXT("Info"),MB_OK);
	}
	
}

void CorrectWidget::CorrectCoffBtnClicked()
{

	int result = QMessageBox::question(this, QStringLiteral("Warning"),
		QStringLiteral("����У��ֽ����λ�ã��ò�����������У��ϵ�����Ƿ������"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
	if (result == QMessageBox::Cancel)
	{
		return;
	}


	CorrectBtn->setEnabled(false);

	CorrectUsbDevice = new CCyUSBDevice(NULL);//����class CCyUSBDeviceָ��

	//�����ڴ�
	if (databuf == NULL)
	{
		databuf = new unsigned char[DATALENGTH];
	}

	if (inbuf == NULL)
	{
		inbuf = new unsigned char[BUFLENGTH];
	}

	if ((databuf == NULL) && (inbuf == NULL))
	{
		//textEditNum->append(QStringLiteral("�ڴ����ʧ��!"));
		CorrectBtn->setEnabled(true);
		return;
	}

	//����ָ��
	UCHAR bufOrder[2] = { 0xaa, 0xaa };

	long Two = 2;
	if (CorrectUsbDevice->BulkOutEndPt == NULL)
	{
		CorrectBtn->setEnabled(true);
		//emit UpdateTitle(2);  //�豸����ʧ��
		MessageBox(NULL, TEXT("�豸����ʧ��"), TEXT("��ʾ"), MB_OK);
		return;
	}
	if (CorrectUsbDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	{
		//textEditNum->append(QStringLiteral("����ָ��ʧ��!"));
		CorrectBtn->setEnabled(true);
		//emit UpdateTitle(2);  //�豸����ʧ��
		MessageBox(NULL,TEXT("�豸����ʧ��"),TEXT("��ʾ"),MB_OK);
		return;
	}
	else
	{
		//emit UpdateTitle(1);  //�豸���ӳɹ�
	}


	//��������
	long buflength = BUFLENGTH;

	//FILE* fp = fopen("temp", "wb+");
	int count = 0, decount = 0;

	if (CorrectUsbDevice->BulkInEndPt == NULL)
	{
		//textEditNum->append(QStringLiteral("USB�豸δ����!"));
		CorrectBtn->setEnabled(true);
		return;
	}

	CorrectUsbDevice->BulkInEndPt->TimeOut = 0xffffffff;	//�ȴ�ʱ������Ϊ���޳�

	//textEditNum->append(QStringLiteral("���ڽ���ͼ��..."));

	for (int i = 0; i < PACKAGES; i++)
	{
		//cout<<i<<endl;
		if (CorrectUsbDevice->BulkInEndPt)
		{

			if (CorrectUsbDevice->BulkInEndPt->XferData(inbuf, buflength))
			{
				CorrectUsbDevice->BulkInEndPt->TimeOut = 1000;
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

	//textEditNum->append(QStringLiteral("����У��ϵ��..."));
	//����У������
	imagegetForCorrect->modType = 3;
	imagegetForCorrect->data = databuf;
	imagegetForCorrect->start();

	//textEditNum->append(QStringLiteral(""));

	//ʹ�ܰ�ť
	CorrectBtn->setEnabled(true);
	Sleep(4000);  //ͣ����

	MessageBox(NULL, TEXT("У�����"), TEXT("Info"), MB_OK);
}
