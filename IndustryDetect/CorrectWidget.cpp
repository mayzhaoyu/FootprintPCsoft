#include "CorrectWidget.h"



CorrectWidget::CorrectWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(sizePolicy);

	//缩放
	const float DEFAULT_DPI = 96.0;
	HDC screen = GetDC(NULL);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	ReleaseDC(0, screen);

	float scale = dpiX / DEFAULT_DPI;

	imagegetForCorrect = ImageGet::getInstance();

	//控件
	//按钮初始 UI设计
	CorrectBtn = new QPushButton(QStringLiteral("校正系数生成"));
	CorrectBtn->setMinimumWidth(110 * scale);
	CorrectBtn->setMaximumWidth(110 * scale);
	CorrectBtn->setMinimumHeight(50 * scale);
	CorrectBtn->setMaximumHeight(50 * scale);

	CorrectBtn->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border-radius:3px;}"
		"QPushButton:hover{ background-color: rgb(240, 240, 240);}");

	reStoreCorrectCoeff = new QPushButton(QStringLiteral("还原校正参数"));
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
	//布局
	//按钮布局
	BtnHLayout = new QHBoxLayout;

	BtnHLayout->addWidget(CorrectBtn);
	BtnHLayout->addWidget(reStoreCorrectCoeff);
	//整体布局
	mainVLayout = new QVBoxLayout(this);
	//mainVLayout->addStretch();
	mainVLayout->addWidget(illuLabel);
	mainVLayout->addLayout(BtnHLayout);

	//信号连接
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
	if (!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
		if (!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList){
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())){
				targetDir.remove(fileInfo.fileName());
			}

			/// 进行文件copy  
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))){
				return false;
			}
		}
	}
	return true;

}//拷贝文件夹
void CorrectWidget::DataBackup()
{
	int result = QMessageBox::question(this, QStringLiteral("Warning"),
		QStringLiteral("是否还原校正参数，该操作不可逆！"),
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
		MessageBox(NULL, TEXT("拷贝成功"), TEXT("Info"), MB_OK);
	}
	else
	{
		MessageBox(NULL,TEXT("拷贝失败"),TEXT("Info"),MB_OK);
	}
	
}

void CorrectWidget::CorrectCoffBtnClicked()
{

	int result = QMessageBox::question(this, QStringLiteral("Warning"),
		QStringLiteral("请检查校正纸放置位置，该操作重新生成校正系数，是否继续？"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
	if (result == QMessageBox::Cancel)
	{
		return;
	}


	CorrectBtn->setEnabled(false);

	CorrectUsbDevice = new CCyUSBDevice(NULL);//定义class CCyUSBDevice指针

	//分配内存
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
		//textEditNum->append(QStringLiteral("内存分配失败!"));
		CorrectBtn->setEnabled(true);
		return;
	}

	//发送指令
	UCHAR bufOrder[2] = { 0xaa, 0xaa };

	long Two = 2;
	if (CorrectUsbDevice->BulkOutEndPt == NULL)
	{
		CorrectBtn->setEnabled(true);
		//emit UpdateTitle(2);  //设备连接失败
		MessageBox(NULL, TEXT("设备连接失败"), TEXT("提示"), MB_OK);
		return;
	}
	if (CorrectUsbDevice->BulkOutEndPt->XferData(bufOrder, Two) == false)
	{
		//textEditNum->append(QStringLiteral("发送指令失败!"));
		CorrectBtn->setEnabled(true);
		//emit UpdateTitle(2);  //设备连接失败
		MessageBox(NULL,TEXT("设备连接失败"),TEXT("提示"),MB_OK);
		return;
	}
	else
	{
		//emit UpdateTitle(1);  //设备连接成功
	}


	//接收数据
	long buflength = BUFLENGTH;

	//FILE* fp = fopen("temp", "wb+");
	int count = 0, decount = 0;

	if (CorrectUsbDevice->BulkInEndPt == NULL)
	{
		//textEditNum->append(QStringLiteral("USB设备未连接!"));
		CorrectBtn->setEnabled(true);
		return;
	}

	CorrectUsbDevice->BulkInEndPt->TimeOut = 0xffffffff;	//等待时间设置为无限长

	//textEditNum->append(QStringLiteral("正在接收图像..."));

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

	//textEditNum->append(QStringLiteral("生成校正系数..."));
	//计算校正参数
	imagegetForCorrect->modType = 3;
	imagegetForCorrect->data = databuf;
	imagegetForCorrect->start();

	//textEditNum->append(QStringLiteral(""));

	//使能按钮
	CorrectBtn->setEnabled(true);
	Sleep(4000);  //停四秒

	MessageBox(NULL, TEXT("校正完成"), TEXT("Info"), MB_OK);
}
